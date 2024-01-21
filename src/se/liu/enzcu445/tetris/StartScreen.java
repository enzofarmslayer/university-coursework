package se.liu.enzcu445.tetris;

import javax.swing.*;

public class StartScreen extends JFrame{
    private JFrame frame;

    public StartScreen(JFrame frame) {
	this.frame = frame;
    }

    public void display() {
	ImageIcon imageIcon = new ImageIcon(ClassLoader.getSystemResource("images/foo.png"));
	JLabel label = new JLabel(imageIcon);
	frame.getContentPane().add(label);
	frame.pack();
	frame.setLocationRelativeTo(null);
	frame.setVisible(true);
    }

    public void hide() {
	frame.getContentPane().removeAll();
	frame.getContentPane().repaint();
    }
}
