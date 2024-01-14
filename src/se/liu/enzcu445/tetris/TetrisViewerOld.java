package se.liu.enzcu445.tetris;

import javax.swing.*;
import java.awt.*;


public class TetrisViewerOld {
    private JFrame frame;
    private Board board;
    private JTextArea textArea;

    public TetrisViewerOld(Board board) {
        this.board = board;
    }

    public void show(){
        frame = new JFrame("Tetris game");
        textArea = new JTextArea(board.getHeight(), board.getWidth());

        textArea.setFont(new Font("Monospaced", Font.PLAIN, 20));
        BoardToTextConverter converter = new BoardToTextConverter();
        String boardText = converter.convertToText(board);
        textArea.setText(boardText);

        frame.setLayout(new BorderLayout());
        frame.add(textArea, BorderLayout.CENTER);

        frame.pack();
        frame.setVisible(true);
    }

}
