#include <jni.h>
#include <string.h>
#include "android_log.h"


/**
 * C ++ 中的三种继承方式
 * public protect private 基类成员在派生类中的访问权限不得高于继承方式中指定的权限；
 *
 * C ++ 中的遮蔽
 * 如果派生类中的成员（包括成员变量和成员函数）和基类中的成员重名，那么就会遮蔽从基类继承过来的成员。
 *
 * 基类成员函数和派生类成员函数不构成重载
 * 基类成员和派生类成员名字一样时就会造成遮蔽，对于成员函数，不过函数的参数如何，只要名字一样就会造成遮蔽。
 *
 * C++ 基类和派生类的构造函数
 * 在设计派生类时，对继承过来的成员变量的初始化工作也要由派生类的构造函数完成，对于基类中的 private 属性的成员变量
 * 可以在派生类的构造函数中调用基类的构造函数
 *
 * 构造函数调用顺序
 * 构造函数的调用顺序是按照继承的层次自顶向下、从基类再到派生类（ps：派生类构造函数只能调用直接基类的构造函数，不能调用间接基类的）
 *
 * 基类构造函数调用规则
 * 通过派生类创建对象时，必须要调用基类的构造函数，如果不指明，就调用基类的默认构造函数
 *
 * C++ 基类和派生类的析构函数
 * 在派生类中不用显式调用基类的析构函数，销毁派生类对象时，先执行派生类析构函数，再执行基类析构函数
 *
 * C ++ 多继承
 * 1. C ++ 支持一个派生类有两个或多个基类；
 * 2. 基类构造函数的调用顺序和声明派生类时基类出现的顺序相同；
 * 3. 当两个或多个基类有相同名的成员时，派生类需要在成员名前面加上类名和域解析符 :: ，以显式指明到底使用哪个类的成员；
 *
 * C ++ 中的菱形继承：类 A 派生出 类 B 和类 C，类 D 继承自 类 B 和 类 C，这个时候类 A 中的成员变量和成员函数继承到类 D 中变成了两份
 * 一份来自 A -> B -> D，另一份来自 A -> C -> D。这样不仅导致了派生类 D 中保留了多分类 A 的成员变量，还容易产生命名冲突。
 *
 * 虚继承
 * 1. 为了解决多继承时的命名冲突和冗余数据问题，C++ 提出了虚继承，使得派生类只保留了一份间接基类的成员；
 * 2. 虚继承的目的是让某个类做出声明，承诺愿意共享它的基类；
 * 3. 最终派生类需要初始化虚基类，也就是说派生类可以调用非直接虚基类的构造函数；
 *
 * 虚函数
 * 1. 通常情况下，基类指针只能访问派生类的成员变量，无法访问派生类的成员函数（即：调用的是自己的成员函数）；
 * 2. 为了解决上面这种问题，C++ 增加了 虚函数，只需要在函数声明前面增加 virtual 关键字即可（函数定义处可以不用加）；
 * 3. 有了虚函数，基类指针指向基类对象时就使用基类的成员，指向派生类对象时就使用派生类的成员。
 *
 * 构成多态的条件
 * 1. 必须存在继承关系；
 * 2. 继承关系中必须有同名的虚函数，并且它们是覆盖关系（函数原型相同）；
 * 3. 存在基类指针，通过该指针调用虚函数；
 *
 * C++ 虚析构函数的必要性
 * 1. 析构函数用于销毁对象时进行清理工作，可以声明为虚函数，而且有时候必须要声明为虚函数；
 * 2. 派生类析构函数始终会调用基类的析构函数，而且这个调用过程是隐式完成的；
 *
 * 纯虚函数
 * 1. 纯虚函数没有函数体，只有函数声明，在虚函数声明的结尾 加上 =0 ，表示为此函数为纯虚函数；
 * 2. 语法格式：virtual 返回值类型 函数名（函数参数）=0;
 * 3. 包含纯虚函数的类称为抽象类，它无法实例化。派生类必须实现纯虚函数才能被实例化；
 */
class People {
protected:
    char *m_name;
    int m_age;
public:
    People();

    People(char *name, int age);

    void setName(char *name);

    void setAge(int age);

    char *getName() const;

    int getAge() const;
};

People::People() {}

People::People(char *name, int age) : m_name(name), m_age(age) {}

void People::setAge(int age) {
    this->m_age = age;
}

void People::setName(char *name) {
    this->m_name = name;
}

char *People::getName() const {
    return this->m_name;
}

int People::getAge() const {
    return this->m_age;
}

class Student : public People {
private:
    float m_score;
public:
    // using 只能改变基类中 public 和 protected 成员的访问权限，不能改变private 成员的访问权限，因为基类中 private 成员在派生类中是不可见的
    using People::m_age;//将protect 改为 public
public:
    Student(char* name ,int age , float score);

    void setScore(float score);

    float getScore() const;
};

//People(name, age)就是调用基类的构造函数
Student::Student(char *name, int age, float score) :People(name,age),m_score(score){}

void Student::setScore(float score) {
    this->m_score = score;
}

float Student::getScore() const {
    return this->m_score;
}