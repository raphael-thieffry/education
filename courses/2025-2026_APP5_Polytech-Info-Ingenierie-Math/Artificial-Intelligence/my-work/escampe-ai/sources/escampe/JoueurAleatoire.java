package escampe;

import java.util.Random;

import games.escampe.EscampeBoard;
import games.escampe.EscampeRole;

/**
 * Joueur aléatoire local : choisit un coup légal au hasard parmi
 * {@link EscampeBoard#possiblesMoves}. Utile pour smoke tests et Solo.
 *
 * (Distinct du JoueurAleatoire obfusqué de la prof dans escampeobf.jar, qui
 * implémente une interface IJoueur obfusquée incompatible avec la nôtre.)
 */
public class JoueurAleatoire implements IJoueur {

    private static final String PLACEMENT_BAS = "C1/A1/B2/D2/E1/F1";
    private static final String PLACEMENT_HAUT = "C6/A6/B5/D5/E6/F5";

    private int couleur;
    private EscampeRole monRole;
    private final EscampeBoard board = new EscampeBoard();
    private final Random rng = new Random();

    @Override
    public void initJoueur(int mycolour) {
        this.couleur = mycolour;
        this.monRole = (mycolour == IJoueur.BLANC) ? EscampeRole.BLANC : EscampeRole.NOIR;
    }

    @Override
    public int getNumJoueur() { return couleur; }

    @Override
    public String choixMouvement() {
        if (!hasMyPieces()) {
            String placement = choosePlacement();
            board.play(placement, monRole.partie1String());
            return placement;
        }
        if (board.isGameOver()) return "xxxxx";

        String[] moves = board.possiblesMoves(monRole.partie1String());
        if (moves.length == 0) return "E";
        String pick = moves[rng.nextInt(moves.length)];
        board.play(pick, monRole.partie1String());
        // "E" = passe (Partie1/réseau). Solo attend "PASSE" mais BenchmarkSolo et ServeurJeu veulent "E".
        return pick;
    }

    @Override
    public void mouvementEnnemi(String coup) {
        if (coup == null || coup.equals("xxxxx")) return;
        String c = coup.equals("PASSE") ? "E" : coup;
        board.play(c, monRole.opponent().partie1String());
    }

    @Override
    public void declareLeVainqueur(int colour) { }

    @Override
    public String binoName() { return "Aleatoire"; }

    private boolean hasMyPieces() {
        char[][] g = board.boardGrid();
        char lic = (monRole == EscampeRole.BLANC) ? 'B' : 'N';
        char pal = (monRole == EscampeRole.BLANC) ? 'b' : 'n';
        for (int i = 0; i < EscampeBoard.SIZE; i++)
            for (int j = 0; j < EscampeBoard.SIZE; j++)
                if (g[i][j] == lic || g[i][j] == pal) return true;
        return false;
    }

    private String choosePlacement() {
        char[][] g = board.boardGrid();
        char advLic = (monRole == EscampeRole.BLANC) ? 'N' : 'B';
        char advPal = (monRole == EscampeRole.BLANC) ? 'n' : 'b';
        boolean enBas = false, enHaut = false;
        for (int j = 0; j < EscampeBoard.SIZE; j++) {
            for (int i : new int[]{0, 1})
                if (g[i][j] == advLic || g[i][j] == advPal) enBas = true;
            for (int i : new int[]{4, 5})
                if (g[i][j] == advLic || g[i][j] == advPal) enHaut = true;
        }
        if (enBas) return PLACEMENT_HAUT;
        if (enHaut) return PLACEMENT_BAS;
        return PLACEMENT_BAS;
    }
}
