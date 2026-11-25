public class Colocataire {
    String username;
    String password;
    String nom;
    String prenom;
    String email;
    Colocataire(String username, String password, String nom, String prenom, String email) {
        if(username == null || password == null || nom == null || prenom == null || email == null) {
            throw new IllegalArgumentException("Arguments cannot be null");
        }
        if(username.length() == 0 || password.length() == 0 || nom.length() == 0 || prenom.length() == 0 || email.length() == 0) {
            throw new IllegalArgumentException("Arguments cannot be empty");
        }
        //check username no spaces
        if(username.contains(" ")) {
            throw new IllegalArgumentException("Username cannot contain spaces");
        }


        this.username = username;
        this.password = password;
        this.nom = nom;
        this.prenom = prenom;
        this.email = email;
    }
    public String toString() {
        return username + " ******* " + nom + " " + prenom + " " + email;
    }
}
