package iialib.games.algs.algorithms;

import iialib.games.algs.GameAlgorithm;
import iialib.games.algs.IHeuristic;
import iialib.games.model.IBoard;
import iialib.games.model.IMove;
import iialib.games.model.IRole;

public class AlphaBeta<Move extends IMove, Role extends IRole, Board extends IBoard<Move, Role, Board>> implements GameAlgorithm<Move, Role, Board> {

	private final static int DEPTH_MAX_DEFAUT = 5;

	private final Role playerMaxRole;
	private final Role playerMinRole;
	private int depthMax = DEPTH_MAX_DEFAUT;
	private IHeuristic<Board, Role> h;

	private int nbNodes;
	private int nbLeaves;

	public AlphaBeta(Role playerMaxRole, Role playerMinRole, IHeuristic<Board, Role> h) {
		this.playerMaxRole = playerMaxRole;
		this.playerMinRole = playerMinRole;
		this.h = h;
	}

	public AlphaBeta(Role playerMaxRole, Role playerMinRole, IHeuristic<Board, Role> h, int depthMax) {
		this(playerMaxRole, playerMinRole, h);
		this.depthMax = depthMax;
	}

	@Override
	public Move bestMove(Board board, Role playerRole) {
		System.out.println("[AlphaBeta]");

		Move bestMove = null;
		int alpha = Integer.MIN_VALUE;
		int beta = Integer.MAX_VALUE;

		for (Move move : board.possibleMoves(playerRole)) {
			Board newBoard = board.play(move, playerRole);

			if (playerRole.equals(playerMaxRole)) {
				int m = minValue(newBoard, depthMax - 1, alpha, beta);
				if (m > alpha) {
					alpha = m;
					bestMove = move;
					System.out.println("Maximisation : New best move: " + move + " with value " + alpha);
				}
			} else {
				int m = maxValue(newBoard, depthMax - 1, alpha, beta);
				if (m < beta) {
					beta = m;
					bestMove = move;
					System.out.println("Minimisation : New best move: " + move + " with value " + beta);
				}
			}
		}

		System.out.println("Best move: " + bestMove);
		return bestMove;
	}

	@Override
	public String toString() {
		return "AlphaBeta(ProfMax=" + depthMax + ")";
	}

	private int maxValue(Board board, int depth, int alpha, int beta) {
		nbNodes++;
		if (board.isGameOver()) {
			nbLeaves++;
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
			v = Math.max(v, minValue(newBoard, depth - 1, alpha, beta));
			if (v >= beta)
				return v; // coupure beta
			alpha = Math.max(alpha, v);
		}
		return v;
	}

	private int minValue(Board board, int depth, int alpha, int beta) {
		nbNodes++;
		if (board.isGameOver()) {
			nbLeaves++;
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
			v = Math.min(v, maxValue(newBoard, depth - 1, alpha, beta));
			if (v <= alpha)
				return v; // coupure alpha
			beta = Math.min(beta, v);
		}
		return v;
	}
}
