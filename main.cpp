#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;

    // 用于调试的简单计算
    int a = 5;
    int b = 7;
    int result = a + b;
    cout << "The result is: " << result << endl;

    return 0;
}