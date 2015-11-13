package com.rpdzkj.abin.copyfilebyjni;

/**
 * author: ybjaychou@gmail.com
 * date: 2015-11-05 11:22
 * version V1.0
 */
public class CopyNative {
    private static final String TAG = "CopyNative";

    public static native long copyAndWriteFile(String srcPath,String destPath);
}
