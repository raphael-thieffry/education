import java.util.Vector;

public class TP5 {

    /**
     * Retourne un vecteur des racines réelles d'un polynôme de degré 2 ou moins, décrit par le coefficient de ses termes.
     * Pour un polynôme aX² + bX + c, cette méthode retourne un vecteur des valeurs de X pour lesquelles le polynôme vaut 0.
     * Cette méthode est aussi valable pour les polynômes de degré inférieur à 2, c'est-à-dire si a, ou a et b, valent
     * 0. Pour le polynôme nul, dont les racines sont l'ensemble des réels, un vecteur vide est retourné.
     *
     * @param a le coefficient du terme de degré 2 du polynôme
     * @param b le coefficient du terme de degré 1 du polynôme
     * @param c le coefficient du terme constant du polynôme
     * @return un vecteur des racines réelles du polynôme
     */
    public static Vector<Double> solveQuadraticPolynomial(double a, double b, double c) {
        Vector<Double> solutions = new Vector<>();
        if (a == 0.0) {
            if (b != 0.0) {
                solutions.add(-c/b);
            }
        } else {
            double delta = b * b - (4.0 * a * c);
            if (delta >= 0.0) {
                double r = Math.sqrt(delta);
                solutions.add((-b + r) / (2.0 * a));
                if (r != 0.0) {
                    solutions.add((-b - r) / (2.0 * a));
                }
            }
        }
        return solutions;
    }

    public static int greatestCommonDivisor(int a, int b) {
        if (a < 0) {
            a = -a;
        }
        if (b < 0) {
            b = -b;
        }
        int t;
        while (b != 0) {
            t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

}
