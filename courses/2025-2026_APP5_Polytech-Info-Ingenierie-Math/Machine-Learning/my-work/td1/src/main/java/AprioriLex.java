import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class AprioriLex {
    private final double minSupport; // Minimum support threshold
    private final Database database;

    public AprioriLex(Database database, double minSupport) {
        this.database = database;
        this.minSupport = minSupport;
    }

    // Step 1: Generate frequent 1-itemsets
    public Map<Set<String>, Integer> generateFrequentItemsets() {
        Map<Set<String>, Integer> frequentItemsets = new HashMap<>();

        this.database.getTransactions().forEach(transaction -> {
            transaction.getItems().forEach(item -> {
                Set<String> itemset = new HashSet<>();
                itemset.add(item); // equivalent à A, B etc.
                frequentItemsets.put(itemset, frequentItemsets.getOrDefault(itemset, 0) + 1);
            });
        });

        frequentItemsets.entrySet().removeIf(entry -> entry.getValue() < this.minSupport * this.database.getTransactions().size());

        return frequentItemsets;
    }

    /**
     * May not be frequent enough
     * @param itemset
     * @return
     */
    private Set<Set<String>> child_candidates(Set<String> itemset) {
        Set<Set<String>> children = new HashSet<>();

        String max_itemset_letter = Collections.max(itemset);//itemset.stream().max(String::compareTo).orElse("");

        // Ajoute un item à la fin pour chaque item possible si l'ordre lexicographique le permet
        for (String item : this.database.getAllItems()) {
            if (!itemset.contains(item) 
                && (itemset.isEmpty() || item.compareTo(max_itemset_letter) > 0)
            ) {
                Set<String> child = new HashSet<>(itemset);
                child.add(item);
                children.add(child);
            }
        }
        return children;
    }

    // Step 2: Generate candidate k-itemsets from (k-1)-itemsets
    public Set<Set<String>> generateCandidates(Set<Set<String>> previousItemsets) {
        Set<Set<String>> candidates = new HashSet<>();

        previousItemsets.forEach(itemset -> {
            candidates.addAll(child_candidates(itemset));
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