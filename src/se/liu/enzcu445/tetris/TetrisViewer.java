package se.liu.enzcu445.tetris;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;

public class TetrisViewer {
    private JFrame frame = null;
    private Board board;
    private StartScreen startScreen = null;
    private HighscoreList highscoreList;
    private PauseController pauseController = new PauseController();
    private GameSpeedController speedController = new GameSpeedController();
    private Timer gameTimer = null;
    private JButton pauseButton = null;

    public TetrisViewer(Board board) {
        this.board = board;
        highscoreList = new HighscoreList();
        try {
            highscoreList.loadHighscoresFromFile();
        } catch (IOException e) {
            handleHighscoreIOException(e, "load");
        }
    }

    public void show() {

        frame = new JFrame("Tetris");
        frame.setResizable(false);
        frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        startScreen = new StartScreen(frame);

        startScreen.display();

        // Wait before the main game starts
	int startScreenDelay = 2000;
	Timer timer = new Timer(startScreenDelay, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                startScreen.hide();
                showTetrisGame();
            }
        });
        timer.setRepeats(false);
        timer.start();
    }
    private void showTetrisGame() {
        TetrisComponent tetrisComponent = new TetrisComponent(board);
        frame.add(tetrisComponent);
        board.addBoardListener(tetrisComponent);
        frame.setSize(tetrisComponent.getPreferredSize());

        JToolBar toolBar = new JToolBar(JToolBar.VERTICAL);
        JButton exitButton = new JButton(new ExitAction());
        exitButton.setText("Avsluta");
        toolBar.add(exitButton);

        JButton resetButton = new JButton(new ResetAction(board));

        resetButton.setText("Omstart");
        toolBar.add(resetButton);

        pauseButton = new JButton(new AbstractAction(pauseController.pauseText()) {
            @Override
            public void actionPerformed(ActionEvent e) {
                pauseController.togglePause();
                pauseButton.setText(pauseController.pauseText());
            }
        });
        toolBar.add(pauseButton);

        JLabel scoreLabel = new JLabel("\n"+"Score:" + board.getScore() + "\n");
        toolBar.add(scoreLabel);
        frame.add(toolBar, BorderLayout.EAST);

        JLabel powerupLabel = new JLabel();
        toolBar.add(powerupLabel);

        toolBar.setPreferredSize(new Dimension(150, 100));

        frame.add(toolBar, BorderLayout.EAST);
        frame.pack(); // Justerar storlek baserat på föredragna storlekar på komponenter

        //Create the gametimer
        gameTimer = new Timer(speedController.getCurrentTickDelayMs(), new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(!pauseController.isPaused()) {
                    speedController.updateSpeed();
                    gameTimer.setDelay(speedController.getCurrentTickDelayMs());
                    board.tick();
                    scoreLabel.setText("Score:" + board.getScore());
                    if (board.isGameOver()) {
                        updateHighscore();
                        board.resetGame();
                        speedController.resetSpeed();
                        gameTimer.setDelay(speedController.getCurrentTickDelayMs());
                    }
                powerupLabel.setText("Powerup:"+ board.getCurrentFallHandlerDescription());
                tetrisComponent.requestFocusInWindow();
            }
            }
        });
        gameTimer.setCoalesce(true); // Säkerställ att händelser inte köas
        gameTimer.start();

        MoveAction.setupKeyBindings(frame, board);
        RotateAction.setupKeyBindings(frame, board);
    }


    private void showHighScores() {
        JDialog dialog = new JDialog(frame, "HighScores", true);
        dialog.setLayout(new BorderLayout());

        StringBuilder formattedHighScores = new StringBuilder();
        for (Highscore highscore : highscoreList.getAllHighscores().reversed()) {
            formattedHighScores.append(highscore.toString()).append("\n");
        }
        // Create a text area to show high scores
        JTextArea textArea = new JTextArea(formattedHighScores.toString());
        textArea.setEditable(false);
        dialog.add(new JScrollPane(textArea), BorderLayout.CENTER);

        // Create a custom button
        JButton customButton = new JButton("Stäng och starta om spel");
        customButton.addActionListener(e -> dialog.dispose()); // Close dialog when button is pressed
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(customButton);
        dialog.add(buttonPanel, BorderLayout.SOUTH);

        // Set dialog size and location
        dialog.setSize(200, 200);
        dialog.setLocationRelativeTo(frame); // Center it relative to the frame

        dialog.setUndecorated(true);
        // Show the dialog
        dialog.setVisible(true);
    }
    private void updateHighscore() {
        String playerName = null;
        while (playerName == null || playerName.trim().isEmpty()) {
            playerName = JOptionPane.showInputDialog(frame, "Enter your name:", "Player Name", JOptionPane.PLAIN_MESSAGE);
        }
        Highscore highscore = new Highscore(playerName, board.getScore());
        highscoreList.addHighscore(highscore);
        showHighScores();
        try {
            highscoreList.saveHighscoresToFile();
        } catch (IOException e) {
            handleHighscoreIOException(e, "save");
        }
    }
    private void handleHighscoreIOException(IOException e, String operation) {
        int result;
        do {
            result = JOptionPane.showConfirmDialog(frame,
                                                   "Ett fel uppstod vid försök att " + operation + " highscores. Vill du försöka igen?",
                                                   "Felmeddelande",
                                                   JOptionPane.YES_NO_OPTION,
                                                   JOptionPane.ERROR_MESSAGE);
            if (result == JOptionPane.YES_OPTION) {
                try {
                    if (operation.equals("load")) {
                        highscoreList.loadHighscoresFromFile();
                    } else {
                        highscoreList.saveHighscoresToFile();
                    }
                    break; // Bryt loopen om operationen lyckas
                } catch (IOException ioException) {
                    e = ioException; // Uppdatera undantaget och försök igen
                }
            }
        } while (result == JOptionPane.YES_OPTION);
    }

}
