import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        Model model;
        try {
            model = new Model();
        } catch (IOException e) {
            System.out.println("Error while loading data : " + e.getMessage());
            return;
        }
        CLIView view = new CLIChooseLogReg(model);
        while (view != null) {
            view = view.routine();
            System.out.println("--------------------");
        }
    }
}