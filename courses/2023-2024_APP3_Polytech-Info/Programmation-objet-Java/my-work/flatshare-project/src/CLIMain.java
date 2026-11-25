import java.util.AbstractMap.SimpleEntry;
import java.util.HashMap;
import java.util.Map;

public class CLIMain extends CLIView{
    public CLIMain(Model model) {
        super(model);
    }
    public CLIView routine() {
        System.out.println("Welcome to the main page "+model.getCurrentUser().username+" :");
        //if login, ask for username and password
        HashMap<Integer, Map.Entry<String, CLIView>> options = new HashMap<>();
        options.put(1, new SimpleEntry<>("Disconnect", new CLIChooseLogReg(model)));
        options.put(2, new SimpleEntry<>("Create a project", new CLICreateProject(model)));
        options.put(3, new SimpleEntry<>("View selected project", new CLIViewProject(model)));
        options.put(4, new SimpleEntry<>("Search property for rent", new CLISearch(model)));
        options.put(5, new SimpleEntry<>("Select your already existing project", new CLIView(model) {
            @Override
            public CLIView routine() {
                try{
                    model.setExistingAsProjetCourant();
                    System.out.println("Your project has been selected.");
                }catch (IllegalArgumentException e){
                    System.out.println(e.getMessage());
                }
                return new CLIMain(model);
            }
        }));
        options.put(6, new SimpleEntry<>("Quit the project you're in (if you're alone in the project it will be deleted)", new CLIView(model) {
            @Override
            public CLIView routine() {
                try{
                    model.leaveProjet();
                }catch (IllegalArgumentException e){
                    System.out.println(e.getMessage());
                }
                return new CLIMain(model);
            }
        }));
        options.put(7, new SimpleEntry<>("Evaluate properties in the selected project", new CLIVote(model) ));
        options.put(8, new SimpleEntry<>("Add a flatmate to your selected project", new CLIView(model) {
            @Override
            public CLIView routine() {
                try{
                    String colname = ask("Enter the username of the flatmate you want to add : ");
                    model.addFlatmate(colname);
                    System.out.println(colname + " has been added to your project.");
                }catch (IllegalArgumentException e){
                    System.out.println(e.getMessage());
                }
                return new CLIMain(model);
            }
        }));
        options.put(9, new SimpleEntry<>("View your profile", new CLIProfile(model)));
        options.put(10, new SimpleEntry<>("Change your criteria", new CLIModificationCriteres(model)));
        options.put(11, new SimpleEntry<>("Visit a property from list", new CLIOfferAbandon(model)));
        System.out.println("What do you want to do?");
        for(int key : options.keySet()) {
            System.out.println("\t"+ key + " : " + options.get(key).getKey());
        }
        int choice = -1;
        try {
            choice = Integer.parseInt(ask(""));
        } catch (NumberFormatException e) {
            System.out.println("It's not a number");
        }
        if (options.containsKey(choice)) {
            return options.get(choice).getValue();
        }
        System.out.println("It appears your choice is not valid, please try again.");
        return this;
    }
}
