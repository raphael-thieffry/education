import java.util.ArrayList;

//
// Partie 2 : code des classes des éléments de train
//

// Plusieurs solutions possibles, notamment autour de l'héritage multiple de
// l'autorail. Solution retenue ici : vrai héritage de EltReservable pour tous
// les éléments recevant des passagers (et indirectement WagonBar, qui est
// officiellement décrit dans l'énoncé comme un cas particulier de Wagon), et
// faux héritage de l'interface EltMoteur pour les éléments apportant une
// traction. 

abstract class EltTrain {
    /**
     *  Un élément de train possède un nom et un poids, et ces derniers ne
     *  changent pas.
     */
    final String nom;
    final int    poids;
    static int   cpt = 1;
	
    /**
     * À la création d'un élément de train, on lui affecte un poids (fourni
     * en argument) et un nom. Le nom est généré automatiquement, et il doit
     * être unique.
     * @param poids  indique le poids de l'élément.
     */
    public EltTrain(int poids){
        nom = "Elt " + cpt++;
        this.poids = poids;
    }
	
    /**
     * Renvoie le poids total d'un élément de train. Pour les éléments
     * transportant des passagers ou des marchandises, cette mèthode devra
     * être redéfinie.
     * @return  le poids de l'élément.
     */
    public int calculerPoids(){
        return poids;
    }
}

abstract class EltReservable extends EltTrain {
    /**
     * Nombre de sièges réservables et nombre de sièges réservés.
     */
    final int capacite;
    int reservations;

    /**
     * Constructeur pour un élément réservable, initialement vide.
     * @param poids     désigne le poids à vide de l'élément
     * @param capacite  désigne le nombre de sièges réservables
     */
    public EltReservable(int poids, int capacite){
        super(poids);
        this.capacite = capacite;
        this.reservations = 0;
    }

    /**
     * Calcul du points total de l'élément et ses passagers.
     * @return  poids de l'élément et de ses passagers
     */
    public int calculerPoids() {
        return this.poids + 75 * this.reservations;
    }

    /**
     * Tentative de réservation
     * @return  true si l'ajout a eu lieu, et false sinon.
     */
    public boolean reserver() {
        if (this.reservations >= this.capacite)
            return false;
        this.reservations++;
        return true;
    }
    
    /**
     * Calcul des places restantes
     * @return  nombre de places encore disponibles
     */
    public int placesRestantes() {
        return this.capacite - this.reservations;
    }
}

class Wagon extends EltReservable {
    public Wagon(int poids, int capacite) {
        super(poids, capacite);
    }
}

class WagonBar extends Wagon {
    /**
     * Constructeur : WagonBar = Wagon pour lequel la capacité en passagers
     * est fixée à 0.
     * @param poids  indique le poids de l'élément à vide.
     */
    public WagonBar(int poids) {
        super(poids, 0);
    }
}

interface EltMoteur {
    /**
     * Un élément moteur possède une capacité de traction maximale,
     * qu'on peut obtenir en appelant cette méthode.
     * @return  la capacité de traction maximale.
     */
    int tractionMax();
}

class Locomotive extends EltTrain implements EltMoteur {
    /**
     * Attribut indiquant la capacité de traction maximale.
     */
    private int tractionMax;
    
    /**
     * Constructeur de Locomotive
     * @param poids  donne le poids de l'élément
     * @param tractionMax  donne sa capacité de traction maximale.
     */
    public Locomotive(int poids, int tractionMax) {
        super(poids);
        this.tractionMax = tractionMax;
    }
    
    /**
     * Renvoie la capacité de traction maximale.
     */
    @Override
    public int tractionMax() {
        return this.tractionMax;
    }
}

class Autorail extends EltReservable implements EltMoteur {
    /**
     * La capacité de traction maximale de l'autorail.
     */
    private int tractionMax;
	
    /**
     * Constructeur d'Autorail.
     * @param poids  donne le poids de l'élément à vide.
     * @param capacite  donne le nombre de passagers pouvant être transportés.
     * @param tractionMax  donne la capacité de traction maximale.
     */
    public Autorail(int poids, int capacite, int tractionMax) {
        super(poids, capacite);
        this.tractionMax = tractionMax;
    }

    /**
     * Renvoie la capacité de traction maximale de l'élément.
     */
    @Override
    public int tractionMax() {
        return this.tractionMax;
    }
}


//
// Partie 3 : Que se passe-t-il ?
//

/*
  EltTrain e;
  Wagon w;
  WagonBar wb;
  Locomotive l;
  Autorail a;
  
  e = new EltTrain(100); 
  -> erreur compilation, on ne peut pas instancier une classe abstraite

  l = new Locomotive(1000, 10000);
  w = new Wagon(1000, 20);
  wb = new WagonBar(1000);
  a = new Autorail(1000, 5000, 10);

  System.out.println(w.capacite);
  -> 20

  System.out.println(wb.capacite);
  -> 10

  System.out.println(e.nom);
  -> NullPointerException (l'élément n'a pas pu être défini)

  System.out.println(wb.nom);
  -> Elt 3

  a.reserver();
  -> true

  w.reserver();
  -> true

  wb.reserver();
  -> false

  l.reserver();
  -> erreur compilation (méthode n'existe pas)

  wb = (WagonBar) w;
  -> erreur exécution (type réel de w pas compatible avec WagonBar)

  System.out.println(wb.capacite);
  -> 0

  l = (Locomotive) a;
  -> erreur compilation (type Autorail et Locomotive incompatibles a priori)

  e = wb;
  e.reserver();
  -> erreur compilation (type apparent EltTrain ne connaît pas reserver)

  System.out.println(e.capacite);
  -> erreur compilation (pareil)

  w = (Wagon) e;
  -> (transtypage ok, car type réel WagonBar sous-type de Wagon)

  w.reserver();
  -> false

  System.out.println((EltTrain) w).capacite);
  -> erreur compilation (type EltTrain ne connaît pas capacite)

  System.out.println((WagonBar) w).capacite);
  -> 0
*/

//
// Partie 4 : classe Train
//

class Train {
    /**
     * L'état d'un train est caractérisé par une liste d'éléments de train.
     */
    private ArrayList<EltTrain> elements;
	
    /**
     * À l'origine, un train ne contient aucun élément.
     */
    public Train(){
        this.elements = new ArrayList<>();
    }
	
    /**
     * Ajout d'un élément au train.
     * @param elt  l'élément à ajouter.
     */
    public void ajouterElt(EltTrain elt){
        this.elements.add(elt);
    }
	
    /**
     * Calcul du poids total du train et de son chargement.
     * @return  le poids total.
     */
    public int calculerPoids(){
        int poids = 0;
        for (EltTrain elt: this.elements) {
            poids += elt.calculerPoids();
        }
        return poids;
    }
	
    /**
     * Calcul de la capacité de traction de l'ensemble des éléments
     * moteurs du train.
     * @return  la capacité de traction totale.
     */
    public int tractionMax() {
        int traction = 0;
        for (EltTrain elt: this.elements) {
            if (elt instanceof EltMoteur) {
                traction += ((EltMoteur)elt).tractionMax();
            }
        }
        return traction;
    }

    /**
     * Vérification de la bonne formation du train.
     * @return  true si et seulement si le train est bien formé.
     */
    public boolean bienForme() {
        for(EltTrain elt:  elements.subList(1,elements.size()-1))
            if(elt instanceof EltMoteur) return false;
       return calculerPoids()<=tractionMax();
    }


}
