package ecommerce;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.math.BigDecimal;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertIterableEquals;

public class UserStory2 {
    Client c;
    Product p1;
    Product p2;

    @BeforeEach
    void setUpBeforeEach() {
        //setup préfixe pour les tests
        c = new Client("John", "Doe");
        p1 = new Product("Laptop", new BigDecimal(1000));
        p2 = new Product("Phone", new BigDecimal(500));
        c.getShoppingCart().add(p1);
        c.getShoppingCart().add(p1);
        c.getShoppingCart().add(p2);
    }

    @Test
    void testAddToCart() {
        //Valeurs du cas de test : p1, p2

        //Valeurs postfixes de sortie
        Boolean b1 = c.getShoppingCart().remove(p1); //true
        Boolean b2 = c.getShoppingCart().remove(p2);//true
        Boolean b3 = c.getShoppingCart().remove(p2);//false
        Boolean b4 = c.getShoppingCart().remove(null);//false

        //Postfixe de verification
        List whatsinthecart = List.of(p1);

        //Proprétés à verifier
        assertEquals(c.getShoppingCart().size(), 1);
        assertEquals(c.getShoppingCart().getArity(p1), 1);
        assertEquals(c.getShoppingCart().getArity(p2), 0);
        assertIterableEquals(c.getShoppingCart(), List.of(p1));
        assertEquals(b1, true);
        assertEquals(b2, true);
        assertEquals(b3, false);
        assertEquals(b4, false);
    }





}
