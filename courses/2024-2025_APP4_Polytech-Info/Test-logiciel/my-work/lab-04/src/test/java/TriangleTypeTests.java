import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

import static org.junit.Assert.*;
//import Triangle;

public class TriangleTypeTests {
    @ParameterizedTest
    @MethodSource("triangleTypeProvider")
    void testQ31(double a, Triangle.Type expected) {
        double side2 = 4; //fixés
        double side3 = 3;
        assertEquals(expected, Triangle.triangleTypeV1(a, side2, side3));
    }

    static Stream<Arguments> triangleTypeProvider() {
        return Stream.of(
                Arguments.of(5.0, Triangle.Type.SCALENE),
                Arguments.of(4.2, Triangle.Type.INVALID),
                Arguments.of(-5.0, Triangle.Type.INVALID),
                Arguments.of(-4.2, Triangle.Type.INVALID),
                Arguments.of(0, Triangle.Type.INVALID)
        );
    }

    @ParameterizedTest
    @MethodSource("triangleTypeProvider2")
    void testQ6(double a, double b, double c, Triangle.Type expected) {
        assertEquals(expected, Triangle.triangleTypeV1(a, b, c));
    }

    static Stream<Arguments> triangleTypeProvider2() {
        return Stream.of(
                //pairwise
                Arguments.of(5.0, 5.0, 3.0, Triangle.Type.ISOSCELES),
                Arguments.of(-5.0, 0.0, 5.0, Triangle.Type.INVALID),
                Arguments.of(0.0, 0.0, 0.0, Triangle.Type.INVALID),
                Arguments.of(-5.0, -5.0, -5.0, Triangle.Type.INVALID),
                Arguments.of(5.0, 4.0, 0.0, Triangle.Type.INVALID),
                Arguments.of(5.0, 4.0, 3.0, Triangle.Type.INVALID),
                Arguments.of(5.0, -4.0, 4.0, Triangle.Type.INVALID),
                );
    }
}
