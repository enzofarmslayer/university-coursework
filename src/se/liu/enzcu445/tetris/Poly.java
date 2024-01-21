package se.liu.enzcu445.tetris;

public class Poly {
    private SquareType[][] shape;
    private int width;
    private int height;

    public SquareType[][] getShape() {
        return shape;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public Poly(SquareType[][] shape) {
        this.shape = shape;
        this.width = shape[0].length;
        this.height = shape.length;
    }
}
