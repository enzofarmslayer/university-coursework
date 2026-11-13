package se.liu.enzcu445.tetris;

public class FallthroughFallHandler extends AbstractFallHandler
{
    @Override public boolean checkPieceCollistion(final Board board, final int boardY, final int boardX) {
	// Fallthrough should not detect collistion between pieces
	return false;
    }

    @Override public String getDescription() {
	return "Fallthrogh";
    }
}

