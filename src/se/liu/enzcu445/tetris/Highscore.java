package se.liu.enzcu445.tetris;

public class Highscore
{
    private String name;
    private int score;

    public Highscore(String name, int score) {
	this.name = name;
	this.score = score;
    }

    public String getName() {
	return name;
    }

    public int getScore() {
	return score;
    }

    @Override
    public String toString() {
	return name + ": " + score;
    }
}
