package simpleGame.test;
import org.junit.jupiter.api.*;
import simpleGame.core.*;
//import static org.junit.Assert.*;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Mockito.*;

import org.junit.*;
import org.mockito.*;

public class TestSequenceDiagram {

	// creation of a mock for Board
	// (alternative to Board b = mock(Board.class);)
	@Mock
	private Board b;
	
	// creation of an instance of Game linked
	// to the mock of Board by injection
	// (the call to the Board constructor inside
	// the Game constructor is replaced by mock b)
	@InjectMocks
	private Game g;

	//on a un board mocké
	@Test
	public void testIsGameOver() {
		// to be completed
		when(b.numberOfPawns()).thenReturn(2);
		when(b.maxGold()).thenReturn(3);

		assertTrue(g.isGameOver());

		InOrder mo = inOrder(b); //verify(b).machin() c'est pas ordoné btw
		mo.verify(b).numberOfPawns();
		mo.verify(b).maxGold();
	}

	//on a un board réel mais des pions mockés
	@Test
	public void testMaxGold() {
		Board b = new Board(1, 10, 12);
		b.removePawn(b.getNextPawn());

		Pawn p1 = mock(Pawn.class);
		Pawn p2 = mock(Pawn.class);
		when(p1.getX()).thenReturn(6);
		when(p1.getY()).thenReturn(6);
		//when(b.getSquareContent(6, 6)).thenReturn(null);
		b.addPawn(p1);

		when(p2.getX()).thenReturn(6);
		when(p2.getY()).thenReturn(7);
		b.addPawn(p2);

		when(p1.getGold()).thenReturn(1);
		when(p2.getGold()).thenReturn(3);

		assertEquals(3, b.maxGold());
		verify(p1).getGold();
		verify(p2).getGold();
	}

	// Mockito technicalities
	private AutoCloseable closeable;
	@BeforeEach
	public void openMocks() {
		closeable = MockitoAnnotations.openMocks(this);
	}
	@AfterEach
	public void releaseMocks() throws Exception {
		closeable.close();
	}
	
}
