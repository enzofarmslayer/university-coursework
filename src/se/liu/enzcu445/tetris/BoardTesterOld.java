package se.liu.enzcu445.tetris;

import javax.swing.*;
import java.awt.event.ActionEvent;

public class BoardTesterOld
{
    public static void main(String[] args) {
            Board board = new Board(20, 10);
            board.boardWithRndSquare();
            JFrame frame = new JFrame("Tetris");
            JTextArea textArea = new JTextArea();
            updateTextArea(textArea, board);
            frame.add(textArea);
            frame.setSize(300, 300);
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setVisible(true);


//            Action doOneStep = new AbstractAction() {
//                @Override
//                public void actionPerformed(ActionEvent e) {
//                    board.boardWithRndSquare();
//                    updateTextArea(textArea, board);
//                }
//            };
//
//            // Create and start the timer
//            Timer timer = new Timer(1000, doOneStep);
//            timer.setCoalesce(true); // Ensure that events are not queued
//            timer.start();
    }

    private static void updateTextArea(JTextArea textArea, Board board) {
        StringBuilder sb = new StringBuilder();
        for (int y = 0; y < board.getHeight(); y++) {
            for (int x = 0; x < board.getWidth(); x++) {
                if (board.getVisibleSquaresAt(y, x) == SquareType.EMPTY) {
                    sb.append("--");
                }
                else{
                    sb.append(board.getVisibleSquaresAt(y, x));
                }
                sb.append(" ");
            }
            sb.append("\n");
        }
        textArea.setText(sb.toString());
    }
}
