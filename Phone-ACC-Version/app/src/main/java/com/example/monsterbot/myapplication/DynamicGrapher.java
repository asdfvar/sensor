package com.example.monsterbot.myapplication;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.graphics.Color;
import android.graphics.DashPathEffect;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import com.androidplot.util.PixelUtils;
import com.androidplot.xy.*;

public class DynamicGrapher extends AppCompatActivity implements SensorEventListener
{
    private static final int HISTORY_SIZE = 100;
    private SensorManager senSensorManager;
    private Sensor senAccelerometer;
    private XYPlot aprHistoryPlot = null;
    private SimpleXYSeries XDATA_series = null;
    private SimpleXYSeries YDATA_series = null;
    private SimpleXYSeries ZDATA_series = null;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTitle("RT XYZ Graph");
        senSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        senAccelerometer = senSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

        setContentView(R.layout.activity_dynamic_grapher);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);

        aprHistoryPlot = (XYPlot) findViewById(R.id.aprHistoryPlot);
        XDATA_series = new SimpleXYSeries("X Data");
        XDATA_series.useImplicitXVals();
        YDATA_series = new SimpleXYSeries("Y Data");
        YDATA_series.useImplicitXVals();
        ZDATA_series = new SimpleXYSeries("Z Data");
        ZDATA_series.useImplicitXVals();
        aprHistoryPlot.setRangeBoundaries(-4, 4, BoundaryMode.FIXED);
        aprHistoryPlot.setDomainStepMode(XYStepMode.INCREMENT_BY_VAL);
        aprHistoryPlot.setDomainStepValue(5);

        aprHistoryPlot.setRangeStepMode(XYStepMode.INCREMENT_BY_PIXELS);
        aprHistoryPlot.setRangeStepValue(10);
        aprHistoryPlot.addSeries(XDATA_series, new LineAndPointFormatter(
                Color.RED, null, null, null));
        aprHistoryPlot.addSeries(YDATA_series, new LineAndPointFormatter(
                Color.GREEN, null, null, null));
        aprHistoryPlot.addSeries(ZDATA_series, new LineAndPointFormatter(
                Color.BLUE, null, null, null));
        aprHistoryPlot.setDomainStepValue(5);
        aprHistoryPlot.setTicksPerRangeLabel(3);
        aprHistoryPlot.setDomainLabel("Time");
        aprHistoryPlot.setRangeLabel("G Factor");
        DashPathEffect dashFx = new DashPathEffect(
                new float[] {PixelUtils.dpToPix(3), PixelUtils.dpToPix(3)}, 0);
        aprHistoryPlot.getGraphWidget().getDomainGridLinePaint().setPathEffect(dashFx);
        aprHistoryPlot.getGraphWidget().getRangeGridLinePaint().setPathEffect(dashFx);
    }

    @Override
    public synchronized void onSensorChanged(SensorEvent sensorEvent) {
        float linear_acceleration;
        float linear_acceleration1;
        float linear_acceleration2;

        linear_acceleration = (sensorEvent.values[0]/(float)9.81);
        linear_acceleration1 = (sensorEvent.values[1]/(float)9.81);
        linear_acceleration2 = (sensorEvent.values[2]/(float)9.81);

        XDATA_series.addLast(null, linear_acceleration);
        YDATA_series.addLast(null, linear_acceleration1);
        ZDATA_series.addLast(null, linear_acceleration2);

        if (XDATA_series.size() > HISTORY_SIZE) {
            XDATA_series.removeFirst();
            YDATA_series.removeFirst();
            ZDATA_series.removeFirst();
        }
        aprHistoryPlot.redraw();
        }

    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {
    }
    public void onStartButton(View view){
            senSensorManager.registerListener(this, senAccelerometer,
                    SensorManager.SENSOR_DELAY_FASTEST);
    }

    public void onStopButton (View view){
        senSensorManager.unregisterListener(this);
}

}