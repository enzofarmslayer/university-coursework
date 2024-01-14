package se.liu.enzcu445.tetris;
import javax.swing.JComponent;
import java.awt.Dimension;
import java.awt.Graphics;

// Antag att Board är en klass som representerar spelets bräde
public class TetrisComponent extends JComponent {
    private Board board; // Fält för att lagra referensen till spelets bräde

    // Konstruktor som tar emot ett Board-objekt
    public TetrisComponent(Board board) {
        this.board = board;
    }

    @Override
    public Dimension getPreferredSize() {
        // Antag att varje block i Tetris är 30x30 pixlar
        // och brädet är 10 block brett och 20 block högt
        int width = 10 * 30; // Bredden på Tetris-brädet i pixlar
        int height = 20 * 30; // Höjden på Tetris-brädet i pixlar

        // Returnera den föredragna storleken för denna komponent
        return new Dimension(width, height);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        // Här kan du lägga till kod för att rita upp Tetris-brädet
    }
}