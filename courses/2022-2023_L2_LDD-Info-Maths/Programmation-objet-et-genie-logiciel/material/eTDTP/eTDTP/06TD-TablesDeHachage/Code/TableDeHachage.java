import java.util.List;
import java.util.LinkedList;
import java.util.ArrayList;

interface Hachable {
    int code();
}

class Table<T extends Hachable> {
   private Tableau table;
    // Invariant : nbPaquets == table.length()
    private int nbPaquets;
    // Invariant : nbElements ==
    // nombre d'éléments dans l'ensemble
    private int nbElements;
    private final float seuilCharge;
    
    public Table(int n, float s) {
        this.nbPaquets = n;
        this.nbElements = 0;
        this.seuilCharge = s;
        this.table = new Tableau(n);
    }

    private class Paquet {
        LinkedList<T> l;
        Paquet() { this.l = new LinkedList<>(); }
        boolean contient(T elt) {
            return l.contains(elt); }
        void ajoute(T elt) { l.add(elt); }
        void retire(T elt) { l.remove(elt); }
    }

    private class Tableau {
        List<Paquet> t;
        Tableau(int n) {
            this.t = new ArrayList<>(n);
            for (Paquet paquet : this.t) {
                paquet = new Paquet();
            }
        }
        Paquet paquet(int i) { return t.get(i); }
    }
    
     private int indicePaquet(T elt) {

        return elt.code() % this.nbPaquets;
    }

     public int cardinal() {
        return this.nbElements;
    }
    
     public boolean contient(T elt) {
        if (elt == null) { return false; }
        int indicePaquet = indicePaquet(elt);
        return table.paquet(indicePaquet).contient(elt);
    }

    public void ajoute(T elt) {
        if (elt == null)
            throw new NullPointerException();
        int ip = indicePaquet(elt);
        Paquet paquet = table.paquet(ip);
        if (!paquet.contient(elt)) {
            paquet.ajoute(elt);
            this.nbElements++;
            if (nbElements / (float)nbPaquets >= seuilCharge) {
                doublePaquets();
            }
        }
    }

    private void doublePaquets() {
        Tableau ancien = this.table;
        this.nbPaquets *= 2;
        this.table = new Tableau(this.nbPaquets);
        for (Paquet p: ancien.t) {
            for (T elt: p.l) {
                this.ajoute(elt);
            }
        }
    }

   public void retire(T elt) {
        if (elt != null) {
            int ip = indiceePaquet(elt);
            Paquet paquet = table.paquet(ip);
            if (paquet.contient(elt)) {
                paquet.retire(elt);
                this.nbElements--;
            }
        }
    }
}
