//
// Created by xcmworkharder on 2020-08-31 下午4:19.
//
#include <iostream>

using namespace std;

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

    virtual void print() {
        cout << "print shape" << endl;
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

    void print() override {
        cout << "print circle" << endl;
    }
};

class triangle : public shape {
public:
    triangle() {
        cout << "ctr triangle" << endl;
    }

    ~triangle() {
        cout << "dtr triangle" << endl;
    }

    void print() override {
        cout << "print triangle" << endl;
    }
};
class rectangle : public shape {
public:
    rectangle() {
        cout << "ctr rectangle" << endl;
    }

    ~rectangle() {
        cout << "dtr rectangle" << endl;
    }

    void print() override {
        cout << "print rectangle" << endl;
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

/// auto_ptr
template <typename T>
class auto_ptr {
public:
    explicit auto_ptr(T* ptr = nullptr) : ptr_(ptr) {

    }

    ~auto_ptr() {
        delete ptr_;
    }

    // 为防止拷贝构造产生的资源多次释放，可以禁用拷贝构造和赋值构造
//    auto_ptr(auto_ptr& other) = delete;
//    auto_ptr&operator = (auto_ptr& rhs) = delete;

    // 使用转移指针所有权的方式更好
    auto_ptr(auto_ptr& other) {
        ptr_ = other.release();
    }

    auto_ptr& operator = (auto_ptr& rhs) {
        auto_ptr(rhs).swap(*this);
        return *this;
    }

    T* get() const {
        return ptr_;
    }

    T& operator * () const {
        return *ptr_;
    }

    T* operator -> () const {
        return ptr_;
    }

    operator bool() const {
        return ptr_;
    }

private:
    T* release() {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void swap(auto_ptr& rhs) {
        using std::swap;
        swap(ptr_, rhs.ptr_);
    }

private:
    T* ptr_;
};

/// unique_ptr
template <typename T>
class unique_ptr {
public:
    explicit unique_ptr(T* ptr = nullptr) : ptr_(ptr) {

    }

    ~unique_ptr() {
        delete ptr_;
    }

    // 为防止构造对象误释放,使用移动语义
    unique_ptr(unique_ptr&& other) {
        ptr_ = other.release();
    }

    // 这里传参使用值,不用进行创建临时对象
    unique_ptr& operator = (unique_ptr rhs) {
        rhs.swap(*this);
        return *this;
    }

    T* get() const {
        return ptr_;
    }

    T& operator * () const {
        return *ptr_;
    }

    T* operator -> () const {
        return ptr_;
    }

    operator bool() const {
        return ptr_;
    }

private:
    T* release() {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void swap(unique_ptr& rhs) {
        using std::swap;
        swap(ptr_, rhs.ptr_);
    }

private:
    T* ptr_;
};

class Shared_Count {
public:
    Shared_Count() noexcept : count_(1) {

    }

    void add_count() noexcept {
        ++count_;
    }
    long reduce_count() noexcept {
        return --count_;
    }
    long get_count() const noexcept {
        return count_;
    }

private:
    long count_;
};

/// share_ptr
template <typename T>
class share_ptr {
    template <typename U> friend class share_ptr;
public:
    explicit share_ptr(T* ptr = nullptr) : ptr_(ptr) {
        //cout << "ctr" << endl;
        if (ptr_) {
            shared_count_ = new Shared_Count();
        }
    }

    ~share_ptr() {
        if (ptr_ && !shared_count_->reduce_count()) {
            delete ptr_;
            delete shared_count_;
        }
    }

    // 为了支持dynamic_cast等转换，定义构造函数如下
    template <typename U>
    share_ptr(const share_ptr<U>& other, T* ptr) noexcept : ptr_(ptr) {
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }

    template <typename U>
    share_ptr(const share_ptr<U>& other) noexcept {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }

    // 使用移动构造函数模板可以实现share_ptr<circle>向share_ptr<shape>转换，无法实现向share_ptr<triangle>转化
    template <typename U>
    share_ptr(share_ptr<U>&& other) noexcept {
        cout << "copy" << endl;
        ptr_ = other.ptr_;
        if (ptr_) {
            shared_count_ = other.shared_count_;
            other.ptr_ = nullptr;
        }
    }

    // 这里传参使用值,不用进行创建临时对象
    share_ptr& operator = (share_ptr rhs) noexcept {
        cout << "assign" << endl;
        rhs.swap(*this);
        return *this;
    }

    T* get() const noexcept {
        return ptr_;
    }

    T& operator * () const noexcept {
        return *ptr_;
    }

    T* operator -> () const noexcept {
        return ptr_;
    }

    operator bool() const noexcept {
        return ptr_;
    }

    long use_count() const noexcept {
        if (ptr_) {
            return shared_count_->get_count();
        } else {
            return 0;
        }
    }

    void swap(share_ptr& rhs) noexcept {
        using std::swap;
        swap(ptr_, rhs.ptr_);
        swap(shared_count_, rhs.shared_count_);
    }

private:
    T* ptr_;
    Shared_Count* shared_count_;
};

template <typename T>
void swap(share_ptr<T>& lhs, share_ptr<T>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename T, typename U>
share_ptr<T> dynamic_pointer_cast(const share_ptr<U>& other) {
    T* ptr = dynamic_cast<T*>(other.get());
    return share_ptr<T>(other, ptr);
}

template <typename T, typename U>
share_ptr<T> static_pointer_cast(const share_ptr<U>& other) {
    T* ptr = static_cast<T*>(other.get());
    return share_ptr<T>(other, ptr);
}

template <typename T, typename U>
share_ptr<T> reinterpret_pointer_cast(const share_ptr<U>& other) {
    T* ptr = reinterpret_cast<T*>(other.get());
    return share_ptr<T>(other, ptr);
}

template <typename T, typename U>
share_ptr<T> const_pointer_cast(const share_ptr<U>& other) {
    T* ptr = const_cast<T*>(other.get());
    return share_ptr<T>(other, ptr);
}

void useShape() {
    share_ptr<circle> ptr1{new circle()};
    cout << "count of ptr1 is " << ptr1.use_count() << endl;

    share_ptr<shape> ptr2;
    cout << "count of ptr2 is " << ptr2.use_count() << endl;

    ptr2 = ptr1;
    cout << "count of ptr2 is " << ptr2.use_count() << endl;
    cout << "count of ptr1 is " << ptr1.use_count() << endl;

    if (!ptr1) {
        cout << "ptr1 is not empty" << endl;
    }

    share_ptr<circle> ptr3 = dynamic_pointer_cast<circle>(ptr2);
    cout << "count of ptr3 is " << ptr3.use_count() << endl;
    cout << "count of ptr1 is " << ptr1.use_count() << endl;
    cout << "count of ptr2 is " << ptr2.use_count() << endl;
}

int main() {

    useShape();
    return 0;
}
