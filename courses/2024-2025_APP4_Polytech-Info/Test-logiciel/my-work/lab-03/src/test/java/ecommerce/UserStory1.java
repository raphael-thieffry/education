package ecommerce;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.math.BigDecimal;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class UserStory1 {
    Client c;


    @BeforeEach
    void setUpBeforeEach() {
        //setup préfixe pour les tests
        c = new Client("John", "Doe");
    }

    @Test
    void testAddToCart() {
        //Valeurs du cas de test
        Product p1 = new Product("Laptop", new BigDecimal(1000));   //x2
        Product p2 = new Product("Phone", new BigDecimal(500));     //x1

        //Postfixe (= valeurs "manuelles" deduites de la spec)
        List whatsinthecart = List.of(p1, p1, p2);

        //Proprétés à verifier (+ postfixes en dur du coup)
        assertTrue(c.getShoppingCart().add(p1));
        assertTrue(c.getShoppingCart().add(p1));
        assertTrue(c.getShoppingCart().add(p2));
        assertIterableEquals(c.getShoppingCart(), whatsinthecart);
        assertEquals(c.getShoppingCart().getArity(p1), 2);
        assertEquals(c.getShoppingCart().getArity(p2), 1);
        assertEquals(c.getShoppingCart().size(), 3);
        assertThrows(NullPointerException.class, () -> c.getShoppingCart().add(null));
    }





}
