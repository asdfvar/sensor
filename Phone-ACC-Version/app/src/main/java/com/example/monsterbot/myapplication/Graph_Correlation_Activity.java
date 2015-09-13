package com.example.monsterbot.myapplication;
import android.app.Activity;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;

import com.androidplot.xy.BoundaryMode;
import com.androidplot.xy.LineAndPointFormatter;
import com.androidplot.xy.PointLabelFormatter;
import com.androidplot.xy.SimpleXYSeries;
import com.androidplot.xy.XYPlot;
import com.androidplot.xy.XYSeries;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
//This is the activity for graphing

public class Graph_Correlation_Activity extends Activity {
    private XYPlot plot;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_http_response_viewer2);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        SharedPreferences sharedPref = PreferenceManager.getDefaultSharedPreferences(this);
        String ip_address = sharedPref.getString("ip_text","192.168.1.157");
        new MyTask().execute(ip_address);
    }

    private List generateListFromGETHTTPDATA(String data) {
        List list = new ArrayList();
        String delimiters = "[,]";
        System.out.println(data);
        String[] tokens = data.split(delimiters);
        float toFloat;

        for (int i = 0; i <= tokens.length-1; i++) {
            toFloat = Float.parseFloat(tokens[i]);
            list.add(toFloat);
        }
        return list;
    }
    public class MyTask extends AsyncTask<String, Void, Void> {
        String textResult;
        protected Void doInBackground(String... params) {
            URL textUrl;

            try{
                textUrl = new URL("http://" + params[0] + "/cgi-bin/run_mycode");
                BufferedReader bufferedReader = new BufferedReader
                        (new InputStreamReader(textUrl.openStream()));
                String stringBuffer;
                String stringText = " ";

                while((stringBuffer = bufferedReader.readLine()) != null){
                    stringText += stringBuffer;
                }
                bufferedReader.close();
                textResult = stringText;
            }catch(MalformedURLException e){
                e.printStackTrace();
            }catch (IOException e){
                e.printStackTrace();
            }

            return null;
        }

        @Override
        protected void onPostExecute(Void result) {

            setContentView(R.layout.activity_http_response_viewer2);
            plot = (XYPlot) findViewById(R.id.xyPlot);

            List s1 = generateListFromGETHTTPDATA(textResult);
            XYSeries series1 = new SimpleXYSeries(s1,
                    SimpleXYSeries.ArrayFormat.Y_VALS_ONLY,"Correlation");

            LineAndPointFormatter s1Format = new LineAndPointFormatter();
            s1Format.setPointLabelFormatter(new PointLabelFormatter());
            s1Format.configure(getApplicationContext(),
                    R.xml.line_point_formatter_with_plf1);

            plot.addSeries(series1, s1Format);
            plot.setRangeBoundaries(0, 1, BoundaryMode.FIXED);
            plot.setTicksPerRangeLabel(2);
            plot.getGraphWidget().setDomainLabelOrientation(-45);
        }
    }
}
