#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    // cout << sizeof(int *) << endl;
    // cout << sizeof(double *) << endl;
    // int intValue{13};
    // double *pDouble{&intValue};

    // 指针的初始化
    // 指向栈
    // 错误的写法
    // int *pNumber{nullptr};
    // int n{12};
    // int *pNumber{&n};
    // int *pNumber = &n;
    // cout << *pNumber << endl;

    // 指向堆
    int *pNumber{new int{13}};
    delete pNumber;    // 只是放弃控制
    pNumber = nullptr; // 清空

    // pNumber = new int{19};

    if (pNumber != nullptr)
    {
        cout << *pNumber << endl;
    }

    int *pNumber2{new int{14}}; // 14泄漏
    delete pNumber2;
    pNumber2 = nullptr;
    pNumber2 = new int{32};
    delete pNumber2;
    pNumber2 = nullptr;

    {
        int *pNumber3{new int{45}};
    } // 在scope后 泄漏45

    cout << "----- yz ------" << endl;
    return 0;
}
