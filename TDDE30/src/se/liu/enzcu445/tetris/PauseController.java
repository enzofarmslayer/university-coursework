package se.liu.enzcu445.tetris;

public class PauseController {
    private boolean paused;

    public PauseController() {
	this.paused = false;
    }

    public void togglePause() {
	paused = !paused;
    }

    public String pauseText(){
	if (paused){
	    return "Unpause";
	}
	else{
	    return "Pause";
	}
    }
    public boolean isPaused() {
	return paused;
    }
}

