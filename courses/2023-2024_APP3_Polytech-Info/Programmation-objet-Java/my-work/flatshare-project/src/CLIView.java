import java.io.Console;
import java.util.Scanner;

public abstract class CLIView {
    Model model;
    public CLIView(Model model) {
        this.model = model;
    }

    /**
     * Pose la question à l'utilisateur puis lit sa réponse avant de la renvoyer
     * @param question : String, la question à poser à l'utilisateur
     * @return la réponse fournie
     */
    protected String ask(String question) {
        Scanner scanner = new Scanner(System.in);
        System.out.println(question);
        return scanner.nextLine();
    }

    /**
     * Ce qui est affiche les menus etc.. Ce qui est executé quand on arrive sur la page
     * @return La page suivante
     */
    public abstract CLIView routine();
}
