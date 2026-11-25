import java.io.IOException;
import java.text.ParseException;
import java.util.Objects;

public class CLISearch extends CLIView {
    public CLISearch(Model model) {
        super(model);
    }
    public CLIView routine() {
        System.out.println("The system will proceed to the search according to the cities you entered in your project : ");
        System.out.println("Searching...");
        Bien b;
        try{
            b = model.rechercherBienDansMesVilles();
        } catch (IOException|ParseException e ){
            System.out.println("An error occured while searching for a property.");
            System.out.println(e.getMessage());
            return new CLIMain(model);
        } catch (IllegalArgumentException e){
            System.out.println(e.getMessage());
            return new CLIMain(model);
        }
        System.out.println("The system found a property in " + b.getVille() + " : ");
        System.out.println(b);
        System.out.println("Matching your criteria ? : ");
        if(model.repondCriteres(b)) {
            System.out.println("Yes");
            System.out.println("accepting...");
            model.ajouteBienProjet(b);
        } else {
            System.out.println("No");
            System.out.println("rejecting...");
            if(Objects.equals(ask("Do you want to continue searching? (y/n)"), "y")) {
                return new CLISearch(model);
            }
        }
        return new CLIMain(model);
    }
}
