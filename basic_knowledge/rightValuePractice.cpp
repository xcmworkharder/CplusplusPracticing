//
// Created by xcmworkharder on 2020-09-01 上午11:38.
//
#include <iostream>

using namespace std;


class shape {
public:
    shape() {
        cout << "shape()" << endl;
    }
    virtual ~shape() {
        cout << "~shape()" << endl;
    };
};

class circle : public shape {
public:
    circle() {
        cout << "circle()" << endl;
    }

    ~circle() {
        cout << "~circle()" << endl;
    }
};

class triangle : public shape {
public:
    triangle() {
        cout << "triangle()" << endl;
    }

    ~triangle() {
        cout << "~triangle()" << endl;
    }
};

class result {
public:
    result() {
        cout << "result()" << endl;
    }

    ~result() {
        cout << "~result()" << endl;
    }
};

result process_shape(const shape& shape1, const shape& shape2) {
    cout << "process_shape()" << endl;
    return result();
}

shape getshape(circle circle1) {
    shape shape1 = circle1;
    return shape1;
}

void testMove() {
    cout << "main()" << endl;
    result&& r = std::move(process_shape(circle(), triangle()));
    cout << "somethiing else" << endl;
}


/// 不要返回本地变量的引用
class Obj {
public:
    Obj() {
        cout << "Obj()" << endl;
    }

    Obj(const Obj&) {
        cout << "Obj(const Obj&)" << endl;
    }

    Obj(Obj&&) {
        cout << "Obj(Obj&&)" << endl;
    }
};

Obj simple() {
    Obj obj;
    // 简单返回对象　一般有NRVO(named return value optimization)返回值优化
    return obj;
}

Obj simple_with_move() {
    Obj obj;
    // 使用move，会禁止NRVO
    return std::move(obj);
}

Obj complicated(int n) {
    Obj obj1;
    Obj obj2;
    if (n % 2 == 0) {
        return obj1;
    } else {
        return obj2;
    }
}

void testReturnObj() {
    cout << "*** 1 ***" << endl;
    auto obj1 = simple();

    cout << "*** 2 ***" << endl;
    auto obj2 = simple_with_move();

    cout << "*** 3 ***" << endl;
    auto obj3 = complicated(42);
}

/// 引用坍缩和完美转发
void foo(const int& a) {
    cout << "foo(const int&)" << endl;
}

void foo(int&& a) {
    cout << "foo(int&&)" << endl;
}

void bar(const int& s) {
    //cout << "bar(int&)" << endl;
    foo(s);
}

//template <typename T>
void bar(int&& s) {
    //cout << "bar(int&&)" << endl;
    int s1 = 10;
    int& s2 = s1;
    foo(forward<int>(s2));
}

void testBar() {
    int a = 10;
    // 左值引用
    bar(a);
    // 右值引用
    bar(move(a));
}

int main() {
    testBar();
    return 0;
}
