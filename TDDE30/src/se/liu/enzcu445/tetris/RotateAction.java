package se.liu.enzcu445.tetris;

import javax.swing.*;
import java.awt.event.ActionEvent;

public class RotateAction extends AbstractAction
{
    private Direction direction;
    private Board board;

    public RotateAction(Board board, Direction direction) {
	this.board = board;
	this.direction = direction;
    }

    @Override public void actionPerformed(ActionEvent e) {
	board.rotate(direction);
    }

    public static void setupKeyBindings(JFrame frame, Board board) {
	InputMap in = frame.getRootPane().getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW);
	ActionMap am = frame.getRootPane().getActionMap();

	in.put(KeyStroke.getKeyStroke("UP"), "rotateLeft");
	am.put("rotateLeft", new RotateAction(board, Direction.LEFT));

	in.put(KeyStroke.getKeyStroke("DOWN"), "rotateRight");
	am.put("rotateRight", new RotateAction(board, Direction.RIGHT));
    }
}

