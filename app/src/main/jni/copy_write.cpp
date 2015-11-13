//
// Created by Administrator on 2015/11/5 0005.
//
#include <jni.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <string.h>

#define LOG_TAG  "copy_write_jni"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)


#ifndef _Included_com_rpdzkj_abin_copyfilebyjni_CopyNative
#define _Included_com_rpdzkj_abin_copyfilebyjni_CopyNative
#ifdef __cplusplus
extern "C" {
#endif


long copyWriteFile(FILE *srcFile, FILE *destFile) {

    if (srcFile == NULL && destFile == NULL) {
        LOGD("open file error");
        return -1;
    }

    unsigned int fileLen;
    unsigned char *data;

    fseek(srcFile, 0L, SEEK_END);
    fileLen = (unsigned int) ftell(srcFile);
    LOGD("File len=%d", fileLen);
    data = (unsigned char *) malloc(fileLen);
    if (data == NULL) {
        LOGD("malloc error");
        return -1;
    }

    rewind(srcFile);

    size_t sizeT = fread(data, fileLen, 1, srcFile);
    LOGD("sizeT=%d",sizeT);
    if (sizeT != 1) {
        if (ferror(srcFile)) {
            LOGD("read file error");
            return -1;
        } else {
            LOGD("read the last data");
        }
    }

    size_t sizeT1 = fwrite(data, fileLen, 1, destFile);
    LOGD("sizeT1=%d",sizeT1);
    if (sizeT1 != 1) {
        LOGD("write error");
    }
    return (long) sizeT1;
}
/*
 * Class:     com_rpdzkj_abin_copyfilebyjni_CopyNative
 * Method:    copyAndWriteFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_rpdzkj_abin_copyfilebyjni_CopyNative_copyAndWriteFile
        (JNIEnv *env, jclass clazz, jstring srcPath, jstring destPath) {

    long result;
    const char *srcPathUtf = env->GetStringUTFChars(srcPath, NULL);
    const char *destPathUtf = env->GetStringUTFChars(destPath, NULL);
    LOGD("srcPath=%s", srcPathUtf);
    LOGD("destPath=%s", destPathUtf);

    FILE *srcFile = fopen(srcPathUtf, "r");
    FILE *destFile = fopen(destPathUtf, "w");

    result = copyWriteFile(srcFile, destFile);

    //release
    env->ReleaseStringUTFChars(srcPath, srcPathUtf);
    env->ReleaseStringUTFChars(destPath, destPathUtf);
    fclose(srcFile);
    fclose(destFile);

    return result;
}


#ifdef __cplusplus
}
#endif
#endif

