#include <jni.h>
#include <string.h>
#include "android_log.h"

/**
 *  函数模板（类模板）：
 *  在 C ++ 中，数据的类型也可以通过参数来传递，在函数定义的时候不指明具体的数据类型，当发生函数调用时，
 *  编译器根据传入的实参自动推断数据类型。这就是类型的参数化；
 *
 *  头模板格式：template<typename T> typename 可以使用 class 关键字代替，它们没有任何区别；
 *
 *  模板实参推断过程中的类型转换
 *  1. 算术转换：例如 int 转换为 float，char 转换为 int ,double 转换为 int 等；
 *  2. 派生类向基类的转换；
 *  3. const 转换：将非 const 类型转换为 const 类型；
 *  4. 数组或函数指针转换：如果函数形参不是引用类型，那么数组名会转换为数组指针，函数名会转换为函数指针；
 *
 *  C++ 模板的显示具体化
 *  C++ 没有办法限制类型参数的范围，我们可以使用任意一种类型来实例化模板，但是模板中的语句不一定能适应所有的类型。
 *  模板的显示具体化，让模板能够针对某种具体的类型使用不能的算法（函数体或类体不同）；
**/

// 模板函数
template<class T>
void tmp(T &t1, T &t2) {
    T tmp = t1;
    t1 = t2;
    t2 = tmp;
}

// 类模板
template<class T>
class A {
private:
    T t;
public:
    A(T t);

    void display() const;
};


template<class T>
A<T>::A(T t):t(t) {}

template<class T>
void A<T>::display() const {
    LOG_I("t = %d", t);
}

typedef struct {
    char *name;
    int age;
    float score;
} STU;
//函数模板
template <typename  T> const T & Max(const T& a,const T& b);

template<class T> const T& Max(const T& a, const T& b){
    return a > b ? a : b;
}

//函数模板的显示具体化（针对STU类型的显示具体化）
template<> const STU& Max<STU>(const STU& a, const STU& b){
    return a.score > b.score ? a : b;
}

template <class  T1,class  T2>
class TmpPoint{
public:
    T1 t;
    T2 t2;
};


//类模板的显式具体化
template <>
class TmpPoint<int,int>{
public:
    int t;
    int t2;
};


extern "C"
JNIEXPORT void JNICALL
Java_com_ljb_jnidemo_utils_JniUtils_callTemplate(JNIEnv *env, jobject thiz) {
    int a = 20;
    int b = 30;
    LOG_I("tmp before a = %d ,b = %d", a, b);
    tmp(a, b);
    LOG_I("tmp after a = %d ,b = %d", a, b);

    A<int> tA(200);
    tA.display();

    STU s1 = {"张山",18,80};
    STU s2 = {"李四",20,100};
    STU s3 = Max(s1,s2);
    LOG_I("s3 name = %s",s3.name);
    TmpPoint<int,int> t;


}