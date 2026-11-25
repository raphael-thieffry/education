import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Apriori {
    private final double minSupport; // Minimum support threshold
    private final Database database;

    private int size = -1;

    public Apriori(Database database, double minSupport) {
        this.database = database;
        this.minSupport = minSupport;
    }
    public Apriori(Database database, double minSupport, int size) {
        this.database = database;
        this.minSupport = minSupport;
        this.size = size;
    }

    // Step 1: Generate frequent size-itemsets
    public Map<Set<String>, Integer> generateFrequentItemsets() {
        Map<Set<String>, Integer> frequentItemsets = new HashMap<>();

        if(this.size == -1){
            this.database.getTransactions().forEach(transaction -> {
                transaction.getItems().forEach(item -> {
                    Set<String> itemset = new HashSet<>();
                    itemset.add(item); // equivalent à A, B etc.
                    frequentItemsets.put(itemset, frequentItemsets.getOrDefault(itemset, 0) + 1);
                });
            });
    
            frequentItemsets.entrySet().removeIf(entry -> entry.getValue() < this.minSupport * this.database.getTransactions().size());
        }else{
            //dernière question, pour avoir les itemsets de taille k ou superieur. On peut juste changer les itemset "de base"
            this.database.getTransactions().forEach(transaction -> {
                if(transaction.getItems().size() == this.size){
                    Set<String> itemset = new HashSet<>(transaction.getItems());
                    frequentItemsets.put(itemset, frequentItemsets.getOrDefault(itemset, 0) + 1);
                }
            });
    
            frequentItemsets.entrySet().removeIf(entry -> entry.getValue() < this.minSupport * this.database.getTransactions().size());
        }

        return frequentItemsets;
    }

    // Step 2: Generate candidate k-itemsets from (k-1)-itemsets
    public Set<Set<String>> generateCandidates(Set<Set<String>> previousItemsets) {
        Set<Set<String>> candidates = new HashSet<>();

        previousItemsets.forEach(itemset1 -> {
            previousItemsets.forEach(itemset2 -> {
                if (!itemset1.equals(itemset2)) {
                    Set<String> candidate = new HashSet<>(itemset1);
                    candidate.addAll(itemset2);
                    if (candidate.size() == itemset1.size() + 1) {
                        candidates.add(candidate);
                    }
                }
            });
        });

        return candidates;
    }

    // Step 3: Count support for candidates
    public Map<Set<String>, Integer> countSupport(Set<Set<String>> candidates) {
        Map<Set<String>, Integer> supportCount = new HashMap<>();

        candidates.forEach(candidate -> {
            int count = 0;
            for (Transaction transaction : this.database.getTransactions()) {
                if (transaction.getItems().containsAll(candidate)) {
                    count++;
                }
            }
            supportCount.put(candidate, count);
        });

        return supportCount;
    }

    // Step 4: Filter candidates by support
    public Map<Set<String>, Integer> filterCandidates(Map<Set<String>, Integer> candidates) {
        Map<Set<String>, Integer> frequentItemsets = new HashMap<>();

        candidates.entrySet().removeIf(entry -> entry.getValue() < this.minSupport * this.database.getTransactions().size());
        frequentItemsets.putAll(candidates);
        return frequentItemsets;
    }

    // Main method to run Apriori
    public List<Map<Set<String>, Integer>> run() {
        List<Map<Set<String>, Integer>> allFrequentItemsets = new ArrayList<>();
        Set<Set<String>> currentCandidates;

        // Step 1: Generate frequent 1-itemsets
        Map<Set<String>, Integer> frequent1Itemsets = generateFrequentItemsets();
        allFrequentItemsets.add(frequent1Itemsets);

        currentCandidates = frequent1Itemsets.keySet();

        // Step 2: Iteratively generate higher-order frequent itemsets
        while (!currentCandidates.isEmpty()) {
            Set<Set<String>> candidates = generateCandidates(currentCandidates);
            Map<Set<String>, Integer> supportCounts = countSupport(candidates);
            Map<Set<String>, Integer> frequentItemsets = filterCandidates(supportCounts);

            if (!frequentItemsets.isEmpty()) {
                allFrequentItemsets.add(frequentItemsets);
                currentCandidates = frequentItemsets.keySet();
            } else {
                break;
            }
        }

        return allFrequentItemsets;
    }
}