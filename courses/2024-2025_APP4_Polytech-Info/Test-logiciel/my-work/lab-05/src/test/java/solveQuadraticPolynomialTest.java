import org.junit.jupiter.api.Test;

import java.util.Vector;

import static org.junit.Assert.assertEquals;


public class solveQuadraticPolynomialTest {
    @Test
    void TestCase1Q2(){
        //couverture d'instructions
        Vector<Double> s = new Vector<Double>();
        s.add(-2.0);
        assertEquals(TP5.solveQuadraticPolynomial(0, 1, 2), s);
    }
    @Test
    void TestCase2Q2(){
        //couverture d'instruction
        Vector<Double> s = new Vector<Double>();
        s.add(1.0);
        s.add(-1.0);
        assertEquals(TP5.solveQuadraticPolynomial(1, 0, -1), s);
    }
    @Test
    void TestCase3Q3(){
        //prise en compte de la couverture par arcs
        Vector<Double> s = new Vector<Double>();
        assertEquals(TP5.solveQuadraticPolynomial(0, 0, -1), s);
    }
    @Test
    void TestCase4Q3(){
        //prise en compte de la couverture par arcs
        Vector<Double> s = new Vector<Double>();
        assertEquals(TP5.solveQuadraticPolynomial(-1, 0, -1), s);
    }
    @Test
    void TestCase5Q3(){
        //prise en compte de la couverture par arcs
        Vector<Double> s = new Vector<Double>();
        s.add(0.0);
        assertEquals(TP5.solveQuadraticPolynomial(1, 0, 0), s);
    }

}
