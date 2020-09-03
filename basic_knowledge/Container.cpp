//
// Created by xcmworkharder on 2020-09-01 下午6:01.
//
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/// string，也当成一种容器
void testString() {
    string testStr = "hello world";
    cout << *testStr.begin() << " " << *(testStr.end()-1) << endl;
    cout << testStr.empty() << endl;
    cout << testStr.size() << endl;
    string().swap(testStr);
    cout << testStr.size() << " " << testStr << endl;

    string testStr2 = "i love";
    string testStr3 = " you";
    cout << testStr2.find('l') << " " << testStr2.rfind("e") << endl;

}

/// 函数参数不建议使用const string& 除非知道参数为string字符串，使用const char* 可以避免c字符串向string的构造，这种构造和析构要付出巨大代价
/// 使用c++17的string_view作为参数较好，及时是c字符串，也不会引发不必要的内存复制

/// vector 尾部插入效率极高，最好提前reserve
// vector通常异常强相关性，其中元素提供一个保证不抛异常的移动构造函数，否则vector会使用拷贝构造函数，可能代价较高
// C++11 提供emplace系列函数，使用push_back会额外生成临时对象，多一次拷贝构造和析构
// 尽早使用reserve函数为vector保留的内存

/// deque(double-ended queue),双端队列，适合头尾添加和删除元素，由于大部分元素连续，能够高效的遍历
// deque不提供data capacity 和 reserve成员函数

/// list 双向链表，高效的O(1)插入和删除， 适合不太需要遍历，需要频繁的插入和删除的场景
// list不提供data capacity 和 reserve成员函数
// 标准算法在list经常会有问题，list提供了merge remove remove_if reverse sort unique作为替代

/// forward_list 只有在为了节省空间的场景才会用它
// 单向链表，标准库的一部分

/// queue 实际是一种容器适配器 可以使用多种容器实现，缺省用deque实现， 不提供begin end
/// stack 也是一种容器适配器 缺省也是deque实现， 没有begin end


//////////////////////////////////////////////////////////////////////

/// 需要函数对象的容器

// less
template <typename T>
class less : binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const {
        return x < y;
    }
};

// hash 没有默认实现，需要进行特化
//template <typename T> class hash;
//
//template <>
//class hash<int> : public unary_function<int, size_t> {
//    size_t operator()(int v) const noexcept {
//        return static_cast<size_t>(v);
//    }
//};


void testList() {
    list<int> lst{1, 3, 2, 8, 3};
    vector<int> vec{1, 4, 2, 8};

    sort(vec.begin(), vec.end());
    //sort(lst.begin(), lst.end()); // 会出错
    lst.sort(); // 正确
    for (const auto& l : lst) {
        cout << l << endl;
    }
}

void testFunctor() {
    vector<int> v{13, 6, 4, 11, 29};
    sort(v.begin(), v.end(), greater<int>());
    for (auto vv : v) {
        cout << vv << endl;
    }

    auto hp = hash<int*>();
    cout << hp(nullptr) << endl;
    cout << *(v.data() + 1) << endl;

    auto hs = hash<string>();
    cout << hs(string("hello")) << endl;
}

// priority_queue 也是一个容器适配器， 使用less实现一个大顶堆 使用greater实现一个小顶堆
void testPriorityQueue() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({1, 1});
    q.push({2, 2});
    q.push({0, 3});
    q.push({9, 4});
    while (!q.empty()) {
        cout << q.top().first << ":" << q.top().second << endl;
        q.pop();
    }
}

int main() {

//    testString();
//    testList();
//    testFunctor();
    testPriorityQueue();
    return 0;
}
