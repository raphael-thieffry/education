package escampe;

import games.escampe.BfsReachability;
import games.escampe.EscampeBoard;
import games.escampe.EscampeRole;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Placement optimal par énumération + scoring BFS.
 *
 * Espace : C(12,6) × 6 = 5 544 configurations (2 rangées × 6 cols).
 * Scoring analytique (pas de copie de board) :
 *   - minBFS(mes paladins → licorne adverse)        ×20
 *   - minBFS(paladins adverses → ma licorne)        ×10
 *   - paladins à ≤2 BFS de la licorne adverse       ×25
 *   - paladins adverses à ≤2 BFS de ma licorne      ×−30
 *   - cases de fuite de ma licorne (liseré-aware)   ×8
 *   - centralité de ma licorne (évite les bords)    ×3
 *
 * Quand l'adversaire n'a pas encore placé (NOIR joue en premier),
 * les critères dépendant de la position adverse sont ignorés — on
 * optimise alors uniquement la mobilité et la centralité.
 */
public class PlacementSearch {

    private static final String DEFAULT_BAS  = "C1/A1/B2/D2/E1/F1";
    private static final String DEFAULT_HAUT = "C6/A6/B5/D5/E6/F5";

    /** Top-N window: pick randomly among configs within this score margin of best. */
    private static final int RANDOM_WINDOW = 30;

    public static String bestPlacement(EscampeBoard board, EscampeRole myRole) {
        char[][] g = board.boardGrid();
        char oppLicChar = (myRole == EscampeRole.BLANC) ? 'N' : 'B';
        char oppPalChar = (myRole == EscampeRole.BLANC) ? 'n' : 'b';

        int[] oppLicPos = null;
        List<int[]> oppPals = new ArrayList<>(5);
        for (int r = 0; r < 6; r++)
            for (int c = 0; c < 6; c++) {
                if (g[r][c] == oppLicChar) oppLicPos = new int[]{r, c};
                if (g[r][c] == oppPalChar) oppPals.add(new int[]{r, c});
            }

        int[] myRows = chooseMyRows(g, myRole);
        List<int[]> cells = new ArrayList<>(12);
        for (int row : myRows)
            for (int col = 0; col < 6; col++)
                cells.add(new int[]{row, col});

        List<int[]> combos = combinations(12, 6);
        int bestScore = Integer.MIN_VALUE;

        // Pass 1: find best score
        int[][] scoredLicIdx = new int[combos.size() * 6][2]; // [comboIdx, licIdx]
        int[] allScores = new int[combos.size() * 6];
        int idx = 0;
        for (int ci = 0; ci < combos.size(); ci++) {
            int[] combo = combos.get(ci);
            for (int licIdx = 0; licIdx < 6; licIdx++) {
                int s = score(combo, licIdx, cells, oppLicPos, oppPals, g);
                scoredLicIdx[idx][0] = ci;
                scoredLicIdx[idx][1] = licIdx;
                allScores[idx] = s;
                if (s > bestScore) bestScore = s;
                idx++;
            }
        }

        // Pass 2: collect all configs within RANDOM_WINDOW of best
        List<String> topN = new ArrayList<>();
        int threshold = bestScore - RANDOM_WINDOW;
        for (int i = 0; i < idx; i++) {
            if (allScores[i] >= threshold) {
                topN.add(toPlacementString(combos.get(scoredLicIdx[i][0]), scoredLicIdx[i][1], cells));
            }
        }

        if (topN.isEmpty()) return defaultPlacement(myRole);
        return topN.get(new Random(System.nanoTime()).nextInt(topN.size()));
    }

    // ── Scoring ───────────────────────────────────────────────────────────────

    private static int score(int[] combo, int licIdx, List<int[]> cells,
                              int[] oppLicPos, List<int[]> oppPals, char[][] g) {
        int[] licPos = cells.get(combo[licIdx]);
        int score = 0;

        // Critères offensifs/défensifs (uniquement si adversaire déjà placé)
        if (oppLicPos != null) {
            int minToOppLic = 15;
            int danger = 0;
            for (int i = 0; i < 6; i++) {
                if (i == licIdx) continue; // paladins seulement
                int[] pos = cells.get(combo[i]);
                int d = BfsReachability.minMoves(pos[0], pos[1], oppLicPos[0], oppLicPos[1]);
                if (d < minToOppLic) minToOppLic = d;
                if (d <= 2) danger++;
            }
            score += (10 - minToOppLic) * 20;
            score += danger * 25;
        }

        if (!oppPals.isEmpty()) {
            int minToMyLic = 15;
            int threat = 0;
            for (int[] op : oppPals) {
                int d = BfsReachability.minMoves(op[0], op[1], licPos[0], licPos[1]);
                if (d < minToMyLic) minToMyLic = d;
                if (d <= 2) threat++;
            }
            score += minToMyLic * 10;
            score -= threat * 30;
        }

        // Mobilité de ma licorne (cases libres atteignables en 1 coup, ignorant mes propres pièces)
        int licL = EscampeBoard.getLisereAt(licPos[0], licPos[1]);
        int mobility = 0;
        for (int[] d : new int[][]{{1,0},{-1,0},{0,1},{0,-1}}) {
            int nr = licPos[0] + d[0] * licL;
            int nc = licPos[1] + d[1] * licL;
            if (nr >= 0 && nr < 6 && nc >= 0 && nc < 6 && g[nr][nc] == '-') mobility++;
        }
        score += mobility * 8;

        // Pénalité : si adversaire pas encore placé, éviter les cases atteignables
        // depuis sa zone en 1 saut (modèle correct : Manhattan distance = liseré).
        // Couvre aussi le cas "paladin adverse placé en X → capture licorne au 1er coup".
        if (oppPals.isEmpty() && oppLicPos == null) {
            int[] oppRows = (licPos[0] <= 1) ? new int[]{4, 5} : new int[]{0, 1};
            int directThreats = 0;
            for (int r : oppRows) {
                for (int c = 0; c < 6; c++) {
                    int L = EscampeBoard.getLisereAt(r, c);
                    // Un paladin en (r,c) atteint toutes les cases à distance Manhattan L
                    if (Math.abs(licPos[0] - r) + Math.abs(licPos[1] - c) == L) {
                        directThreats++;
                    }
                }
            }
            score -= directThreats * 80;
        }

        // Centralité de la licorne (préférer cols 1-4, rows intérieures)
        int centerScore = (3 - Math.abs(licPos[1] - 2)) + (oppPals.isEmpty() ? 0 : 0);
        score += centerScore * 3;

        // Couverture liseré : compter les types {1,2,3} couverts par les 6 pièces.
        // Chaque type manquant = risque de passe forcé. Bonus fort pour avoir ≥2 pièces
        // sur liseré=3 (le plus rare en ligne 1, et le plus exploité par l'adversaire).
        boolean[] lisTypes = new boolean[4];
        int count3 = 0;
        lisTypes[EscampeBoard.getLisereAt(licPos[0], licPos[1])] = true;
        if (EscampeBoard.getLisereAt(licPos[0], licPos[1]) == 3) count3++;
        for (int i = 0; i < 6; i++) {
            if (i == licIdx) continue;
            int L = EscampeBoard.getLisereAt(cells.get(combo[i])[0], cells.get(combo[i])[1]);
            lisTypes[L] = true;
            if (L == 3) count3++;
        }
        int coverage = (lisTypes[1]?1:0) + (lisTypes[2]?1:0) + (lisTypes[3]?1:0);
        score += coverage * 15;  // couvrir tous les types
        score += count3   * 20;  // bonus par pièce liseré=3 supplémentaire (robustesse)

        return score;
    }

    // ── Helpers ───────────────────────────────────────────────────────────────

    private static String toPlacementString(int[] combo, int licIdx, List<int[]> cells) {
        // Premier token = licorne (convention EscampeBoard.playPlacement cells[0])
        StringBuilder sb = new StringBuilder();
        int[] lic = cells.get(combo[licIdx]);
        sb.append((char)('A' + lic[1])).append(lic[0] + 1);
        for (int i = 0; i < 6; i++) {
            if (i == licIdx) continue;
            int[] pos = cells.get(combo[i]);
            sb.append('/').append((char)('A' + pos[1])).append(pos[0] + 1);
        }
        return sb.toString();
    }

    /** Rangées dans lesquelles je dois placer, en miroir de l'adversaire. */
    private static int[] chooseMyRows(char[][] g, EscampeRole myRole) {
        char advLic = (myRole == EscampeRole.BLANC) ? 'N' : 'B';
        char advPal = (myRole == EscampeRole.BLANC) ? 'n' : 'b';
        boolean advEnBas = false, advEnHaut = false;
        for (int j = 0; j < 6; j++) {
            for (int i : new int[]{0, 1})
                if (g[i][j] == advLic || g[i][j] == advPal) advEnBas = true;
            for (int i : new int[]{4, 5})
                if (g[i][j] == advLic || g[i][j] == advPal) advEnHaut = true;
        }
        if (advEnBas)  return new int[]{4, 5}; // adversaire BAS → je vais HAUT
        if (advEnHaut) return new int[]{0, 1}; // adversaire HAUT → je vais BAS
        return new int[]{0, 1};                // adversaire pas encore placé → BAS par défaut
    }

    private static String defaultPlacement(EscampeRole role) {
        return (role == EscampeRole.BLANC) ? DEFAULT_BAS : DEFAULT_HAUT;
    }

    /** Toutes les combinaisons de k parmi n (ordre lexicographique). */
    private static List<int[]> combinations(int n, int k) {
        List<int[]> result = new ArrayList<>(924); // C(12,6) = 924
        int[] c = new int[k];
        for (int i = 0; i < k; i++) c[i] = i;
        while (true) {
            result.add(c.clone());
            int i = k - 1;
            while (i >= 0 && c[i] == n - k + i) i--;
            if (i < 0) break;
            c[i]++;
            for (int j = i + 1; j < k; j++) c[j] = c[j-1] + 1;
        }
        return result;
    }
}
