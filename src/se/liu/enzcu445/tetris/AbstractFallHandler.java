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

	// Check if falling is moving straight down from previous position
	boolean movingStraightDown = (board.getFallingPosX() - oldX == 0);

	// Check for collision and collapse unsupported squares if needed
	for (int row = 0; row < board.getFalling().getHeight(); row++) {
	    for (int col = 0; col < board.getFalling().getWidth(); col++) {
		if (board.getFalling().getShape()[row][col] != SquareType.EMPTY) {
		    int boardY = board.getFallingPosY() + row;
		    int boardX = board.getFallingPosX() + col;

		    // Check out of bounds, ensure that overlappingpiece wont be OUTSIDE
		    if (boardY >= board.getHeight() + Board.getMARGIN() || boardX < Board.getMARGIN() ||
			boardX >= board.getWidth() + Board.getMARGIN()) {
			return true;
		    }

		    // Check normal collistion between pieces
		    if (this instanceof DefaultFallHandler || !movingStraightDown && this instanceof HeavyFallHandler){
			if (board.getSquareType(boardY,boardX) != SquareType.EMPTY){
			    return true;
			}
		    }

		    // Check collistion with Heavy piece
		    if (this instanceof HeavyFallHandler && movingStraightDown){
			if (board.getSquareType(boardY, boardX) != SquareType.EMPTY){
			    if (!board.canCollapseBelow(board, boardY, boardX, board.getFallingPos())){
				// If canCollapseBelow is false, we have a collision and the piece should lock in place.
				return true;
			    }
			    // If canCollapseBelow is true, we collapse the squares below it
			    board.collapseBelow(board, boardY, boardX);
			}
		    }
		}
	    }
	}
	return false;
    }
    @Override public String getDescription() {
	    return null;}
    }
