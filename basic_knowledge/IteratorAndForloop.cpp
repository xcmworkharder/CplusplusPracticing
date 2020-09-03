//
// Created by xcmworkharder on 2020-09-02 上午10:04.
//
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;


/***
 * 迭代器是一个通用的概念，并不是一个特定的类型，应该说是一组对类型的要求，基本要求是从一个端点出发，下一步、下一步地到达另一个断点。
 * 这里迭代和遍历相似。
 */

/// begin end 的返回类型提出要求。begin的类型为I, end的类型为S
/// 要求包括：I 对象支持*操作，解引用取得容器内某个对象；支持++,指向下一个对象；I可以和I或者S比较，判断是否到了指定位置（S表示遍历结束)
/// c++ 17之前，I和S必须相同，c++17开始，I和S可以不同

/// 迭代器按照能力强弱，以及容器类型需要，从弱到强分为读取、输入；前向、双向、随机和连续（c++20）几种。
/// 指针满足所有迭代器的要求，因此也是迭代器。因为迭代器都是对指针进行抽象得出的。

/// 常用的容器迭代器
/// iterator可以写入，const_iterator不可写入。
/// vector::iterator array::iterator 可以满足连续迭代器
/// deque::iterator可以满足随机访问迭代器（部分内存连续）
/// list::iterator 可以满足双向迭代要求
/// forward_list::iterator 可以满足单向迭代要求

/// 输出迭代器back_inserter 返回类型是back_inserter_iterator,可以方便在容器尾部进行插入操作。
/// ostream_iterator，方便容器内容拷贝到一个输出流
void testBackInserter() {
    vector<int> v1{1, 3, 3, 5};
    vector<int> v2;
    copy(v1.begin(), v1.end(), back_inserter(v2));
//    for (auto v : v2) {
//        cout << v << endl;
//    }
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
}

int main() {

    testBackInserter();
    return 0;
}
