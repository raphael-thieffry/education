import java.io.*;
import java.text.ParseException;
import java.util.*;

public class API {
     /**
      * CLasse interne permettant de lire un CSV de taille arbitraire ligne par ligne dans un format confortable pour travailler
      */
     public class CSVReader {
         BufferedReader reader;
         InputStream fIn;
         String[] headers;
         int lineCount = 0;
         int totalLines = -1;
         String filename;

         /**
          * Constructeur
          * @param filename : le nom d'un fichier csv au bon format
          * @throws IOException : en cas d'échec de lecture/si le nom de fichier n'existe pas ^par exemple
          */
         public CSVReader(String filename) throws IOException {
             //fIn = new FileInputStream(filename);
             this.filename = filename;
             fIn = this.getClass().getResourceAsStream(filename);
             this.reader = new BufferedReader(new InputStreamReader(fIn));
             headers = readLine();
             if(headers == null) {
                 throw new EOFException("Empty file, no headers");
             }
             computeTotalLines();
         }

         /**
          * Fonction utilitaire au sein de la classe
          * @return ligne : la ligne dans un format String[]
          * @throws IOException : erreur de lecture du fichier
          */
         private String[] readLine () throws IOException{
             /**
              * @return: null if EOF, else the line
              */
             String line = reader.readLine();
             if (line == null) {
                 return null;
             }
             lineCount++;
             return line.split(";", -1);
         }
        /**
         * Renvoie une ligne du csv dans un fromat inteligible grace à un HashMap
         * qui relie le nom de la colonne à son contenu pour chaque ligne
        * @return row : null if EOF, else a hashmap of the row
        */
         public HashMap<String, String> readRow() throws IOException, ParseException {
                String[] line = readLine();
                if (line == null) {
                    return null;
                }
                HashMap<String, String> row = new HashMap<>();
                try {
                    for (int i = 0; i < headers.length; i++) {
                        row.put(headers[i], line[i]);
                    }
                } catch (ArrayIndexOutOfBoundsException e) {
                    throw new ParseException("CSV file is not well formatted, row does not match header length on " + lineCount, lineCount);
                }
                return row;
         }

         /**
          * Cette fonction reinitialise la lecture du CSV au début.
          * @throws IOException : en cas d'erreur à la réouverture du fichier
          */
         public void reset() throws IOException {
             //fIn.getChannel().position(0);
             fIn = this.getClass().getResourceAsStream(filename);
             reader = new BufferedReader(new InputStreamReader(fIn));
             readLine(); //skip headers
             lineCount = 0;
         }

         /**
          * Compte les lignes totales de chaque fichier.
          * @throws IOException : erreur de lecture du fichier
          */
         private void computeTotalLines() throws IOException {
             reset();
             totalLines = 0;
             while(readLine() != null) {
                 totalLines++;
             }
             reset();
         }
     }

     CSVReader csvImb;
     CSVReader csvInternet;

    /**
     * Constructeur : Initialise une instance de la classe API
     * @param filenameImb : le nom du fichier immeuble
     * @param filenameInternet : le nom du fichier internet
     * @throws FileNotFoundException : si on ne trouve pas les fichiers
     * @throws IOException : si il y a une erreur à la lecture
     */
    public API(String filenameImb, String filenameInternet) throws FileNotFoundException, IOException{
        csvImb = new CSVReader(filenameImb);
        csvInternet = new CSVReader(filenameInternet);
        //check headers are like expected
        String[] idealHeaderImb = {"imb_id","imb_x","imb_y","imb_code","imb_code_insee","imb_nbr_logloc","imb_source","imb_type","addr_code","imb_num","addr_numero","addr_rep","addr_nom_voie","addr_nom_ld","addr_code_insee","addr_nom_commune","addr_id_fantoir","addr_source"};
        String[] idealHeaderInternet = {"imb_id","addr_code","imb_code","code_operateur","code_techno","classe_debit_montant","classe_debit_descendant","limitation","saturation"};
        if(!Arrays.equals(csvImb.headers, idealHeaderImb) || !Arrays.equals(csvInternet.headers, idealHeaderInternet)) {
            throw new IOException("CSV file is not well formatted, headers do not match expected ones for API to work");
        }
    }
    /**
     * Vérifie et renvoie la ville correspondante à une string
     * @param ville: nom de la ville improprement formaté, ou un code insee (trimé)
     * @return Ville : la ville sous le forme d'une instance de la classe VIlle si elle existe, null sinon.
     */
    public Ville getVilleDetails(String ville) throws IOException, ParseException{
        csvImb.reset();
        HashMap<String, String> row;
        while ((row = csvImb.readRow()) != null) {
            if (row.get("addr_nom_commune").trim().equalsIgnoreCase(ville) || row.get("addr_code_insee").trim().equalsIgnoreCase(ville)) {
                return new Ville(row.get("addr_nom_commune"), Double.parseDouble(row.get("imb_y")), Double.parseDouble(row.get("imb_x")), row.get("addr_code_insee"));
            }
        }
        return null;
    }
    /**
     * Renvoie une rangée du csv internet à partir d'un identifiant d'immeuble.
     * @param id: id imb
     * @return row : ligne du csv internet
     */
    public HashMap<String, String> randomRowInternetFromImb(String id) throws IOException, ParseException {
        csvInternet.reset();
        HashMap<String, String> row;
        ArrayList<HashMap<String, String>> rowsThatMatchimb = new ArrayList<>();
        while ((row = csvInternet.readRow()) != null) {
            if (row.get("imb_id").equalsIgnoreCase(id)) {
                //row clone
                HashMap<String, String> rowcp = new HashMap<>();
                for (String key : row.keySet()) {
                    rowcp.put(key, row.get(key));
                }
                rowsThatMatchimb.add(rowcp);
            }
        }
        if (rowsThatMatchimb.size() == 0) {
            throw new IOException("No internet data for this imb (" + id + ")");
        }
        return rowsThatMatchimb.get((int) (Math.random() * rowsThatMatchimb.size()));
    }

    /**
     *
     * @param ville : un ensemble de villes choisies
     * @return row : une rangée aléatoire d'un immeuble parmi ces villes
     * @throws IOException : en cas d'erreur à la lecture des csv
     * @throws ParseException : en cas de pdf mal formaté
     */
    public HashMap<String, String> randomRowImb(HashSet<Ville> ville) throws IOException, ParseException{
        //passe pour compter les ville et ranger les row dans un arraylist
        csvImb.reset();
        HashMap<String, String> row;
        ArrayList<HashMap<String, String>> rowsThatMatchVilles = new ArrayList<>();
        while ((row = csvImb.readRow()) != null) {
            for (Ville v : ville) {
                if (row.get("addr_nom_commune").trim().equalsIgnoreCase(v.nom) || row.get("addr_code_insee").trim().equalsIgnoreCase(v.insee)) {
                    //row clone
                    HashMap<String, String> rowcp = new HashMap<>();
                    for (String key : row.keySet()) {
                        rowcp.put(key, row.get(key));
                    }
                    rowsThatMatchVilles.add(rowcp);
                }
            }
        }
        if (rowsThatMatchVilles.size() == 0) {
            throw new IOException("No imb data for the cities you selected");
        }
        return rowsThatMatchVilles.get((int) (Math.random() * rowsThatMatchVilles.size()));
    }

    /**
     * @param villes: villes dans lesquelles on veut chercher un bien
     * @return Bien : un bien aléatoire de ces villes
     */
    public Bien randomBien(HashSet<Ville> villes) throws IOException, ParseException {
        HashMap<String, String> row = randomRowImb(villes);
        HashMap<String, String> rowInternet = randomRowInternetFromImb(row.get("imb_id"));

        HashSet<String> imIdMMRue = new HashSet<>(); //calcul des id de la mm rue
        csvImb.reset();
        HashMap<String, String> row2;
        while ((row2 = csvImb.readRow()) != null) {
            if (row2.get("addr_nom_voie").equalsIgnoreCase(row.get("addr_nom_voie")) && row2.get("imb_code_insee").equalsIgnoreCase(row.get("imb_code_insee"))) {
                imIdMMRue.add(row2.get("imb_id"));
            }
        }
        HashSet<HashMap<String, String>> rowsInternetMMRue = new HashSet<>(); //calcul des rowsInternet de la mm rue
        csvInternet.reset();
        HashMap<String, String> row3;
        while ((row3 = csvInternet.readRow()) != null) {
            if (imIdMMRue.contains(row3.get("imb_id"))) {
                rowsInternetMMRue.add(row3);
            }
        }

        return new Bien(row,
                        rowInternet,
                        averageRue("classe_debit_montant", rowsInternetMMRue),
                        averageRue("classe_debit_descendant", rowsInternetMMRue),
                        averageRue("limitation", rowsInternetMMRue),
                        averageRue("saturation", rowsInternetMMRue)
                        );
    }

    /**
     * Fait la moyenne de certaines colonnes particulières d'un ensemble de lignes du CSV internet
     * @param columnName : nom de la colonne dont on soubhaite calculer la moyenne
     * @param rowsInternetMMRue : les lignes sources
     * @return double : la moyenne
     */
    public double averageRue(String columnName, HashSet<HashMap<String, String>> rowsInternetMMRue){
        double sum = 0;
        int count = 0;
        for(HashMap<String, String> row : rowsInternetMMRue){
            try{
                if(Objects.equals(columnName, "saturation") && row.get(columnName).equalsIgnoreCase("f"))// saturation
                    sum += 1;
                else if (Objects.equals(columnName, "limitation")) //limitation
                    sum += Double.parseDouble(row.get(columnName));
                else if(Objects.equals(columnName, "classe_debit_montant") || Objects.equals(columnName, "classe_debit_descendant"))
                    sum += Bien.minimumDebit(row.get(columnName));

                /*else
                    sum += 0;*/

                count++;
            }catch (NumberFormatException e){
                //do nothing if misread
            }
        }
        return sum / count;
    }
}
