#include <jni.h>
#include <string.h>
#include "android_log.h"

/**
 * 友元：可以使得其他类中的成员函数以及全局范围内的函数访问当前类中private 成员
 * 友元函数：
 * 在当前类以外定义的，不属于当前类的函数也可以在类中声明，但是在前面加上friend 关键字。
 * 友元函数可以是不属于任何类的成员函数，也可以是其他类的成员函数；
 * 友元类：
 * 将类 B 声明为 类 A 的友元类，那么类 B 中所有的成员变量都是类 A 的友元函数，可以访问类 A 的所有成员
 */
class StudentTwo;//提前声明StudentTwo类

class PrintClz{
public:
    void display(StudentTwo& studentTwo);
};

class FriendPrintClz{
public:
    void display(StudentTwo& studentTwo);
};


class StudentTwo {
private:
    char *name;
    int age;
    float score;
public:
    StudentTwo(char *name, int age, float score);
    // 将非成员函数声明为友元函数
    friend void display(StudentTwo& stu);
   // 将其他类的成员函数声明为友元函数
    friend void PrintClz::display(StudentTwo& studentTwo);
    // FriendPrintClz类声明为StudentTwo的友元类
    friend class FriendPrintClz;
    ~StudentTwo();
};



// 非成员函数
void display(StudentTwo& stu){
    LOG_I("name : %s ，age : %d ，score : %f",stu.name,stu.age,stu.score);
}

StudentTwo::StudentTwo(char* name, int age, float score) : name(name), age(age), score(score) {
}

StudentTwo::~StudentTwo() {
    LOG_I("%s的析构函数被调用了",name);
}

void PrintClz::display(StudentTwo &stu) {
    LOG_I("PrintClz 打印的 ：name : %s ，age : %d ，score : %f",stu.name,stu.age,stu.score);
}

void FriendPrintClz::display(StudentTwo &stu) {
    LOG_I("FriendPrintClz 打印的 ：name : %s ，age : %d ，score : %f",stu.name,stu.age,stu.score);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ljb_jnidemo_utils_JniUtils_callFriendMethod(JNIEnv *env, jobject thiz) {
    StudentTwo stu("张山",20,80.5);
    display(stu);

    PrintClz printClz;
    printClz.display(stu);

    FriendPrintClz friendPrintClz;
    friendPrintClz.display(stu);


}