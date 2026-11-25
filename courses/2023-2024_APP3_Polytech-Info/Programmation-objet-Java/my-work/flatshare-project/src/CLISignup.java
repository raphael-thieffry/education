public class CLISignup extends CLIView{
    public CLISignup(Model model) {
        super(model);
    }
    public CLIView routine() {
        System.out.println("Welcome to the signup page :");
        //asks all the info to build a new user and then add it to the database
        String login = ask("What is your login?");
        String password = ask("What is your password?");
        String name = ask("What is your name?");
        String surname = ask("What is your surname?");
        String email = ask("What is your email?");
        try {
            model.register(login, password, name, surname, email);
            model.login(login, password);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
            return new CLIChooseLogReg(model);
        }
        return new CLIMain(model);
    }
}
