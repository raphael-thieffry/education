public class CLIChooseLogReg extends CLIView{
    public CLIChooseLogReg(Model model) {
        super(model);
    }
    public CLIView routine() {
        model.disconnect();
        //first ask if the user wants to login or register
        String choice = ask("Do you want to login or register? (r/l)");
        if (choice.equals("r")) {
            return new CLISignup(model);
        } else if (choice.equals("l")) {
            return new CLILogin(model);
        }
        return new CLIChooseLogReg(model);
    }
}
