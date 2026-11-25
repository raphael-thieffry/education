import java.util.Arrays;
import java.util.HashSet;

public class Criteres {
    HashSet<Ville> villes;
    double upDebMin;
    double downDebMin;
    double debitlimitemin;
    public Criteres(double up, double down, Ville[] villesArg, double debitlimitemin) {
        /**
         * @param up: upDebMin
         * @param down: downDebMin
         * @param villesArg: villes
         */
        villes = new HashSet<Ville>(Arrays.asList(villesArg));
        upDebMin = up;
        downDebMin = down;
        this.debitlimitemin = debitlimitemin;
    }
    public void ajouteVille(Ville ville) {
        villes.add(ville);
    }
    public void setDebMin(double up, double down) {
        upDebMin = up;
        downDebMin = down;
    }
    public String toString() {
        String res = "Villes :\n";
        for(Ville ville : villes) {
            res += "\t" + ville.toString() + "\n";
        }
        res += "Debits minimum :\n";
        res += "\tUpload speed mini : " + upDebMin + "\n";
        res += "\tDownload speed mini : " + downDebMin + "\n";
        return res;
    }

    /**
     * @param bien: bien
     * @return true if the criteria are respected
     */
    public boolean estValide(Bien bien) {
        double upDeb = bien.minimumDebit(true);
        double downDeb = bien.minimumDebit(false);
        /*System.out.println("\t"+ upDeb + " >=? " + upDebMin );
        System.out.println("\t"+ downDeb + " >=? " + downDebMin );*/
        //check if the city is in the list
        boolean cityInList = false;
        for (Ville ville : villes) {
            if (ville.equals(bien.ville)) {
                cityInList = true;
            }
        }

        boolean debitlimite = bien.dataMaxLimitPMonth<0 || bien.dataMaxLimitPMonth>=debitlimitemin;

        return cityInList && (upDeb >= upDebMin) && (downDeb >= downDebMin) && debitlimite;
    }
}