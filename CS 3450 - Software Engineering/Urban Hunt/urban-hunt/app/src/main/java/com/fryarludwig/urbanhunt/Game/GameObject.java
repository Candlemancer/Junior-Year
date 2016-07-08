package com.fryarludwig.urbanhunt.Game;

import com.google.android.gms.maps.model.LatLng;

/**
 * Created by candlemancer on 4/25/15.
 */
public class GameObject {

    private LatLng location;
    private int score;

    // Constructors
    public GameObject(LatLng initLocation, int initScore) {
        location = initLocation;
        score = initScore;
    }


    // Member Functions
    public void action() {
        // Empty
    }


    // Mutators
    public void setLocation(LatLng coords) {
        location = coords;
    }

    public void setScore(int newScore) {
        score = newScore;
    }


    // Accessors
    public LatLng getLocation() {
        return location;
    }

    public int getScore() {
        return score;
    }

}
