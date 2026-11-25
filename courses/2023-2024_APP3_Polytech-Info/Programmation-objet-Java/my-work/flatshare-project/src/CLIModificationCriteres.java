public class CLIModificationCriteres extends CLIView{
    public CLIModificationCriteres(Model model) {
        super(model);
    }
    private void addCities(){
        System.out.println("Adding cities : ");
        while(true){
            String ville = ask("What is the city you want to add? (Write either city-name or insee code) (/next to end current task)");
            if(ville.equals("/next")){
                break;
            }
            Ville v = model.getVille(ville.trim());
            if (v == null) {
                System.out.println("This city doesn't exist, please try again.");
                continue;
            }
            this.model.getProjet().addVille(v);
            System.out.println("City added successfully.");
        }
    }
    private void removeCities(){
        System.out.println("Removing cities : ");
        System.out.println("Current cities in your project : ");
        for(Ville v : this.model.getProjet().getVilles()){
            System.out.println("\t" + v + "\n");
        }
        while(true){
            String ville = ask("What is the name of the city you want to remove? (Write city-name only) (/next to end current task)");
            if(ville.equals("/next")){
                break;
            }
            try{
                this.model.getProjet().removeVille(ville);
                System.out.println("City removed successfully.");
            }catch (IllegalArgumentException e){
                System.out.println("This city is not in your project.");
            }
        }
    }
    public CLIView routine() {
        if(model.getProjet() == null){
            System.out.println("You have to select a project first.");
            return new CLIMain(model);
        }
        System.out.println("Welcome to the criteria modification page :");
        String up = ask("What is the minimum upload speed you desire for the colocation project? (Press enter to keep the current value)");
        double newUp;
        try{
            newUp = Double.parseDouble(up);
            this.model.getProjet().setUploadSpeed(newUp);
        }catch (NumberFormatException ignored){}
        String down = ask("And what is the minimum download speed? (Press enter to keep the current value)");
        double newDown;
        try{
            newDown = Double.parseDouble(down);
            this.model.getProjet().setDownloadSpeed(newDown);
        }catch (NumberFormatException ignored){}
        String datalimit = ask("What is the minimum data limit per month you desire for the colocation project? (Press enter to keep the current value)");
        double newDataLimit;
        try{
            newDown = Double.parseDouble(datalimit);
            this.model.getProjet().setDebitLimite(newDown);
        }catch (NumberFormatException ignored){}

        System.out.println("You will now enter the city selection page. You can add cities, remove cities, or keep the current list of cities.");
        System.out.println("Write /next to end the current task : ");
        System.out.println("Current cities in your project : ");
        for(Ville v : this.model.getProjet().getVilles()){
            System.out.println("\t" + v + "\n");
        }
        String choice = ask("What do you want to do? (add/remove/both/keep, type the one you want)");
        while(true){
            switch (choice){
                case "add":
                    addCities();
                    break;
                case "remove":
                    removeCities();
                    break;
                case "both":
                    removeCities();
                    addCities();
                    break;
                case "keep":
                    break;
                default:
                    System.out.println("Invalid choice, please try again.");
                    continue;
            }
            break;
        }
        return new CLIMain(model);
    }
}
