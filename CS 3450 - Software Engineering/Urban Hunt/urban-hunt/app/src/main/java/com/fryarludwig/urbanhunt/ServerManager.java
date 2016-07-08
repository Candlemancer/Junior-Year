package com.fryarludwig.urbanhunt;

import android.os.AsyncTask;

import com.fryarludwig.urbanhunt.Controllers.mapControl;
import com.fryarludwig.urbanhunt.Game.Game;
import com.google.android.gms.maps.model.LatLng;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import org.json.JSONException;
import org.json.JSONObject;
import java.net.Socket;

/**
 * Created by candlemancer on 4/10/15.
 */
public class ServerManager extends AsyncTask<String, Void, Void> {

    private Exception exception;

    public static final int BUFFER_SIZE = 2048;
    private Socket socket = null;
    private PrintWriter out = null;
    private BufferedReader in = null;

    private String hostname = "fryarludwig.com";
    private int port = 21000;

    @Override
    protected Void doInBackground(String... params) {

        // Send Data
        connectToServer();

        Game g = mapControl.game;
        int commandMode = new Integer(params[0]);
        String gameID = g.getGameID();
        LatLng myCoords = g.getObjectLocationByID(g.getMyUserID());


        try {
            JSONObject message = new JSONObject();
            message.put("command", commandMode);

            switch (commandMode) {

                // GAME_INIT [command, gameid, hostid]
                case 1:
                // GAME_EDIT [command, gameId, hostId]
                case 2:
                    message.put("gameId", gameID);
                    message.put("hostId", g.getMyUserID());
                    break;

                // PLAYER_INIT [command, gameId, pid, gid, stat, lat, long]
                case 3:
                // PLAYER_EDIT [command, gameId, pid, gid, stat, lat, long]
                case 4:
                    message.put("gameId", gameID);
                    message.put("pid", g.getMyUserID());
                    message.put("gid", gameID);
                    message.put("stat", "Active");
                    message.put("lat", myCoords.latitude);
                    message.put("long", myCoords.longitude);
                    break;

                // PLAYER_UPDATE_LOC [command, gameId, pid, lat, long]
                case 5:
                    message.put("gameId", gameID);
                    message.put("pid", g.getMyUserID());
                    message.put("lat", myCoords.latitude);
                    message.put("long", myCoords.longitude);
                    break;
            }
            sendData(message.toString());

        } catch (JSONException e) {
            e.printStackTrace();
        }

        // Receive Data
//        JSONObject data = null;
//        try {
//            data = new JSONObject(recvData());
//            System.out.println("---------------------");
////            System.out.println("MyLat: " + data.get("lat"));
//            System.out.println("---------------------");
//        } catch (JSONException e) {
//            System.out.println("Error unpacking response: " + e.getMessage());
//        }
        System.out.println(recvData());

        disconnectFromServer();

        return null;
    }

    private void connectToServer() {
        try {
            if (socket == null) {
//            Socket socket = new Socket("10.0.2.2", 21000);
                Socket socket = new Socket(hostname, port);
                out = new PrintWriter(socket.getOutputStream());
                in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void disconnectFromServer() {
        if (socket != null) {
            if (socket.isConnected()) {
                try {
                    out.close();
                    in.close();
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public boolean sendData(String message) {
        if (message != null) {
//            connectToServer();
            out.write(message);
            out.flush();
            return true;
        }
        return false;
    }

    public String recvData() {
        try {
            String msg = "";
            int charsRead = 0;
            char[] buffer = new char[BUFFER_SIZE];

            while ((charsRead = in.read(buffer)) != -1) {
                msg += new String(buffer).substring(0, charsRead);
            }

//            disconnectFromServer();
//            System.out.println("[Urban-hunt] Recv'd: " + msg);

            return msg;
        } catch (IOException e) {
            return "Error receiving response: " + e.getMessage();
        }
    }

    private boolean testOpeningSocket() {
        try {
            Socket socket = new Socket("10.0.2.2", port);
            socket.close();
        } catch (IOException e) {
            System.out.println("[Urban-hunt] Failed opening socket!");
            return false;
        }

        System.out.println("[Urban-hunt] Successfully opened socket!");
        return true;
    }

    private boolean testConnectToServer() {
        try {
            Socket socket = new Socket(hostname, port);
            socket.close();
        } catch (IOException e) {
            System.out.println("[Urban-hunt] Failed to connect to server!");
            return false;
        }

        System.out.println("[Urban-hunt] Successfully connected to server!");
        return true;
    }

    private boolean testSendDataToServer() {
        try {
            Socket socket = new Socket(hostname, port);

            if (socket.isConnected()) {
                System.out.println("[Urban-hunt] Socket is ready for communication!");
                return true;
            }
            else {
                System.out.println("[Urban-hunt] Socket is not ready for communication!");
                return false;
            }

        } catch (IOException e) {
            System.out.println("[Urban-hunt] Socket is not ready for communication!");
            return false;
        }
    }

    private boolean testRecvDataFromServer() {

        try {
            Socket socket = new Socket(hostname, port);

            if (sendData("{ \"lat\":0, \"lon\":0 }")) {
             return true;
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        return false;
    }

}
