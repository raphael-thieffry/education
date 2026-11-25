//-----------------------------------------------------------------------------
// Menu.java
//-----------------------------------------------------------------------------

import java.io.*; // pour la fonction lireClavier uniquement
import java.sql.*;
import java.util.Properties;

class Menu {

    static void creerVillage(Connection c) throws SQLException {
	System.out.println("ici traitement 1");
	String ordre = "insert into village values(454,'Orsay','tp',50,15)";
	Statement s = c.createStatement();
	int n = s.executeUpdate(ordre);
	System.out.println("fini traitement 1");
    }

    static void traitement3() {
	System.out.println("ici traitement3");

    }

    static String lireClavier(String message) {
	// Dans cette fonction l'exception est catchee pour ne pas avoir a la 
        // gerer dans le main, et donc mieux voir les exceptions BD. 
	try {
            System.out.print(message);
	    BufferedReader clavier =
		new BufferedReader(new InputStreamReader(System.in));
	    return clavier.readLine();
	} catch (Exception e) {
	    return "erreur dans fonction lireClavier";
	}
    }

    public static void main(String[] args) throws
       	ClassNotFoundException, SQLException
    	{
	
	String url = "jdbc:postgresql://tp-postgres/";
	Properties prop = new Properties();
	prop.setProperty("user", "<login>");
	prop.setProperty("password", "<password>");
	prop.setProperty("escapeSyntaxCallMode", "callIfNoReturn");
	Connection c = DriverManager.getConnection(url,prop);

	while (true) {
	    System.out.println("-------------------------------");
	    System.out.println("Bienvenue dans le menu Menu");
	    System.out.println("1 : creerVillage");
	    System.out.println("2 : traitement3");
	    System.out.println("0 : terminer");
	    int n = Integer.parseInt(lireClavier("Entrez votre choix : "));
	    switch (n) {
	    case 1 : creerVillage(c); break;
	    case 3 : traitement3(); break;
	    case 0 : return;
	    }
	}
    }
}

//-----------------------------------------------------------------------------
