package LinAlg;

public class LinAlg {
    /**
     * Calcule le produit scalaire de deux vecteurs.
     * @param vectorA le premier vecteur
     * @param vectorB le deuxième vecteur
     * @return le produit scalaire de vectorA et vectorB
     * @throws IllegalArgumentException si les vecteurs n'ont pas la même longueur ou si l'un des vecteurs est null
     */
    public static int dotProduct(int[] vectorA, int[] vectorB) {
        if(vectorA == null || vectorB == null) {
            throw new IllegalArgumentException("Les vecteurs ne peuvent pas être null");
        }
        if (vectorA.length != vectorB.length) {
            throw new IllegalArgumentException("Les vecteurs n'ont pas la même longueur");
        }
        int result = 0;
        for (int i = 0; i < vectorA.length; i++) {
            result += vectorA[i] * vectorB[i];
        }
        return result;
    }

    /**
     * Ajoute deux vecteurs.
     * @param vectorA le premier vecteur
     * @param vectorB le deuxième vecteur
     * @return le vecteur somme de vectorA et vectorB
     * @throws IllegalArgumentException si les vecteurs n'ont pas la même longueur ou si l'un des vecteurs est null
     */
    public static int[] add(int[] vectorA, int[] vectorB) {
        if (vectorA == null || vectorB == null) {
            throw new IllegalArgumentException("Les vecteurs ne peuvent pas être null");
        }
        if (vectorA.length != vectorB.length) {
            throw new IllegalArgumentException("Les vecteurs n'ont pas la même longueur");
        }
        int[] result = new int[vectorA.length];
        for (int i = 0; i < vectorA.length; i++) {
            result[i] = vectorA[i] + vectorB[i];
        }
        return result;
    }

    /**
     * Multiplie un vecteur par un scalaire.
     * @param vector le vecteur
     * @param scalar le scalaire
     * @return le vecteur produit de vector et scalar
     * @throws IllegalArgumentException si le vecteur est null
     */
    public static int[] scalarMult(int[] vector, int scalar) {
        if (vector == null) {
            throw new IllegalArgumentException("Le vecteur ne peut pas être null");
        }
        int[] result = new int[vector.length];
        for (int i = 0; i < vector.length; i++) {
            result[i] = vector[i] * scalar;
        }
        return result;
    }
}
