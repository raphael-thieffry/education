import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class PileTest {
    @Test
    public void testPush(){
        Pile<Integer> pile = new Pile<>(new Integer[0]);
        pile.push(1);
        assertEquals(1, pile.peek());
    }

    @Test
    public void testPop(){
        Pile<Integer> pile = new Pile<>(new Integer[0]);
        pile.push(1);
        pile.pop();
        assertTrue(pile.isEmpty());
    }

    @Test
    public void testSize(){
        Pile<Integer> pile = new Pile<>(new Integer[0]);
        pile.push(1);
        pile.push(2);
        assertEquals(2, pile.size());
    }

    @Test
    public void testIsEmpty(){
        Pile<Integer> pile = new Pile<>(new Integer[0]);
        assertTrue(pile.isEmpty());
    }

    @Test
    public void testPeek(){
        Pile<Integer> pile = new Pile<>(new Integer[0]);
        pile.push(1);
        assertEquals(1, pile.peek());
    }

    @Test
    public void testToArray(){
        Pile<Integer> pile = new Pile<>(new Integer[0]);
        pile.push(1);
        pile.push(2);
        Integer[] arr = pile.toArray();
        assertEquals(1, arr[0]);
        assertEquals(2, arr[1]);
    }

    @Test
    public void testSearch(){
        Pile<Integer> pile = new Pile<>(new Integer[0]);
        pile.push(1);
        pile.push(2);
        assertEquals(1, pile.search(2));
    }

    @Test
    public void testClear(){
        Pile<Integer> pile = new Pile<>(new Integer[0]);
        pile.push(1);
        pile.push(2);
        pile.clear();
        assertTrue(pile.isEmpty());
    }

    @Test
    public void testDup(){
        Pile<Integer> pile = new Pile<>(new Integer[0]);
        pile.push(1);
        pile.dup();
        assertEquals(1, pile.pop());
        assertEquals(1, pile.pop());
    }

    @Test
    public void testSwap(){
        Pile<Integer> pile = new Pile<>(new Integer[0]);
        pile.push(1);
        pile.push(2);
        pile.swap();
        assertEquals(1, pile.pop());
        assertEquals(2, pile.pop());
    }
}
