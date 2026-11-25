public class Ville {
    /**
     * Ville is a class that represents a city.
     * It is just some sort of format, and it does not
     * mean that the city is in the database.
     */
    String nom;
    double latitude;
    double longitude;
    String insee;
    public Ville(String nom, double latitude, double longitude, String insee) {
        /**
         * @param nom: nom
         * @param latitude: latitude
         * @param longitude: longitude
         * @param insee: insee
         */
        this.nom = nom;
        this.latitude = latitude;
        this.longitude = longitude;
        this.insee = insee;
    }
    public String toString() {
        /**
         * @return: a string representation of the city
         */
        return nom + " (" + latitude + ", " + longitude + ") " + insee;
    }
    public boolean equals(Ville ville) {
        /**
         * @param ville: ville
         * @return: true if the two cities are the same
         */
        return nom.equals(ville.nom) && insee.equals(ville.insee);
    }
}
