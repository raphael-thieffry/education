import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class LCM {
    private final double minSupport; // Minimum support threshold
    private final Database database;
    private final boolean silent;

    public LCM(Database database, double minSupport, boolean silent) {
        this.database = database;
        this.minSupport = minSupport;
        this.silent = silent;
    }
    public LCM(Database database, double minSupport) {
        this.database = database;
        this.minSupport = minSupport;
        this.silent = false;
    }

    private Set<String> closure(Set<String> itemset) {
        //une grosse intersection
        Set<String> closure = new HashSet<>(this.database.getAllItems());
        this.database.getTransactions().forEach(transaction -> {
            if (transaction.getItems().containsAll(itemset)) {
                closure.retainAll(transaction.getItems());
            }
        });
        return closure;
    }

    private String tail(Set<String> itemset) {
        List<String> sortedItems = itemset.stream().sorted().toList();
        return sortedItems.get(sortedItems.size() - 1);
    }

    private boolean tail_compare(Set<String> itemset, String item) {
        if(itemset.isEmpty()) return true;
        return tail(itemset).compareTo(item) < 0;
    }

    private boolean is_frequent(Set<String> itemset) {
        int count = 0;
        for (Transaction transaction : this.database.getTransactions()) {
            if (transaction.getItems().containsAll(itemset)) {
                count++;
            }
        }
        return count >= this.minSupport * this.database.getTransactions().size();
    }

    private Set<Set<String>> run(Set<String> itemset) {
        if(!silent){
            System.out.println(itemset);
        }
        List<String> p_i = this.database.getAllItems();

        Set<Set<String>> results = new HashSet<>();

        for (String item : p_i) {
            if (tail_compare(itemset, item)) {
                Set<String> newItemset = new HashSet<>(itemset);
                newItemset.add(item);
                Set<String> closure = closure(newItemset);
                if (is_frequent(closure)) {
                    results.add(closure);
                    results.addAll(run(closure));
                }
            }
        }

        return results;
        
    }

    public Set<Set<String>> run() {
        
        return run(new HashSet<>());
    }
}