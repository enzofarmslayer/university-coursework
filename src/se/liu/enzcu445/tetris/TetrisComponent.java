package se.liu.enzcu445.tetris;
import javax.swing.JComponent;
import java.awt.*;
import java.util.EnumMap;

public class TetrisComponent extends JComponent implements BoardListener{
    private Board board;
    private final static int SQUARE_SIZE = 20;
    private final static EnumMap<SquareType, Color> SQUARE_COLORS = createColorMap();

    private static EnumMap<SquareType, Color> createColorMap() {
        EnumMap<SquareType, Color> colorMap = new EnumMap<>(SquareType.class);
        colorMap.put(SquareType.EMPTY, Color.BLACK);
        colorMap.put(SquareType.I, Color.CYAN);
        colorMap.put(SquareType.O, Color.YELLOW);
        colorMap.put(SquareType.T, Color.MAGENTA);
        colorMap.put(SquareType.S, Color.GREEN);
        colorMap.put(SquareType.Z, Color.RED);
        colorMap.put(SquareType.J, Color.BLUE);
        colorMap.put(SquareType.L, Color.ORANGE);
        colorMap.put(SquareType.OUTSIDE, Color.BLACK);
        return colorMap;
    }

    public TetrisComponent(Board board) {
        this.board = board;
    }

    @Override
    public Dimension getPreferredSize() {
        int width = (SQUARE_SIZE * board.getWidth());
        int height = SQUARE_SIZE * board.getHeight();

        return new Dimension(width, height);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        final Graphics2D g2d = (Graphics2D) g;
        for (int y = 0; y < board.getHeight(); y++) {
            for (int x = 0; x < board.getWidth(); x++) {
                SquareType type = board.getVisibleSquaresAt(y,x);
                g2d.setColor(SQUARE_COLORS.get(type));
                g2d.fillRect(x*SQUARE_SIZE, y*SQUARE_SIZE, SQUARE_SIZE,SQUARE_SIZE);
                g2d.setColor(Color.BLACK);
                g2d.setStroke(new BasicStroke(2));
                g2d.drawRect(x*SQUARE_SIZE, y*SQUARE_SIZE, SQUARE_SIZE,SQUARE_SIZE);
            }
        }
    }

    @Override public void boardChanged() {
        repaint();
    }
}