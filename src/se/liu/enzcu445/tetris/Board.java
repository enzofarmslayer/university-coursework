package se.liu.enzcu445.tetris;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Random;

public class Board
{
    private final static Random RND = new Random();
    private SquareType[][] squares;
    private int width;
    private int height;
    private Poly falling = null;
    private Point fallingPos = null;
    private List<BoardListener> listeners = new ArrayList<>();
    private TetrominoMaker tetrominoMaker = new TetrominoMaker();
    private static final int MARGIN = 2;
    private static final int DOUBLE_MARGIN = MARGIN * 2;
    private boolean gameOver = false;
    private int score;
    private static final Map<Integer, Integer> SCORE_MAP = Map.of(1, 100, 2, 300, 3, 500, 4, 800);
    private FallHandler currentFallHandler = new DefaultFallHandler();

    private final int pieceAmount = 7;

    public Poly getFalling() {
        return falling;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public int getScore() {
        return score;
    }

    private Point previousFallingPos = new Point();

    public SquareType getSquareType(int height, int width) {
        return squares[height][width];
    }

    public Board(int height, int width) {
        this.squares = new SquareType[height + DOUBLE_MARGIN][width + DOUBLE_MARGIN];
        this.width = width;
        this.height = height;
        this.score = 0;

        constructBoard();
        notifyListeners();
    }

    public Point getFallingPos() {
        return fallingPos;
    }

    public int getFallingPosX() {
        return fallingPos.x;
    }

    public int getFallingPosY() {
        return fallingPos.y;
    }

    public SquareType getVisibleSquaresAt(int boardY, int boardX) {
        // Justera för MARGIN
        boardY += MARGIN;
        boardX += MARGIN;

        // Kontrollera om koordinaterna är utanför brädet
        if (boardY < MARGIN || boardY >= height + MARGIN || boardX < MARGIN || boardX >= width + MARGIN) {
            return SquareType.OUTSIDE;
        }

        // Kontrollera om koordinaterna överlappar med den fallande tetrominon
        if (falling != null) {
            int x1 = fallingPos.x;
            int y1 = fallingPos.y;
            int fallingWidth = falling.getWidth();
            int fallingHeight = falling.getHeight();

            if (boardY >= y1 && boardY < y1 + fallingHeight && boardX >= x1 && boardX < x1 + fallingWidth) {
                int shapeY = boardY - y1;
                int shapeX = boardX - x1;
                SquareType type = falling.getShape()[shapeY][shapeX];
                if (type != SquareType.EMPTY) {
                    return type;
                }
            }
        }
        // Returnera typen av statiska block
        return squares[boardY][boardX];
    }


    public void buildBoardWithRndSquare() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                squares[y][x] = SquareType.values()[RND.nextInt(pieceAmount)];
            }
        }
        notifyListeners();
    }

    public void addBoardListener(BoardListener bl) {
        listeners.add(bl);
    }

    private void notifyListeners() {
        for (BoardListener listener : listeners) {
            listener.boardChanged();
        }
    }

    public void tick() {

        if (gameOver) {
            return;
        }

        if (falling == null) {
            falling = tetrominoMaker.getPoly(RND.nextInt(pieceAmount));//RND.nextInt(7)
            fallingPos = new Point(((width + MARGIN) / 2), MARGIN);
            if (hasCollision()) {
                gameOver = true;
            }
        } else {
            previousFallingPos = new Point(fallingPos);
            fallingPos.y += 1;
            if (hasCollision()) {
                fallingPos = new Point(previousFallingPos);
                for (int y = MARGIN; y < height + MARGIN; y++) {
                    for (int x = MARGIN; x < width + MARGIN; x++) {
                        squares[y][x] = getVisibleSquaresAt(y - MARGIN, x - MARGIN);
                    }
                }
                clearFilledLines();
                falling = null;
            }
        }
        notifyListeners();
    }

    public void move(Direction direction) {
        previousFallingPos = new Point(fallingPos);

        switch (direction) {
            case RIGHT:
                fallingPos.x += 1;
                break;
            case LEFT:
                fallingPos.x -= 1;
                break;
            default:
                break;
        }

        if (hasCollision()) {
            fallingPos = new Point(previousFallingPos); // Revert position due to collision
        }

        notifyListeners();
    }

    private boolean hasCollision() {
        return currentFallHandler.hasCollision(this, previousFallingPos.x);
    }

    public void rotate(Direction dir) {
        if (falling == null) {
            return;
        }
        Poly rotatedPoly = new Poly(new SquareType[falling.getHeight()][falling.getWidth()]);

        for (int y = 0; y < falling.getHeight(); y++) {
            for (int x = 0; x < falling.getWidth(); x++) {
                if (dir == Direction.RIGHT) {
                    rotatedPoly.getShape()[x][falling.getHeight() - 1 - y] = falling.getShape()[y][x];
                } else if (dir == Direction.LEFT) {
                    rotatedPoly.getShape()[falling.getWidth() - 1 - x][y] = falling.getShape()[y][x];
                }
            }
        }

        Poly fallingCopy = falling;
        falling = rotatedPoly;

        if (hasCollision()) {
            falling = fallingCopy;
        }
        notifyListeners();
    }

    public void clearFilledLines() {
        int clearedLines = 0;
        for (int y = MARGIN; y < height + MARGIN; y++) {
            boolean isFilled = true;
            for (int x = MARGIN; x < width + MARGIN; x++) {
                if (squares[y][x] == SquareType.EMPTY) {
                    isFilled = false;
                    break;
                }
            }
            if (isFilled) {
                clearLine(y);
                clearedLines += 1;
            }
        }
        updateScore(clearedLines);
        activateFallthroughPowerup(clearedLines);
        notifyListeners();
    }

    public void activateFallthroughPowerup(int clearedLines) {

        if (clearedLines > 1) {
         currentFallHandler = new HeavyFallHandler();
        }
        else if (clearedLines == 1) {
            currentFallHandler = new FallthroughFallHandler();
        }
        else {
            currentFallHandler = new DefaultFallHandler();
        }
    }

    public String getCurrentFallHandlerDescription() {
        return currentFallHandler.getDescription();
    }

    private void clearLine(int clearLineY) {
        for (int x = MARGIN; x < getWidth() + MARGIN; x++) {
            for (int y = clearLineY; y > MARGIN; y--) {
                squares[y][x] = squares[y - 1][x];
            }
        }
    }

    private void updateScore(int clearedLines) {
        if (clearedLines > 0) {
            score += SCORE_MAP.getOrDefault(clearedLines, 0);
        }
    }

    public boolean isGameOver() {
        return gameOver;
    }

    public static int getMARGIN() {
        return MARGIN;
    }

    public void resetGame() {
        // Reset score and game over flag
        falling = null;
        score = 0;
        gameOver = false;

        constructBoard();
        notifyListeners();
    }

    private void constructBoard() {
        for (int y = 0; y < height + DOUBLE_MARGIN; y++) {
            for (int x = 0; x < width + DOUBLE_MARGIN; x++) {
                if (y < MARGIN || y >= height + MARGIN || x < MARGIN || x >= width + MARGIN) {
                    squares[y][x] = SquareType.OUTSIDE;
                } else {
                    squares[y][x] = SquareType.EMPTY;
                }
            }
        }
    }

    public void collapseBelow(Board board, int collistionY, int collistionX) {
        for (int y = collistionY; y < board.getHeight()+MARGIN ; y++) {
            if (squares[y][collistionX] == SquareType.EMPTY){
                for (int y2 = y; y2 > collistionY-board.getFalling().getHeight() ; y2--) {
                    squares[y2][collistionX] = squares[y2-1][collistionX];
                }
                notifyListeners();
                break;
            }
        }
        notifyListeners();
    }

    public boolean canCollapseBelow(Board board, int collistionY, int collistionX, Point fallingPos) {

        int fallingSquaresToRight = (fallingPos.x+board.getFalling().getWidth() - collistionX);
        int polyY = collistionY - fallingPos.y;
        boolean columnHasEmptySquare = false;

        // Iterate over the columns of the falling piece and rows below it, starting from collistionX.
        for (int x = collistionX; x < collistionX + fallingSquaresToRight; x++) {
            int polyX = x - fallingPos.x;
            if(board.getFalling().getShape()[polyY][polyX] != SquareType.EMPTY) {
                columnHasEmptySquare = false;
                for (int y = collistionY; y < board.getHeight() + MARGIN; y++) {
                    {
                        if (squares[y][x] == SquareType.EMPTY) {
                            columnHasEmptySquare = true;
                            break;
                        }
                    }
                }
            }

            // If any column is found to be full (no empty squares), return false.
            if (!columnHasEmptySquare) {
                return false;
            }
        }

        // If all checked columns have at least one empty square, return true.
        return true;
    }
}

