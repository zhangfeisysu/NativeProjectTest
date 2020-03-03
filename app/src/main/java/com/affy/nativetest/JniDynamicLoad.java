package com.affy.nativetest;

public class JniDynamicLoad {
    static {
        System.loadLibrary("dynamic-lib");
    }

    public native String getNativeString();
    public native int sum(int x, int y);
}
