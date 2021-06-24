//
// Created by DM on 2021/6/23.
//
#include <jni.h>
#include <sys/mman.h>
#include <string>
#include <unistd.h>
#include <android/log.h>
#include <locale>
#include <fcntl.h>
#include <vector>

#define LOG_TAG "c++_write_log"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

std::string jstring2str(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    std::string stemp(rtn);
    free(rtn);
    return stemp;
}

jstring char2jstring(JNIEnv *env, const char *pat) {
    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring) env->NewObject(strClass, ctorID, bytes, encoding);
}

extern "C"
jboolean
Java_com_biao_testdemokotlin_Jni_write(JNIEnv *env, jobject clazz, jstring path, jstring text) {
    try {
        std::string file_path = jstring2str(env, path);
        std::string write_text = jstring2str(env, text);
//    m_size = getpagesize();//获取一页大小
        int32_t m_size = env->GetStringLength(text);
        int fd = open(file_path.c_str(), O_RDWR | O_CREAT, S_IRWXU);//打开文件
        LOGI("write fd = %d\n", fd);
        ftruncate(fd, m_size);//设置文件为一页大小
        int8_t *ptr = (int8_t *) mmap(0, m_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//    LOGI("write_text size = %d\n", write_text.size());
        memcpy(ptr, write_text.data(), m_size);
        close(fd);
        munmap((void *) ptr, m_size);
        return true;
    } catch (...) {
        return false;
    }
}

extern "C"
jstring
Java_com_biao_testdemokotlin_Jni_read(JNIEnv *env, jobject clazz, jstring path) {
    try {
        std::string file_path = jstring2str(env, path);
        // 打开文件
        int fd = open(file_path.c_str(), O_RDONLY);
        LOGI("read fd = %d\n", fd);
        // 读取文件长度
        int len = lseek(fd, 0, SEEK_END);
        LOGI("len = %d", len);
        // 建立内存映射
        char *addr = (char *) mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
        close(fd);
        char *data = new char[len];// data用于保存读取的数据
        memcpy(data, addr, len);// 复制过来
        close(fd);
        munmap(addr, len); // 解除映射
        jstring js = char2jstring(env, data);
        delete[]data;//释放内存空间
        return js;
    } catch (...) {
        return NULL;
    }
}
