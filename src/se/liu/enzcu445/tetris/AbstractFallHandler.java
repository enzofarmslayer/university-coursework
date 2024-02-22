package se.liu.enzcu445.tetris;

import java.awt.*;

public class AbstractFallHandler implements FallHandler {
    /**
     * Checks if the falling piece has a collision on the board at its new position
     * based on the active Fallhandler on the falling piece
     *
     * @param board The game board.
     * @param oldX  The previous x-coordinate of the falling piece before the move.
     * @return true if there is a collision; false otherwise.
     */
    @Override public boolean hasCollision(final Board board, int oldX) {
	// Check if falling piece is on board
	if (board.getFalling() == null) {
	    return false;
	}

	// Check for collision
	for (int row = 0; row < board.getFalling().getHeight(); row++) {
	    for (int col = 0; col < board.getFalling().getWidth(); col++) {
		if (board.getFalling().getShape()[row][col] != SquareType.EMPTY) {
		    int boardY = board.getFallingPosY() + row;
		    int boardX = board.getFallingPosX() + col;

		    // if collitiiondetectors finds a collition (based on Fallhandler) a collistion is detected
		    if (checkBorderCollistion(board, boardY, boardX) || checkPieceCollistion(board, boardY, boardX)
			|| checkHeavyCollistion(board, boardY, boardX, oldX)){
			return true;
		    }
		}
	    }
	}
	return false;
    }
    @Override public String getDescription() {
	// Default implimentation for getDescription
	return null;
    }

    public boolean checkPieceCollistion(Board board, int boardY, int boardX){
	// Default implimentation for checkPieceCollitsion
	if (board.getSquareType(boardY,boardX) != SquareType.EMPTY){
	    return true;
	}
	return false;
    }

    public boolean checkBorderCollistion(Board board, int boardY, int boardX){
	// Default implimentation for checkBorderCollitsion
	if (boardY >= board.getHeight() + Board.getMARGIN() || boardX < Board.getMARGIN() ||
	    boardX >= board.getWidth() + Board.getMARGIN()) {
	    return true;
	}
	return false;
    }

    public boolean checkHeavyCollistion(Board board, int boardY, int boardX, int oldX){
	// Default implimentation for checkHeavyCollitsion
	return false;
    }

}
