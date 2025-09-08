#include <iostream>
#include <cstdlib> // 用于 rand() 和 srand()
#include <ctime>   // 用于 time()
#include <limits>  // 用于 numeric_limits

using namespace std;

int main() {
    // 初始化随机数种子
    srand(static_cast<unsigned int>(time(0)));
    
    char playAgain = 'y';
    
    cout << "🎮 欢迎来到猜数字游戏！" << endl;
    cout << "======================" << endl;
    
    // 主游戏循环
    while (playAgain == 'y' || playAgain == 'Y') {
        // 难度选择
        int maxNumber;
        int difficulty;
        cout << "\n请选择难度：" << endl;
        cout << "1. 简单 (1-50)" << endl;
        cout << "2. 中等 (1-100)" << endl;
        cout << "3. 困难 (1-200)" << endl;
        cout << "请选择 (1-3): ";
        cin >> difficulty;
        
        switch (difficulty) {
            case 1: maxNumber = 50; break;
            case 2: maxNumber = 100; break;
            case 3: maxNumber = 200; break;
            default: 
                cout << "无效选择，使用默认难度 (1-100)" << endl;
                maxNumber = 100;
        }
        
        // 生成随机数字
        int secretNumber = rand() % maxNumber + 1;
        int guess;
        int attempts = 0;
        int maxAttempts;
        
        // 根据难度设置最大尝试次数
        switch (difficulty) {
            case 1: maxAttempts = 10; break;
            case 2: maxAttempts = 7; break;
            case 3: maxAttempts = 5; break;
            default: maxAttempts = 7;
        }
        
        cout << "\n我已经想好了一个 1 到 " << maxNumber << " 之间的数字。" << endl;
        cout << "你有 " << maxAttempts << " 次机会来猜中它！" << endl;
        cout << "开始猜吧！" << endl;
        
        // 猜数字循环
        bool hasWon = false;
        while (attempts < maxAttempts && !hasWon) {
            cout << "\n第 " << (attempts + 1) << "/" << maxAttempts << " 次尝试: ";
            
            // 输入验证
            if (!(cin >> guess)) {
                cout << "请输入有效的数字！" << endl;
                cin.clear(); // 清除错误状态
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入
                continue;
            }
            
            attempts++;
            
            if (guess == secretNumber) {
                hasWon = true;
                cout << "🎉 恭喜你！第 " << attempts << " 次就猜对了！" << endl;
            } else if (guess < secretNumber) {
                cout << "⬆️  太小了！再试一次。" << endl;
            } else {
                cout << "⬇️  太大了！再试一次。" << endl;
            }
            
            // 给点提示（还剩3次机会时）
            if (maxAttempts - attempts == 3 && !hasWon) {
                if (secretNumber % 2 == 0) {
                    cout << "💡 提示：这个数字是偶数" << endl;
                } else {
                    cout << "💡 提示：这个数字是奇数" << endl;
                }
            }
        }
        
        // 游戏结束处理
        if (!hasWon) {
            cout << "\n😢 很遗憾，你没有猜中。正确的数字是: " << secretNumber << endl;
        }
        
        // 询问是否再玩一局
        cout << "\n是否再玩一局？(y/n): ";
        cin >> playAgain;
    }
    
    cout << "\n感谢游玩！再见！👋" << endl;
    return 0;
}