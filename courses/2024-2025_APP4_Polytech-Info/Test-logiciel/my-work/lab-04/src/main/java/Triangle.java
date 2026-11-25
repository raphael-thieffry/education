import static java.lang.Double.max;
import static java.lang.Math.min;

/**
 * Classe à tester pour l'exercice 1.
 */
public class Triangle {

    private Triangle() {}

    /**
     * Type de triangles, suivant le nombre de côtés de même longueur
     */
    public enum Type {
        /**
         * Un triangle dont les trois côtés sont égaux
         */
        EQUILATERAL,
        /**
         * Un triangle dont deux côtés exactement sont égaux
         */
        ISOSCELES,
        /**
         * Un triangle dont les trois côtés sont distincts
         */
        SCALENE,
        /**
         * Les côtés ne correspondent pas à un triangle en géométrie euclidienne
         */
        INVALID
    }

    // le code est obscurci afin de forcer les étudiants à faire des tests boîte noire, ils n'auront accès qu'à la
    // version compilée et à la javadoc.

    /**
     * Retourne le type d'un triangle décrit par la longueur de ses trois côtés.
     * <br/>Cette première implémentation <strong>contient des défauts</strong> qui sont détectables avec des tests issus d'un partionnement
     * basé sur l'interface
     *
     * @param side1 la longueur du côté 1
     * @param side2 la longueur du côté 2
     * @param side3 la longueur du côté 3
     * @return le type du triangle, ou INVALID si les longueurs ne correspondent pas à un triangle en géométrie
     * euclidienne
     */
    public static Type triangleTypeV1(double side1, double side2, double side3) {
        // cette version contient des défauts qui ne dépendent que d'une variable d'entrée (pas de test de finitude par exemple)
        return c(side1, side2, side3) ? a(side1, side2, side3) : Type.INVALID;
    }

    /**
     * Retourne le type d'un triangle décrit par la longueur de ses trois côtés.
     * <br/>Cette deuxième implémentation <strong>contient des défauts</strong> qui sont détectables avec des tests issus d'un partionnement
     * basé sur la fonctionnalité.
     *
     * @param side1 la longueur du côté 1
     * @param side2 la longueur du côté 2
     * @param side3 la longueur du côté 3
     * @return le type du triangle, ou INVALID si les longueurs ne correspondent pas à un triangle en géométrie
     * euclidienne
     */
    public static Type triangleTypeV2(double side1, double side2, double side3) {
        // cette version contient des défauts qui ne peuvent être détectés qu'en choisissant les trois variables
        // d'entrée simultanément (pas de vérification que les longueurs forment un triangle par exemple)
        return c(side1, side2, side3) && d(side1, side2, side3) ? a(side1, side2, side3) : Type.INVALID;
    }

    /**
     * Retourne le type d'un triangle décrit par la longueur de ses trois côtés.
     * <br/>Cette dernière implémentation est correcte, elle doit passer les différents tests.
     *
     * @param side1 la longueur du côté 1
     * @param side2 la longueur du côté 2
     * @param side3 la longueur du côté 3
     * @return le type du triangle, ou INVALID si les longueurs ne correspondent pas à un triangle en géométrie
     * euclidienne
     */
    public static Type triangleTypeV3(double side1, double side2, double side3) {
        return c(side1, side2, side3) && d(side1, side2, side3) && e(side1, side2, side3) ? a(side1, side2, side3) : Type.INVALID;
    }

    private static Type a(double var1, double var2, double var3) {
        /* équivalent à
        if (var1 == var2 && var2 == var3) {
            return Type.EQUILATERAL;
        } else if (var1 == var2 || var2 == var3 || var1 == var3) {
            return Type.ISOSCELES;
        } else {
            return Type.SCALENE;
        }*/
        boolean var4 = var1 == var2;
        boolean var5 = var3 == var2;
        if (var4 == var5) {
            return var4 ? Type.EQUILATERAL : (var1 == var3 ? Type.ISOSCELES : Type.SCALENE);
        } else {
            return Type.ISOSCELES;
        }
    }

    private static boolean c(double var1, double var2, double var3) {
        // équivalent à var1 >= 0 && var2 >= 0 && var3 >= 0
        return min(var1, min(var2, var3)) >= 0.0;
    }

    private static boolean d(double var1, double var2, double var3) {
        // équivalent à isFinite(var1) && isFinite(var2) && isFinite(var3) à condition que var1 >= 0 && var2 >= var3 >= 0
        return max(var1, max(var2, var3)) <= Double.MAX_VALUE;
    }

    private static boolean e(double var1, double var2, double var3)  {
        // équivalent à var1 <= var2 + var3 && var2 <= var1 + var3 && var3 <= var1 + var2
        return 2.0 * max(var1, max(var2, var3)) <= var1 + var2 + var3;
    }

}