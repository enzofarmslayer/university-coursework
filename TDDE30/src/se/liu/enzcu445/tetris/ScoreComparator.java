package se.liu.enzcu445.tetris;

import java.util.Comparator;

public class ScoreComparator implements Comparator<Highscore> {

    @Override
    public int compare(Highscore o1, Highscore o2) {
	return Integer.compare(o1.getScore(), o2.getScore());
    }
}

