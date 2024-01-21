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
	highscores.add(highscore);
	Collections.sort(highscores, new ScoreComparator());
    }


    public void saveHighscoresToFile() throws IOException {
	Gson gson = new Gson();
	String json = gson.toJson(highscores);
	String filePath = System.getProperty("user.home") + "/HighscoreList.json";
	String tempFilePath = filePath + ".tmp";

	// Skriv till en temporär fil
	try (FileWriter writer = new FileWriter(tempFilePath)) {
	    writer.write(json);
	}

	// Byt namn på den temporära filen till den slutgiltiga filen
	File tempFile = new File(tempFilePath);
	File finalFile = new File(filePath);
	if (finalFile.exists()) {
	    finalFile.delete(); // Ta bort den gamla filen
	}
	if (!tempFile.renameTo(finalFile)) {
	    throw new IOException("Kunde inte döpa om temporärfilen till den slutgiltiga filen.");
	}
    }


    public void loadHighscoresFromFile() throws IOException {
	Gson gson = new Gson();
	String filePath = System.getProperty("user.home") + "/TetrisHighscoreList.json";
	try (FileReader reader = new FileReader(filePath)) {
	    Type type = new TypeToken<List<Highscore>>() {}.getType();
	    highscores = gson.fromJson(reader, type);
	    if (highscores == null) {
		highscores = new ArrayList<>();
	    }
	}
    }

    public List<Highscore> getAllHighscores() {
	return highscores;
    }
}
