public class CLILogin extends CLIView{
    public CLILogin(Model model) {
        super(model);
    }
    public CLIView routine() {
        System.out.println("Welcome to the login page :");
        //if login, ask for username and password
        String login = ask("What is your login?");
        String password = ask("What is your password?");
        if (model.login(login, password)) {
            return new CLIMain(model);
        } else {
            System.out.println("Wrong login or password");
            return new CLIChooseLogReg(model);
        }
    }
}
