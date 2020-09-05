#include <jni.h>
#include <string>
#include "android_log.h"



/**
 * 类中成员变量在堆区或栈区分配内存，成员函数在代码区分配内存
 */
class Student{
    // 访问权限:public、protect、private
private:
    // 成员变量
    char* name;
    int age;
    float score;
    // static 成员变量不属于某个具体的对象，static 成员变量必须在类声明的外部初始化，
    // static 成员变量的内存是在类外初始化时分配，没有在类外初始化的 static 成员变量不能使用。
    static int m_total;
   // 初始化 const 成员变量的唯一方法就是使用初始化列表
//    const int type;
public:
    // 声明构造函数
    Student();
    Student(char* name);
    Student(char* name,int age,float score);
    // 函数声明
    // 在类体中定义的函数，默认是内联函数，所以通常情况下，在类内声明函数，在类外定义函数
    void say();
    void setAge(int age);
    void setName(char* name);
    void setScore(float score);
    // 常成员函数的声明和定义都需要在函数头部和尾部加上 const 关键字
    // 常成员函数可以使用类中的所有成员变量，但是不能修改它们的值；
    int getAge() const ;
    char* getName() const ;
    float getScore() const ;
    // 声明静态函数
    static int getTotal()  ;
    // 声明析构函数：析构函数不需要显式调用，在销毁对象时自动执行。析构函数不能被重载，一个类只能有一个析构函数，
    ~Student();
};

class Class{
private:
    int num;
    Student student;
public:
    Class(int num, char*,int age, float score);

    void display();
};
int Student::m_total = 10;
// 函数定义
Student::Student() {}

Student::Student(char *name) {
    this->name = name;
}
//采用初始化列表
Student::Student(char* name,int age,float score):name(name),age(age),score(score) {

}

void Student::setAge(int age) {
    // this 是 c++ 中的一个关键字，也是一个 const 指针，它指向当前对象，通过它可以访问当前所有成员
    // this 虽然用在类的内部，但是只有在对象创建以后才会给 this 赋值，并且这个赋值的过程是编译器自动完成的，
    // 不需要用户干预，用户也不能显式地给 this 赋值。
    // this 实际上是成员函数的一个形参，在调用成语函数时将对象的地址作为实参传递给 this，不过 this 这个形参是隐式的，它并出现在代码中
    // 而是在编译阶段编译器默默地将它添加到参数列表中。
    this->age =age;
}

void Student::setScore(float score) {
    this->score = score;
}

void Student::setName(char* name){
    this->name = name;
}

int Student::getAge() const {
    return this->age;
}

char* Student::getName() const {
    return this->name;
}

float Student::getScore() const {
    return this->score;
}

int Student::getTotal()  {
    return m_total;
}
void Student::say(){
    LOG_I("name : %s；age : %d ; score : %f，m_total : %d",name,age,score,m_total);
}

Student::~Student(){
    LOG_I("%s的析构函数被调用了",name);
}
/**
 * 成员对象student初始化，需要借助封闭类构造函数的初始化列表
 */
Class::Class(int num,char*  name,int age, float score):num(num),student(name,age,score){}

void Class::display() {
    LOG_I("num = %d，name= %s，age= %d，score = %f，m_total = %d",num,student.getName(),student.getAge(),student.getScore(),Student::getTotal());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_ljb_jnidemo_utils_JniUtils_printStudentMessage(JNIEnv *env, jobject thiz) {    Student stu;  // 在栈内存中，不需要首手动回收
    stu.setName("张三");
    stu.setAge(18)  ;
    stu.setScore(80.0) ;
    stu.say();
    //使用 new 在堆上创建出来的对象是匿名的，没法直接使用，必须要用一个指针指向它，再借助指针来访问它的成员变量或成员函数
    Student* stu_new = new Student("李四",18,87.5);// 手动new的，在堆内存中，需要手动释放
    stu_new->say();

    // 常对象只能调用类的 const 成员（包括 const 成员变量和 const 成员函数）
    const Student* student_const = new Student("赵七",20,60.0);
    student_const->getName();

    Class* clz = new Class(1,"王五",20,99.999);
    clz->display();


    delete stu_new;//手动释放内存
    delete clz;
}