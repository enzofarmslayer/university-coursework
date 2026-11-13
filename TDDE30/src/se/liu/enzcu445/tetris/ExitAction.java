package se.liu.enzcu445.tetris;
import javax.swing.*;
import java.awt.event.ActionEvent;

public class ExitAction extends AbstractAction {
    @Override public void actionPerformed(final ActionEvent e) {
	int result = JOptionPane.showConfirmDialog(null, "Vill du verkligen avsluta spelet?", "Avsluta", JOptionPane.YES_NO_OPTION);
	if (result == JOptionPane.YES_OPTION) {
	    System.exit(0);
	}
	//.requestFocusInWindow();
    }
}
