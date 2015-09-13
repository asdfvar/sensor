package com.example.monsterbot.myapplication;
import android.os.Environment;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class sdCard_Write{

    File filename = Environment.getExternalStorageDirectory();
    boolean header_applied = false;

    public void appendDatatoCSV(int SensorNumber, String XDATA, String YDATA,
                                String ZDATA, String file) throws IOException {
        FileOutputStream out = new FileOutputStream(new File(filename, file), true);

        if(!header_applied){
            out.write("Sensor 1 ax".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 1 ay".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 1 az".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 1 wx".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 1 wy".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 1 wz".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 2 ax".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 2 ay".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 2 az".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 2 wx".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 2 wy".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 2 wz".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 3 ax".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 3 ay".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 3 az".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 3 wx".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 3 wy".getBytes());
            out.write(", ".getBytes());
            out.write("Sensor 3 wz".getBytes());
            out.write(", ".getBytes());
            out.write("EMG 1".getBytes());
            out.write(", ".getBytes());
            out.write("EMG 2".getBytes());
            out.write(", ".getBytes());
            out.write("Event".getBytes());
            out.write(", ".getBytes());
            out.close();
            header_applied = true;
        }
        try{
            out.write("\n".getBytes());
            switch (SensorNumber) {
                case 1:
                    out.write(XDATA.getBytes());
                    out.write(",".getBytes());
                    out.write(YDATA.getBytes());
                    out.write(",".getBytes());
                    out.write(ZDATA.getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    break;
                case 2:
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write(XDATA.getBytes());
                    out.write(",".getBytes());
                    out.write(YDATA.getBytes());
                    out.write(",".getBytes());
                    out.write(ZDATA.getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    break;
                case 3:
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write(XDATA.getBytes());
                    out.write(",".getBytes());
                    out.write(YDATA.getBytes());
                    out.write(",".getBytes());
                    out.write(ZDATA.getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    break;
                default:
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write(XDATA.getBytes());
                    out.write(",".getBytes());
                    out.write(YDATA.getBytes());
                    out.write(",".getBytes());
                    out.write(ZDATA.getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
                    out.write("0".getBytes());
                    out.write(",".getBytes());
            }
            out.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void deleteCSV(String file){
        File out = new File(filename, file);
        boolean deleted = out.delete();
        header_applied = false;
    }
}
