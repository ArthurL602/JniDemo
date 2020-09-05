package com.ljb.jnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.ljb.jnidemo.utils.JniUtils;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        JniUtils jniUtils = new JniUtils();
        tv.setText(jniUtils.getStringFromJni());
        jniUtils.printStudentMessage();
        jniUtils.callFriendMethod();
    }

}
