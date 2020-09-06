package com.ljb.jnidemo.utils;

/**
 * Author      :ljb
 * Date        :2020/9/5
 * Description :
 */
public class JniUtils {

    static {
        System.loadLibrary("native-lib");
    }


    public native String getStringFromJni();

    public native void printStudentMessage();

    public native void callFriendMethod();

    public native void callCPlusPlusRefrence();

    public native void callOperation();

    public native void callTemplate();

}
