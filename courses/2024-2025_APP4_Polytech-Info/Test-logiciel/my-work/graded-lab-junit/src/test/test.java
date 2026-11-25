import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

public class test {
    Systeme s = new Systeme();

    /**
     * Verifie "
     * si aucun processus ne détient la ressource, alors aucun processus n'est en attente de la ressource ;
     * le processus courant ne fait pas partie des processus en attente."
     */
    void check_constraint(Processus current){
        if(s.isCurrent(current)){
            if(current == null){
                assertEquals(s.getWaiting().size(), 0);
            }else{
                assertFalse(s.getWaiting().contains(current));
            }
        }else{
            fail("Constraint checked and current is not what was expected");
        }
    }
    @BeforeEach
    void init_systeme(){
        s.init();
        check_constraint(null);
    }

    /**
     * Test égalité de deux process
     */
    @Test
    void egalite_process(){
        Processus p1;
        Processus p1bis;
        try{
            p1 = new Processus("p1");
            p1bis = new Processus("p1");
            assertEquals(p1, p1bis);
        } catch (ErreurSysteme ex) {
            fail();
            throw new RuntimeException(ex);
        }
    }
    /**
     * Test nom vide
     */
    @Test
    void nom_vide_process(){
        assertThrows(ErreurSysteme.class, ()->{
            Processus p = new Processus("");
        });
        assertThrows(ErreurSysteme.class, ()->{
            Processus p = new Processus(null);
        });
    }

    /**
     * Systeme ajout processus
     */
    @Test
    void add_systeme() throws ErreurSysteme {
        Processus p = new Processus("p");
        Processus pBis = new Processus("p");
        assertThrows(ErreurSysteme.class, ()->s.add(null));
        s.add(p);
        check_constraint(p);
        assertThrows(ErreurSysteme.class, ()->s.add(p));
        assertThrows(ErreurSysteme.class, ()->s.add(pBis));
        assertThrows(ErreurSysteme.class, ()->s.add(null));
        assertTrue(s.isCurrent(p));
        assertTrue(s.isCurrent(pBis));
        Processus p2 = new Processus("p2");
        s.add(p2);
        assertEquals(1, s.getWaiting().size());
        assertTrue(s.getWaiting().contains(p2));
    }

    /**
     * Test des differentes conditions d'erreur sur swap (0 ou 1 process)
     */
    @Test
    void swap_errors_systeme() throws ErreurSysteme {
        Processus p = new Processus("p");
        assertThrows(ErreurSysteme.class, ()->s.swap());
        s.add(p);
        check_constraint(p);
        assertThrows(ErreurSysteme.class, ()->s.swap());
    }

    /**
     * L'état ne doit pas changer après le déclanchement d'une erreur (cas 1 processus)
     */
    @Test
    void swap_error_state_unchanged() throws ErreurSysteme {
        Processus p = new Processus("p");
        s.add(p);
        try{
            s.swap();
        }catch(ErreurSysteme e){
            //"laisse l'état inchangé"
            assertTrue(s.isCurrent(p));
            assertEquals(s.getWaiting().size(), 0);
            assertTrue(s.isLast(null));
        }
    }

    /**
     * Systeme : L'opération swap() change le processus actif qui détient la ressource.
     * Si un seul processus est en attente, il devient le processus courant même s'il détenait
     * la ressource lors de l'appel précédent de swap.
     */
    @Test
    void swap_change_duo_systeme() throws ErreurSysteme {
        Processus p1 = new Processus("p1");
        Processus p2 = new Processus("p2");
        s.add(p1);
        assertTrue(s.isCurrent(p1));
        assertEquals(0, s.getWaiting().size());
        s.add(p2);
        assertTrue(s.isCurrent(p1));
        assertTrue(s.getWaiting().contains(p2));
        assertTrue(s.isLast(null));
        s.swap();
        assertTrue(s.isCurrent(p2));
        assertTrue(s.getWaiting().contains(p1));
        assertTrue(s.isLast(p1));
        check_constraint(p2);
        s.swap();
        assertTrue(s.isCurrent(p1));
        assertTrue(s.getWaiting().contains(p2));
        assertTrue(s.isLast(p2));
        check_constraint(p1);
    }

    /**
     * Systeme:
     * S'il y a plus d'un processus en attente, alors la
     * ressource est attribuée à n'importe lequel de ces processus, sauf celui qui possédait la ressource
     * lors de l'appel de swap précédent. Dans tous les cas, si un échange a lieu, l'ancien processus courant
     * rejoint la liste des processus en attente.
     *
     * Donc en quelques mots, le cas à n>=3 processus
     */
    @ParameterizedTest
    @MethodSource("nb_process")
    void swap_change_nuplet_systeme(int n) throws ErreurSysteme {
        for(int i = 1; i<=n; i++){
            s.add(new Processus("p"+ Integer.toString(i)));
        }
        assertTrue(s.isCurrent(new Processus("p1")));
        check_constraint(new Processus("p1"));
        s.swap();
        assertTrue(s.isLast(new Processus("p1")));
        assertTrue(s.getWaiting().contains(new Processus("p1")));
        s.swap();
        assertFalse(s.isCurrent(new Processus("p1")));
        if(n == 3){
            s.swap();
            assertTrue(s.isCurrent(new Processus("p1")));
            check_constraint(new Processus("p1"));
        }
    }

    static Stream<Arguments> nb_process() {
        return Stream.of(
                Arguments.of(3),
                Arguments.of(4),
                Arguments.of(6),
                Arguments.of(9),
                Arguments.of(13)
        );
    }
}
