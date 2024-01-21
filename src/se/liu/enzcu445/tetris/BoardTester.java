package se.liu.enzcu445.tetris;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;

public class BoardTester
{
    private final static int BOARDSQUAREHEIGHT = 20;
    private final static int BOARDSQUAREWITDH = 10;
    public static void main(String[] args) {
	TetrisViewer viewer = new TetrisViewer(new Board(BOARDSQUAREHEIGHT,BOARDSQUAREWITDH));
	viewer.show();
    }
}
