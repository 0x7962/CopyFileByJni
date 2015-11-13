package com.rpdzkj.abin.copyfilebyjni;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.io.File;

public class MainActivity extends AppCompatActivity implements AdapterView.OnItemClickListener {

    private static final String TAG = MainActivity.class.getSimpleName();
    private File[] files;

    static {
        System.loadLibrary("copy_write");
    }
    String destPath = "";
    String path = "";
    ListView lv;
    private ArrayAdapter<File> adapter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        lv = (ListView) findViewById(R.id.listView);
        lv.setOnItemClickListener(this);

        path = Environment.getExternalStorageDirectory().getPath();
        Log.d(TAG, "scan Path=" + path);
        path = path + "/pictest";
        String str = String.valueOf(System.currentTimeMillis());

        destPath = path+"/pic_"+str+".jpg";

        File dir = new File(path);
        files = dir.listFiles();
//        for(File f : files){
//
//        }
        adapter = new ArrayAdapter<>(this,android.R.layout.simple_list_item_1,files);
        lv.setAdapter(adapter);
    }


    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Log.d(TAG, "file=" + files[position].getName());

        long result = CopyNative.copyAndWriteFile(files[position].getPath(),destPath);
        Log.d(TAG, "result=" + result);
        syncAdapter();
    }

    private void syncAdapter(){
        adapter = null;
        File dir = new File(path);
        files = dir.listFiles();
        adapter = new ArrayAdapter<>(this,android.R.layout.simple_list_item_1,files);
        lv.setAdapter(adapter);
    }

}
