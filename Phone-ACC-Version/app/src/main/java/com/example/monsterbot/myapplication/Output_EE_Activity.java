package com.example.monsterbot.myapplication;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.os.AsyncTask;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;

public class Output_EE_Activity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_http_response_viewer);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setTitle("Total Energy Expenditure");
        SharedPreferences sharedPref = PreferenceManager.getDefaultSharedPreferences(this);
        String parameters = sharedPref.getString("ip_text","192.168.1.157");

        new MyTask().execute(parameters);
    }

    public class MyTask extends AsyncTask<String, Void, Void> {
        String textResult;
        protected Void doInBackground(String... params) {
            URL textUrl;

            try{
                textUrl = new URL("http://" + params[0] + "/cgi-bin/run_demo2");
                BufferedReader bufferedReader = new BufferedReader
                        (new InputStreamReader(textUrl.openStream()));
                String stringBuffer;
                String stringText = "";

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
            TextView textView2 = (TextView) findViewById(R.id.textView2);
            textView2.setText(textResult);
        }
    }
}
