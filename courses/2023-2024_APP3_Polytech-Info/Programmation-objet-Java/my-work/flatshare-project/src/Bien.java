import java.time.LocalTime;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Objects;

import static java.time.temporal.ChronoUnit.SECONDS;

public class Bien {
    public boolean disponible;
    int id;
    /* Tout ça c'est dans ville
    double longitude;
    double latitude;
    String addr_city;
    int insee;*/
    final Ville ville;
    final String code;
    final int nbrlog;
    final String type;
    final String addr_code;
    final String addr_name; // num, rep et voie concaténés
    final String rueName; //nom de voie pris séparément
    //tout ceux là après pourraient avoir leur classe en vrai, mais bon...
    final String operateur;
    final String techno;
    final String debitUpClass; //(INEL, HD05, HD3, BHD8, THD30, THD100, THD1G)
    final String debitDownClass; //(INEL, HD05, HD3, BHD8, THD30, THD100, THD1G)
    final int dataMaxLimitPMonth;
    final boolean sature;

    final LocalTime timeCreate = LocalTime.now(); //On fait l'approximation que c'est + ou - l'heure de son ajout dans une liste
    final double averageUploadStreet;
    final double averageDownloadStreet;
    final double averageLimitation;
    final double averageSaturationStreet;
    HashSet<Vote> votes = new HashSet<Vote>();
    double loyer = 100 + Math.random()*1000;

    /**
     * Constructeur : Bien
     * @param row : une rangée du CSV immeubles
     * @param rowInternet : une rangée du CSV Internet
     * @param averageUploadStreet : une vitesse de connexion montante moyenne dans la rue de ce Bien
     * @param averageDownloadStreet : une vitesse de connexion descendante moyenne dans la rue de ce Bien
     * @param averageLimitation : moyenne des data max par mois dans la rue
     * @param averageSaturationStreet : moyenne de saturation dans la rue
     */
    Bien(HashMap<String, String> row, HashMap<String, String> rowInternet, double averageUploadStreet, double averageDownloadStreet, double averageLimitation, double averageSaturationStreet) {
        id = Integer.parseInt(row.get("imb_id"));
        this.ville = new Ville(row.get("addr_nom_commune"), Double.parseDouble(row.get("imb_y")), Double.parseDouble(row.get("imb_x")), row.get("addr_code_insee"));
        code = row.get("imb_code");
        nbrlog = Integer.parseInt(row.get("imb_nbr_logloc"));
        type = row.get("imb_type");
        addr_code = row.get("addr_code");
        addr_name = row.get("addr_numero") + " " + row.get("addr_rep") + " " + row.get("addr_nom_voie") + " " + row.get("addr_nom_ld");
        rueName = row.get("addr_nom_voie");
        operateur = rowInternet.get("code_operateur");
        techno = rowInternet.get("code_techno");
        debitUpClass = rowInternet.get("classe_debit_montant");
        debitDownClass = rowInternet.get("classe_debit_descendant");
        int tmpDataMaxLimitPMonth;
        try{
            tmpDataMaxLimitPMonth = Integer.parseInt(rowInternet.get("limitation"));
        }catch (NumberFormatException e){
            tmpDataMaxLimitPMonth = -1;
        }
        dataMaxLimitPMonth = tmpDataMaxLimitPMonth;
        sature = Objects.equals(rowInternet.get("saturation"), "f");
        this.averageUploadStreet = averageUploadStreet;
        this.averageDownloadStreet = averageDownloadStreet;
        this.averageLimitation = averageLimitation;
        this.averageSaturationStreet = averageSaturationStreet;
    }

    /**
     * Converti une classe de débit en le minimum auquel on peut s'attendre
     * Le maximum est ignoré dans la mesure où un utilisateur cherche avant tout un débit palier
     * plutôt qu'un débit plafond atteint rarement
     * @param classe : la classe de débit
     * @return : le débit minimum de cette classe
     */
    static double minimumDebit(String classe){
        if (classe.equals("INEL")) {
            return 0;
        } else if (classe.equals("HD05")) {
            return 0.512;
        } else if (classe.equals("HD3")) {
            return 2;
        } else if (classe.equals("BHD8")) {
            return 6;
        } else if (classe.equals("THD30")) {
            return 20;
        } else if (classe.equals("THD100")) {
            return 100;
        } else if (classe.equals("THD1G")) {
            return 1000;
        } else {
            return -1; //error, n'arrive pas, n'est pas dans la base, et puis fait refuser les critères.
        }
    }

    /**
     * Renvoie le debit minimum du bien courant
     * @param up : true = debit montant ; false = debit descendant
     * @return le debit minimum de this
     */
    double minimumDebit(boolean up) {
        /**
         * @param up: true if up, false if down
         */
        String classe = up ? debitUpClass : debitDownClass;
        return Bien.minimumDebit(classe);
    }
    Ville getVille() {
        return ville;
    }
    /**
     * Calcul pour savoir si le bien est disponible ie: si on l'enleve de sa liste à l'update
     * @param nbItemList: nombre d'item dans la liste
     * @return true if the bien is available, false if not
     *
     * ~ 1 retrait par liste toutes les 180sec
     */
    boolean estDisponible(int nbItemList) {
        double proba = ((double) SECONDS.between(timeCreate, LocalTime.now())) / (180*nbItemList);
        return Math.random() > proba;
    }

    /**
     * Evalue la moyenne des votes donnés à ce bien
     * @return la moyenne des notes données
     */
    double note() {
        /**
         * @return la note du bien
         */
        if(votes.size() == 0) return -1;
        double note = 0;
        for (Vote vote : votes) {
            note += vote.note;
        }
        return note/votes.size();
    }
    /**
     * @param note : la note donnée
     * @param votant : le Votant
     * @return true if the vote is added, false if not
     */
    boolean vote(double note, Colocataire votant) {
        try{
            //override if 2eme vote
            votes.removeIf(v -> v.votant.username.equals(votant.username));
            votes.add(new Vote(note, votant));
            return true;
        }catch (IllegalArgumentException e){
            return false;
        }
    }

    public String toString() {
        return  "\tCity: " + ville + "\n" +
                "\tNumber of housings: " + nbrlog + "\n" +
                "\ttype: " + type + "\n" +
                "\tAddress: " + addr_name + "\n" +
                "\toperateur: " + operateur + "\n" +
                "\tTechnology: " + techno + "\n" +
                "\tMinimum upload speed (Mb/s): " + minimumDebit(true) + "\n" +
                "\tMinimum download speed (Mb/s) : " + minimumDebit(false) + "\n" +
                "\tMaximum data limit per month: " + (dataMaxLimitPMonth>0?dataMaxLimitPMonth:"None") + "\n" +
                "\tSature: " + sature + "\n" +
                ((note()>0)?("\tNote: " + note() + "\n"):"") +
                "\tAverage minimum upload speed of the street (Mb/s): " + averageUploadStreet + "\n" +
                "\tAverage minimum download speed of the street (Mb/s): " + averageDownloadStreet + "\n" +
                "\tAverage data limit per month of the street: " + averageLimitation + "\n" +
                "\tPercentage saturation of the street: " + averageSaturationStreet*100 + "%\n"+
                "\tRent price : " + loyer + "€\n";
    }

    /**
     * Implementation du compare
     * @param bien : bien à comparer avec this
     * @return un entier de telle sorte que lorsqu'on sort une liste de bien cela se fasse par ordre décroissant de note
     */
    public int compareTo(Bien bien) {
        return (int) (bien.note() - this.note());
    }

    public String getRue() {
        /**
         * @return the name of the street (addr_nom_voie)
         */
        return rueName;
    }
    public boolean equals(Object o) {
        if (o == this) return true;
        if (!(o instanceof Bien bien)) {
            return false;
        }
        boolean result = true;
        result &= id == bien.id;
        result &= ville.equals(bien.ville);
        result &= code.equals(bien.code);
        result &= nbrlog == bien.nbrlog;
        result &= type.equals(bien.type);
        result &= addr_code.equals(bien.addr_code);
        result &= addr_name.equals(bien.addr_name);
        result &= rueName.equals(bien.rueName);
        result &= operateur.equals(bien.operateur);
        result &= techno.equals(bien.techno);
        result &= debitUpClass.equals(bien.debitUpClass);
        result &= debitDownClass.equals(bien.debitDownClass);
        result &= dataMaxLimitPMonth == bien.dataMaxLimitPMonth;
        result &= sature == bien.sature;
        result &= averageUploadStreet == bien.averageUploadStreet;
        result &= averageDownloadStreet == bien.averageDownloadStreet;
        result &= averageLimitation == bien.averageLimitation;
        result &= averageSaturationStreet == bien.averageSaturationStreet;
        return result;
    }

    /**
     * Indique si l'offre est acceptée ou non
     * @param propose : le loyer proposé
     * @return Si l'offre est acceptée
     */
    public boolean offre(double propose){
        return propose > 0.5*loyer && Math.random() > 0.5;
    }
}
