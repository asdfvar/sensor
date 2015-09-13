package com.example.monsterbot.myapplication;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;


public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("MedWear 2 App");
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            Intent myIntent = new Intent(MainActivity.this, SettingsActivity.class);
            MainActivity.this.startActivity(myIntent);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
    public void sendMessage(View view){
        Intent myIntent = new Intent(MainActivity.this, Output_EE_Activity.class);
        MainActivity.this.startActivity(myIntent);
    }
    public void sendMessage2(View view){
        Intent myIntent = new Intent(MainActivity.this, Graph_Correlation_Activity.class);
        MainActivity.this.startActivity(myIntent);
    }
    public void sendMessage3(View view){
        Intent myIntent = new Intent(MainActivity.this, Process_Input_Activity.class);
        MainActivity.this.startActivity(myIntent);
    }
    public void sendMessage4(View view){
        Intent myIntent = new Intent(MainActivity.this, DynamicGrapher.class);
        MainActivity.this.startActivity(myIntent);
    }
    public void onTrainButton(View view){
        Intent myIntent = new Intent(MainActivity.this, Train_Activity.class);
        MainActivity.this.startActivity(myIntent);
    }
    public void onSensorButton(View view){
        Intent myIntent = new Intent(MainActivity.this, Sensor_Activity.class);
        MainActivity.this.startActivity(myIntent);
    }

}
