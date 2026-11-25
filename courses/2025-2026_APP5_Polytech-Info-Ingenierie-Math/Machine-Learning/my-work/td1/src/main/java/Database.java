import java.io.File;
import java.io.FileNotFoundException;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

public final class Database {
    private final List<Transaction> transactions;
    private List<String> allItems;

    public Database(List<Transaction> transactions) {
        this.transactions = transactions;
        getAllItems(); // Precompute all items for later use
    }

    public List<Transaction> getTransactions() {
        return transactions;
    }

    public List<String> getAllItems() {
        if(allItems == null) {
            allItems = transactions.stream()
                    .flatMap(transaction -> transaction.getItems().stream())
                    .distinct()
                    .toList();
        }
        return allItems;
    }

    public static Database fromFile(String filename) {
        File file = new File("datasets/" + filename + ".txt");

        List<Transaction> transactions = new java.util.ArrayList<>();
        
        try (Scanner scanner = new Scanner(file)) {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] items = line.split(" ");
                Transaction transaction = new Transaction(Set.of(items));
                transactions.add(transaction);
            }   
        } catch (FileNotFoundException e) {
            System.out.println("Fichier non trouvé : " + e.getMessage());
        }
        return new Database(transactions);
    }


    public int size() {
        return transactions.size();
    }
}