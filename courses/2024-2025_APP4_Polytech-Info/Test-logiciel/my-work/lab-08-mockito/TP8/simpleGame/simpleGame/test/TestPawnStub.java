package simpleGame.test;
import simpleGame.core.*;
import simpleGame.exception.OutOfBoardException;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;
import org.junit.jupiter.api.*;

public class TestPawnStub {
	
	Board b;
	Pawn p;
	
	@BeforeEach 
	public void Setup(){
		// to be completed:
		// create a mock for Board
		// and stub the necessary methods
		b = mock(Board.class);
		p = new Pawn('p',8,9,b);		
	}
	
	@Test
	public void testGetX(){
		assertEquals(8,p.getX());	
	}
	
	@Test
	public void testGetY(){
		assertEquals(9,p.getY());
	}
	
	@Test
	public void testGetletter(){
		assertEquals('p',p.getLetter());
	}
	
	@Test
	public void testGetGold(){
		assertEquals(0,p.getGold());
	}	
	
	@Test
	public void testIsDead(){
		assertFalse(p.isDead());
	}

	@Test
	public void testMoveUpOK(){
		try{
			//via graph de dependances des fonctions
			when(b.getXSize()).thenReturn(10);
			when(b.getYSize()).thenReturn(10);
			when(b.getSquareContent(8, 10)).thenReturn(null);
			p.move(Direction.Up);
			assertEquals(10, p.getY());
			assertEquals(8, p.getX());
		}catch (OutOfBoardException e){
			fail();
		}
	}

	@Test
	public void testMoveUpNOK(){
		//via graph de dependances des fonctions
		when(b.getXSize()).thenReturn(9);
		when(b.getYSize()).thenReturn(9);
		when(b.getSquareContent(8, 10)).thenReturn(null);
		assertThrows(OutOfBoardException.class, ()->p.move(Direction.Up));
	}

	@Test
	public void testMoveAttack(){
		try {
			//via graph de dependances des fonctions
			Pawn p2 = new Pawn('3', 8, 10, b);
			when(b.getXSize()).thenReturn(10);
			when(b.getYSize()).thenReturn(10);
			when(b.getSquareContent(8, 10)).thenReturn(p2);
			when(b.isBonusSquare(8, 9)).thenReturn(false);
			p.move(Direction.Up);
			p.move(Direction.Up);
			p.move(Direction.Up);
			assertEquals(p.getX(), 8);
			assertEquals(p.getY(), 9);
			assertEquals(p.getGold(), 1);
            assertTrue(p2.isDead());
		}catch (OutOfBoardException e){
			fail();
		}
	}
	@Test
	public void testMoveAttackBonus(){
		try {
			//via graph de dependances des fonctions
			Pawn p2 = new Pawn('3', 8, 10, b);
			when(b.getXSize()).thenReturn(10);
			when(b.getYSize()).thenReturn(10);
			when(b.getSquareContent(8, 10)).thenReturn(p2);
			when(b.isBonusSquare(8, 9)).thenReturn(true);
			p.move(Direction.Up);
			p.move(Direction.Up);
			assertEquals(p.getX(), 8);
			assertEquals(p.getY(), 9);
			assertTrue(p2.isDead());
			assertEquals(p.getGold(), 1);
		}catch (OutOfBoardException e){
			fail();
		}
	}
}
