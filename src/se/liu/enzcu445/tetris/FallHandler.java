package se.liu.enzcu445.tetris;

import java.awt.*;

public interface FallHandler {
    boolean hasCollision(Board board, Poly poly, Point position);
}
