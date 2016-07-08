package com.fryarludwig.urbanhunt.Controllers;

import android.content.Intent;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;

import com.fryarludwig.urbanhunt.R;

public class JoinGameActivity extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.join_game);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.OptionMainMenu) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }


    public void startGame(View view){
        EditText Name = (EditText)findViewById(R.id.Name);
        EditText Team = (EditText)findViewById(R.id.Team);

        String name = Name.getText().toString();
        String team = Team.getText().toString();

        Intent intent = new Intent(this, mapControl.class);
        Bundle bundle = new Bundle();
        bundle.putString("name", name);
        bundle.putString("team", team);

        intent.putExtras(bundle);

        startActivity (intent);
    }
}
