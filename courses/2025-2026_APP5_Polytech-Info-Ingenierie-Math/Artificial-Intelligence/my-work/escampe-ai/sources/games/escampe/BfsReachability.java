package games.escampe;

import java.util.ArrayDeque;

/**
 * Distance réelle en coups pour Escampe (BFS avec contrainte liseré).
 *
 * RÈGLE CORRECTE : depuis (r,c) sur liseré L, le paladin fait exactement L
 * pas unitaires (±1 en ligne ou colonne), avec possibilité de changer de
 * direction à chaque pas. Il atteint ainsi toute case à distance Manhattan L
 * (en ignorant les obstacles).
 *
 * Ce n'est PAS un saut rectiligne de L cases — les déplacements "en L" sont
 * valides. Ex : liseré=3 depuis D5 peut atteindre C3 via D5→C5→C4→C3.
 *
 * La BFS donne le nombre minimum de COUPS (pas de pas unitaires) pour
 * atteindre la cible, en ignorant le blocage par d'autres pièces
 * (borne inférieure exacte utilisable comme heuristique).
 */
public class BfsReachability {

    private static final int UNREACHABLE = 15;

    /** Nombre minimum de coups de (sr,sc) à (tr,tc), liseré-aware. */
    public static int minMoves(int sr, int sc, int tr, int tc) {
        if (sr == tr && sc == tc) return 0;
        int[][] dist = new int[6][6];
        for (int[] row : dist) java.util.Arrays.fill(row, Integer.MAX_VALUE);
        dist[sr][sc] = 0;
        ArrayDeque<int[]> q = new ArrayDeque<>();
        q.add(new int[]{sr, sc});

        while (!q.isEmpty()) {
            int[] cur = q.poll();
            int r = cur[0], c = cur[1];
            int L = EscampeBoard.getLisereAt(r, c);

            // Depuis (r,c) avec liseré L : toutes les cases à distance Manhattan L
            // atteignables en L pas unitaires (sans obstacle, modèle borne inférieure).
            for (int[] dest : reachableInL(r, c, L)) {
                int nr = dest[0], nc = dest[1];
                if (dist[nr][nc] == Integer.MAX_VALUE) {
                    dist[nr][nc] = dist[r][c] + 1;
                    if (nr == tr && nc == tc) return dist[nr][nc];
                    q.add(new int[]{nr, nc});
                }
            }
        }
        return dist[tr][tc] == Integer.MAX_VALUE ? UNREACHABLE : dist[tr][tc];
    }

    /**
     * Toutes les cases atteignables depuis (r,c) en exactement L pas unitaires
     * (distance Manhattan = L, dans la grille 6×6).
     */
    static int[][] reachableInL(int r, int c, int L) {
        // Toutes (r+dr, c+dc) avec |dr|+|dc|=L, dans la grille.
        // dr ∈ [-L..L], dc = ±(L-|dr|)
        int count = 0;
        int[][] buf = new int[4*L + 4][2]; // max 4L+4 destinations
        for (int dr = -L; dr <= L; dr++) {
            int rem = L - Math.abs(dr);
            if (rem == 0) {
                int nr = r + dr, nc = c;
                if (inBounds(nr, nc)) buf[count++] = new int[]{nr, nc};
            } else {
                for (int dc : new int[]{rem, -rem}) {
                    int nr = r + dr, nc = c + dc;
                    if (inBounds(nr, nc)) buf[count++] = new int[]{nr, nc};
                }
            }
        }
        int[][] result = new int[count][2];
        System.arraycopy(buf, 0, result, 0, count);
        return result;
    }

    private static boolean inBounds(int r, int c) {
        return r >= 0 && r < 6 && c >= 0 && c < 6;
    }
}
