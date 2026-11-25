
/**
 * Classe à tester pour l'exercice 2.
 */
public class StringUtility {

    private StringUtility() {};

    /**
     * Retourne une chaîne de caractère semblable à celle spécifiée, de laquelle auront été retirées toutes les balises
     * XML.
     * <br/>Est considérée comme balise XML toute sous-chaîne de caractères commençant par le caractère &lt; et
     * finissant par le caractère &gt;
     * <br/>Cette implémentation <strong>contient un défaut</strong>.
     * @param string la chaîne de caractère à modifier
     * @return une chaîne de caractère, sans balises XML
     */
    public static String stripXmlTags(String string) {
        StringBuilder res = new StringBuilder();
        int i = 0;
        int j = string.indexOf('<');
        while (j != -1) {
            res.append(string, i, j);
            int k = string.indexOf('>', j + 1);
            if (k == -1) {
                i = j + 1;
                j = -1;
            } else {
                i = k + 1;
                j = string.indexOf('<', i + 1);
            }
        }
        res.append(string.substring(i));
        return res.toString();
    }

}
