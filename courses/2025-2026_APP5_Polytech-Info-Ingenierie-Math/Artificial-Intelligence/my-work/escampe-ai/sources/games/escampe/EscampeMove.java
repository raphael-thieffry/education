package games.escampe;

import iialib.games.model.IMove;

/**
 * Wrapper d'un coup Escampe pour s'intégrer à iialib.
 * Le format string suit le protocole prof : "B1-D1", "C6/A6/B5/D5/E6/F5", "E".
 */
public class EscampeMove implements IMove {

    private final String move;

    public EscampeMove(String move) {
        this.move = move;
    }

    public String value() {
        return move;
    }

    @Override
    public String toString() {
        return move;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof EscampeMove)) return false;
        return move.equals(((EscampeMove) o).move);
    }

    @Override
    public int hashCode() {
        return move.hashCode();
    }
}
