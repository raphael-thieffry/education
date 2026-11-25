package ecommerce;

/**
 * Cette classe correspond à la livraison d'une commande pour un client
 */
public class Shipping {

    private final ClientI client;

    private final OrderI order;

    private static final int DOMESTIC_RATE = 3;

    private static final int INTERNATIONAL_RATE = 4;

    private static final int INTERNATIONAL_FLAT_COST = 5;

    private static final int PREMIUM_DISCOUNT_MINIMUM = 100;

    private static final int DISCOUNT_VALUE = 10;

    private static final int METROPOLITAN_ZIPCODE_LIMIT = 95;

    /**
     * Construit une livraison pour une commande et un client spécifiés
     * @param client le client
     * @param order la commande
     */
    public Shipping(ClientI client, OrderI order) {
        this.client = client;
        this.order = order;
    }

    /**
     * Retourne le client de la livraison
     * @return le client de la livraison
     */
    public ClientI getClient() {
        return client;
    }

    /**
     * Retourne la commande de la livraison
     * @return la commande de la livraison
     */
    public OrderI getOrder() {
        return order;
    }

    /**
     * Retourne le coût de la livraison
     * @return le coût de la livraison
     */
    public int getCost() {
        int cost;
        if (client.getDeliveryCountry().equalsIgnoreCase("france")
                && client.getDeliveryZipcode() / 1000 <= METROPOLITAN_ZIPCODE_LIMIT) {
            cost = DOMESTIC_RATE * (int) Math.ceil(order.getWeight());
        } else {
            cost = INTERNATIONAL_FLAT_COST + INTERNATIONAL_RATE * (int) Math.ceil(order.getWeight());
        }
        if ((client.hasPremiumAccount() && order.getValue() >= PREMIUM_DISCOUNT_MINIMUM)
                || order.hasSpecialShippingDiscount()) {
            cost = Math.max(0, cost - DISCOUNT_VALUE);
        }
        return cost;
    }
}
