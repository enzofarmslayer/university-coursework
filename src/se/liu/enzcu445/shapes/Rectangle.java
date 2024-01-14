package se.liu.enzcu445.shapes;

import java.awt.*;

public class Rectangle extends AbstractShape{
    private int height;
    private int width;

    public Rectangle(int x, int y, int height, int width, Color color) {
        super(x,y,color);
        this.height = height;
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public int getWidth() {
        return width;
    }

    public void draw(Graphics g) {
        g.setColor(color);
        g.drawRect(x, y, width, height);
    }
    @Override
    public String toString() {
        return "Rectangle{" +
                "x=" + x +
                ", y=" + y +
                ", height=" + height +
                ", width=" + width +
                ", color=" + color +
                '}';
    }
}
