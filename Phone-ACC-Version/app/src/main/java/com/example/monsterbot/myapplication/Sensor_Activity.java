package com.example.monsterbot.myapplication;
import android.content.pm.ActivityInfo;
import android.os.Handler;
import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Context;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.view.View;
import android.widget.TextView;


import java.io.IOException;

public class Sensor_Activity extends AppCompatActivity implements SensorEventListener {
    private SensorManager senSensorManager;
    private Sensor senAccelerometer;
    private sdCard_Write sdwriter = new sdCard_Write();
    private long startTime = 0L;
    private Handler customHandler = new Handler();
    long timeInMilliseconds = 0L;
    long timeSwapBuff = 0L;
    long updatedTime = 0L;
    private TextView timerValue;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTitle("Sensor");
        senSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        senAccelerometer = senSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        setContentView(R.layout.activity_sensor_);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        TextView tv1 = (TextView)findViewById(R.id.textView5);
        tv1.setText("Ready");
        timerValue = (TextView) findViewById(R.id.timerVal);
    }
    @Override
    public synchronized void onSensorChanged(SensorEvent sensorEvent) {

        float linear_acceleration;
        float linear_acceleration1;
        float linear_acceleration2;

        linear_acceleration = (sensorEvent.values[0]/(float)9.81);
        linear_acceleration1 = (sensorEvent.values[1]/(float)9.81);
        linear_acceleration2 = (sensorEvent.values[2]/(float)9.81);

        try {
            sdwriter.appendDatatoCSV(2, Float.toString(linear_acceleration),
                    Float.toString(linear_acceleration1),
                    Float.toString(linear_acceleration2), "sensor.csv");
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {
    }
    public void onStartButton(View view){
        startTime = SystemClock.uptimeMillis();
        customHandler.postDelayed(updateTimerThread, 0);
        sdwriter.deleteCSV("sensor.csv");
        TextView tv1 = (TextView)findViewById(R.id.textView5);
        tv1.setText("Collecting Data...");
        senSensorManager.registerListener(this, senAccelerometer,
                SensorManager.SENSOR_DELAY_FASTEST);
    }

    public void onStopButton (View view){
        Intent myIntent = new Intent(Sensor_Activity.this, FTP_Upload_Activity.class);
        senSensorManager.unregisterListener(this);
        timeSwapBuff += timeInMilliseconds;
        customHandler.removeCallbacks(updateTimerThread);
        TextView tv1 = (TextView)findViewById(R.id.textView5);
        tv1.setText("Collecting Stopped.");
        myIntent.putExtra("file", "sensor.csv");
        Sensor_Activity.this.startActivity(myIntent);
    }
    private Runnable updateTimerThread = new Runnable() {

        public void run() {

            timeInMilliseconds = SystemClock.uptimeMillis() - startTime;

            updatedTime = timeSwapBuff + timeInMilliseconds;

            int secs = (int) (updatedTime / 1000);
            int mins = secs / 60;
            secs = secs % 60;
            int milliseconds = (int) (updatedTime % 1000);
            timerValue.setText("" + mins + ":"
                    + String.format("%02d", secs) + ":"
                    + String.format("%03d", milliseconds));
            customHandler.postDelayed(this, 0);
        }

    };
}
