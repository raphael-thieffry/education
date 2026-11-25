import java.time.LocalTime;
import java.util.Collection;
import java.util.HashSet;

import static java.time.temporal.ChronoUnit.SECONDS;

public class ProjetColocation {
    HashSet<Colocataire> colocataires;
    Criteres criteres;
    ListeBiens biens;
    boolean finished = false;

    /**
     * Constructeur : crée un projet
     * @param coloc : le colocataire créateur du projet
     * @param criteres : les critères du projet
     */
    ProjetColocation(Colocataire coloc, Criteres criteres) {
        colocataires = new HashSet<Colocataire>();
        this.biens = new ListeBiens();
        colocataires.add(coloc);
        this.criteres = criteres;
    }

    /**
     * Ajoute un coloc au projet
     * @param colocataire : une instance de la classe Colocataire
     */
    void ajouteColocataire(Colocataire colocataire) {
        colocataires.add(colocataire);
    }

    /**
     * renvoi un string formaté décrivant le projet
     * @return String : string formaté
     */
    public String toString() {
        String res = "Projet de colocation :\n";
        res += "Colocataires :\n";
        for(Colocataire coloc : colocataires) {
            res += coloc.toString() + "\n";
        }
        res += "Criteres :\n";
        res += criteres.toString() + "\n";
        res += "Biens :\n";
        res += biens.toString() + "\n";
        return res;
    }

    /**
     * Ajoute un bien au biens du projet
     * @param bien : une instance de la classe bien
     */
    public void ajouteBien(Bien bien) {
        biens.ajouteBien(bien);
    }


    /**
     * Met à jour la liste des biens en supprimant ceux qui ne sont plus disponibles ou qui ne répondent plus au critères si ils ont été modifiés.
     * @return : la liste des biens qui ont disparu depuis la dernière mise à jour
     */
    ListeBiens updateListeBiens() {
        return biens.update(criteres);

    }

    public ListeBiens getBiens() {
        return biens;
    }
    public HashSet<Ville> getVilles() {
        return criteres.villes;
    }
    public void setUploadSpeed(double speed) {
        criteres.upDebMin = speed;
    }
    public void setDownloadSpeed(double speed) {
        criteres.downDebMin = speed;
    }
    public void setDebitLimite(double speed) {
        criteres.debitlimitemin = speed;
    }

    /**
     * Ajoute une ville aux criteres du projet
     * @param ville : une ville sous la forme d'une instance de la classe ville
     */
    public void addVille(Ville ville){
        criteres.ajouteVille(ville);
    }

    /**
     * Enleve une ville des criteres du projet
     * @param ville : le nom de la ville à enlever
     * @throws IllegalArgumentException : si la ville n'est pas dans le projet
     */
    public void removeVille(String ville) throws IllegalArgumentException{
        for(Ville v : criteres.villes) {
            if(v.nom.equalsIgnoreCase(ville.trim())) {
                criteres.villes.remove(v);
                return;
            }
        }
        throw new IllegalArgumentException("This city does not exist");
    }

    /**
     * retire un bien du projet
     * @param bien : un Bien
     * @return boolean : si le retrait a reussi ou echoué
     */
    boolean removeBien(Bien bien) {
        return biens.remove(bien);
    }

    public boolean isFinished() {
        return finished;
    }
    public void finish() {
        finished = true;
    }
}
