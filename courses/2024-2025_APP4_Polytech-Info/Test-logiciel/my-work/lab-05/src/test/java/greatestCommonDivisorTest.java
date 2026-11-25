import org.junit.jupiter.api.Test;

import java.util.Vector;

import static org.junit.Assert.assertEquals;


public class greatestCommonDivisorTest {
    @Test
    void TestCase1Q2(){
        //couverture d'arc (1, 3, 5, 6, 8)
        assertEquals(TP5.greatestCommonDivisor(9, 0), 9);
    }
    @Test
    void TestCase2Q2(){
        //couverture d'arc (1, 2, 3, 4, 5, 6, 7)
        assertEquals(TP5.greatestCommonDivisor(-2, -4), 2);
    }
    @Test
    void TestCase3Q5(){
        //couverture de chemin (1, 2, 3, 4, 5, 6, 8)
        // -> ce chemin n'est pas faisable, car si on passe par 4, on est forcé de faire un tour de boucle
    }
    @Test
    void TestCase4Q5(){
        //couverture de chemin (1, 3, 4, 5, 6, 8)
        // -> ce chemin n'est pas faisable, car si on passe par 4, on est forcé de faire un tour de boucle
    }
    @Test
    void TestCase5Q5(){
        //couverture de chemin (1, 2, 3, 5, 6, 8)
        assertEquals(TP5.greatestCommonDivisor(-2, 0), 2);
    }
    @Test
    void TestCase6Q5(){
        //couverture de chemin (1, 3, 4, 5, 6, 7)
        assertEquals(TP5.greatestCommonDivisor(2, -4), 2);
    }
    @Test
    void TestCase7Q5(){
        //couverture de chemin (1, 2, 3, 5, 6, 7)
        assertEquals(TP5.greatestCommonDivisor(-2, 4), 2);
    }
    @Test
    void TestCase8Q5(){
        //couverture de chemin (1, 3, 5, 6, 7), (6, 7, 6) et (7, 6, 8)
        assertEquals(TP5.greatestCommonDivisor(2, 4), 2);
    }
    @Test
    void TestCase9Q5(){
        //couverture de chemin (7, 6, 7) ie: plusieurs tours de boucle
        assertEquals(TP5.greatestCommonDivisor(13, 17), 1);
    }

}
