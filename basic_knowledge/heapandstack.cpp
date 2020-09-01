//
// Created by xcmworkharder on 2020-08-31 下午12:52.
//
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/// 以下是不推荐的方式,这样的话可以直接使用栈空间就可以了
void foo() {
    int* intPtr = new int();
    cout << "call function" << endl;
    delete intPtr;
}

/// 推荐的方法是下面写法,分配和释放不在一起写
int* make_int() {
    int* intPtr = nullptr;
    try {
        intPtr = new int();
        // 中间代码
    } catch(...) {
        delete intPtr;
        throw;
    }
    return intPtr;
}

void callAbove() {
    int* intPtr = make_int();
    cout << "call above" << endl;
    //...
    delete intPtr; // 这样容易漏掉delete,可以使用智能指针
}

enum class shape_type {
    circle,
    triangle,
    rectangle
};

class shape {
public:
    shape() {
        cout << "ctr shape" << endl;
    }

    virtual ~shape() {
        cout << "dtr shape" << endl;
    }
};

class circle : public shape {
public:
    circle() {
        cout << "ctr circle" << endl;
    }

    ~circle() {
        cout << "dtr circle" << endl;
    }
};

class triangle : public shape {
public:
    triangle() {
        cout << "ctr triangle" << endl;
    }
};
class rectangle : public shape {
public:
    rectangle() {
        cout << "ctr rectangle" << endl;
    }
};

shape* create_shape(shape_type type) {
    switch (type) {
        case shape_type::circle:
            return new circle;
        case shape_type::triangle:
            return new triangle;
        case shape_type::rectangle:
            return new rectangle;
        default:
            return new circle;
    }
}

class shape_wrapper {
public:
    explicit shape_wrapper(shape* ptr = nullptr) : ptr_(ptr) {

    }

    ~shape_wrapper() {
        delete ptr_;
    }

    shape* get() const { return ptr_; }

private:
    shape* ptr_;
};

void useShape() {
    shape_wrapper ptr_wrapper(create_shape(shape_type::circle));
}

/// 推荐的方法
std::mutex mtx;
void some_func() {
    std::lock_guard<std::mutex> guard(mtx);
    // 需要同步的工作...
}

/// 不推荐的方法
void some_fun1() {
    mtx.lock();

    // 需要同步的工作...

    mtx.unlock();
}

int main(int argc, char** argv) {

    useShape();
    return 0;
}
