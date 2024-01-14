package se.liu.enzcu445.tetris;

import java.awt.*;
import java.util.Random;

public class Board {
    private final static Random RND = new Random();
    private SquareType[][] squares;
    private int width;
    private int height;
    private Poly falling;
    private Point fallingPos;

    public Poly getFalling() {
        return falling;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public SquareType getSquareType(int height, int width){
        return squares[height][width];
    }

    public Board(int height, int width) {
        this.squares = new SquareType[height][width];
        this.width = width;
        this.height = height;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                squares[y][x] = SquareType.EMPTY;
            }
        }
        TetrominoMaker tetrominoMaker = new TetrominoMaker();
        this.falling = tetrominoMaker.getPoly(0);
        this.fallingPos = new Point(0,0);
    }

    public Point getFallingPos() {
        return fallingPos;
    }

    public SquareType getVisibleSquaresAt(int height, int width){
        // Om det inte finns något fallande block
        if (falling == null) {
            return squares[height][width];
        }
        // Kontrollera om det fallande blocket täcker den aktuella positionen
        int blockX = fallingPos.x;
        int blockY = fallingPos.y;
        int blockWidth = falling.getWidth();
        int blockHeight = falling.getHeight();

        if (height >= blockY && height < blockY + blockHeight &&
                width >= blockX && width < blockX + blockWidth) {
            // Adjust the indices for the falling block's shape array
            int shapeY = height - blockY;
            int shapeX = width - blockX;

            // Ensure the indices are within the bounds of the falling block's shape
            if (shapeY >= 0 && shapeY < falling.getShape().length &&
                    shapeX >= 0 && shapeX < falling.getShape()[shapeY].length) {
                SquareType type = falling.getShape()[shapeY][shapeX];
                if (type != SquareType.EMPTY) {
                    return type;
                }
            }
        }

        return squares[height][width];
    }
    public void boardWithRndSquare(){
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                squares[y][x] = SquareType.values()[RND.nextInt(8)];
            }
        }
    }

    public static void main(String[] args) {
        Board board = new Board(10,10);
    }
}

