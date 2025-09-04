#include <iostream>
#include <cstdlib> //用于rand（）和srand()
#include <ctime> // 用于time（）
#include <limits> //用于numeric_limits

using namespace std;

int main() {
    // 初始化随机数种子
    srand(static_cast<unsigned int>(time(0)));

    char playagain = 'y';

    cout << "🎮 欢迎来到猜数字游戏！" << endl;
    cout << "======================" << endl;


    // 主游戏循环
    while (playagain == 'y' || playagain == 'Y')
    {
        int maxNumber;
        int difficulty;
        cout << "\n请选择难度" << endl;
        cout << "1. 简单 (1-50)" << endl;
        cout << "2. 中等 (1-100)" << endl;
        cout << "3. 困难 (1-150)" << endl;
        cout << "4. 噩梦 (1-200)" << endl;
        cout << "请选择 (1-4): ";
        cin >> difficulty ;

        switch (difficulty)
        {
        case 1: maxNumber = 50; break;
        case 2: maxNumber = 100; break;
        case 3: maxNumber = 150; break;   
        case 4: maxNumber = 200; break;     
        default:
            cout << "无效选择，使用默认难度"  << endl;
            maxNumber = 100;
            break;
        }

        // 生成随机数  srand():播种，rand():生成
        int secretNumber = rand() % maxNumber +1;
        int guess;
        int attemps = 0;
        int maxAttemps;

        //根据难度设置最大尝试数
        switch (difficulty)
        {
        case 1: maxAttemps = 10; break;
        case 2: maxAttemps = 9; break;
        case 3: maxAttemps = 8; break;    
        case 4: maxAttemps = 7; break;    
        default: maxAttemps = 9; break;
        }

        cout << "\n我已经想好了一个 1 到 " << maxNumber << "之间的数。" << endl;
        cout << "你有 " << maxAttemps << "次机会来猜中它！" << endl;
        cout << "开始猜吧！" << endl;

        while (attemps < maxAttemps)
        {
            cout << "\n第 " << (attemps +1) << "/" << maxAttemps << " 次尝试";

            //输入验证
            if (!(cin >> guess))
            {
                cout << "请输入有效的数字！" << endl;
                cin.clear(); // 清除错误状态
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入
                continue;
            }

            attemps++;

            if (guess == secretNumber)
            {   
                cout << "🎉 恭喜你！第 " << attemps << " 次就猜对了！" << endl;
                break;
            } else if (guess < secretNumber)
            {
                cout << "⬆️  太小了！再试一次。" << endl;
            }
            else {
                cout << "⬇️  太大了！再试一次。" << endl;
            }
            
            
        }
        cout << "😢 很遗憾，你没有猜中。正确的数字是:" << secretNumber << endl;

        //是否再玩一局
        cout << "\n是否再玩一局？(y/n): ";
        cin >> playagain;
    }
    

    cout << "\n感谢游玩！ 再见！👋" << endl;
    return 0;
}