public class CLIVote extends CLIView{
    public CLIVote(Model model) {
        super(model);
    }
    public CLIView routine() {
        //call to vote function in model
        if(
            model.getProjet()==null
        ){
            System.out.println("You don't have a project yet or haven't selected it.");
            return new CLIMain(model);
        }
        if(model.getProjet().getBiens().size()==0){
            System.out.println("You don't have any property in your project yet.");
            return new CLIMain(model);
        }
        System.out.println("The following properties for rent are in your project : ");
        for(Bien b : model.getProjet().getBiens()){
            System.out.println(b.toString());
            String unformattedvote = ask("Evaluate (/10) oor press enter to skip.");
            while(true) {
                try {
                    double vote = Double.parseDouble(unformattedvote);
                    b.vote(vote, model.getCurrentUser());
                    break;
                } catch (NumberFormatException e) {
                    System.out.println("Skipping...");
                    break;
                } catch (IllegalArgumentException e) {
                    System.out.println(e.getMessage());
                }
            }
        }
        System.out.println("You've gone through all properties.");
        return new CLIMain(model);
    }
}
