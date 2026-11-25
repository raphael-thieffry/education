import java.util.ArrayList;

public class Circuit {

    public static void main(String[] args) {

        Circuit  c = new Circuit ();
        Noeud n0 = c.creeEntree();	c.sortie=n0;
        System.out.println("Ceci doit afficher 33 : " + c.calcule(33));
//            Noeud n1=c.creeAddition(n0,n0);c.sortie=n1;
//            System.out.println("Ceci doit afficher 66 : " + c.calcule(33));
//            Noeud n2=c.creeAddition(n1,c.creeConstante(1));c.sortie=n2;
//            System.out.println("Ceci doit afficher 67 : " + c.calcule(33));
//            Noeud n3 = c.creeMultiplication(n2, c.creeMultiplication(n0,n0)); c.sortie = n3;
//            System.out.println("Ceci doit afficher 20 : " + c.calcule(2));
//            c.sortie=n0;System.out.print("Ceci doit afficher x:  ");c.affiche();
//            c.sortie = n3; System.out.print("Ceci doit afficher (((x + x) + 1) * (x * x)) : ");   c.affiche();
//
//            Circuit c2 = new Circuit();
//            Noeud n4 = c2.creeEntree();
//            Noeud n5=c2.creeMultiplication(n4,n4);
//            Noeud n6=c2.creeMultiplication(n5,n5); c2.sortie=n6;
//            System.out.print("Ceci doit afficher  ((x * x) * (x * x)):   ");  c2.affiche();
//            System.out.println("Ceci doit afficher 2 : " + c2.nbNoeudsArith());
//            c2.calcule(1); System.out.println("Ceci doit afficher 3: " + c2.nbOpEffectuees());
//
//
//            Circuit c3 = new Circuit();
//            Noeud n7 = c3.creeEntree();
//            Noeud n8=c3.creeMultiplicationMemoisee(n7,n7);
//            Noeud n9=c3.creeMultiplicationMemoisee(n8,n8); c3.sortie=n9;
//            System.out.print("Ceci doit afficher  ((x * x) * (x * x)):   ");  c2.affiche();
//            System.out.println("Ceci doit afficher 2 : " + c2.nbNoeudsArith());
//            c2.calcule(1); System.out.println("Ceci doit afficher 2: " + c2.nbOpEffectuees());
//
//
//            Circuit p4 = expRapide(4); p4.affiche();
//            System.out.println("Ceci doit afficher 4 : " + p4.nbNoeudsArith());
//            System.out.println("Ceci doit afficher  65536 : " + p4.calcule(2));
//            System.out.println("Ceci doit afficher  15: " + p4.nbOpEffectuees());
//
//            Circuit p4m = expRapideMemoise(4);
//            System.out.println("Ceci doit afficher 4 : " + p4m.nbNoeudsArith());
//            System.out.println("Ceci doit afficher 65536 : " + p4m.calcule(2));
//            System.out.println("Ceci doit afficher 4 : " + p4m.nbOpEffectuees());

    }

    /**
     * Valeur de la variable dont dépend le calcul
     */
    private int entree;

    /**
     * Dernier nœud, calculant le résultat
     */
    private Noeud sortie;

    /**
     * Ensemble des nœuds
     */
    private ArrayList<Noeud> noeuds;

    /**
     * Constructeur.
     * N'initialise pas l'entrée : la méthode calcule s'en chargera avant
     * chaque calcul. La sortie n'est pas initialisée non plus pour éviter
     * un problème de circularité.
     */
    private Circuit() {
        this.noeuds = new ArrayList<Noeud>();
    }

    /**
     * Ajout d'un nœud à la liste
     * @param n Nœud à ajouter
     */
    private void ajouteNoeud(Noeud n) {
        noeuds.add(n);
    }


    // Création de nœuds avec ajout direct
    /**
     * Création d'un nœud entree
     */
    public Noeud creeEntree() {
        Noeud e = new Entree(this);
        this.ajouteNoeud(e);
        return e;
    }

    /**
     * Donne la valeur de l'entrée, dont auront besoin certains nœuds
     */
    public int litEntree() {
        return this.entree;
    }

    /**
     * Initialise la variable d'entrée et calcule le résultat
     * @param e Valeur affectée à la variable d'entrée
     * @return Valeur calculée par le circuit
     */
    public int calcule(int e) {
        this.entree = e;
        return this.sortie.valeur();
    }

}


abstract class Noeud {
    abstract public int valeur();
}


class Entree extends Noeud {
    private Circuit circuit;
    public Entree(Circuit  c) {
        this.circuit = c;
    }
    public int valeur() {
        return this.circuit.litEntree();
    }
    public String toString() {
        return "x";
    }
}
