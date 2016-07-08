package com.fryarludwig.urbanhunt.Controllers;

import android.content.Intent;
import android.location.Location;
import android.media.MediaPlayer;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.FragmentActivity;
import android.os.Bundle;

import com.fryarludwig.urbanhunt.Game.Game;
import com.fryarludwig.urbanhunt.Game.GameObject;
import com.fryarludwig.urbanhunt.ServerManager;
import com.fryarludwig.urbanhunt.R;

import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.LocationListener;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.maps.CameraUpdate;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.Circle;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;

import java.util.List;
import java.util.Set;
import java.util.Vector;

public class mapControl extends FragmentActivity implements GoogleApiClient.ConnectionCallbacks,
        GoogleApiClient.OnConnectionFailedListener,
        LocationListener {

    public static final String GAME_INIT = "1";
    public static final String GAME_EDIT = "2";
    public static final String PLAYER_INIT = "3";
    public static final String PLAYER_EDIT = "4";
    public static final String PLAYER_UPDATE_LOC = "5";

    public static GoogleMap mMap; // Might be null if Google Play services APK is not available.

//    private Circle myCircle;
    public Marker playerMarker;
    public Vector<Marker> otherMarkers = new Vector<>();

    private GoogleApiClient mGoogleApiClient;
    private LocationRequest mLocationRequest;

    public static Game game;

//    MediaPlayer testsound;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // Gather info from the previous screens
        super.onCreate(savedInstanceState);
        Intent previous = getIntent();

        // Set up the new game and display
        game = new Game(previous.getStringExtra("name"), previous.getStringExtra("name"));
        game.updateGameState(game.getMyUserID(), new GameObject(new LatLng(0, 0), 0));
        setContentView(R.layout.map_fragment);
        setUpMapIfNeeded();

//        testsound = MediaPlayer.create(this, R.raw.thenextworstthing);
//        testsound.setLooping(true);
//        testsound.start();

        //Start GPS Service
        mGoogleApiClient = new GoogleApiClient.Builder(this)
                .addApi(LocationServices.API)
                .addConnectionCallbacks(this)
                .addOnConnectionFailedListener(this)
                .build();
        mGoogleApiClient.connect();

        // Send an event to the server to initialize the game.
        new ServerManager().execute(GAME_INIT, game.getMyUserID());
    }

    @Override
    protected void onResume() {
        super.onResume();
        setUpMapIfNeeded();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mGoogleApiClient.disconnect();
    }

    /**
     * Sets up the map if it is possible to do so (i.e., the Google Play services APK is correctly
     * installed) and the map has not already been instantiated.. This will ensure that we only ever
     * call {@link #setUpMap()} once when {@link #mMap} is not null.
     * <p/>
     * If it isn't installed {@link SupportMapFragment} (and
     * {@link com.google.android.gms.maps.MapView MapView}) will show a prompt for the user to
     * install/update the Google Play services APK on their device.
     * <p/>
     * A user can return to this FragmentActivity after following the prompt and correctly
     * installing/updating/enabling the Google Play services. Since the FragmentActivity may not
     * have been completely destroyed during this process (it is likely that it would only be
     * stopped or paused), {@link #onCreate(Bundle)} may not be called again so we should call this
     * method in {@link #onResume()} to guarantee that it will be called.
     */

    private void setUpMapIfNeeded() {
        // Do a null check to confirm that we have not already instantiated the map.
        if (mMap == null) {
            // Try to obtain the map from the SupportMapFragment.
            mMap = ((SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.map))
                    .getMap();
            // Check if we were successful in obtaining the map.
            if (mMap != null) {
               setUpMap();
            }
        }
    }

    private void setUpMap() {
        //Set marker options and add to map
        MarkerOptions markerOptions = (new MarkerOptions()
                .position(game.getMyLastLocation()) //position is the only required attribute to make a map marker
                .visible(true)
//                .alpha(1.0f)
                .title("[" + game.getMyTeamID() + "] " + game.getMyUserID())
                .icon(BitmapDescriptorFactory.fromResource(R.drawable.stickman)));
        playerMarker = mMap.addMarker(markerOptions);

        //Update Camera Position
        CameraUpdate center = CameraUpdateFactory.newLatLng(game.getMyLastLocation());
        mMap.moveCamera(center);

        // Clean up all old markers.
        for (Marker m : otherMarkers) {
            m.remove();
        }

        // Add markers for all the other players
        MarkerOptions otherOptions;
        Set<String> keys = game.getObjects().keySet();
        for (String key : keys) {
            otherOptions = new MarkerOptions()
                    .position(game.getObjectLocationByID(key))
                    .title(key);
            otherMarkers.add(mMap.addMarker(otherOptions));
        }

//        //Set circle options and add to map
//        CircleOptions circleOptions = new CircleOptions() //Creates a new circle object and defines the center and radius
//                .center(new LatLng(playerLat, playerLon))
//                .radius(10) //In meters
//                .strokeColor(40111111)
//                .fillColor(04444444); //Color Values stored in /res/values/colors.xml
//        myCircle = mMap.addCircle(circleOptions);

        new ServerManager().execute(PLAYER_UPDATE_LOC);
        locationHandler.sendEmptyMessage(0);
    }

    Handler locationHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {

            if (mGoogleApiClient != null) {
                //Update Circle Position
//                if (myCircle != null) {
//                    myCircle.setCenter(new LatLng(playerLat, playerLon));
//                }
                //  Update My Marker position
                new ServerManager().execute(PLAYER_UPDATE_LOC);

                playerMarker.setPosition(game.getMyLastLocation());
                for (Marker m : otherMarkers) {
                    m.setPosition(game.getObjectLocationByID(m.getTitle()));
                }

                locationHandler.sendEmptyMessageDelayed(0, 1000);
            }
        }

    };

//    public static void updateEnemyLocations(LatLng coords) {
//
////        enemy1Lat = enemy1Lat + enemy1LatV;
////        enemy1Lon = enemy1Lon + enemy1LonV;
////
////        if (enemy1Lat >= 90.0) { enemy1Lat = -90.0; }
////        if (enemy1Lat <= -90.0) { enemy1Lat = 90.0; }
////        if (enemy1Lon >= 180) { enemy1Lon = -180; }
////        if (enemy1Lon <= -180) { enemy1Lon = 180; }
////
////        if (enemy1Lat >= playerLat + 1.005000 || enemy1Lat <= playerLat - 1.005000) { enemy1LatV *= -1; }
////        if (enemy1Lon >= playerLon + 1.005000 || enemy1Lon <= playerLon - 1.005000) { enemy1LonV *= -1; }
//
//        enemy1Marker.setPosition(coords);
//    }

    private boolean testUpdateMarkerPosition(LatLng coords) {

        MarkerOptions testOptions = new MarkerOptions().position(new LatLng(0, 0));
        Marker test = mMap.addMarker(testOptions);
        test.setPosition(coords);
        if (test.getPosition() == coords) {
            System.out.println("[Urban-hunt] Successfully updated marker position!");
            test.remove();
            return true;
        } else {
            test.remove();
            System.out.println("[Urban-hunt] Could not update marker position!");
        }

        return false;
    }

    private boolean testGPS(){
        if (mGoogleApiClient == null) {
            System.out.println("[Urban-hunt] Successfully connected to GPS Service!");
            return true;
        }

        System.out.println("[Urban-hunt] Could not connect to GPS Service!");
        return false;
    }

    @Override
    public void onConnected(Bundle bundle) {
        mLocationRequest = LocationRequest.create();
        mLocationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
        mLocationRequest.setInterval(1000); //Update location every 1 seconds
        mLocationRequest.setFastestInterval(1000); //Update every 1 second at the most
        LocationServices.FusedLocationApi.requestLocationUpdates(mGoogleApiClient, mLocationRequest, this);
        new ServerManager().execute(PLAYER_INIT);
    }

    @Override
    public void onConnectionSuspended(int i) {

    }

    @Override
    public void onLocationChanged(Location location) {
        //Update Location Variables
        LatLng myPosition = new LatLng(location.getLatitude(), location.getLongitude());
        game.updateObjectLocation(game.getMyUserID(), myPosition);

    }

    @Override
    public void onConnectionFailed(ConnectionResult connectionResult) {

    }
}
