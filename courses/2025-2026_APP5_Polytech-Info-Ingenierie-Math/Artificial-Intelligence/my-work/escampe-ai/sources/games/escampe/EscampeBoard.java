package games.escampe;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import iialib.games.model.IBoard;
import iialib.games.model.Score;

public class EscampeBoard implements Partie1, IBoard<EscampeMove, EscampeRole, EscampeBoard> {

	// ---------------------- Constants ---------------------

	public static final int SIZE = 6;

	// Carte des liserés (figure 4 du sujet).
	// LISERAIS[i][j] avec i = (numéro de ligne du jeu) - 1 (i=0 -> ligne 1, en bas).
	private static final int[][] LISERAIS = {
			{ 1, 2, 2, 3, 1, 2 }, // ligne 1
			{ 3, 1, 3, 1, 3, 2 }, // ligne 2
			{ 2, 3, 1, 2, 1, 3 }, // ligne 3
			{ 2, 1, 3, 2, 3, 1 }, // ligne 4
			{ 1, 3, 1, 3, 1, 2 }, // ligne 5
			{ 3, 2, 2, 1, 3, 2 }  // ligne 6
	};

	private static final char EMPTY = '-';
	private static final char W_LICORNE = 'B';
	private static final char W_PALADIN = 'b';
	private static final char N_LICORNE = 'N';
	private static final char N_PALADIN = 'n';

	private static final int[][] DIRS = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

	// ---------------------- Attributes ---------------------

	private final char[][] boardGrid;
	// Liseré obligatoire pour le prochain coup (0 = aucune contrainte).
	private int requiredLisere;
	// Bord choisi par les noirs : 0 = non encore choisi, 1 = bas (lignes 1-2), 6 = haut (lignes 5-6).
	private int blackBorder;

	// ---------------------- Constructors ---------------------

	public EscampeBoard() {
		boardGrid = new char[SIZE][SIZE];
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				boardGrid[i][j] = EMPTY;
		requiredLisere = 0;
		blackBorder = 0;
	}

	public EscampeBoard(EscampeBoard other) {
		boardGrid = new char[SIZE][SIZE];
		for (int i = 0; i < SIZE; i++)
			System.arraycopy(other.boardGrid[i], 0, boardGrid[i], 0, SIZE);
		requiredLisere = other.requiredLisere;
		blackBorder = other.blackBorder;
	}

	// --------------------- Partie1 Methods ---------------------

	@Override
	public String[] possiblesMoves(String playerRole) {
		// Phase de placement : si le joueur n'a pas encore posé ses pièces.
		if (!hasPlacedPieces(playerRole)) {
			return placementMoves(playerRole).toArray(new String[0]);
		}
		List<String> moves = movePhaseMoves(playerRole);
		if (moves.isEmpty()) {
			return new String[] { "E" };
		}
		return moves.toArray(new String[0]);
	}

	@Override
	public void play(String move, String playerRole) {
		if (move.equals("E")) {
			// Tour passé : la contrainte de liseré est levée pour l'adversaire.
			requiredLisere = 0;
			return;
		}
		if (move.contains("/")) {
			playPlacement(move, playerRole);
			return;
		}
		String[] parts = move.split("-");
		int[] from = parseCell(parts[0]);
		int[] to = parseCell(parts[1]);
		char piece = boardGrid[from[0]][from[1]];
		boardGrid[from[0]][from[1]] = EMPTY;
		boardGrid[to[0]][to[1]] = piece;
		// La case d'arrivée détermine le liseré obligatoire pour l'adversaire.
		requiredLisere = LISERAIS[to[0]][to[1]];
	}

	@Override
	public boolean isValidMove(String move, String playerRole) {
		if (move == null || move.isEmpty()) return false;
		if (!isValidPlayer(playerRole)) return false;

		if (move.equals("E")) {
			// Le joueur ne peut passer son tour QUE s'il n'a aucun coup possible.
			if (!hasPlacedPieces(playerRole)) return false;
			return movePhaseMoves(playerRole).isEmpty();
		}

		if (move.contains("/")) {
			return isValidPlacement(move, playerRole);
		}

		// Coup classique : "Xn-Yn"
		if (!move.matches("[A-Fa-f][1-6]-[A-Fa-f][1-6]")) return false;
		String[] parts = move.split("-");
		int[] from = parseCell(parts[0]);
		int[] to = parseCell(parts[1]);

		char piece = boardGrid[from[0]][from[1]];
		if (!isPlayerPiece(piece, playerRole)) return false;

		int lisereStart = LISERAIS[from[0]][from[1]];
		if (requiredLisere != 0 && lisereStart != requiredLisere) return false;

		// Vérifie qu'il existe un chemin orthogonal valide de longueur lisereStart.
		Set<Long> dests = new HashSet<>();
		findReachable(from[0], from[1], lisereStart, piece, dests);
		return dests.contains(encode(to[0], to[1]));
	}

	@Override
	public boolean gameOver() {
		boolean wLic = false, bLic = false;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (boardGrid[i][j] == W_LICORNE) wLic = true;
				else if (boardGrid[i][j] == N_LICORNE) bLic = true;
			}
		}
		return !wLic || !bLic;
	}

	@Override
	public void setFromFile(String fileName) {
		try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
			char[][] tmp = new char[SIZE][SIZE];
			for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++)
					tmp[i][j] = EMPTY;

			String line;
			int rowsRead = 0;
			while ((line = reader.readLine()) != null && rowsRead < SIZE) {
				String trimmed = line.trim();
				if (trimmed.isEmpty() || trimmed.startsWith("%")) continue;

				String[] tokens = trimmed.split("\\s+");
				if (tokens.length < 2) continue;
				int gameRow;
				try {
					gameRow = Integer.parseInt(tokens[0]);
				} catch (NumberFormatException e) {
					continue;
				}
				if (gameRow < 1 || gameRow > SIZE) continue;
				String cells = tokens[1];
				if (cells.length() != SIZE) continue;
				for (int j = 0; j < SIZE; j++) {
					char c = cells.charAt(j);
					if (c != EMPTY && c != W_LICORNE && c != W_PALADIN
							&& c != N_LICORNE && c != N_PALADIN) {
						throw new IOException("Caractère invalide dans le fichier : " + c);
					}
					tmp[gameRow - 1][j] = c;
				}
				rowsRead++;
			}

			for (int i = 0; i < SIZE; i++)
				System.arraycopy(tmp[i], 0, this.boardGrid[i], 0, SIZE);
			this.requiredLisere = 0;
			this.blackBorder = detectBlackBorder();
		} catch (IOException e) {
			throw new RuntimeException("Erreur lecture du fichier : " + fileName, e);
		}
	}

	@Override
	public void saveToFile(String fileName) {
		try (PrintWriter writer = new PrintWriter(new FileWriter(fileName))) {
			writer.println("%  ABCDEF");
			for (int i = 0; i < SIZE; i++) {
				String num = String.format("%02d", i + 1);
				StringBuilder sb = new StringBuilder();
				sb.append(num).append(' ');
				for (int j = 0; j < SIZE; j++) sb.append(boardGrid[i][j]);
				sb.append(' ').append(num);
				writer.println(sb);
			}
			writer.println("%  ABCDEF");
		} catch (IOException e) {
			throw new RuntimeException("Erreur écriture du fichier : " + fileName, e);
		}
	}

	// --------------------- Other Methods ---------------------

	/**
	 * Variante non-mutative de {@link #play(String, String)} : renvoie une
	 * nouvelle instance sans modifier l'objet courant. Pratique pour
	 * l'exploration d'arbres de jeu (Minimax/AlphaBeta).
	 */
	public EscampeBoard playNoEdge(String move, String playerRole) {
		EscampeBoard next = new EscampeBoard(this);
		next.play(move, playerRole);
		return next;
	}

	public char getCell(int gameRow, char colLetter) {
		return boardGrid[gameRow - 1][colLetter - 'A'];
	}

	public int getLisere(int gameRow, char colLetter) {
		return LISERAIS[gameRow - 1][colLetter - 'A'];
	}

	/** Row/col in array coordinates (0-based, row 0 = bottom). */
	public static int getLisereAt(int row, int col) {
		return LISERAIS[row][col];
	}

	public int getRequiredLisere() { return requiredLisere; }

	public void setRequiredLisere(int l) { this.requiredLisere = l; }

	public void setBlackBorder(int b) { this.blackBorder = b; }

	/** Accès direct à la grille interne (utile pour les tests, l'IA et l'heuristique). */
	public char[][] boardGrid() { return boardGrid; }

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("%  ABCDEF\n");
		// Affichage "physique" : ligne 6 en haut, ligne 1 en bas.
		for (int i = 0; i < SIZE; i++) {
			String num = String.format("%02d", i + 1);
			sb.append(num).append(' ');
			for (int j = 0; j < SIZE; j++) sb.append(boardGrid[i][j]);
			sb.append(' ').append(num).append('\n');
		}
		sb.append("%  ABCDEF\n");
		sb.append("(liseré requis pour le prochain coup : ")
				.append(requiredLisere == 0 ? "aucun" : requiredLisere).append(")\n");
		return sb.toString();
	}

	// =====================================================================
	// iialib.IBoard – versions typées Move/Role pour réutiliser AlphaBeta/MiniMax
	// =====================================================================

	@Override
	public ArrayList<EscampeMove> possibleMoves(EscampeRole role) {
		// AlphaBeta uses isEmpty() on terminal nodes to determine win/loss:
		// empty = this player lost (their turn but game is over = opponent captured their unicorn).
		if (isGameOver()) return new ArrayList<>();
		String[] raw = possiblesMoves(role.partie1String());
		ArrayList<EscampeMove> out = new ArrayList<>(raw.length);
		for (String s : raw) out.add(new EscampeMove(s));
		return out;
	}

	@Override
	public EscampeBoard play(EscampeMove move, EscampeRole role) {
		// Immutable : on délègue à playNoEdge (copie + play mutant la copie).
		return playNoEdge(move.value(), role.partie1String());
	}

	@Override
	public boolean isValidMove(EscampeMove move, EscampeRole role) {
		return isValidMove(move.value(), role.partie1String());
	}

	@Override
	public boolean isGameOver() {
		return gameOver();
	}

	@Override
	public ArrayList<Score<EscampeRole>> getScores() {
		ArrayList<Score<EscampeRole>> scores = new ArrayList<>();
		if (!gameOver()) return scores;
		// Le perdant est celui dont la licorne a disparu.
		boolean wLic = false, bLic = false;
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) {
				if (boardGrid[i][j] == 'B') wLic = true;
				else if (boardGrid[i][j] == 'N') bLic = true;
			}
		if (!wLic) {
			scores.add(new Score<>(EscampeRole.BLANC, Score.Status.LOOSE, 0));
			scores.add(new Score<>(EscampeRole.NOIR, Score.Status.WIN, 1));
		} else if (!bLic) {
			scores.add(new Score<>(EscampeRole.BLANC, Score.Status.WIN, 1));
			scores.add(new Score<>(EscampeRole.NOIR, Score.Status.LOOSE, 0));
		}
		return scores;
	}

	// =====================================================================
	// Helpers internes
	// =====================================================================

	private static boolean isValidPlayer(String playerRole) {
		return "noir".equalsIgnoreCase(playerRole) || "blanc".equalsIgnoreCase(playerRole);
	}

	private static boolean isBlack(String playerRole) {
		return "noir".equalsIgnoreCase(playerRole);
	}

	private static boolean isPlayerPiece(char c, String playerRole) {
		if (isBlack(playerRole)) return c == N_LICORNE || c == N_PALADIN;
		return c == W_LICORNE || c == W_PALADIN;
	}

	private static boolean isLicorne(char c) {
		return c == W_LICORNE || c == N_LICORNE;
	}

	private static boolean isPaladin(char c) {
		return c == W_PALADIN || c == N_PALADIN;
	}

	private static boolean isOpponentLicorne(char c, String playerRole) {
		if (isBlack(playerRole)) return c == W_LICORNE;
		return c == N_LICORNE;
	}

	/** "B1" -> [0, 1] (ligne 1 -> indice 0, colonne B -> indice 1). */
	private static int[] parseCell(String cell) {
		char colChar = Character.toUpperCase(cell.charAt(0));
		int gameRow = Integer.parseInt(cell.substring(1));
		return new int[] { gameRow - 1, colChar - 'A' };
	}

	private static String formatCell(int row, int col) {
		return "" + (char) ('A' + col) + (row + 1);
	}

	private static long encode(int r, int c) {
		return ((long) r << 16) | (c & 0xFFFFL);
	}

	private boolean hasPlacedPieces(String playerRole) {
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				if (isPlayerPiece(boardGrid[i][j], playerRole)) return true;
		return false;
	}

	/** Si les noirs sont déjà sur le plateau, retrouve leur bord. */
	private int detectBlackBorder() {
		for (int j = 0; j < SIZE; j++) {
			if (isPlayerPiece(boardGrid[0][j], "noir") || isPlayerPiece(boardGrid[1][j], "noir")) return 1;
			if (isPlayerPiece(boardGrid[5][j], "noir") || isPlayerPiece(boardGrid[4][j], "noir")) return 6;
		}
		return 0;
	}

	// ---------------- Phase de placement ----------------

	private boolean isValidPlacement(String move, String playerRole) {
		String[] cells = move.split("/");
		if (cells.length != SIZE) return false;

		Set<Long> seen = new HashSet<>();
		int[][] coords = new int[SIZE][2];
		for (int i = 0; i < cells.length; i++) {
			if (!cells[i].matches("[A-Fa-f][1-6]")) return false;
			int[] c = parseCell(cells[i]);
			coords[i] = c;
			if (!seen.add(encode(c[0], c[1]))) return false; // doublon
		}

		// Détermine le bord du joueur. Pour le noir : libre (bas ou haut),
		// mais toutes les pièces doivent être dans 2 lignes contiguës d'un même bord.
		// Pour le blanc : doit prendre le bord opposé à celui du noir (s'il a déjà joué).
		Integer requiredBorder = null;
		if (isBlack(playerRole)) {
			if (blackBorder != 0) return false; // déjà placé
		} else {
			if (blackBorder == 1) requiredBorder = 6;
			else if (blackBorder == 6) requiredBorder = 1;
		}

		// Détecte le bord d'après les coordonnées proposées.
		boolean allBottom = true, allTop = true;
		for (int[] c : coords) {
			int row = c[0]; // 0 ou 1 pour bas, 4 ou 5 pour haut
			if (row != 0 && row != 1) allBottom = false;
			if (row != 4 && row != 5) allTop = false;
		}
		if (!allBottom && !allTop) return false;
		int chosen = allBottom ? 1 : 6;
		if (requiredBorder != null && chosen != requiredBorder) return false;

		// Les cases doivent être vides (sauf si on rejoue par-dessus son propre placement).
		for (int[] c : coords) {
			char existing = boardGrid[c[0]][c[1]];
			if (existing != EMPTY && !isPlayerPiece(existing, playerRole)) return false;
		}

		return true;
	}

	private void playPlacement(String move, String playerRole) {
		String[] cells = move.split("/");
		char licorne = isBlack(playerRole) ? N_LICORNE : W_LICORNE;
		char paladin = isBlack(playerRole) ? N_PALADIN : W_PALADIN;

		int[] lic = parseCell(cells[0]);
		boardGrid[lic[0]][lic[1]] = licorne;
		for (int i = 1; i < cells.length; i++) {
			int[] c = parseCell(cells[i]);
			boardGrid[c[0]][c[1]] = paladin;
		}

		if (isBlack(playerRole)) {
			blackBorder = (lic[0] <= 1) ? 1 : 6;
		}
		// Le placement ne contraint pas le liseré du prochain coup.
		requiredLisere = 0;
	}

	/**
	 * Génère un échantillon de placements valides. Le nombre total de
	 * placements étant énorme (12*C(11,5)*permutations), on se contente ici
	 * de produire quelques placements canoniques utiles pour les tests/IA.
	 * Les bords disponibles dépendent de l'avancée du jeu.
	 */
	private List<String> placementMoves(String playerRole) {
		List<String> result = new ArrayList<>();
		List<Integer> borders = new ArrayList<>();
		if (isBlack(playerRole)) {
			borders.add(1);
			borders.add(6);
		} else {
			if (blackBorder == 1) borders.add(6);
			else if (blackBorder == 6) borders.add(1);
			else { borders.add(1); borders.add(6); }
		}

		for (int border : borders) {
			int rowLic = (border == 1) ? 0 : 5; // licorne sur la ligne extrême du bord
			int rowPal = (border == 1) ? 1 : 4; // paladins sur la deuxième ligne
			// Place la licorne en colonne C par défaut puis 5 paladins sur l'autre ligne.
			StringBuilder sb = new StringBuilder();
			sb.append(formatCell(rowLic, 2));
			int placed = 0;
			for (int j = 0; j < SIZE && placed < 5; j++) {
				sb.append('/').append(formatCell(rowPal, j));
				placed++;
			}
			result.add(sb.toString());
		}
		return result;
	}

	// ---------------- Phase de déplacement ----------------

	private List<String> movePhaseMoves(String playerRole) {
		List<String> moves = new ArrayList<>();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				char piece = boardGrid[i][j];
				if (!isPlayerPiece(piece, playerRole)) continue;
				int lisere = LISERAIS[i][j];
				if (requiredLisere != 0 && lisere != requiredLisere) continue;

				Set<Long> dests = new HashSet<>();
				findReachable(i, j, lisere, piece, dests);
				for (long enc : dests) {
					int dr = (int) (enc >> 16);
					int dc = (int) (enc & 0xFFFFL);
					moves.add(formatCell(i, j) + "-" + formatCell(dr, dc));
				}
			}
		}
		return moves;
	}

	/**
	 * Énumère toutes les destinations atteignables depuis (sr, sc) en exactement
	 * {@code steps} pas orthogonaux, sans repasser deux fois sur la même case
	 * et sans traverser de case occupée. La case finale doit être vide ou
	 * contenir la licorne adverse (uniquement si la pièce qui se déplace est
	 * un paladin — la licorne ne capture jamais).
	 */
	private void findReachable(int sr, int sc, int steps, char piece, Set<Long> dests) {
		boolean[][] visited = new boolean[SIZE][SIZE];
		visited[sr][sc] = true;
		dfs(sr, sc, steps, piece, visited, dests);
	}

	private void dfs(int r, int c, int remaining, char piece, boolean[][] visited, Set<Long> dests) {
		if (remaining == 0) {
			char target = boardGrid[r][c];
			if (target == EMPTY) {
				dests.add(encode(r, c));
			} else if (isPaladin(piece) && isOpponentLicorne(target, isWhitePiece(piece) ? "blanc" : "noir")) {
				dests.add(encode(r, c));
			}
			return;
		}
		for (int[] d : DIRS) {
			int nr = r + d[0], nc = c + d[1];
			if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) continue;
			if (visited[nr][nc]) continue;
			char target = boardGrid[nr][nc];
			if (remaining > 1) {
				// Cases intermédiaires : doivent être vides.
				if (target != EMPTY) continue;
			} else {
				// Dernière case : vide, ou licorne adverse si c'est un paladin.
				if (target != EMPTY) {
					if (!isPaladin(piece)) continue;
					if (!isOpponentLicorne(target, isWhitePiece(piece) ? "blanc" : "noir")) continue;
				}
			}
			visited[nr][nc] = true;
			dfs(nr, nc, remaining - 1, piece, visited, dests);
			visited[nr][nc] = false;
		}
	}

	private static boolean isWhitePiece(char c) {
		return c == W_LICORNE || c == W_PALADIN;
	}

	// =====================================================================
	// Démonstration
	// =====================================================================

	public static void main(String[] args) {
		System.out.println("=== Démonstration EscampeBoard ===\n");

		// 1) Création d'un plateau vide + placement initial des deux joueurs.
		EscampeBoard board = new EscampeBoard();
		System.out.println("Plateau vide :");
		System.out.println(board);

		String blackPlacement = "C6/A6/B5/D5/E6/F5";
		String whitePlacement = "C1/A1/B2/D2/E1/F1";

		System.out.println("Placement noir (" + blackPlacement + ") valide ? "
				+ board.isValidMove(blackPlacement, "noir"));
		board.play(blackPlacement, "noir");

		System.out.println("Placement blanc (" + whitePlacement + ") valide ? "
				+ board.isValidMove(whitePlacement, "blanc"));
		board.play(whitePlacement, "blanc");

		System.out.println("\nAprès placement :");
		System.out.println(board);

		// 2) Coups possibles pour blanc (premier joueur, aucune contrainte de liseré).
		String[] whiteMoves = board.possiblesMoves("blanc");
		System.out.println("Coups possibles pour blanc (" + whiteMoves.length + ") :");
		for (String m : whiteMoves) System.out.print(m + "  ");
		System.out.println("\n");

		// 3) Joue le premier coup possible et vérifie le liseré requis pour le noir.
		if (whiteMoves.length > 0 && !whiteMoves[0].equals("E")) {
			String mv = whiteMoves[0];
			System.out.println("Blanc joue : " + mv);
			board.play(mv, "blanc");
			System.out.println("Liseré requis pour le noir : " + board.getRequiredLisere());
			System.out.println(board);
		}

		// 4) Coups possibles pour noir avec la contrainte courante.
		String[] blackMoves = board.possiblesMoves("noir");
		System.out.println("Coups possibles pour noir (" + blackMoves.length + ") :");
		for (String m : blackMoves) System.out.print(m + "  ");
		System.out.println("\n");

		// 5) Vérification d'un coup invalide (mauvais liseré).
		String invalid = "A6-A5";
		System.out.println("Le coup " + invalid + " (noir) est-il valide ? "
				+ board.isValidMove(invalid, "noir"));

		// 6) Détection de fin de partie.
		System.out.println("Fin de partie ? " + board.gameOver());

		// 7) Sauvegarde / relecture.
		String tmpFile = "escampe_demo.txt";
		board.saveToFile(tmpFile);
		System.out.println("\nPlateau sauvegardé dans " + tmpFile);

		EscampeBoard reloaded = new EscampeBoard();
		reloaded.setFromFile(tmpFile);
		System.out.println("Plateau rechargé :");
		System.out.println(reloaded);

		// 8) Scénario de capture (figure 6 du sujet).
		System.out.println("=== Scénario de capture (figure 6) ===");
		EscampeBoard capture = new EscampeBoard();
		// Position : noirs licorne C1, paladins A1,B1,C4,D4,A6 ; blancs licorne C6, paladins A4,C5,C2,F6,F3.
		capture.boardGrid[0][0] = N_PALADIN; // A1
		capture.boardGrid[0][1] = N_PALADIN; // B1
		capture.boardGrid[0][2] = N_LICORNE; // C1
		capture.boardGrid[1][2] = W_PALADIN; // C2
		capture.boardGrid[2][5] = W_PALADIN; // F3
		capture.boardGrid[3][0] = W_PALADIN; // A4
		capture.boardGrid[3][2] = N_PALADIN; // C4
		capture.boardGrid[3][3] = N_PALADIN; // D4
		capture.boardGrid[4][2] = W_PALADIN; // C5
		capture.boardGrid[5][0] = N_PALADIN; // A6
		capture.boardGrid[5][2] = W_LICORNE; // C6
		capture.boardGrid[5][5] = W_PALADIN; // F6
		// Le noir vient de jouer en D4, dont le liseré est :
		capture.requiredLisere = LISERAIS[3][3];
		capture.blackBorder = 1;
		System.out.println(capture);
		System.out.println("Liseré obligatoire (D4) = " + capture.requiredLisere
				+ " — le blanc doit partir d'une case de ce liseré.");

		// C2 a liseré 3 : le blanc ne PEUT PAS encore capturer directement.
		System.out.println("C2-C1 directement ? "
				+ capture.isValidMove("C2-C1", "blanc")
				+ "  (faux : il faut d'abord forcer le noir sur une case liseré 3)");

		// Séquence tactique du sujet : F6-E5  puis  A1-A2  puis  C2-C1 (capture).
		System.out.println("\nSéquence : F6-E5 (blanc) -> A1-A2 (noir) -> C2-C1 (blanc, capture)");

		System.out.println("F6-E5 (blanc) valide ? " + capture.isValidMove("F6-E5", "blanc"));
		capture.play("F6-E5", "blanc");
		System.out.println("Liseré requis pour noir = " + capture.getRequiredLisere());

		System.out.println("A1-A2 (noir) valide ? " + capture.isValidMove("A1-A2", "noir"));
		capture.play("A1-A2", "noir");
		System.out.println("Liseré requis pour blanc = " + capture.getRequiredLisere());

		System.out.println("C2-C1 (blanc) valide ? " + capture.isValidMove("C2-C1", "blanc"));
		capture.play("C2-C1", "blanc");

		System.out.println("\nAprès capture :");
		System.out.println(capture);
		System.out.println("Fin de partie ? " + capture.gameOver());
	}
}
