package se.liu.enzcu445.tetris;

import java.util.Timer;
import java.util.TimerTask;
import javax.swing.JTextArea;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;

public class BoardTester {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Board board = new Board(10, 5);

            JFrame frame = new JFrame("Tetris");
            JTextArea textArea = new JTextArea();
            frame.add(textArea);
            frame.setSize(300, 300);
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setVisible(true);

            // Skapa och starta timern
            Timer timer = new Timer();
            timer.scheduleAtFixedRate(new TimerTask() {
                @Override
                public void run() {
                    board.boardWithRndSquare();
                    updateTextArea(textArea, board);
                }
            }, 0, 1000);
        });
    }

    private static void updateTextArea(JTextArea textArea, Board board) {
        StringBuilder sb = new StringBuilder();
        for (int y = 0; y < board.getHeight(); y++) {
            for (int x = 0; x < board.getWidth(); x++) {
                sb.append(board.getSquareType(y, x));
                sb.append(" ");
            }
            sb.append("\n");
        }
        textArea.setText(sb.toString());
    }
}
