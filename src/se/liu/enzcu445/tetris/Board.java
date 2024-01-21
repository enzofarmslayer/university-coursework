package se.liu.enzcu445.tetris;

import java.awt.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.Random;

public class Board
{
    private final static Random RND = new Random();
    private SquareType[][] squares;
    private int width;
    private int height;
    private Poly falling;
    private Point fallingPos;
    private ArrayList<BoardListener> listeners = new ArrayList<>();
    private TetrominoMaker tetrominoMaker = new TetrominoMaker();
    private static int MARGIN = 2;
    private static int DOUBLE_MARGIN = MARGIN * 2;
    private boolean gameOver = false;
    private int score;
    private static final Map<Integer, Integer> scoreMap = Map.of(1, 100, 2, 300, 3, 500, 4, 800);
    private FallHandler fallHandler = new DefaultFallHandler();
    public Poly getFalling() {
        return falling;
    }
    public int getWidth() {
        return width;
    }
    public int getHeight() {
        return height;
    }
    public int getScore(){return score;}

    public SquareType getSquareType(int height, int width) {
        return squares[height + MARGIN][width + MARGIN];
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


        public void boardWithRndSquare() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                squares[y][x] = SquareType.values()[RND.nextInt(7)];
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

        if (gameOver){
            return;
        }

        if (falling == null) {
            falling = tetrominoMaker.getPoly(RND.nextInt(7));
            fallingPos = new Point(((width + MARGIN) / 2), MARGIN);
            if(hasCollision()){
                gameOver = true;
            }
        } else {
            fallingPos.y += 1;
            if(hasCollision()){
                fallingPos.y -= 1;
                for (int y = MARGIN; y < height+MARGIN; y++) {
                    for (int x = MARGIN; x < width+MARGIN; x++) {
                        squares[y][x] = getVisibleSquaresAt(y-MARGIN,x-MARGIN);
                    }
                }
                ClearFilledLines();
                falling = null;
            }
        }
        notifyListeners();
    }

    public void move(Direction direction) {
        switch (direction) {
            case Direction.RIGHT:
                fallingPos.x += 1;
                if(hasCollision()){
                    fallingPos.x -= 1;
                }
                break;
            case Direction.LEFT:
                fallingPos.x -= 1;
                if(hasCollision()){
                    fallingPos.x += 1;
                }
                break;
            default:
                break;
        }
        notifyListeners();
    }

    private boolean hasCollision(){
        return fallHandler.hasCollision(this, falling, fallingPos);
    }
    public SquareType[][] getSquares() {
        return squares;
    }
//    private boolean hasCollision() {
//        if (falling == null) {
//            return false;
//        }
//        int x1 = fallingPos.x;
//        int y1 = fallingPos.y;
//        int fallingWidth = falling.getWidth();
//        int fallingHeight = falling.getHeight();
//
//        for (int row = 0; row < fallingHeight; row++) {
//            for (int col = 0; col < fallingWidth; col++) {
//                if (falling.getShape()[row][col] != SquareType.EMPTY) {
//                    int boardY = y1 + row;
//                    int boardX = x1 + col;
//
//                    // Control collision out of bounds
//                    if (boardY >= height + MARGIN || boardX < MARGIN || boardX >= (width + MARGIN)) {
//                        return true;
//                    }
//
//                    // Control collision between nonEmpty squares
//                    if (squares[boardY][boardX] != SquareType.EMPTY) {
//                        return true;
//                    }
//                }
//            }
//        }
//        return false;
//    }

    public void rotate(Direction dir){
        if (falling == null){
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

        if (hasCollision()){
            falling = fallingCopy;
        }
        notifyListeners();
    }

    public void ClearFilledLines(){
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
        notifyListeners();
    }

    private void clearLine(int clearLineY){
        for (int x = MARGIN; x < getWidth()+MARGIN; x++) {
            for (int y = clearLineY; y > MARGIN; y--) {
                squares[y][x] = squares[y-1][x];
            }
        }
    }

    private void updateScore(int clearedLines) {
        if (clearedLines > 0) {
            score += scoreMap.getOrDefault(clearedLines, 0);
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

    private void constructBoard(){
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

    public static void main(String[] args) {
        //Board board = new Board(10,10);
    }
}

