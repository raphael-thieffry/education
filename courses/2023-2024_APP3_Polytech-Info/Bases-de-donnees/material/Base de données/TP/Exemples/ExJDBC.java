//-----------------------------------------------------------------------------
// ExJDBC1.java
//-----------------------------------------------------------------------------

import java.io.*;
import java.sql.*;
import java.util.Properties;

class ExJDBC1 {

    //-------------------------------------------------------------------------
    static void ex1(Connection c)
	throws SQLException {
	String name = lireClavier("entrez le nom : ");
	String texte = 
	    "update personne set age = age + 1 where nom = '"+name+"'";
	System.out.println(texte);
	Statement s = c.createStatement();
	int n;
	n = s.executeUpdate(texte);
	System.out.println("nombre de lignes traitees : "+n);

	lireClavier("Pause programme (entrez return) :");
	n = s.executeUpdate("update personne set age = age + 1");
	System.out.println("nombre de lignes traitees : "+n);
	s.close();
    }

    //-------------------------------------------------------------------------
    static void ex2(Connection c)
	throws SQLException {

	Statement s = c.createStatement();
	String texte = "insert into t values(42,52)"; 
	System.out.println(texte);
	s.executeUpdate(texte);
	s.close();

	String url = "jdbc:postgresql://tp-postgres/";
	Properties prop = new Properties();
	prop.setProperty("user", "<login>");
	prop.setProperty("password", "<password>");

	Connection c2 = DriverManager.getConnection(url,prop);

	Statement s2 = c2.createStatement();
	s2.executeUpdate(texte);
	s2.close();
	c2.close();
    }

    //-------------------------------------------------------------------------

    static String lireClavier(String message) {
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
	String url = "jdbc:postgresql://tp-postgres/";
	Properties prop = new Properties();
	prop.setProperty("user", "<login>");
	prop.setProperty("password", "<password>");
	//Class.forName("oracle.jdbc.driver.OracleDriver");
	Connection c = DriverManager.getConnection(url,prop);	
	while (true) {
	    System.out.println("-------------------------------");
	    System.out.println("Bienvenue dans ExJDBC1");
	    System.out.println("1 : update et compte-rendu : ");
	    System.out.println("2 : double connexion : ");
	    System.out.println("9 : deconnexion");
	    System.out.println("0 : terminer");
	    int n = Integer.parseInt(lireClavier("Entrez votre choix : "));
	    switch (n) {
	    case 1 : ex1(c); break;
	    case 2 : ex2(c); break;
	    case 9 : c.close(); break;
	    case 0 : return;
	    }
	}
    }
}

//-----------------------------------------------------------------------------
