package com.fryarludwig.urbanhunt.Game;

import com.google.android.gms.maps.model.LatLng;

import java.util.Hashtable;
import java.util.Random;

/**
 * Created by candlemancer on 4/25/15.
 */
public class Game {

    private final String myUserID;
    private final String myTeamID;
    private final String gameID;

    private Hashtable<String, GameObject> objects;

    // Constructors
    public Game(String myName, String myTeam) {
        myUserID = myName;
        myTeamID = myTeam;

        Random r = new Random();
        gameID = Integer.toString(r.nextInt(1000));
        objects = new Hashtable<String, GameObject>();
    }

    // Member Functions
    public void updateGameState(String key, GameObject newData) {
        objects.put(key, newData);
    }

    public void updateObjectLocation(String key, LatLng location) {
        GameObject object = objects.get(key);
        object.setLocation(location);

    }

    public LatLng getObjectLocationByID(String key) {
        return objects.get(key).getLocation();
    }

    // Accessors
    public String getMyUserID() {
        return myUserID;
    }

    public String getMyTeamID() {
        return myTeamID;
    }

    public String getGameID() {
        return gameID;
    }

    public Hashtable<String, GameObject> getObjects() {
        return objects;
    }

    public LatLng getMyLastLocation() {
        return getObjectLocationByID(getMyUserID());
    }

    public boolean testAddPlayer() {

        String testPlayerID = "Test";
        LatLng testPlayerLoc = new LatLng(0, 0);

        GameObject testPlayer = new GameObject(testPlayerLoc, 0);
        updateGameState(testPlayerID, testPlayer);

        GameObject verify = objects.get(testPlayerID);
        if (testPlayer.getLocation() == verify.getLocation() &&
            testPlayer.getScore() == verify.getScore()) {
            System.out.println("[Urban-Hunt] Correctly Added a player!");
            return true;
        }

        System.out.println("[Urban-Hunt] Could not add player!");
        return false;
    }

}
