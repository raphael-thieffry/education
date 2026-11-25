import java.io.IOException;
import java.text.ParseException;
import java.util.HashSet;

public class Model {

    /**
     * le modèle
     **/
    HashSet<ProjetColocation> projets; //may be replaced by sqlite soon
    HashSet<Colocataire> utilisateurs; //may be replaced by sqlite soon
    ProjetColocation projetCourant;
    private Colocataire user;
    API api;

    /**
     * Constructeur : construit le modèle
     * @throws IOException : en cas d'erreur à la création de l'API
     */
    public Model() throws IOException{
        projets = new HashSet<ProjetColocation>();
        utilisateurs = new HashSet<Colocataire>();
        projetCourant = null;
        user = null;
        System.out.println(System.getProperty("user.dir"));
        api = new API("base_imb_33.csv", "actuel_33.csv");
    }

    /**
     * Comme son nom l'indique, met à jour l'utilisateur courant
     * @param user : un Collocataire, le nouveau user
     */
    private void setCurrentUser(Colocataire user) {
        this.user = user;
    }

    /**
     * getter pour l'utilisateur courant
     * @return Collocataire : l'user courant
     */
    public Colocataire getCurrentUser() {
        return user;
    }

    /**
     * ajoute un utilisateur au projet courant
     * @param colocataire : instance de la classe colocataire
     */
    public void ajouteColocataireProjetCourant(Colocataire colocataire) {
        projetCourant.ajouteColocataire(colocataire);
    }

    /**
     * verifie si un utilisateur existe
     * @param username : string, le nom d'utilisateur
     * @return boolean : est ce que ça existe
     */
    private boolean usernameExists(String username) {
        for(Colocataire user : utilisateurs) {
            if(user.username.equals(username)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Connecte un utilisateur sur le programme à partir de la liste d'utilisateur du constructeur
     * @param username : nom d'utilisateur
     * @param password : mot de passe
     * @return boolean : la connection a fonctionné ou non
     */
    public boolean login(String username, String password) {
        for(Colocataire user : utilisateurs) {
            if(user.username.equals(username) && user.password.equals(password)) {
                setCurrentUser(user);
                return true;
            }
        }
        return false;
    }

    /**
     * Inscrit quelqu'un
     * @param username : nom d'utilisateur
     * @param password : mot de passe
     * @param nom : nom
     * @param prenom : prénom
     * @param email : email
     * @throws IllegalArgumentException : si l'utilisateur existe déja
     */
    public void register(String username, String password,  String nom, String prenom, String email) throws IllegalArgumentException {
        register(new Colocataire(username, password, nom, prenom, email));
    }

    /**
     * Inscrit un utilisateur
     * @param user : une instance de la classe Colocataire
     * @throws IllegalArgumentException : si le nom d'utilisateur existe déja
     */
    public void register(Colocataire user) throws IllegalArgumentException {
        if(usernameExists(user.username)) {
            throw new IllegalArgumentException("Registration failed : Username already exists, try log in ?");
        }
        utilisateurs.add(user);
    }

    /**
     * déconnecte l'utilisateur courant
     */
    public void disconnect() {
        user = null;
        projetCourant = null;
    }

    /**
     * Créé un nouveau projet et le rajoute à la liste
     * @param crit : une instance de Critère pour connaitre les critères du projet
     * @throws IllegalArgumentException : si l'utilisateur a deja un projet
     */
    public void nouveauProjet(Criteres crit) throws IllegalArgumentException {
        /**
         * On ne peut pas créer un nouveau projet si l'utilisateur est déjà
         * dans un projet. Set le projet courant à ce nouveau projet.
         */
         for(ProjetColocation projet : projets) {
             if(projet.colocataires.contains(user)) {
                 throw new IllegalArgumentException("The user is already in a project!");
                 /*projetCourant = projet;
                 return;*/
             }
         }
         projetCourant = new ProjetColocation(user, crit);
         projets.add(projetCourant);
    }

    /**
     * Crée un nouveau projet à partir d'arguments "atomiques" plutot que Critères
     * @param up : debit montant minimum utilisateur
     * @param down : debit descendant minimum utilisateur
     * @param villesArg : les villes choisies par l'utilisateur
     * @param debitlimitemin : le debit limite minimum attendu
     * @throws IllegalArgumentException : si l'utilisateur est déja dans un projet
     */
    public void nouveauProjet(double up, double down, Ville[] villesArg, double debitlimitemin) throws IllegalArgumentException {
        nouveauProjet(new Criteres(up, down, villesArg, debitlimitemin));
    }
    /**
     * @return boolean : True si l'utilisateur est dans un projet, false sinon.
     */
    public boolean userHasProject() {
        for(ProjetColocation projet : projets) {
            if(projet.colocataires.contains(user)) {
                return true;
            }
        }
        return false;
    }

    /**
     * set le projet courrant de l'utilisateur courrant comme son projet déja existant.
     * @throws IllegalArgumentException : si son projet existant n'existe pas
     */
    public void setExistingAsProjetCourant() throws IllegalArgumentException{
        for(ProjetColocation projet : projets) {
            if(projet.colocataires.contains(user)) {
                projetCourant = projet;
                return;
            }
        }
        throw new IllegalArgumentException("The user isn't in any project!");
    }

    /**
     * Appelle l'API pour recupérer une ville à partir d'un string correctement formaté (trimé)
     * @param ville : le nom de la ville ou code insee correspondant, trimé
     * @return Ville : la ville en s'étant assuré qu'elle existe dans le CSV
     */
    Ville getVille(String ville) {
        try {
            return api.getVilleDetails(ville);
        } catch (IOException e) {
            System.out.println("Error while getting ville details : " + e.getMessage());
            return null;
        } catch (ParseException e) {
            System.out.println("The CSV given isn't well formatted, and thus the program can't check if the city is in the database : " + e.getMessage());
            return null;
        }
    }

    /**
     * Getter du projet courant
     * @return projetCourant : le projet courant
     */
    public ProjetColocation getProjet() {
        return projetCourant;
    }

    /**
     * setter projet courant
     * @param projet : le projet
     */
    public void setProjetCourant(ProjetColocation projet) {
        projetCourant = projet;
    }

    /**
     * L'utilisateur courant quitte son projet. Le projet est supprimé si il était le dernier utilisateur dedans.
     * @throws IllegalArgumentException : si il n'est pas dans un projet
     */
    public void leaveProjet() throws IllegalArgumentException{
        /*
         * On ne peut pas quitter un projet si on n'est pas dans un projet.
         * Si on est seul on supprimme
         */
        if(projetCourant == null) {
            throw new IllegalArgumentException("You must select a project first! (And create one if you don't have any)");
        }
        projetCourant.colocataires.remove(user);
        if(projetCourant.colocataires.size() == 0) {
            this.supprimerProjet();
        }
        projetCourant = null;
    }

    /**
     * Supprime le projet courant
     * @throws IllegalArgumentException :si le projet n'existe pas
     */
    public void supprimerProjet() throws IllegalArgumentException{
        /*
         * On ne peut pas supprimer un projet si on n'est pas dans un projet.
         */
        if(projetCourant == null) {
            throw new IllegalArgumentException("You must select a project first! (And create one if you don't have any)");
        }
        projets.remove(projetCourant);
        projetCourant = null;
    }

    /**
     * Appelle l'api pour donner un bien au hasard des villes choisies par l'utilisateur
     * @return Bien : un bien aleatoire des villes du projet
     * @throws IOException :  si il y a une erreur de lecture les csv
     * @throws ParseException : si le csv est mal formaté
     * @throws IllegalArgumentException : Si l'utilisateur n'a pas de projet
     */
    public Bien rechercherBienDansMesVilles() throws IOException, ParseException, IllegalArgumentException{
        /*
         * On cherche un bien dans les villes du projet courant.
         * Ne verifie pas les critères internet encore, mais le Bien content déja les données
         */
        if(projetCourant == null) {
            throw new IllegalArgumentException("You must select a project first! (And create one if you don't have any)");
        }
        return api.randomBien(projetCourant.criteres.villes);
    }
    /**
     * Verifie si le bien repond aux criteres du projet courant
     * et n'est pas sature
     * @param bien : le bien à tester (ne pas oublier qu'il s'agit d'un logement "unique", ie d'un appartement. le choix de la configuration internet du bien s'est faite aléatoirement dans api.randomBien() )
     * @return : true si le bien repond aux criteres du projet courant
     */
    public boolean repondCriteres(Bien bien) throws IllegalArgumentException{
        if(projetCourant == null) {
            throw new IllegalArgumentException("You must select a project first! (And create one if you don't have any)");
        }
        return projetCourant.criteres.estValide(bien) && !bien.sature;
    }

    /**
     * ajoute Bien au Projet
     * @param bien : un bien
     * @throws IllegalArgumentException : l'utilisateur n'a pas de projet
     */
    public void ajouteBienProjet(Bien bien) throws IllegalArgumentException {
        if(projetCourant == null) {
            throw new IllegalArgumentException("You must select a project first! (And create one if you don't have any)");
        }
        projetCourant.ajouteBien(bien);
    }
    /**
     * Met à jour la liste des biens du projet courant
     * @return : la liste des biens qui ont disparu depuis la dernière mise à jour
     */
    public ListeBiens updateListeBiens() throws IllegalArgumentException{
        if(projetCourant == null) {
            throw new IllegalArgumentException("You must select a project first! (And create one if you don't have any)");
        }
        return projetCourant.updateListeBiens();
    }

    /**
     * Ajoute un colocataire au projet courant
     * @param colname : le nom d'utilisateur du colocataire qu'on souhaite ajouter
     */
    public void addFlatmate(String colname) throws IllegalArgumentException{
        if(projetCourant == null) {
            throw new IllegalArgumentException("You must select a project first! (And create one if you don't have any)");
        }
        if(!this.usernameExists(colname)){
            throw new IllegalArgumentException("The username doesn't exist!");
        }
        if(projetCourant.colocataires.contains(this.getColocataire(colname))){
            throw new IllegalArgumentException("The user is already in the project!");
        }
        projetCourant.colocataires.add(this.getColocataire(colname));
    }

    /**
     * Renvoie le coloataire choisi
     * @param colname : le nom d'utilisateur du colocataire
     * @return : le colocataire choisi
     */
    private Colocataire getColocataire(String colname) {
        for(Colocataire coloc : utilisateurs){
            if(coloc.username.equals(colname)){
                return coloc;
            }
        }
        return null;
    }
}
