import java.io.*;
import java.sql.*;
import java.util.Properties;

class CorrJDBC {

    //-------------------------------------------------------------------------
    static Connection connexion(String serveur, String login, String password) 
	throws SQLException, ClassNotFoundException {
	System.out.println("ici connexion "+login+"@"+serveur);
	String url = "jdbc:postgresql://"+ serveur + "/";
	Properties prop = new Properties();
	prop.setProperty("user", login);
	prop.setProperty("password", password);
	prop.setProperty("escapeSyntaxCallMode", "callIfNoReturn"); //proc sans retour
	Connection c = DriverManager.getConnection(url, prop);
	return c;
    }

    //-------------------------------------------------------------------------
    static void deconnexion(Connection c) 
	throws SQLException {
	System.out.println("ici deconnexion");
	c.close();
    }

    //-------------------------------------------------------------------------
    static void creerVillage(Connection c) 
	throws SQLException {

	// parametres :
	String v = lireClavier("entrez ville : ");
	String a = lireClavier("entrez activite : ");
	int p = Integer.parseInt(lireClavier("entrez prix : "));
	int cap = Integer.parseInt(lireClavier("entrez capacite : "));

	// construction texte ordre :
        String texte = 
	    "insert into village values(DEFAULT,'"
	    +v+"','"+a+"',"+p+","+cap+")";
        System.out.println(texte);

	// acces serveur :
	Statement stmt = c.createStatement();
	stmt.executeUpdate(texte);
	stmt.close();

	// retours : neant
    }

    //-------------------------------------------------------------------------
    static void traitement3(Connection c) 
	throws SQLException {
	System.out.println("ici traitement3");

	// parametres :
	int jour = Integer.parseInt(lireClavier("entrez jour : "));

	// construction texte ordre :
        String texte = "delete sejour where jour<"+jour;
        System.out.println(texte);

	// acces serveur :
	Statement stmt = c.createStatement();
	int nb = stmt.executeUpdate(texte);
	stmt.close();

	// retours :
	System.out.println("Retour : nombre de sejours detruits : "+nb);
    }

    //-------------------------------------------------------------------------
    static void traitement3TryCatch(Connection c) {
	System.out.println("ici traitement3TryCatch");
	int jour = Integer.parseInt(lireClavier("entrez jour : "));
        String texte = "delete sejour where jour<"+jour;
        System.out.println(texte);
	try {
	    Statement stmt = c.createStatement();
	    int nb = stmt.executeUpdate(texte);
	    stmt.close();
	    System.out.println("Retour : nombre de sejours detruits : "+nb);
	} catch (SQLException e) {
	    System.out.print("erreur : ");
	    System.err.println(e);
	}
    }

    //-------------------------------------------------------------------------
    static void authentification(Connection c) throws SQLException {
	String nom = lireClavier("entrez nom : ");
	int age = Integer.parseInt(lireClavier("entrez age : "));
	String texte = "select idc from client where nom='"+nom+"' and age="+age;
	System.out.println(texte);
	Statement s = c.createStatement();
	ResultSet r = s.executeQuery(texte);
	if (r.next())
	    System.out.println("id client: "+r.getInt(1));
	else
	    System.out.println("client inexistant");
	r.close();
	s.close();
    }

    //-------------------------------------------------------------------------
    static void consulterVillagesEmploye(Connection c) 
	throws SQLException {
	System.out.println("ici consulterVillagesEmploye");
        String texte = "select * from village";
        System.out.println(texte);
	Statement stmt = c.createStatement();
	ResultSet r = stmt.executeQuery(texte);
	while (r.next())
	    System.out.println(r.getInt(1)+", "+r.getString(2)+", "
			       +r.getString(3)+", "+r.getInt(4)+", "
			       +r.getInt(5));
	r.close();
	stmt.close();
    }

    //-------------------------------------------------------------------------
    static void consulterVillagesClient(Connection c) 
	throws SQLException {
	System.out.println("ici consulterVillagesClient");
	int ic = Integer.parseInt(lireClavier("entrez identifiant client : "));
        String texte =
	    "select village.idv, ville, activite,prix, capacite\n"
	    +"from village, sejour\n"
	    +"where village.idv = sejour.idv and idc = "+ic;
        System.out.println(texte);
	Statement stmt = c.createStatement();
	ResultSet r = stmt.executeQuery(texte);
	while (r.next())
	    System.out.println(r.getInt(1)+", "+r.getString(2)+", "
			       +r.getString(3)+", "+r.getInt(4)+", "
			       +r.getInt(5));
	r.close();
	stmt.close();
    }

    //-------------------------------------------------------------------------
    static void traitement1(Connection c) 
	throws SQLException {
	System.out.println("ici traitement1");

	// parametre(s) :
	String n = lireClavier("entrez nom : ");
	int a = Integer.parseInt(lireClavier("entrez age : "));

        String texte = "select nextval('client_idc_seq')";
        System.out.println(texte);
	Statement s = c.createStatement();
	ResultSet r = s.executeQuery(texte);
	r.next();
	int ic = r.getInt(1); 
	r.close();
	// ideal serait un select into au lieu d'un curseur puisqu'il y a 
	// exactement une valeur de retour

        texte = 
	    "insert into client(idc,nom,age) values("+ic+",'"+n+"',"+a+")";
        System.out.println(texte);
	// acces serveur :
	Statement stmt = c.createStatement();
	stmt.executeUpdate(texte);
	stmt.close();

	// retour(s) :
	System.out.println("identifiant client : "+ic);
    }

    //-------------------------------------------------------------------------
    static void doubleConnexion(Connection c) 
	throws SQLException, 
	       ClassNotFoundException { // a noter !
	System.out.println("ici doubleConnexion");

        String texte = "select count(*) from village";
        System.out.println(texte);
	Statement s = c.createStatement();
	ResultSet r = s.executeQuery(texte);
	r.next();
	int nb_moi = r.getInt(1); 
	r.close();
        s.close();

	Connection c2 = connexion("tp-postgres","<login>","<password>"); 
	s = c2.createStatement();
	r = s.executeQuery(texte);
	r.next();
	int nb_autre = r.getInt(1); 
	c2.close();
        s.close();

	String result;
	if (nb_moi<nb_autre)
	    result = "conn1";
	else
	    result = "conn2";
	System.out.println("c'est "+result);
    }

    //-------------------------------------------------------------------------
    static String lireClavier(String message) {
	// dans cette fonction l'exception est catchee pour ne pas avoir a la 
        // gerer dans le main, et donc mieux voir les exceptions BD
	try {
	    System.out.print(message);
	    BufferedReader clavier =
		new BufferedReader(new InputStreamReader(System.in));
	    return clavier.readLine();
	} catch (Exception e) {
	    return "erreur dans fonction lireClavier";
	}
    }

    //-------------------------------------------------------------------------
    public static void main(String[] args) 
	throws SQLException, ClassNotFoundException {
	// rem : une seule fois dans programme (donc pas dans connnexion) :
	Connection c = connexion("tp-postgres","<login>","<password>"); 
	while (true) {
	    System.out.println("-------------------------------");
	    System.out.println("Bienvenue dans le menu CorrJDBC");
	    System.out.println("0 : deconnexion");
	    System.out.println("1 : creer village (employe)");
	    System.out.println("2 : traitement 3 (employe)");
	    System.out.println("3 : traitement 3 avec try-catch");
	    System.out.println("4 : consulter villages (employe)");
	    System.out.println("5 : traitement 1 (client)");
	    System.out.println("6 : consulter villages (client)");
	    System.out.println("9 : double connexion");
	    System.out.println("10 : creerVillageBoucle"); 
	    System.out.println("-1 : terminer");
	    int n = Integer.parseInt(lireClavier("Entrez votre choix : "));
	    switch (n) {
	    case 0 : deconnexion(c); break;
	    case 1 : creerVillage(c); break;
	    case 2 : traitement3(c); break;
	    case 3 : traitement3TryCatch(c); break;
	    case 4 : consulterVillagesEmploye(c); break;
	    case 5 : traitement1(c); break;
	    case 6 : consulterVillagesClient(c); break;
	    case 9 : doubleConnexion(c); break;
	    case -1 : return;
	    }
	}
    }
}

//-----------------------------------------------------------------------------
