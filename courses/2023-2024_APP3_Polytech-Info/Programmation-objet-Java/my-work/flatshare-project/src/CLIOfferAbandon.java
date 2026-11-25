import static java.lang.Integer.parseInt;

public class CLIOfferAbandon extends CLIView{
    /**
     * Permet de faire une offre sur un bien ou d'abandonner un bien de la liste. Les affiche sous la forme d'une liste avec des chiffres pour les sélectionner. Puis demande à l'utilisateur de choisir un chiffre et ce qu'il veut faire avec (faire offre, abandonner, rien).
     */
    public CLIOfferAbandon(Model model) {
        super(model);
    }
    public CLIView routine(){
        if(model.getProjet() == null){
            System.out.println("You must select a project first! (And create one if you don't have any)");
            return new CLIMain(model);
        }
        System.out.println("You're going to visit a property.");
        ListeBiens disparus = model.updateListeBiens();
        ListeBiens listeBiens = model.getProjet().getBiens();
        if(disparus.size() > 0){
            System.out.println("The following properties for rent are no longer available and were deleted from the project : ");
            for(Bien b : disparus){
                System.out.println(b);
            }
        }
        System.out.println("List of the properties in your project :");
        System.out.println(listeBiens.toString());
        int choix;
        while(true) {
            try {
                String choixtmp = ask("Select a property by typing its number in the list : (quit : /quit)");
                if(choixtmp.equals("/quit")) return new CLIMain(model);
                choix = Integer.parseInt(choixtmp) - 1;
                if(choix < 0 || choix >= listeBiens.size()) throw new NumberFormatException();
                break;
            } catch (NumberFormatException e) {
                System.out.println("Invalid number");
            }
        }
        Bien bien = listeBiens.get(choix);
        System.out.println("You chose : \n"+bien);
        System.out.println("What do you want to do with this property ?");
        System.out.println("1 : Make an offer");
        System.out.println("2 : Remove it from the project");
        System.out.println("3 : Nothing");
        while(true) {
            try {
                String choixtmp = ask("Select an option by typing its number : (quit : /quit)");
                if(choixtmp.equals("/quit")) return new CLIMain(model);
                choix = Integer.parseInt(choixtmp);
                break;
            } catch (NumberFormatException e) {
                System.out.println("Invalid number");
            }
        }
        switch(choix){
            case 1:
                return new CLIView(model){
                    public CLIView routine(){
                        System.out.println("You're going to make an offer on a property.");
                        System.out.println("You chose : \n"+bien);
                        System.out.println("What is your offer ?");
                        double choix;
                        while(true) {
                            try {
                                String choixtmp = ask("Type your offer : (quit : /quit)");
                                if(choixtmp.equals("/quit")) return new CLIMain(model);
                                choix = Double.parseDouble(choixtmp);
                                break;
                            } catch (NumberFormatException e) {
                                System.out.println("Invalid number");
                            }
                        }
                        if(bien.offre(choix)) {
                            System.out.println("It got accepted !");
                            model.projetCourant.finish();
                            return new CLIVictoire(model, bien);
                        }else{
                            System.out.println("It got refused.");
                            model.getProjet().removeBien(bien);

                        }
                        return new CLIMain(model);
                    }
                };
            case 2:
                if(model.getProjet().removeBien(bien)){
                    System.out.println("The property was removed from the project.");
                }else{
                    System.out.println("An error occurred. The property was not removed from the project.");
                }
                return new CLIMain(model);
            case 3:
                return new CLIMain(model);
            default:
                System.out.println("Invalid number");
                return new CLIMain(model);
        }
    }
}
