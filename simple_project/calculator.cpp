/*
项目一：计算器
目标：创建一个能进行加、减、乘、除运算的命令行程序
补充功能：
1. 支持连续计算。
2. 增加更多运算（求模、指数等）。
3. 处理除以零等错误。  
*/

// calculator.cpp
// 包含程序所需的基本输入输出流库
#include <iostream>
// 包含数学函数库，用于pow()等运算
#include <cmath>
// 包含字符串库，用于处理用户输入
#include <string>

using namespace std; // 使用标准命名空间，避免重复写std::

// 函数声明 (告诉编译器这些函数的存在)
void displayMenu();
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double modulo(int a, int b); // 求模运算通常用于整数
double power(double base, double exponent);

// 主函数，程序的入口点
int main() {
    // 变量声明
    char operation; // 存储用户选择的操作符
    char continueCalculation = 'y'; // 控制是否继续计算的变量，初始化为'y'
    double num1, num2, result; // 存储操作数和结果

    // 程序欢迎语
    cout << "欢迎使用高级命令行计算器!" << endl;
    cout << "==========================" << endl;

    // 主循环：只要用户想继续，程序就持续运行
    while (continueCalculation == 'y' || continueCalculation == 'Y') {
        
        // 显示计算器菜单
        displayMenu();
        
        // 获取用户选择的操作
        cout << "请选择操作 (+, -, *, /, %, ^): ";
        cin >> operation;

        // 获取操作数
        cout << "请输入第一个数字: ";
        cin >> num1;
        cout << "请输入第二个数字: ";
        cin >> num2;

        // 使用 switch 语句根据用户选择执行不同的计算
        switch (operation) {
            case '+':
                result = add(num1, num2);
                break;
            case '-':
                result = subtract(num1, num2);
                break;
            case '*':
                result = multiply(num1, num2);
                break;
            case '/':
                // 除法需要特别处理除以零的错误
                if (num2 == 0) {
                    cout << "错误：除数不能为零!" << endl;
                    // 跳过本次循环的剩余部分，直接询问是否继续
                    continue;
                } else {
                    result = divide(num1, num2);
                }
                break;
            case '%':
                // 求模运算需要整数，所以进行类型转换
                // 同样需要检查除数是否为零
                if (static_cast<int>(num2) == 0) {
                    cout << "错误：求模运算的除数不能为零!" << endl;
                    continue;
                } else {
                    result = modulo(static_cast<int>(num1), static_cast<int>(num2));
                }
                break;
            case '^':
                result = power(num1, num2);
                break;
            default:
                // 如果用户输入了无效的操作符
                cout << "错误：无效的操作符! 请使用 +, -, *, /, %, 或 ^." << endl;
                continue; // 跳过本次循环的剩余部分
        }

        // 显示计算结果
        cout << "计算结果: " << num1 << " " << operation << " " << num2 << " = " << result << endl;

        // 询问用户是否想继续计算
        cout << endl << "是否继续计算? (输入 y 继续, 其他键退出): ";
        cin >> continueCalculation;
        cout << endl;
    }

    // 程序结束语
    cout << "感谢使用计算器，再见!" << endl;
    return 0; // 程序正常退出
}

// 显示计算器菜单的函数
void displayMenu() {
    cout << endl;
    cout << "可用操作:" << endl;
    cout << "+ : 加法" << endl;
    cout << "- : 减法" << endl;
    cout << "* : 乘法" << endl;
    cout << "/ : 除法" << endl;
    cout << "% : 求模 (取余数)" << endl;
    cout << "^ : 指数 (幂运算)" << endl;
    cout << endl;
}

// 加法函数
double add(double a, double b) {
    return a + b;
}

// 减法函数
double subtract(double a, double b) {
    return a - b;
}

// 乘法函数
double multiply(double a, double b) {
    return a * b;
}

// 除法函数
double divide(double a, double b) {
    return a / b;
}

// 求模函数 (注意参数是int类型)
double modulo(int a, int b) {
    return a % b;
}

// 指数函数 (使用cmath库中的pow函数)
double power(double base, double exponent) {
    return pow(base, exponent);
}