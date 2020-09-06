#include <jni.h>
#include <string.h>
#include "android_log.h"

/**
 * C++ 中运算符重载：
 * 1. 运算符重载其实就是定义一个函数，在函数体内实现想要的功能，当用到该运算符时，编译器会自动调用这个函数；
 * 2. 运算符重载的格式为：
 * 返回值类型 operate运算符名称（形参列表）{}
 * 3. 运算符重载函数除了函数名有特定的格式，其他地方和普通函数没有区别；
 *
 *  C++ 运算符重载的规则
 *  1. 不是所有运算符都可以重载，只有部分运算符可以重载；
 *  2. 重载不能改变运算符的优先级和结合性；
 *  3. 重载不会改变运算符的用法，原有几个操作数，操作数在左边还是右边，这都不会改变；
 *  4. 运算符重载函数不能有默认的参数，否则就变成了运算符操作数的个数；
 *  5. 运算符重载函数可以作为类的成员函数，也可以作为全局函数；
 *
 *  为什么要以全局函数的形式重载 +
 *  C ++ 只会对成员函数的参数进行类型转换，而不会对调用成员函数的对象进行类型转换，这样 complex c = 15 + complex(20)会报错
 *
**/

class complex {
private:
    int m_real;
    int m_img;
public:
    complex();

    complex(int real, int img);

    complex(int read);

public:
    complex operator+(const complex &c) const;

    void display() const;
};

complex::complex() {}

complex::complex(int real, int img) : m_real(real), m_img(img) {}

complex::complex(int real) : m_real(real), m_img(0) {}

void complex::display() const {
    LOG_I("m_real = %d;m_img=%d", m_real, m_real);
}

complex complex::operator+(const complex &c) const {
    complex B;
    B.m_real = this->m_real + c.m_real;
    B.m_img = this->m_img + c.m_img;
    return B;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ljb_jnidemo_utils_JniUtils_callOperation(JNIEnv *env, jobject thiz) {
    complex a(10, 20);
    complex b(20, 30);
    complex c = a + b;
    c.display();

}

