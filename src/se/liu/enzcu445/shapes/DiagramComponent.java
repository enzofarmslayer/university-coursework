package se.liu.enzcu445.shapes;
import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class DiagramComponent extends JComponent {
    private ArrayList<Shape> shapes;
    @Override protected void paintComponent(final Graphics g) {
        super.paintComponent(g);
        for (Shape shape : shapes) {
            shape.draw(g); // Assuming each shape has a 'draw' method
        }
        // Senare ska vi rita upp alla former här!
    }

    public DiagramComponent(ArrayList<Shape> shapes) {
        this.shapes = shapes;
    }
    public void addShape(Shape s){
        shapes.add(s);
    }
}

