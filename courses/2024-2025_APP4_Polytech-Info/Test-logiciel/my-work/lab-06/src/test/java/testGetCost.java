import ecommerce.ClientI;
import ecommerce.OrderI;
import ecommerce.Shipping;
import org.junit.jupiter.api.Test;

import java.util.Collection;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class testGetCost {
    ClientI jeand = new ClientI() {
        @Override
        public String getName() {
            return "Jean Dupont";
        }

        @Override
        public boolean hasPremiumAccount() {
            return false;
        }

        @Override
        public String getDeliveryStreetAddress() {
            return "69 rue des Potiers";
        }

        @Override
        public String getDeliveryCountry() {
            return "France";
        }

        @Override
        public int getDeliveryZipcode() {
            return 69000;
        }
    };
    ClientI vladimir = new ClientI() {
        @Override
        public String getName() {
            return "Vladimir Poutine";
        }

        @Override
        public boolean hasPremiumAccount() {
            return true;
        }

        @Override
        public String getDeliveryStreetAddress() {
            return "42 rue du Kremelin";
        }

        @Override
        public String getDeliveryCountry() {
            return "Russie";
        }

        @Override
        public int getDeliveryZipcode() {
            return 42696;
        }
    };
    //France outre mer, tres gros zicode, Premium, grande valeur, special
    ClientI bayrou = new ClientI() {
        @Override
        public String getName() {
            return "François Bayrou";
        }

        @Override
        public boolean hasPremiumAccount() {
            return true;
        }

        @Override
        public String getDeliveryStreetAddress() {
            return "16 rue des tropiques";
        }

        @Override
        public String getDeliveryCountry() {
            return "France";
        }

        @Override
        public int getDeliveryZipcode() {
            return 974000;
        }
    };
    //Etranger, tres petit zicode, pas Premium, petite valeur, normal
    ClientI gunther = new ClientI() {
        @Override
        public String getName() {
            return "Gunther Steiner";
        }

        @Override
        public boolean hasPremiumAccount() {
            return false;
        }

        @Override
        public String getDeliveryStreetAddress() {
            return "16 an der kartoffel salat alle";
        }

        @Override
        public String getDeliveryCountry() {
            return "Allemagne";
        }

        @Override
        public int getDeliveryZipcode() {
            return 12;
        }
    };

    OrderI aucunavantage = new OrderI() {
        @Override
        public double getWeight() {
            return 10;
        }

        @Override
        public int getValue() {
            return 10;
        }

        @Override
        public Collection<Object> getProducts() {
            return List.of();
        }

        @Override
        public boolean hasSpecialShippingDiscount() {
            return false;
        }
    };
    OrderI avecavantage = new OrderI() {
        @Override
        public double getWeight() {
            return 10;
        }

        @Override
        public int getValue() {
            return 200;
        }

        @Override
        public Collection<Object> getProducts() {
            return List.of();
        }

        @Override
        public boolean hasSpecialShippingDiscount() {
            return true;
        }
    };

    OrderI orderBuilder(int value, boolean ssd){
        return new OrderI() {
            @Override
            public double getWeight() {
                return 10;
            }

            @Override
            public int getValue() {
                return value;
            }

            @Override
            public Collection<Object> getProducts() {
                return List.of();
            }

            @Override
            public boolean hasSpecialShippingDiscount() {
                return ssd;
            }
        };
    }

    @Test
    void question2_1(){
        //1 : True; 2 : False
        Shipping shipping = new Shipping(jeand, aucunavantage);
        assertEquals(30, shipping.getCost());
    }
    @Test
    void question2_2(){
        //1 : False; 2 : True
        Shipping shipping = new Shipping(vladimir, avecavantage);
        assertEquals(35, shipping.getCost());
    }

    @Test
    void question3_1(){
        //Toutes les conditions à vrai
        Shipping shipping = new Shipping(bayrou, avecavantage);
        assertEquals(35, shipping.getCost());
    }
    @Test
    void question3_2(){
        //Toutes les conditions à faux
        Shipping shipping = new Shipping(gunther, aucunavantage);
        assertEquals(45, shipping.getCost());
    }
    @Test
    void mcdc1(){
        Shipping shipping = new Shipping(gunther, orderBuilder(10, true));
        assertEquals(35, shipping.getCost());
    }
    @Test
    void mcdc2(){
        Shipping shipping = new Shipping(vladimir, orderBuilder(10, true));
        assertEquals(35, shipping.getCost());
    }
    @Test
    void mcdc3(){
        Shipping shipping = new Shipping(jeand, orderBuilder(200, true));
        assertEquals(35, shipping.getCost());
    }
}
