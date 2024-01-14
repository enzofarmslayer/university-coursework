package se.liu.enzcu445.shapes;

import java.awt.*;
import java.util.ArrayList;

public class CircleTest {
    public static void main(String[] args) {

        ArrayList<Circle> circles = new ArrayList<>();
        Circle circle1 = new Circle(1,1,1, Color.blue);
        Circle circle2 = new Circle(4,3,2, Color.green);

        circles.add(circle1);
        circles.add(circle2);

        for (Circle circle : circles) {
            System.out.println(circle.getX() +" "+ circle.getY());
        }
    }
}