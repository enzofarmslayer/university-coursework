package se.liu.enzcu445.tetris;

public class PauseController {
    private boolean paused;

    public PauseController() {
	this.paused = false;
    }

    public void togglePause() {
	paused = !paused;
    }

    public boolean isPaused() {
	return paused;
    }
}

