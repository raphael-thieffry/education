import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import LinAlg.*;

public class TestLinAlg {
    @ParameterizedTest
    @MethodSource("entreesValides")
    void testValide(int[] x, int[] y, int z) {
        assertEquals(LinAlg.dotProduct(x, y), z);
    }
    static Stream<Arguments> entreesValides() {
        return Stream.of(
                Arguments.of(new int[]{1, 2, 3}, new int[]{4, 5, 6}, 32),
                Arguments.of(new int[]{1, 2, 3}, new int[]{1, 2, 3}, 14),
                Arguments.of(new int[]{1, 2, 3}, new int[]{0, 0, 0}, 0),
                Arguments.of(new int[]{0, 0, 0}, new int[]{0, 0, 0}, 0),
                Arguments.of(new int[]{0, 0, 0}, new int[]{1, 2, 3}, 0),
                Arguments.of(new int[]{1, 2, 3}, new int[]{0, 0, 0}, 0),
                Arguments.of(new int[]{-1, 2, -3}, new int[]{1, -2, 3}, -14)
        );
    }

    @ParameterizedTest
    @MethodSource("troisVectsEtUnEntier")
    void testProprietesGenerales(int[] x, int[] y, int[] z, int alpha) {
        assertEquals(LinAlg.dotProduct(x, y), LinAlg.dotProduct(y, x));

        //optionnelles ci dessous, car ça utilise des fonctions qui n'étaient pas demandées
        assertEquals(LinAlg.dotProduct(x, LinAlg.add(y, z)), LinAlg.dotProduct(x, y) + LinAlg.dotProduct(x, z));
        assertEquals(LinAlg.dotProduct(x, LinAlg.scalarMult(y, alpha)), alpha * LinAlg.dotProduct(x, y));
    }
    static Stream<Arguments> troisVectsEtUnEntier(){
        return Stream.of(
                Arguments.of(new int[]{1, 2, 3}, new int[]{4, 5, 6}, new int[]{7, 8, 9}, 45),
                Arguments.of(new int[]{1, 2, 3}, new int[]{1, 2, 3}, new int[]{1, 2, 3}, 56),
                Arguments.of(new int[]{1, 2, 3}, new int[]{0, 0, 0}, new int[]{0, 0, 0}, 76),
                Arguments.of(new int[]{0, 0, 0}, new int[]{0, 0, 0}, new int[]{0, 0, 0}, -87),
                Arguments.of(new int[]{0, 0, 0}, new int[]{1, 2, 3}, new int[]{0, 0, 0}, 0),
                Arguments.of(new int[]{1, 2, 3}, new int[]{0, 0, 0}, new int[]{0, 0, 0}, 10),
                Arguments.of(new int[]{-1, 2, -3}, new int[]{1, -2, 3}, new int[]{1, -2, 3}, -1),
                Arguments.of(new int[]{}, new int[]{}, new int[]{}, -1)
        );
    }

    @ParameterizedTest
    @MethodSource("entreesInvalides")
    void testThrows(int[] x, int[] y) {
        assertThrows(IllegalArgumentException.class, ()->LinAlg.dotProduct(x, y));
    }
    static Stream<Arguments> entreesInvalides() {
        return Stream.of(
                Arguments.of(new int[]{1, 2, 3}, new int[]{4, 5}),
                Arguments.of(new int[]{1, 2, 3}, new int[]{1, 2, 3, 6})
        );
    }
}
