package se.liu.enzcu445.tetris;

import javax.swing.*;

public class StartScreen {
    private JFrame frame;

    public StartScreen(JFrame frame) {
	this.frame = frame;
    }

    public void display() { // Displays the start screen with an image
	ImageIcon imageIcon = new ImageIcon(ClassLoader.getSystemResource("images/foo.png"));
	JLabel label = new JLabel(imageIcon);
	frame.getContentPane().add(label);
	frame.pack(); // Adjusts frame size to fit the image
	frame.setLocationRelativeTo(null); // Centers the frame on the screen
	frame.setVisible(true);
    }

    public void hide() { // Hides the start screen
	frame.getContentPane().removeAll(); // Removes all components from the frame
	frame.getContentPane().repaint(); // Repaints the frame to update the UI
    }
}

