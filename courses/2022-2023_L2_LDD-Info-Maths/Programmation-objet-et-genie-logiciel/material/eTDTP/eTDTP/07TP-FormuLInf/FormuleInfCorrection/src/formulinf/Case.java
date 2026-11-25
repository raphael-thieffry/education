package formulinf;
import java.awt.Color;

import ig.ZoneCliquable;

public class Case extends ZoneCliquable {
    final boolean traversable;
    final Vect coord;
    final Circuit circuit;
    
    // Création d'une case de coordonnées données, traversable ou non
    Case(Circuit c, Vect p, boolean b) {
        super("", 12, 12);
        this.traversable = b;
        this.coord = p;
        this.circuit = c;
        if (!this.traversable)
            this.setBackground(Color.BLACK);
    }
    
    // Réaction au clic
    public void clicGauche() {
        this.circuit.gereClic(this.coord);
    }
    
    public void clicDroit() {}
}
