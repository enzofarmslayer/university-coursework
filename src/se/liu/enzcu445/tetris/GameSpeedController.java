package se.liu.enzcu445.tetris;

public class GameSpeedController
{
    private static final int INITIAL_TICK_DELAY_MS = 500;
    private static final int MINIMUM_TICK_DELAY_MS = 100;
    private static final int SPEED_INCREMENT_INTERVAL_MS = 1; // 1 minut
    private static final int TICK_DECREMENT_PER_LEVEL = 10;

    private int currentTickDelayMs;
    private long lastSpeedIncreaseTime;

    public GameSpeedController() {
	currentTickDelayMs = INITIAL_TICK_DELAY_MS;
	lastSpeedIncreaseTime = System.currentTimeMillis();
    }

    public int getCurrentTickDelayMs() {
	return currentTickDelayMs;
    }

    public void updateSpeed() {
	long currentTime = System.currentTimeMillis();
	long elapsedTimeSinceLastIncrease = currentTime - lastSpeedIncreaseTime;

	if (currentTickDelayMs > MINIMUM_TICK_DELAY_MS && elapsedTimeSinceLastIncrease >= SPEED_INCREMENT_INTERVAL_MS) {
	    currentTickDelayMs -= TICK_DECREMENT_PER_LEVEL;
	    lastSpeedIncreaseTime = currentTime;
	}
    }

    public void resetSpeed() {
	currentTickDelayMs = INITIAL_TICK_DELAY_MS;
    }
}
