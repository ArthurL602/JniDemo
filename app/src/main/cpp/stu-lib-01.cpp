#include <jni.h>
#include <string>
#include "android_log.h"

/**
 * 为了解决合作开发带来的命令冲突问题，C++中引入命名空间概念，以
 * namespace name{
 *       //variables, functions, classes
 * }
 * 使用的时候：
 * 1. name::variable ;
 * 2. 也可以采用 using 关键字（using name;)，使用using声明后，后续程序中
 * 出现未使用命名空间的变量等时，就使用该命令空间下的
 */
namespace Li {
    int value;
}

/**
 * 内联函数（在函数前加上 inline 关键字，函数声明的时候可以不用加【内联函数不推荐声明】，但是函数定义的时候必须得加）
 * ：在编译的时候，将函数调用处用函数体替换，最好的函数体比较小，如果函数体比较大，那么插入的代码
 * 量也是非常多的，会增大程序的体积
 */
inline void printSomething(){
    LOG_I("这是一条来自Jni的日志");
}

/**
 * extern 是 C 和 C++ 中的一个关键字
 * extern "C"既可以修饰一句 C++ 代码，也可以修复一段C++代码，它的作用是让编译器以处理C语言代码的方式处理修饰的 C++ 代码。
 * 常用方式：
 * #ifdef _cplusplus
 * extern "C"{
 * #endif
 * void method();
 * #ifdef _cplusplus
 * }
 * #endif
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_ljb_jnidemo_utils_JniUtils_getStringFromJni(JNIEnv *env, jobject thiz) {
    printSomething();

    return env->NewStringUTF("Hello From Jni");
}


