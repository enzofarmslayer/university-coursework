package se.liu.enzcu445.shapes;

import java.awt.*;

public class Circle extends AbstractShape{
    private int radius;

    public Circle(int x, int y, int radius, Color color) {
        super(x, y, color);
        if (radius < 0) {
            throw new IllegalArgumentException("Negativ radie!");
        }
        this.radius = radius;
    }

    public int getRadius() {
        return radius;
    }

    @Override
    public void draw(Graphics g) {
        g.setColor(color);
        g.drawOval(x, y, 2*radius, 2*radius); // calc. from radius!
    }

    @Override
    public String toString() {
        return "Circle{" +
                "x=" + getX() +
                ", y=" + getY() +
                ", radius=" + radius +
                ", color=" + getColor() +
                '}';
    }
}

