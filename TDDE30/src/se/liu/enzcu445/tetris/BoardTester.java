package se.liu.enzcu445.tetris;

public class BoardTester
{
    private final static int BOARD_SQUARE_HEIGHT = 20;
    private final static int BOARD_SQUARE_WITDH = 10;
    public static void main(String[] args) {
	TetrisViewer viewer = new TetrisViewer(new Board(BOARD_SQUARE_HEIGHT, BOARD_SQUARE_WITDH));
	viewer.show();
    }
}
