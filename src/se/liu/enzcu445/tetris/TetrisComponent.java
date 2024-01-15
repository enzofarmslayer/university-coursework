package se.liu.enzcu445.tetris;
import javax.swing.JComponent;
import java.awt.Dimension;
import java.awt.Graphics;

public class TetrisComponent extends JComponent {
    private Board board;

    public TetrisComponent(Board board) {
        this.board = board;
    }

    @Override
    public Dimension getPreferredSize() {

        int width = 10 * 30;
        int height = 20 * 30;

        return new Dimension(width, height);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
    }
}