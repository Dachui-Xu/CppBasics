#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{

    cout << isalnum('A') << endl;
    cout << isalnum('e') << endl;
    cout << isalnum('1') << endl;
    cout << isalnum('^') << endl;

    cout << "isalpha" << endl;
    // isalpha是否为字符
    cout << isalpha('A') << endl;
    cout << isalpha('e') << endl;
    cout << isalpha('1') << endl;
    cout << isalpha('^') << endl;
    // isdigit是否为数字
    cout << isdigit('A') << endl;
    cout << isdigit('e') << endl;
    cout << isdigit('1') << endl;
    cout << isdigit('^') << endl;

    cout << "isblank" << endl;
    string msg{"HSello yzzy yz!"};
    int blankNum{0};
    for (auto i : msg)
    {
        if (isblank(i))
        {
            blankNum++;
        }
    }

    cout << blankNum << endl;

    cout << "islower isupper" << endl;

    cout << isupper('a') << endl;
    cout << isupper('e') << endl;
    cout << isupper('L') << endl;
    cout << isupper('1') << endl;
    cout << endl;

    cout << islower('a') << endl;
    cout << islower('e') << endl;
    cout << islower('L') << endl;
    cout << islower('1') << endl;
    cout << endl;
    // 用引用进行修改
    for (auto &i : msg)
    {
        i = toupper(i);
    }

    cout << msg << endl;
    for (size_t i = 0; i < msg.size(); i++)
    {
        msg[i] = tolower(msg[i]);
    }
    cout << msg << endl;
    return 0;
}
