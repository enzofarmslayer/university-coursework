package se.liu.enzcu445.tetris;

import java.awt.*;

public interface FallHandler {
    boolean hasCollision(Board board, int fallingOldX);
    String getDescription();
}
