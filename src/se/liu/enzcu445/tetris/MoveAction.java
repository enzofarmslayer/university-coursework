package se.liu.enzcu445.tetris;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;

public class MoveAction extends AbstractAction
{
    private Direction direction;
    private Board board;

    public MoveAction(Board board, Direction direction) {
	this.board = board;
	this.direction = direction;
    }

    @Override public void actionPerformed(ActionEvent e) {
	board.move(direction);
    }

    public static void setupKeyBindings(JFrame frame, Board board) {
	InputMap in = frame.getRootPane().getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW);
	ActionMap am = frame.getRootPane().getActionMap();

	in.put(KeyStroke.getKeyStroke("LEFT"), "moveLeft");
	am.put("moveLeft", new MoveAction(board, Direction.LEFT));

	in.put(KeyStroke.getKeyStroke("RIGHT"), "moveRight");
	am.put("moveRight", new MoveAction(board, Direction.RIGHT));
    }
}

