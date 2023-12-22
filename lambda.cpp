#include <iostream>
using namespace std;

void f(int a,int b){
    cout <<"----f-----"<<endl;
        cout << "a :" << a << endl;
        cout << "b :" << b << endl;


}

int main(int argc,char *argv[]){
    auto func =[](){
        cout<<"xujq52"<<endl;

    };
    int a{10};
    auto func0 = [a]()
    {
        cout << "a : " << a << endl;
    };

    int b{20};

    auto func1 = [&b, a]()
    {
        cout <<"----func1-----"<<endl;
        cout << "a :" << a << endl;
        cout << "b :" << b << endl;
        b++;
    };
    //取值
    auto func2 = [=]()
    {
         cout <<"----func2-----"<<endl;
        cout << "a :" << a << endl;
        cout << "b :" << b << endl;
    };
    //取引用
    auto func3 = [&]()
    {
         cout <<"----func3-----"<<endl;
        cout << "a :" << a << endl;
        cout << "b :" << b << endl;
        a++;
        b++;
    };
    func();
    func0();
    func1();
    f(a,b);
    func2();
    func3();
    cout << a << endl;
    cout << b << endl;
    return 0;
}

