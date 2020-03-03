package com.affy.nativetest;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.affy.nativetest.bean.Animal;

public class MainActivity extends AppCompatActivity {
    private String name;
    private static int num;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        final TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        final JniDynamicLoad jniDynamicLoad = new JniDynamicLoad();
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                tv.setText(jniDynamicLoad.getNativeString());
                String str = callNativeStr("java string");
                Log.d("affy", str);
                stringMethod("java string");

                String[] strings = {"apple", "pear", "banana"};
                Log.d("affy", "the first item of strings: " + callNativeStrArray(strings));

                accessInstanceField();
                Log.d("affy", "access instance field and change name to:" + name);
                accessStaticField();
                Log.d("affy", "access static field and change num to:" + num);

                accessInstanceMethod();
                accessStaticMethod();

                Log.d("affy", invokeConstructors().getName());
                Log.d("affy", allocConstructors().getName());
            }
        });
    }

    public void callInstanceMethod(int num) {
        Log.d("affy", "instance method invoked in MainActivity,and pass param: " + num);
    }

    public static void callStaticMethod(String str, int num) {
        Log.d("affy", "static method invoked in MainActivity,and pass param:" + str + " and " + num);
    }

    public static void callStaticMethod(String[] strs) {
        for (int i = 0; i < strs.length; i++) {
            Log.d("affy", i + " static method invoked in MainActivity,and pass param:" + strs[i]);
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String callNativeStr(String str);

    public native void stringMethod(String str);

    public native String callNativeStrArray(String[] strArray);

    public native void accessInstanceField();

    public native void accessStaticField();

    public native void accessInstanceMethod();

    public native void accessStaticMethod();

    public native Animal invokeConstructors();

    public native Animal allocConstructors();
}
