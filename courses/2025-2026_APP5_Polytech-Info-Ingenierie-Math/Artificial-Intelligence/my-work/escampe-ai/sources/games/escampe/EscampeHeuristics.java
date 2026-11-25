package games.escampe;

import escampe.HeuristicWeights;
import iialib.games.algs.IHeuristic;

/**
 * Heuristiques d'évaluation pour Escampe (latex partie 1).
 *
 * Critères combinés :
 *   1. Distance minimale entre mes paladins et la licorne adverse (plus petite = mieux)
 *   2. Distance minimale entre paladins adverses et ma licorne (plus grande = mieux)
 *   3. Nombre de coups possibles pour moi vs adversaire (mobilité)
 *
 * Si la licorne adverse est capturée → +∞. Si la mienne l'est → -∞.
 */
public class EscampeHeuristics {

    /** Première heuristique simple : combine distance + mobilité. */
    public static final IHeuristic<EscampeBoard, EscampeRole> H_BASIC = (board, role) -> {
        if (board.isGameOver()) {
            // Si la licorne adverse a disparu, victoire ; sinon défaite.
            char myLic = (role == EscampeRole.BLANC) ? 'B' : 'N';
            char oppLic = (role == EscampeRole.BLANC) ? 'N' : 'B';
            boolean myAlive = contains(board, myLic);
            boolean oppAlive = contains(board, oppLic);
            if (!oppAlive) return IHeuristic.MAX_VALUE - 1;
            if (!myAlive) return IHeuristic.MIN_VALUE + 1;
            return 0;
        }

        char myPal = (role == EscampeRole.BLANC) ? 'b' : 'n';
        char oppPal = (role == EscampeRole.BLANC) ? 'n' : 'b';
        char myLic = (role == EscampeRole.BLANC) ? 'B' : 'N';
        char oppLic = (role == EscampeRole.BLANC) ? 'N' : 'B';

        int[] myLicPos = findPiece(board, myLic);
        int[] oppLicPos = findPiece(board, oppLic);

        int distMineToOppLic = minDist(board, myPal, oppLicPos);
        int distOppToMyLic = minDist(board, oppPal, myLicPos);

        // Plus mes paladins sont proches de la licorne adverse, meilleur c'est.
        // Plus les paladins adverses sont loin de ma licorne, meilleur c'est.
        int score = 0;
        score += (10 - distMineToOppLic) * 10;
        score += distOppToMyLic * 5;

        // Mobilité bonus : différence de coups possibles.
        int myMoves = board.possiblesMoves(role.partie1String()).length;
        int oppMoves = board.possiblesMoves(role.opponent().partie1String()).length;
        score += (myMoves - oppMoves) * 2;

        return score;
    };

    private static boolean contains(EscampeBoard board, char c) {
        char[][] g = board.boardGrid();
        for (int i = 0; i < EscampeBoard.SIZE; i++)
            for (int j = 0; j < EscampeBoard.SIZE; j++)
                if (g[i][j] == c) return true;
        return false;
    }

    /**
     * Heuristique V2 : distances BFS réelles + menaces directes + mobilité licorne.
     *
     * Remplace Manhattan par la distance en coups effective (liseré-aware).
     * Ajoute :
     *   - dangerCount  : mes paladins à ≤2 coups de la licorne adverse (+offensif)
     *   - threatCount  : paladins adverses à ≤2 coups de ma licorne (−défensif)
     *   - licMobility  : cases de fuite de ma licorne (cases libres atteignables en 1 coup)
     */
    public static final IHeuristic<EscampeBoard, EscampeRole> H_V2 = (board, role) -> {
        if (board.isGameOver()) {
            char myLic  = (role == EscampeRole.BLANC) ? 'B' : 'N';
            char oppLic = (role == EscampeRole.BLANC) ? 'N' : 'B';
            boolean myAlive  = contains(board, myLic);
            boolean oppAlive = contains(board, oppLic);
            if (!oppAlive) return IHeuristic.MAX_VALUE - 1;
            if (!myAlive)  return IHeuristic.MIN_VALUE + 1;
            return 0;
        }

        char myPal  = (role == EscampeRole.BLANC) ? 'b' : 'n';
        char oppPal = (role == EscampeRole.BLANC) ? 'n' : 'b';
        char myLic  = (role == EscampeRole.BLANC) ? 'B' : 'N';
        char oppLic = (role == EscampeRole.BLANC) ? 'N' : 'B';

        char[][] g        = board.boardGrid();
        int[] myLicPos    = findPiece(board, myLic);
        int[] oppLicPos   = findPiece(board, oppLic);

        if (myLicPos  == null) return IHeuristic.MIN_VALUE + 1;
        if (oppLicPos == null) return IHeuristic.MAX_VALUE - 1;

        // Mes paladins → licorne adverse (BFS) + couverture liseré
        int minBfsToOppLic = 15;
        int dangerCount = 0, killShot = 0;
        // Paladins adverses → ma licorne (BFS)
        int minBfsToMyLic = 15;
        int threatCount = 0, immediateThreat = 0;

        boolean[] myLiseres  = new boolean[4]; // [1],[2],[3] = types couverts par mes pièces
        boolean[] oppLiseres = new boolean[4];

        // Licornes aussi couvrent un liseré
        myLiseres[EscampeBoard.getLisereAt(myLicPos[0], myLicPos[1])] = true;
        oppLiseres[EscampeBoard.getLisereAt(oppLicPos[0], oppLicPos[1])] = true;

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                char p = g[i][j];
                if (p == myPal) {
                    myLiseres[EscampeBoard.getLisereAt(i, j)] = true;
                    int d = BfsReachability.minMoves(i, j, oppLicPos[0], oppLicPos[1]);
                    if (d < minBfsToOppLic) minBfsToOppLic = d;
                    if (d == 1) killShot++;      // capture directe possible
                    if (d <= 2) dangerCount++;
                } else if (p == oppPal) {
                    oppLiseres[EscampeBoard.getLisereAt(i, j)] = true;
                    int d = BfsReachability.minMoves(i, j, myLicPos[0], myLicPos[1]);
                    if (d < minBfsToMyLic) minBfsToMyLic = d;
                    if (d == 1) immediateThreat++; // peut capturer ma licorne au prochain coup
                    if (d <= 2) threatCount++;
                }
            }
        }

        // Couverture liseré : chaque type (1/2/3) non couvert = vulnérabilité au passe forcé
        int myLisereCoverage  = (myLiseres[1]?1:0)  + (myLiseres[2]?1:0)  + (myLiseres[3]?1:0);
        int oppLisereCoverage = (oppLiseres[1]?1:0) + (oppLiseres[2]?1:0) + (oppLiseres[3]?1:0);

        // Cases de fuite de ma licorne (modèle Manhattan correct)
        int licL = EscampeBoard.getLisereAt(myLicPos[0], myLicPos[1]);
        int licMobility = 0;
        for (int[] dest : BfsReachability.reachableInL(myLicPos[0], myLicPos[1], licL)) {
            if (g[dest[0]][dest[1]] == '-') licMobility++;
        }

        // Mobilité globale
        int myMoves  = board.possiblesMoves(role.partie1String()).length;
        int oppMoves = board.possiblesMoves(role.opponent().partie1String()).length;

        int score = 0;
        score += (10 - minBfsToOppLic) * 20;  // approcher la licorne adverse
        score += minBfsToMyLic          * 10;  // éloigner les adversaires
        score += killShot               * 25;  // capture directe disponible
        score += dangerCount            * 15;  // menaces offensives ≤2 coups
        score -= immediateThreat        * 50;  // paladin adverse à 1 coup de ma licorne !
        score -= threatCount            * 25;  // menaces défensives ≤2 coups
        score += licMobility            * 12;  // cases de fuite de ma licorne
        score += myLisereCoverage       * 20;  // couverture liseré (évite passe forcé)
        score -= oppLisereCoverage      * 10;  // adversaire bien couvert = dangereux
        score += (myMoves - oppMoves)   *  3;  // mobilité différentielle

        return Math.max(IHeuristic.MIN_VALUE + 2, Math.min(IHeuristic.MAX_VALUE - 2, score));
    };

    /**
     * Heuristique paramétrée par un vecteur de poids.
     * Même structure que H_V2 mais chaque coefficient vient de HeuristicWeights.
     */
    public static IHeuristic<EscampeBoard, EscampeRole> hOf(HeuristicWeights w) {
        return (board, role) -> {
            if (board.isGameOver()) {
                char myLic  = (role == EscampeRole.BLANC) ? 'B' : 'N';
                char oppLic = (role == EscampeRole.BLANC) ? 'N' : 'B';
                if (!contains(board, oppLic)) return IHeuristic.MAX_VALUE - 1;
                if (!contains(board, myLic))  return IHeuristic.MIN_VALUE + 1;
                return 0;
            }

            char myPal  = (role == EscampeRole.BLANC) ? 'b' : 'n';
            char oppPal = (role == EscampeRole.BLANC) ? 'n' : 'b';
            char myLic  = (role == EscampeRole.BLANC) ? 'B' : 'N';
            char oppLic = (role == EscampeRole.BLANC) ? 'N' : 'B';

            char[][] g      = board.boardGrid();
            int[] myLicPos  = findPiece(board, myLic);
            int[] oppLicPos = findPiece(board, oppLic);

            if (myLicPos  == null) return IHeuristic.MIN_VALUE + 1;
            if (oppLicPos == null) return IHeuristic.MAX_VALUE - 1;

            int minBfsToOppLic = 15, dangerCount = 0, killShot = 0;
            int minBfsToMyLic  = 15, threatCount = 0, immediateThreat = 0;
            boolean[] myLiseres  = new boolean[4];
            boolean[] oppLiseres = new boolean[4];
            myLiseres[EscampeBoard.getLisereAt(myLicPos[0], myLicPos[1])] = true;
            oppLiseres[EscampeBoard.getLisereAt(oppLicPos[0], oppLicPos[1])] = true;

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    char p = g[i][j];
                    if (p == myPal) {
                        myLiseres[EscampeBoard.getLisereAt(i, j)] = true;
                        int d = BfsReachability.minMoves(i, j, oppLicPos[0], oppLicPos[1]);
                        if (d < minBfsToOppLic) minBfsToOppLic = d;
                        if (d == 1) killShot++;
                        if (d <= 2) dangerCount++;
                    } else if (p == oppPal) {
                        oppLiseres[EscampeBoard.getLisereAt(i, j)] = true;
                        int d = BfsReachability.minMoves(i, j, myLicPos[0], myLicPos[1]);
                        if (d < minBfsToMyLic) minBfsToMyLic = d;
                        if (d == 1) immediateThreat++;
                        if (d <= 2) threatCount++;
                    }
                }
            }

            int myLisCov  = (myLiseres[1]?1:0)  + (myLiseres[2]?1:0)  + (myLiseres[3]?1:0);
            int oppLisCov = (oppLiseres[1]?1:0) + (oppLiseres[2]?1:0) + (oppLiseres[3]?1:0);

            int licL = EscampeBoard.getLisereAt(myLicPos[0], myLicPos[1]);
            int licMobility = 0;
            for (int[] dest : BfsReachability.reachableInL(myLicPos[0], myLicPos[1], licL))
                if (g[dest[0]][dest[1]] == '-') licMobility++;

            int myMoves  = board.possiblesMoves(role.partie1String()).length;
            int oppMoves = board.possiblesMoves(role.opponent().partie1String()).length;

            int score = 0;
            score += (int)((10 - minBfsToOppLic) * w.proximity);
            score += (int)(minBfsToMyLic          * w.safety);
            score += (int)(killShot               * w.killShot);
            score += (int)(dangerCount            * w.danger);
            score -= (int)(immediateThreat        * w.immThreat);
            score -= (int)(threatCount            * w.threat);
            score += (int)(licMobility            * w.licMobility);
            score += (int)(myLisCov               * w.myLisere);
            score -= (int)(oppLisCov              * w.oppLisere);
            score += (int)((myMoves - oppMoves)   * w.mobility);

            return Math.max(IHeuristic.MIN_VALUE + 2, Math.min(IHeuristic.MAX_VALUE - 2, score));
        };
    }

    private static int[] findPiece(EscampeBoard board, char c) {
        char[][] g = board.boardGrid();
        for (int i = 0; i < EscampeBoard.SIZE; i++)
            for (int j = 0; j < EscampeBoard.SIZE; j++)
                if (g[i][j] == c) return new int[]{i, j};
        return null;
    }

    /** Distance Manhattan minimale entre toutes les pièces 'piece' et la cible. */
    private static int minDist(EscampeBoard board, char piece, int[] target) {
        if (target == null) return 0;
        char[][] g = board.boardGrid();
        int min = Integer.MAX_VALUE;
        for (int i = 0; i < EscampeBoard.SIZE; i++) {
            for (int j = 0; j < EscampeBoard.SIZE; j++) {
                if (g[i][j] == piece) {
                    int d = Math.abs(i - target[0]) + Math.abs(j - target[1]);
                    if (d < min) min = d;
                }
            }
        }
        return min == Integer.MAX_VALUE ? 10 : min;
    }
}
