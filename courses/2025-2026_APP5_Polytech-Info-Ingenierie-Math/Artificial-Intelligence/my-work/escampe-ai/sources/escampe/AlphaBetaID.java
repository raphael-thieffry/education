package escampe;

import games.escampe.EscampeBoard;
import games.escampe.EscampeMove;
import games.escampe.EscampeRole;
import iialib.games.algs.IHeuristic;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Random;

/**
 * AlphaBeta avec iterative deepening, transposition table (Zobrist) et quiescence search.
 *
 * Améliorations vs iialib.AlphaBeta :
 *  - Iterative deepening : depth 1→N jusqu'à deadline, retourne le meilleur coup
 *    de la dernière profondeur complète
 *  - Move ordering : coup TT d'abord, captures ensuite, reste après
 *    → effectivement double la profondeur utile (O(b^d) → O(b^(d/2)))
 *  - Transposition table (Zobrist hash) : évite la re-évaluation de positions
 *    identiques atteintes par des chemins différents
 *  - Quiescence search : à la frontière (depth=0), continue sur les captures
 *    jusqu'au calme → élimine l'effet horizon (position "presque-capture" mal évaluée)
 */
public class AlphaBetaID {

    private static final int INF            = 500_000;
    private static final int CHECK_INTERVAL = 1_000;  // nodes entre checks temporels

    // ── Zobrist hashing ──────────────────────────────────────────────────────
    private static final long[][][] ZOBRIST = new long[6][6][6];
    static {
        Random rng = new Random(0xDEADBEEFL);
        for (int r = 0; r < 6; r++)
            for (int c = 0; c < 6; c++)
                for (int p = 0; p < 6; p++)
                    ZOBRIST[r][c][p] = rng.nextLong();
    }

    // ── Transposition table ───────────────────────────────────────────────────
    private static final int FLAG_EXACT = 0, FLAG_LOWER = 1, FLAG_UPPER = 2;

    private static class TTEntry {
        int depth, score, flag;
        EscampeMove bestMove;
        TTEntry(int d, int s, int f, EscampeMove m) { depth=d; score=s; flag=f; bestMove=m; }
    }

    private final HashMap<Long, TTEntry> tt = new HashMap<>(1 << 18);

    // ── État de la recherche ──────────────────────────────────────────────────
    private long deadline;
    private boolean timeOut;
    private int nodesSinceCheck;

    // ─────────────────────────────────────────────────────────────────────────

    /**
     * Retourne le meilleur coup trouvé dans le budget de temps donné.
     * Repart de depth=1 et descend aussi loin que le temps le permet.
     */
    public EscampeMove bestMove(EscampeBoard board, EscampeRole maxRole,
                                IHeuristic<EscampeBoard, EscampeRole> h, long budgetMs) {
        deadline = System.currentTimeMillis() + budgetMs;
        timeOut  = false;
        nodesSinceCheck = 0;
        tt.clear();

        EscampeMove best     = null;
        EscampeRole minRole  = maxRole.opponent();

        for (int depth = 1; depth <= 20 && !timeOut; depth++) {
            EscampeMove candidate = rootSearch(board, depth, maxRole, minRole, h);
            if (!timeOut && candidate != null) {
                best = candidate;
                // Coup gagnant trouvé → inutile d'aller plus loin
                EscampeBoard after = board.play(candidate, maxRole);
                if (after.isGameOver()) break;
            }
        }
        return best;
    }

    // ── Racine ───────────────────────────────────────────────────────────────

    private EscampeMove rootSearch(EscampeBoard board, int depth,
                                    EscampeRole maxRole, EscampeRole minRole,
                                    IHeuristic<EscampeBoard, EscampeRole> h) {
        int alpha = -INF, beta = INF;
        EscampeMove bestMove = null;

        TTEntry ttEntry = tt.get(zobrist(board));
        EscampeMove ttMove = (ttEntry != null) ? ttEntry.bestMove : null;

        for (EscampeMove move : orderedMoves(board, maxRole, ttMove, maxRole)) {
            if (tickTime()) break;
            EscampeBoard next = board.play(move, maxRole);
            int score = minValue(next, depth - 1, alpha, beta, maxRole, minRole, h);
            if (!timeOut && score > alpha) {
                alpha    = score;
                bestMove = move;
            }
        }
        return bestMove;
    }

    // ── MaxValue ─────────────────────────────────────────────────────────────

    private int maxValue(EscampeBoard board, int depth, int alpha, int beta,
                          EscampeRole maxRole, EscampeRole minRole,
                          IHeuristic<EscampeBoard, EscampeRole> h) {
        if (tickTime()) return 0;
        if (board.isGameOver())
            return board.possibleMoves(maxRole).isEmpty() ? -INF + 1 : INF - 1;
        if (depth == 0)
            return quiesce(board, alpha, beta, maxRole, minRole, h, true);

        long hash = zobrist(board);
        TTEntry entry = tt.get(hash);
        EscampeMove ttMove = null;
        if (entry != null) {
            ttMove = entry.bestMove;
            if (entry.depth >= depth) {
                if (entry.flag == FLAG_EXACT) return entry.score;
                if (entry.flag == FLAG_LOWER) alpha = Math.max(alpha, entry.score);
                if (entry.flag == FLAG_UPPER) beta  = Math.min(beta,  entry.score);
                if (alpha >= beta) return entry.score;
            }
        }

        int v = -INF, origAlpha = alpha;
        EscampeMove bestMove = null;

        for (EscampeMove move : orderedMoves(board, maxRole, ttMove, maxRole)) {
            if (tickTime()) break;
            int score = minValue(board.play(move, maxRole), depth-1, alpha, beta, maxRole, minRole, h);
            if (score > v) { v = score; bestMove = move; }
            if (v > alpha) alpha = v;
            if (v >= beta) break;
        }

        if (!timeOut) {
            int flag = v <= origAlpha ? FLAG_UPPER : (v >= beta ? FLAG_LOWER : FLAG_EXACT);
            tt.put(hash, new TTEntry(depth, v, flag, bestMove));
        }
        return v;
    }

    // ── MinValue ─────────────────────────────────────────────────────────────

    private int minValue(EscampeBoard board, int depth, int alpha, int beta,
                          EscampeRole maxRole, EscampeRole minRole,
                          IHeuristic<EscampeBoard, EscampeRole> h) {
        if (tickTime()) return 0;
        if (board.isGameOver())
            return board.possibleMoves(minRole).isEmpty() ? INF - 1 : -INF + 1;
        if (depth == 0)
            return quiesce(board, alpha, beta, maxRole, minRole, h, false);

        long hash = zobrist(board);
        TTEntry entry = tt.get(hash);
        EscampeMove ttMove = null;
        if (entry != null) {
            ttMove = entry.bestMove;
            if (entry.depth >= depth) {
                if (entry.flag == FLAG_EXACT) return entry.score;
                if (entry.flag == FLAG_LOWER) alpha = Math.max(alpha, entry.score);
                if (entry.flag == FLAG_UPPER) beta  = Math.min(beta,  entry.score);
                if (alpha >= beta) return entry.score;
            }
        }

        int v = INF, origBeta = beta;
        EscampeMove bestMove = null;

        for (EscampeMove move : orderedMoves(board, minRole, ttMove, maxRole)) {
            if (tickTime()) break;
            int score = maxValue(board.play(move, minRole), depth-1, alpha, beta, maxRole, minRole, h);
            if (score < v) { v = score; bestMove = move; }
            if (v < beta) beta = v;
            if (v <= alpha) break;
        }

        if (!timeOut) {
            int flag = v >= origBeta ? FLAG_LOWER : (v <= alpha ? FLAG_UPPER : FLAG_EXACT);
            tt.put(hash, new TTEntry(depth, v, flag, bestMove));
        }
        return v;
    }

    // ── Quiescence search ────────────────────────────────────────────────────
    // Continue uniquement sur les captures à depth=0 → évite l'effet horizon.

    private int quiesce(EscampeBoard board, int alpha, int beta,
                         EscampeRole maxRole, EscampeRole minRole,
                         IHeuristic<EscampeBoard, EscampeRole> h, boolean isMax) {
        if (tickTime()) return 0;
        if (board.isGameOver()) {
            if (isMax) return board.possibleMoves(maxRole).isEmpty() ? -INF+1 : INF-1;
            else       return board.possibleMoves(minRole).isEmpty() ? INF-1  : -INF+1;
        }

        int standPat = h.eval(board, maxRole);

        if (isMax) {
            if (standPat >= beta)  return standPat;
            if (standPat > alpha)  alpha = standPat;
            for (EscampeMove m : captures(board, maxRole, maxRole)) {
                if (tickTime()) break;
                int score = quiesce(board.play(m, maxRole), alpha, beta, maxRole, minRole, h, false);
                if (score >= beta)  return score;
                if (score > alpha)  alpha = score;
            }
            return alpha;
        } else {
            if (standPat <= alpha) return standPat;
            if (standPat < beta)   beta = standPat;
            for (EscampeMove m : captures(board, minRole, maxRole)) {
                if (tickTime()) break;
                int score = quiesce(board.play(m, minRole), alpha, beta, maxRole, minRole, h, true);
                if (score <= alpha) return score;
                if (score < beta)   beta = score;
            }
            return beta;
        }
    }

    // ── Helpers ───────────────────────────────────────────────────────────────

    /** Moves : coup TT en tête, captures ensuite, reste après. */
    private ArrayList<EscampeMove> orderedMoves(EscampeBoard board, EscampeRole role,
                                                  EscampeMove ttMove, EscampeRole maxRole) {
        char oppLic = oppLicChar(role, maxRole);
        char[][] g  = board.boardGrid();
        ArrayList<EscampeMove> all = board.possibleMoves(role);
        ArrayList<EscampeMove> ttList = new ArrayList<>(1);
        ArrayList<EscampeMove> caps   = new ArrayList<>();
        ArrayList<EscampeMove> rest   = new ArrayList<>(all.size());

        for (EscampeMove m : all) {
            if (ttMove != null && m.value().equals(ttMove.value())) {
                ttList.add(m);
            } else {
                int[] dest = dest(m.value());
                if (dest != null && g[dest[0]][dest[1]] == oppLic) caps.add(m);
                else rest.add(m);
            }
        }
        ArrayList<EscampeMove> result = new ArrayList<>(all.size());
        result.addAll(ttList);
        result.addAll(caps);
        result.addAll(rest);
        return result;
    }

    /** Uniquement les coups captures (destination = licorne adverse). */
    private ArrayList<EscampeMove> captures(EscampeBoard board, EscampeRole role, EscampeRole maxRole) {
        char oppLic = oppLicChar(role, maxRole);
        char[][] g  = board.boardGrid();
        ArrayList<EscampeMove> caps = new ArrayList<>();
        for (EscampeMove m : board.possibleMoves(role)) {
            int[] d = dest(m.value());
            if (d != null && g[d[0]][d[1]] == oppLic) caps.add(m);
        }
        return caps;
    }

    private static char oppLicChar(EscampeRole role, EscampeRole maxRole) {
        // "opponent unicorn" du point de vue du joueur qui bouge (role)
        return (role == EscampeRole.BLANC) ? 'N' : 'B';
    }

    /** Parse "B1-D1" → {row=0, col=3}. Retourne null si pas un coup de déplacement. */
    private static int[] dest(String move) {
        int h = move.indexOf('-');
        if (h < 0) return null;
        String d = move.substring(h + 1);
        if (d.length() < 2) return null;
        int col = d.charAt(0) - 'A';
        int row = Character.getNumericValue(d.charAt(1)) - 1;
        if (row < 0 || row >= 6 || col < 0 || col >= 6) return null;
        return new int[]{row, col};
    }

    private boolean tickTime() {
        if (++nodesSinceCheck >= CHECK_INTERVAL) {
            nodesSinceCheck = 0;
            if (System.currentTimeMillis() >= deadline) timeOut = true;
        }
        return timeOut;
    }

    private static int pieceIdx(char c) {
        switch (c) {
            case 'b': return 1; case 'B': return 2;
            case 'n': return 3; case 'N': return 4;
            case '-': return 0; default:  return 5;
        }
    }

    private static long zobrist(EscampeBoard board) {
        long hash = 0;
        char[][] g = board.boardGrid();
        for (int r = 0; r < 6; r++)
            for (int c = 0; c < 6; c++)
                hash ^= ZOBRIST[r][c][pieceIdx(g[r][c])];
        return hash;
    }
}
