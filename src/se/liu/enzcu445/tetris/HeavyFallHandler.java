package se.liu.enzcu445.tetris;

public class HeavyFallHandler extends AbstractFallHandler
{
    @Override public boolean checkHeavyCollistion(final Board board, final int boardY, final int boardX, final int oldX) {
	boolean movingStraightDown = (board.getFallingPosX() - oldX == 0);
	if (movingStraightDown) {
	    if (board.getSquareType(boardY, boardX) != SquareType.EMPTY) {
		if (!board.canCollapseBelow(board, boardY, boardX, board.getFallingPos())) {
		    // If canCollapseBelow is false, we have a collision and the piece should lock in place.
		    return true;
		} else {// If canCollapseBelow is true, we collapse the squares below it
		    board.collapseBelow(board, boardY, boardX);
		    return false;
		}
	    }
	}
    return false;
    }

    @Override public boolean checkPieceCollistion(final Board board, final int boardY, final int boardX) {
	// HeavyFallhandler uses checkHeavyCollition instead of checkPieceCollistion
	return false;
    }

    @Override public String getDescription () {
	    return "Heavy";
	}
}


