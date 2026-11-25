package escampe;

import games.escampe.EscampeBoard;
import games.escampe.EscampeHeuristics;
import games.escampe.EscampeMove;
import games.escampe.EscampeRole;
import iialib.games.algs.IHeuristic;

public class JoueurThieffry implements IJoueur {

    // Budget total : 5 min = 300s par joueur. On s'arrête à 290s pour la sécurité.
    private static final long BUDGET_TOTAL_MS   = 290_000L;
    // Estimation réaliste : ~15 coups par partie (pas 60).
    private static final int  EXPECTED_MOVES    = 15;
    private static final long BUDGET_MIN_MS     = 1_000L;

    private static final String PLACEMENT_BAS  = "C1/A1/B2/D2/E1/F1";
    private static final String PLACEMENT_HAUT = "C6/A6/B5/D5/E6/F5";

    private static final IHeuristic<EscampeBoard, EscampeRole> HEURISTIC =
            EscampeHeuristics.hOf(HeuristicWeights.defaults());

    private int couleur;
    private EscampeRole monRole;
    private EscampeBoard board;
    private final AlphaBetaID alphaBeta = new AlphaBetaID();
    private long gameStartMs;
    private int moveCount;
    private String forcedPlacement = null;

    public void setPlacement(String p) { this.forcedPlacement = p; }

    public JoueurThieffry() {
        this.board = new EscampeBoard();
    }

    @Override
    public void initJoueur(int mycolour) {
        this.couleur  = mycolour;
        this.monRole  = (mycolour == IJoueur.BLANC) ? EscampeRole.BLANC : EscampeRole.NOIR;
        this.gameStartMs = System.currentTimeMillis();
        this.moveCount   = 0;
    }

    @Override
    public int getNumJoueur() {
        return couleur;
    }

    @Override
    public String choixMouvement() {
        // 1) Phase placement : si je n'ai posé aucune pièce → je place.
        if (!boardHasMyPieces()) {
            String placement = (forcedPlacement != null)
                    ? forcedPlacement
                    : PlacementSearch.bestPlacement(board, monRole);
            board.play(placement, monRole.partie1String());
            return placement;
        }

        // 2) Phase déplacement : alphabeta iteratif avec gestion du temps.
        if (board.isGameOver()) return "xxxxx";

        // Passe forcé : un seul coup légal, pas besoin de recherche.
        String[] legal = board.possiblesMoves(monRole.partie1String());
        if (legal.length == 0 || (legal.length == 1 && legal[0].equals("E"))) {
            board.play("E", monRole.partie1String());
            moveCount++;
            return "E";
        }

        long elapsed   = System.currentTimeMillis() - gameStartMs;
        long remaining = Math.max(BUDGET_MIN_MS, BUDGET_TOTAL_MS - elapsed);
        int  movesLeft = Math.max(1, EXPECTED_MOVES - moveCount);
        long budget    = Math.max(BUDGET_MIN_MS, remaining / movesLeft);

        EscampeMove best = alphaBeta.bestMove(board, monRole, HEURISTIC, budget);
        moveCount++;
        if (best == null) return "E";
        String coup = best.value();
        board.play(coup, monRole.partie1String());
        return coup;
    }

    @Override
    public void mouvementEnnemi(String coup) {
        if (coup == null || coup.equals("xxxxx")) return;
        // Accepte "PASSE" (Solo) et "E" (réseau/Partie1) comme passe.
        String c = coup.equals("PASSE") ? "E" : coup;
        EscampeRole adv = monRole.opponent();
        board.play(c, adv.partie1String());
    }

    @Override
    public void declareLeVainqueur(int colour) {
        if (colour == couleur) System.out.println("[Thieffry] Victoire !");
        else System.out.println("[Thieffry] Défaite.");
    }

    @Override
    public String binoName() {
        return "Thieffry";
    }

    // -----------------------------------------------------------------

    private boolean boardHasMyPieces() {
        char[][] g = board.boardGrid();
        char lic = (monRole == EscampeRole.BLANC) ? 'B' : 'N';
        char pal = (monRole == EscampeRole.BLANC) ? 'b' : 'n';
        for (int i = 0; i < EscampeBoard.SIZE; i++)
            for (int j = 0; j < EscampeBoard.SIZE; j++)
                if (g[i][j] == lic || g[i][j] == pal) return true;
        return false;
    }

    /**
     * Choisit le bord à placer. Si l'adversaire (noir) a déjà placé, on prend
     * le bord opposé ; sinon on prend le bas par défaut.
     */
    private String choosePlacement() {
        char[][] g = board.boardGrid();
        boolean advEnHaut = false, advEnBas = false;
        char advLic = (monRole == EscampeRole.BLANC) ? 'N' : 'B';
        char advPal = (monRole == EscampeRole.BLANC) ? 'n' : 'b';
        for (int j = 0; j < EscampeBoard.SIZE; j++) {
            for (int i : new int[]{0, 1})
                if (g[i][j] == advLic || g[i][j] == advPal) advEnBas = true;
            for (int i : new int[]{4, 5})
                if (g[i][j] == advLic || g[i][j] == advPal) advEnHaut = true;
        }
        if (advEnBas) return PLACEMENT_HAUT;
        if (advEnHaut) return PLACEMENT_BAS;
        // Adversaire pas encore placé (cas du noir qui démarre) : on prend le bas.
        return PLACEMENT_BAS;
    }
}
