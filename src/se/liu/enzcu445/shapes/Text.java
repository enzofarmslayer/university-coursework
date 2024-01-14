package se.liu.enzcu445.shapes;

import java.awt.*;

public class Text extends AbstractShape{
    private int size;
    private String text;

    public Text(int x, int y, int size, Color color, String text) {
        super(x,y,color);
        this.size = size;
        this.text = text;
    }

    public void draw(Graphics g) {
        g.setColor(color);
        g.setFont(new Font("serif", Font.PLAIN, size));
        g.drawString(text, x, y);
    }
    @Override
    public String toString() {
        return "Text{" +
                "x=" + x +
                ", y=" + y +
                ", size=" + size +
                ", color=" + color +
                ", text='" + text + '\'' +
                '}';
    }
}
