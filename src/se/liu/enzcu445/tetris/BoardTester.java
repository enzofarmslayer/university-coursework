package se.liu.enzcu445.tetris;

import java.util.Timer;
import java.util.TimerTask;
import javax.swing.JTextArea;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;

public class BoardTester {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            // Skapa ett Board-objekt
            Board board = new Board(10, 5);

            // Skapa en JFrame och JTextArea för att visa spelet
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
                    board.boardWithRndSquare(); // Uppdatera spelplanen
                    updateTextArea(textArea, board); // Uppdatera textarean
                }
            }, 0, 1000); // 0 initial delay, 1000ms period
        });
    }

    // Metod för att uppdatera textarean med den nya spelplanen
    private static void updateTextArea(JTextArea textArea, Board board) {
        // Konvertera spelplanen till en String och visa den i textarean
        StringBuilder sb = new StringBuilder();
        for (int y = 0; y < board.getHeight(); y++) {
            for (int x = 0; x < board.getWidth(); x++) {
                sb.append(board.getSquareType(y, x)); // Anpassa detta för att visa SquareType korrekt
                sb.append(" ");
            }
            sb.append("\n");
        }
        textArea.setText(sb.toString());
    }
}
