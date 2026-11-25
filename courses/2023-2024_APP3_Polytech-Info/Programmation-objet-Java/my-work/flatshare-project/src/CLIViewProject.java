public class CLIViewProject extends CLIView{
    public CLIViewProject(Model model) {
        super(model);
    }
    public CLIView routine() {
        //call to disparition function in model
        if(
            model.getProjet()==null
        ){
            System.out.println("You don't have a project yet or haven't selected it.");
            return new CLIMain(model);
        }

        ListeBiens disparus = model.updateListeBiens();
        System.out.println(model.getProjet());
        if(disparus.size()>0){
            System.out.println("The following properties for rent are no longer available and were deleted from the project : ");
            for(Bien b : disparus){
                System.out.println(b);
            }
        }
        return new CLIMain(model);
    }
}
