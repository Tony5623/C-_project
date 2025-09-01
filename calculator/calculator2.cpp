#include <iostream>
#include <cmath>
#include <string>

using namespace std;

void displaymenu();
double add(double a, double b);
double sub(double a, double b);
double multiply(double a, double b);
double div(double a, double b);


void dispalymenu(){
    cout << endl;
    std::cout << "可用操作" << std::endl;
    std::cout << "+ : 加法" << std::endl;
    std::cout << "- : 减法" << std::endl;
    std::cout << "* : 乘法" << std::endl;
    std::cout << "/ : 除法" << std::endl;
    std::cout << "% : 求模（取余数）" << std::endl;
    std::cout << "^ : 指数（幂运算）" << std::endl;
    cout << endl;
}

double add(double a, double b){
    return a + b;
}

double sub(double a, double b){
    return a - b;
}

double multiply(double a, double b){
    return a * b;
}

double div(double a, double b){
    return a / b;
}

int main() {
    // 变量声明
    char opreation;
    double num1, num2, result;
    std::cout << "欢迎使用高级命令行计算器！" << std::endl;
    cout << "============================" << endl;
    dispalymenu();
    std::cout << "请选择操作 (+, -, *, /, %, ^): " << std::endl;
    cin >> opreation;
    std::cout << "请输入第一个数字：" << std::endl;
    cin >> num1;
    std::cout << "请输入第二个数字：" << std::endl;
    cin >> num2;

    switch (opreation)
    {
    case '+':
        result = add(num1, num2);
        break;
    case '-':
        result = sub(num1, num2);
        break;
    case '*':
        result = multiply(num1 ,num2);
        break;
    case '/':
        result = div(num1 ,num2);
        break;    
    default:
        std::cout << "请输入有效字符！！" << std::endl;
        break;
    }

    cout << "计算结果：" << num1 << "" << opreation << " " << num2 << " = " << result <<endl;
    return 0;
}