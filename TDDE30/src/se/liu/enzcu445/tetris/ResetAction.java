package se.liu.enzcu445.tetris;

import javax.swing.*;
import java.awt.event.ActionEvent;

public class ResetAction extends AbstractAction
{
    private Board board;
    public ResetAction(Board board) {
	this.board = board;
    }
    @Override public void actionPerformed(final ActionEvent e) {
	board.resetGame();
    }
}
