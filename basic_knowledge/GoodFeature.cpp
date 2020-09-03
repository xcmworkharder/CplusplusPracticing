//
// Created by xcmworkharder on 2020-09-02 上午11:33.
//
#include <iostream>
#include <vector>
#include <complex>
//#include <array>
#include <map>

using namespace std;

/// auto: 自动决定变量类型 c++14以后包括函数返回类型，依然是静态类型，编译器帮助填充

template<typename T>
void foo(const T& container) {
//    for (typename T::const_iterator it = container.begin(); it != container.end(); ++it) {
//        cout << (*it) << endl;
//    }
//    for (auto it = begin(container); it != end(container); ++it) {
//        cout << (*it) << endl;
//    }

    for (auto c : container) {
        cout << c << endl;
    }
}

void testFoo() {
    vector<int> vec{1, 3, 5};
    foo(vec);
}

/// decltype 获取一个表达式类型
/// decltype(变量) decltype(表达式)
/// int a; decltype(a) 会获得int; decltype((a))获得int&; decltype(a + a)获得int
/// decltype(expr) a = expr; c++14 之后可以写成decltype(auto) a = expr;
void testDecltype() {
    int a = 10;
    decltype(a) b = 10;
    decltype((a)) c = b;

    decltype(a + b) d = 10;
    //decltype(auto) e = d; // c++14可以用

    pair<int, int> pr{1, 42};
    auto pr1 = make_pair(1, 42);

    //pair pr3{1, 42};  // 据说c++17可以这样，但是调试不行
    //array a{13, 3};   // 同上
    multimap<string, int> mmp;
    multimap<string, int>::iterator lower, upper;
    std::tie(lower, upper) = mmp.equal_range("four");
}

/// 初始化列表 列表初始化
/// 作用1：方便初始化
/// 作用2:防奇异错误发生，比如 ifstream ifs(utf8_to_wstring(filename));可能会误认为函数调用
/// 可以改成 ifstream ifs{utf8_to_wstring{filename}};

/// 对于没有explicit关键字时，可以使用大括号不写类名进行构造
class Obj {
public:
    Obj(int a = 1) : a_(a) {

    }

private:
    int a_;
};

Obj getObj() {
    //return {1.0}; // 可以直接返回，但不能窄化
    return {1};
}

/// 如果类有多个数据成员可以在构造函数进行初始化，逐个初始化很麻烦，有容易漏掉，c++11可以直接在变量声明时初始化
/// 这样下面的第一个构造函数使用变量自己的初始化，第二个构造函数中im_自己初始化，第三个使用构造函数初始化
class Complex {
public:
    Complex() {

    }

    Complex(float re) : re_(re) {

    }

    Complex(float re, float im) : re_(re), im_(im) {

    }

private:
    float re_{0};
    float im_{0};

};


/// 字面量（literal)是指在源代码中写出的固定常量
/// c++98中只能是原生类型，如：“hello"，字符串字面量，类型是const char[6]; 1, 整数字面量，类型int
/// 0.0,浮点数字面量，类型double；3.14f,浮点字面量； 123456789ul 无符号长整数字面量，类型unsigned long
/// c++11引入了自定义字面量，可用operator""后缀来将用于提供的字面量转换成实际类型。c++14则在标准哭中加入了不少标准字面量。
void testLiteral() {
//    cout << "i * i = " << 1i * 1i << endl; // c++14可以通过 c++11不行
//    cout << "hello world"s.substr(0, 5) << endl;
}

/// std 中包含3个子命名空间：std::literals::complex_literals std::literals::chrono_literals std::literals::string_literals


/// 自定义字面量实例
static constexpr double factors[] = {1.0, 1000.0, 1e-3, 1e-2, 0.0254, 0.3048, 0.9144, 1609.344};
class Length {
public:
    double value;

    enum unit {
        meter,
        kilometer,
        millimiter,
        centimiter,
        inch,
        foot,
        yard,
        mile
    };
    explicit Length(double v, unit u = meter) {
        value = v * factors[u];
    }

    // 可以把友元定义到类外也可以
    friend Length operator+(const Length& lhs, const Length& rhs) {
        return Length(lhs.value + rhs.value);
    }


};

Length operator"" _m(long double v) {
    return Length(v, Length::meter);
}

Length operator"" _cm(long double v) {
    return Length(v, Length::centimiter);
}

void testLength() {
    //Length length(1.0, Length::meter);
    Length length = 1.0_m; // 使用字面量进行初始化
    Length length1  = 1.0_m + 10.0_cm;
}

#include <bitset>
void testBitset() {
    unsigned mask = 0b111000000;
    cout << bitset<9>(mask) << endl;
}

//// 如下数字分割在c++14下是通过的，c++11不行
//void testSeprator() {
//    unsigned mask = 0b111'000'000;
//    long r_earth = 6'378'137;
//    double pi = 3.14159'26535'89793;
//    const unsigned magic = 0x44'42'47'4E;
//}
/// assert允许在运行时发现函数的前置条件是否成立。c++11从语言层面提供了静态断言机制
void testStaticAssert() {
//    const int a = 10; // 必须是编译时可计算的，满足常量表达式才行 int a = 10不行
//    static_assert(a == 10, "a must not be 10");
    const int n = 10;
    static_assert(n!=0, "n equals to zero");
}

// 似乎在模板编程中作用有些，因为这里模板实例化在编译器确定
template <typename T, int div>
double divide() {
    static_assert(div!=0, "div must not be zero");
};

template <typename T, int N>
class MyArray {
public:
    MyArray() {
        static_assert(N > 0, "N must bigger than zero");
    }
};

// 下面还是不行，必须是常量表达式
//double divide1(int a, int b) {
//    static_assert(b != 0, "div must not be zero");
//}

class AA {
public:
    AA(int a = 10) : b(a) {
    }
private:
//    const int a_ ; // constructor delete 非静态const成员&没有初始化 ，会导致默认构造函数被delete
//    const int a_ = 10; // ok
//    static const int a_; // ok
    //static int a_; // ok
    //int a; // ok
    int& b;         // 引用类型成员，会导致默认构造函数被delete
//    int a;      // 以下两行ok
//    int& b = a;
};

template <typename T>
class my_array {
public:
    my_array(size_t size) {};
//    my_array() : data_{nullptr}, size_{0} {
//
//    }
    // 或者
    my_array() = default;

private:
    T* data_{nullptr};
    size_t size_{0};
};

class BA final {

};

// BA无法继承
//class BAA : public BA {
//
//};
class B {
public:
    virtual void foo();
    virtual void bar() final;
};

class BB : public B {

    void foo() override ;
    //void bar() override ; // error
};

int main() {

    my_array<double> myArray;

//    AA a;
//    AA b(a);

    //MyArray<double, 1> myArray;
    //divide<double, 0>();
    //divide1(10, 10); // 不行
    //testStaticAssert();

    //testBitset();
    //testLiteral();
    //testFoo();
    //testDecltype();
    return 0;
}

