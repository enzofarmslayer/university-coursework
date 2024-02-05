package se.liu.enzcu445.shapes;

import java.awt.*;
import java.util.ArrayList;

public class ShapesTest {
    public static void main(String[] args) {

        ArrayList<Shape> shapes = new ArrayList<>();

        Shape shapeCircle = new Circle(1, 1, 1, Color.blue);
        Shape shapeRectangle = new Rectangle(3, 3, 2, 2, Color.cyan);
        Shape shapeText = new Text(4,4,1,Color.black, "ee");

        shapes.add(shapeCircle);
        shapes.add(shapeRectangle);
        shapes.add(shapeText);

        for (Shape shape : shapes) {
            //shape.draw();
        }
    }
}
