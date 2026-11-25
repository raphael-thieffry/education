public class CLIProfile extends CLIView{
    public CLIProfile(Model model) {
        super(model);
    }
    public CLIView routine() {
        System.out.println("Your profile :");
        System.out.println(model.getCurrentUser().toString());
        //soon : edit profile ? Normalement c'est la même reference dans la "bdd" que partout ailleurs
        return new CLIMain(model);
    }
}
