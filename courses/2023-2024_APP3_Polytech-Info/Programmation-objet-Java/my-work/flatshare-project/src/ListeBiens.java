import java.time.LocalTime;
import java.util.ArrayList;

public class ListeBiens extends ArrayList<Bien> {
    LocalTime lastdisparition = null;

    public ListeBiens() {
        super();
    }
    public void ajouteBien(Bien bien) {
        add(bien);
        if(lastdisparition == null) { //start timer on first addition
            lastdisparition = LocalTime.now();
        }
    }
    public void supprimeBien(Bien bien) {
        remove(bien);
    }
    public String toString() {
        sort(Bien::compareTo);
        String res = "[\n";
        int i = 1;
        for (Bien bien : this) {
            res += "Bien n°"+i+" : \n"+(bien.note()>=0?("Noté "+bien.note()+":\n"):"") + bien + ", \n";
            i++;
        }
        return res + "]";
    }
    ListeBiens update(Criteres criteres) {
        /**
         * Met à jour la liste des biens en supprimant ceux qui ne sont plus disponibles ou qui ne répondent plus au critères si ils ont été modifiés.
         * @return : la liste des biens qui ont disparu depuis la dernière mise à jour
         */
        if(lastdisparition == null) { //start timer on first addition
            return new ListeBiens();
        }
        ListeBiens res = new ListeBiens();
        for (Bien bien : this) {
            if (!criteres.estValide(bien) || !bien.estDisponible(this.size())) {
                res.ajouteBien(bien);
            }
        }
        removeAll(res);
        return res;
    }
}
