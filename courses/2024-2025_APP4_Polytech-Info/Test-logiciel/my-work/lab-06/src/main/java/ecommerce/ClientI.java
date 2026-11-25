package ecommerce;

/**
 * Cette interface correspond à un client.
 */
public interface ClientI {

    /**
     * Le nom du client
     * @return le nom du client
     */
    String getName();

    /**
     * Indique si le client a un compte premium
     * @return true si le client a un compte premium
     */
    boolean hasPremiumAccount();

    /**
     * La rue de l'adresse de livraison
     * @return la rue de l'adresse de livraison
     */
    String getDeliveryStreetAddress();

    /**
     * Le pays de l'adresse de livraison
     * @return Le pays de l'adresse de livraison
     */
    String getDeliveryCountry();

    /**
     * Le code postal de l'adresse de livraison
     * @return le code postal de l'adresse de livraison
     */
    int getDeliveryZipcode();


}
