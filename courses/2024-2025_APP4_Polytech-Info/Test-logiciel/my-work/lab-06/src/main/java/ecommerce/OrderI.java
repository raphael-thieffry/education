package ecommerce;

import java.util.Collection;

/**
 * Cette interface correspond à une commande.
 */
public interface OrderI {

    /**
     * Le poids de la commande, en kilogrammes
     * @return le poids de la commande
     */
    double getWeight();

    /**
     * La valeur des articles de la commande
     * @return la valeur des articles de la commande
     */
    int getValue();

    /**
     * Les articles de la commande
     * @return les articles de la commande
     */
    Collection<Object> getProducts();

    /**
     * Indique si la commande bénéficie d'une remise exceptionnelle sur la livraison
     * @return true si la commande bénéficie d'une remise exceptionnelle sur la livraison
     */
    boolean hasSpecialShippingDiscount();
}
