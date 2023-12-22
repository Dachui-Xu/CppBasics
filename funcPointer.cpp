#include <iostream>
#include <string>
using namespace std;

char encrypt(const char &param)
{
    return param - 13;
}

char decrypt(const char &param)
{
    return param + 13;
}

void change(string &stringItem, char (*callbackFunction)(const char &))
{
    for (size_t i = 0; i < stringItem.size(); i++)
    {
        stringItem[i] = callbackFunction(stringItem[i]);
    }
}

int main(int argc, char *argv[])
{
    string msg{"xujq52"};
    // encrypt char - 13
    change(msg, encrypt);
    cout << "encrypt: " << msg << endl;

    change(msg, decrypt);
    cout << "msg : " << msg << endl;
    // decrypt char + 13
    cout << "----- yz ------" << endl;
    return 0;
}
