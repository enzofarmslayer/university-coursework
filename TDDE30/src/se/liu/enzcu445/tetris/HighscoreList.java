package se.liu.enzcu445.tetris;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class HighscoreList {
    private List<Highscore> highscores;

    public HighscoreList() {
	highscores = new ArrayList<>();
    }

    public void addHighscore(Highscore highscore) {
	// Adds a highscore to the list and sorts it
	highscores.add(highscore);
	highscores.sort(new ScoreComparator());
    }


    public void saveHighscoresToFile() throws IOException {
	// Saves the highscores list to a file
	Gson gson = new Gson();
	String json = gson.toJson(highscores);
	String filePath = System.getProperty("user.home") + "/HighscoreList.json";
	String tempFilePath = filePath + ".tmp";

	// FileWrite to a temporary file
	try (FileWriter writer = new FileWriter(tempFilePath)) {
	    writer.write(json);
	}

	// Change name on the temporary file to the final file
	File tempFile = new File(tempFilePath);
	File finalFile = new File(filePath);
	if (finalFile.exists()) {
	    boolean deleted = finalFile.delete();
	    if (!deleted) { // Check if the file was not successfully deleted
		throw new IOException("Could not delete the old file.");
	    }
	}

	if (!tempFile.renameTo(finalFile)) {
	    throw new IOException("Could not rename the temp file to the final file name.");
	}
    }

    public void loadHighscoresFromFile() throws IOException, FileNotFoundException {
	// Loads the highscores list from a file

	Gson gson = new Gson();
	String filePath = System.getProperty("user.home") + "/HighscoreList.json";
	try (FileReader reader = new FileReader(filePath)) {
	    Type type = new TypeToken<List<Highscore>>() {}.getType();
	    highscores = gson.fromJson(reader, type);
	    if (highscores == null) {
		highscores = new ArrayList<>();
	    }
	}
    }

    public List<Highscore> getHighscores() {
	return highscores;
    }
}
