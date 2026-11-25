import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class LCMTest {

    private Database database;
    private LCM lcm;

    @BeforeEach
    void setUp() {
        List<Transaction> transactions = Arrays.asList(
                new Transaction(Set.of("A", "B", "C")),
                new Transaction(Set.of("A", "C")),
                new Transaction(Set.of("A", "B")),
                new Transaction(Set.of("B", "C")),
                new Transaction(Set.of("A", "B", "C"))
        );

        database = new Database(transactions);
        lcm = new LCM(database, 0.5, true); // silent = true pour éviter l'affichage
    }

    @Test
    void testRunLCM() {

        Set<Set<String>> expected = new HashSet<>();

        expected.add(Set.of("A"));
        expected.add(Set.of("B"));
        expected.add(Set.of("C"));
        expected.add(Set.of("A", "B"));
        expected.add(Set.of("A", "C"));
        expected.add(Set.of("B", "C"));

        Set<Set<String>> result = lcm.run();

        assertEquals(expected, result,
                "Les fermés fréquents générés par LCM ne correspondent pas aux attentes.");
    }
}
