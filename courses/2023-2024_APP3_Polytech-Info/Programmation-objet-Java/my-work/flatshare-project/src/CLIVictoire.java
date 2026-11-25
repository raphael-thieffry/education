public class CLIVictoire extends CLIView {
    Bien bien;
    public CLIVictoire(Model model, Bien bien) {
        super(model);
        this.bien = bien;
    }

    public CLIView routine() {
        System.out.println("You got a rental !");
        System.out.println("It's this one : \n"+bien);
        return null;
    }
}
