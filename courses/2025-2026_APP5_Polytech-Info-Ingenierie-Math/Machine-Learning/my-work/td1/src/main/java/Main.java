import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.Set;



public class Main {

     

    public static void main(String[] args) {
        // Example database
        List<Transaction> transactions = Arrays.asList(
                new Transaction(Set.of("A", "B", "C")),
                new Transaction(Set.of("A", "C")),
                new Transaction(Set.of("A", "B")),
                new Transaction(Set.of("B", "C")),
                new Transaction(Set.of("A", "B", "C"))
        );

        Database db = new Database(transactions);

        // Run Apriori
        Apriori apriori = new Apriori(db, 0.5); // 50% minimum support
        List<Map<Set<String>, Integer>> frequentItemsets = apriori.run();

        // Display results
        System.out.println("Frequent Itemsets:");
        for (int i = 0; i < frequentItemsets.size(); i++) {
            System.out.println("Level " + (i + 1) + ": " + frequentItemsets.get(i));
        }

        System.out.println("\nComparaison Apriori et AprioriLex...");

        Database db2 = Database.fromFile("mushroom");

        //on mesure le timing

        long startTime = System.currentTimeMillis();
        Apriori apriori2 = new Apriori(db2, 0.50); 
        List<Map<Set<String>, Integer>> frequentItemsets2 = apriori2.run();
        for (int i = 0; i < frequentItemsets2.size(); i++) {
            System.out.println("Level " + (i + 1) + ": " + frequentItemsets2.get(i));
        }
        long endTime = System.currentTimeMillis();
        long durationApriori = endTime - startTime;

        System.out.println("Duration Apriori: " + durationApriori + " ms");

        long startTimeLex = System.currentTimeMillis();
        AprioriLex aprioriLex = new AprioriLex(db2, 0.50); 
        List<Map<Set<String>, Integer>> frequentItemsetsLex = aprioriLex.run();
        for (int i = 0; i < frequentItemsetsLex.size(); i++) {
            System.out.println("Level " + (i + 1) + ": " + frequentItemsetsLex.get(i));
        }
        long endTimeLex = System.currentTimeMillis();
        long durationAprioriLex = endTimeLex - startTimeLex;
        System.out.println("Duration AprioriLex: " + durationAprioriLex + " ms");


        System.out.println("\n -------LCM------- \n");

        List<Transaction> transactions3 = Arrays.asList(
                new Transaction(Set.of("B", "C", "D")),
                new Transaction(Set.of("A", "B", "C", "E")),
                new Transaction(Set.of("A", "B", "C", "D", "F")),
                new Transaction(Set.of("D", "E")),
                new Transaction(Set.of("A", "B")),
                new Transaction(Set.of("A", "C", "E", "F")),
                new Transaction(Set.of("A", "B", "E", "F")),
                new Transaction(Set.of("D", "F")),
                new Transaction(Set.of("C", "E")),
                new Transaction(Set.of("A", "B", "F"))
        );

        Database db3 = new Database(transactions3);

        LCM lcm = new LCM(db3, 0.3); //alpha 3 en gros
        System.out.println("Print comme l'algo du cours :");
        Set<Set<String>> frequentItemsetsLCM = lcm.run();
        System.out.println("Itemsets clos, sans doublons résultat :");
        frequentItemsetsLCM.forEach(System.out::println);

        System.out.println("--------PERF LCM--------");

        long startTimeLCM = System.currentTimeMillis();
        LCM lcm_perf = new LCM(db2, 0.50, true); 
        Set<Set<String>> closure = lcm_perf.run();
        System.out.println(closure);
        long endTimeLCM = System.currentTimeMillis();
        long durationAprioriLCM = endTimeLCM - startTimeLCM;
        System.out.println("Duration LCM sur mushrooms: " + durationAprioriLCM + " ms");
    }
}