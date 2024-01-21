package se.liu.enzcu445.tetris;

import java.awt.*;

public class DefaultFallHandler implements FallHandler {

    @Override
    public boolean hasCollision(final Board board, final Poly poly, final Point position) {
	if (poly == null) {
	    return false;
	}

        int x1 = position.x;
        int y1 = position.y;
        int fallingWidth = poly.getWidth();
        int fallingHeight = poly.getHeight();

        for (int row = 0; row < fallingHeight; row++) {
            for (int col = 0; col < fallingWidth; col++) {
                if (poly.getShape()[row][col] != SquareType.EMPTY) {
                    int boardY = y1 + row;
                    int boardX = x1 + col;

                    // Control collision out of bounds
                    if (boardY >= board.getHeight() + Board.getMARGIN() || boardX < Board.getMARGIN() || boardX >= (board.getWidth() + Board.getMARGIN())) {
                        return true;
                    }

                    // Control collision between nonEmpty squares
                    if (board.getSquares()[boardY][boardX] != SquareType.EMPTY) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}
