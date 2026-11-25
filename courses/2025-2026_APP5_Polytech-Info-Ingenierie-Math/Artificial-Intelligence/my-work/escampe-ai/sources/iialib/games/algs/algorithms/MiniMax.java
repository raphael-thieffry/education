package iialib.games.algs.algorithms;

import iialib.games.algs.GameAlgorithm;
import iialib.games.algs.IHeuristic;
import iialib.games.model.IBoard;
import iialib.games.model.IMove;
import iialib.games.model.IRole;

public class MiniMax<Move extends IMove,Role extends IRole,Board extends IBoard<Move,Role,Board>> implements GameAlgorithm<Move,Role,Board> {

	// Constants
	/** Defaut value for depth limit 
     */
	private final static int DEPTH_MAX_DEFAUT = 5;

	// Attributes
	/** Role of the max player 
     */
	private final Role playerMaxRole;

	/** Role of the min player 
     */
	private final Role playerMinRole;

	/** Algorithm max depth
     */
	private int depthMax = DEPTH_MAX_DEFAUT;

	
	/** Heuristic used by the max player 
     */
	private IHeuristic<Board, Role> h;

	//
	/** number of internal visited (developed) nodes (for stats)
     */
	private int nbNodes;
	
	/** number of leaves nodes nodes (for stats)

     */
	private int nbLeaves;

	// --------- Constructors ---------

	public MiniMax(Role playerMaxRole, Role playerMinRole, IHeuristic<Board, Role> h) {
		this.playerMaxRole = playerMaxRole;
		this.playerMinRole = playerMinRole;
		this.h = h;
	}

	//
	public MiniMax(Role playerMaxRole, Role playerMinRole, IHeuristic<Board, Role> h, int depthMax) {
		this(playerMaxRole, playerMinRole, h);
		this.depthMax = depthMax;
	}

	/*
	 * IAlgo METHODS =============
	 */

	@Override
	public Move bestMove(Board board, Role playerRole) {
		System.out.println("[MiniMax]");

		Move bestMove = null;
		int value = (playerRole.equals(playerMaxRole)) ? Integer.MIN_VALUE : Integer.MAX_VALUE;

		for (Move move : board.possibleMoves(playerRole)) {
			Board newBoard = board.play(move, playerRole);
			
			if(playerRole.equals(playerMaxRole)) {
				int m = minValue(newBoard, depthMax - 1);
				if(value < m) {
					value = m;
					System.out.println("Maxmimisation : New best move: " + move + " with value " + value);
					bestMove = move;
				}
			}else {
				int m = maxValue(newBoard, depthMax - 1);
				if(value > m) {
					value = m;
					System.out.println("Minimisation : New best move: " + move + " with value " + value);
					bestMove = move;
				}
			}
			// value = Math.max(value, minValue(newBoard, depthMax - 1));
			//if (bestMove == null || value > h.eval(board, playerMaxRole)) {
				// System.out.println("New best move: " + move + " with value " + value);
				// bestMove = move;
			//}
		}
		System.out.println("Best move: " + bestMove + " with value " + value);
		return bestMove;
	}

	/*
	 * PUBLIC METHODS ==============
	 */

        @Override
	public String toString() {
		return "MiniMax(ProfMax=" + depthMax + ")";
	}

	/*
	 * PRIVATE METHODS ===============
	 */

	private int maxValue(Board board, int depth) {
		nbNodes++;
		if (board.isGameOver()) {
			nbLeaves++;
			// max doit jouer : s'il n'a pas de move, il a perdu ; sinon c'est min qui est bloqué → max gagne
			return board.possibleMoves(playerMaxRole).isEmpty()
					? Integer.MIN_VALUE + 1
					: Integer.MAX_VALUE - 1;
		}
		if (depth == 0) {
			nbLeaves++;
			return h.eval(board, playerMaxRole);
		}
		int v = Integer.MIN_VALUE;
		for (Move move : board.possibleMoves(playerMaxRole)) {
			Board newBoard = board.play(move, playerMaxRole);
			v = Math.max(v, minValue(newBoard, depth - 1));
		}
		return v;
	}

	private int minValue(Board board, int depth) {
		nbNodes++;
		if (board.isGameOver()) {
			nbLeaves++;
			// min doit jouer : s'il n'a pas de move, min a perdu → max gagne ; sinon c'est max qui est bloqué → max perd
			return board.possibleMoves(playerMinRole).isEmpty()
					? Integer.MAX_VALUE - 1
					: Integer.MIN_VALUE + 1;
		}
		if (depth == 0) {
			nbLeaves++;
			return h.eval(board, playerMaxRole);
		}
		int v = Integer.MAX_VALUE;
		for (Move move : board.possibleMoves(playerMinRole)) {
			Board newBoard = board.play(move, playerMinRole);
			v = Math.min(v, maxValue(newBoard, depth - 1));
		}
		return v;
	}
}