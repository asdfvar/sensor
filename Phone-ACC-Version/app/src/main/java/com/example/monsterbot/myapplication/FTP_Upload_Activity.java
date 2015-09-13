package com.example.monsterbot.myapplication;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.os.AsyncTask;
import android.os.Environment;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import java.io.File;
import java.io.IOException;
import it.sauronsoftware.ftp4j.FTPAbortedException;
import it.sauronsoftware.ftp4j.FTPClient;
import it.sauronsoftware.ftp4j.FTPDataTransferException;
import it.sauronsoftware.ftp4j.FTPException;
import it.sauronsoftware.ftp4j.FTPIllegalReplyException;

public class FTP_Upload_Activity extends AppCompatActivity {
    String[] parameters = {"","","",""};
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ftp__upload_);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        SharedPreferences sharedPref = PreferenceManager.getDefaultSharedPreferences(this);

        parameters[0] = sharedPref.getString("ip_text","192.168.1.157");
        parameters[1] = sharedPref.getString("User Name","user");
        parameters[2] = sharedPref.getString("Password","monster*87");
        parameters[3] = getIntent().getExtras().getString("file");

        new MyTask().execute(parameters);
    }
    public class MyTask extends AsyncTask<String, Void, Void> {
        protected Void doInBackground(String... params) {
            try {

                File root = Environment.getExternalStorageDirectory();
                File file = new File(root, parameters[3]);

                FTPClient ftp = new FTPClient();

                ftp.connect(params[0]);
                ftp.login(params[1], params[2]);
                String currentDirectory = ftp.currentDirectory();
                String path = currentDirectory + "/Documents/FTP-Server";
                ftp.changeDirectory(path);
                ftp.setType(FTPClient.TYPE_BINARY);
                ftp.upload(file);
                ftp.disconnect(true);

            } catch(FTPIllegalReplyException e){
                e.printStackTrace();
            } catch (FTPException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (FTPAbortedException e){
                e.printStackTrace();
            } catch (FTPDataTransferException e){
                e.printStackTrace();
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result) {
            Intent myIntent = new Intent(FTP_Upload_Activity.this, MainActivity.class);
            FTP_Upload_Activity.this.startActivity(myIntent);
        }
    }
}
