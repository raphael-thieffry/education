import java.util.ArrayList;

public class CLICreateProject extends CLIView{
    public CLICreateProject(Model model) {
        super(model);
    }
    private Ville askVille() {
        //asks for a city and returns it
        //if the city doesn't exist, asks again
        //if the user writes /end, returns null
        String ville = ask("What is the city you want to test? (Write either city-name or insee code)");
        if (ville.equals("/end")) {
            return null;
        }
        Ville v = model.getVille(ville.trim());
        if (v == null) {
            System.out.println("This city doesn't exist, please try again.");
            return askVille();
        }
        return v;
    }
    private Ville[] askVilles() {
        System.out.println("Write /end to stop adding cities : ");
        //asks for a list of cities and returns it while it's not null

        ArrayList<Ville> villesArg = new ArrayList<>();
        while (true) {
            Ville v = askVille(); //v is null <=> the user wrote /end
            if (v == null && villesArg.size() != 0) { //if the user wrote /end and there is at least one city
                break;
            } else if (v == null) {
                System.out.println("You must add at least one city when creating a project.");
                continue;
            }
            villesArg.add(v);
        }
        return villesArg.toArray(new Ville[villesArg.size()]);
    }
    public CLIView routine() {
        //first check if user already has a project
        if (model.userHasProject()) {
            System.out.println("You already have a project, you can't create a new one.");
            return new CLIMain(model);
        }
        System.out.println("Welcome to the project creation page :");
        //asks all the info to build a new project and then add it to the database
        String up = ask("What is the minimum upload speed you desire for the colocation project?");
        String down = ask("And what is the minimum download speed?");
        String datalimit = ask("What is the minimum data limit per month you desire for the colocation project?");
        Ville[] villesArg = askVilles();
        try {
            model.nouveauProjet(Double.parseDouble(up), Double.parseDouble(down), villesArg, Double.parseDouble(datalimit));
            System.out.println("Project created successfully.");
        } catch (IllegalArgumentException e) {
            System.out.println("Error while creating the project : ");
            System.out.println("\t" + e.getMessage());
            return new CLIMain(model);
        }
        return new CLIMain(model);
    }
}
