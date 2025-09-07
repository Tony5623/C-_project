#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

// 任务结构体
struct Task
{
    int id;
    string description;
    string priority;
    string deueDate;
    bool completed;

    Task(int i, string desc, string pri = "中", string date = "", bool comp = false)
        :id(i), description(desc), priority(pri), deueDate(date), completed(comp){}
};

class TodoList{
private:
    vector<Task> tasks;
    int nextId;
    const string filename = "todo_data2.txt";

public:
    TodoList() : nextId(1) // 初始化列表：在构造函数体执行之前初始化成员变量;将nextId初始化为1
    {
        loadFromFile();
    }

    //从文件加载任务
    void loadFromFile(){
        ifstream file(filename);
        if (!file.is_open()){
            cout << "未找到保存文件，创建新的代办列表..." << endl;
            return;
        }

        tasks.clear(); //清空当前内存中的任务列表，为加载新数据做准备
        string line;
        while (getline(file, line))
        {
            if (line.empty()) continue; // 跳过空行，避免处理无效数据

            stringstream ss(line); //将一行字符串转换为字符串流，便于分割
            string token;
            vector<string> tokens;

            while (getline(ss, token, '|'))  //使用'|'作为分隔符来分割字符串
            {
                tokens.push_back(token);  //将分割后的每个部分存入tokens向量

            }

            if (tokens.size() >= 5){
                int id = stoi(tokens[0]); //字符串转整数
                string desc = tokens[1];
                string pri = tokens[2];
                string date = tokens[3];
                bool comp = (tokens[4] == "1");

                tasks.emplace_back(id, desc, pri, date, comp);
                nextId = max(nextId, id +1);
            }


            
        }
        file.close();
        


    }

    //保存任务到文件
    void saveToFile() {
        ofstream file(filename);  // 如果文件不存在：自动创建新文件;  如果文件已存在：清空文件内容并重新写入（覆盖模式）
        for ( const auto& task : tasks)  //tasks容器中的单个任务（单数）;在循环中，task依次表示：任务1 → 任务2 → 任务3
        {
            file << task.id << "|"
                 << task.description << "|"
                 << task.priority << "|"
                 << task.deueDate << "|"
                 << (task.completed ? "1" : "0") << "\n";
        }
        file.close();        
    }

    void addTask(const string& description, const string& priority = "中", const string& dueData = ""){
        tasks.emplace_back(nextId++, description, priority, dueData);
        saveToFile();
        std::cout << "✅ 任务添加成功! (ID: " << (nextId - 1) << ")" << std::endl;
    }

     // 验证日期格式
    bool isValidDate(const string& date) {
        if (date.empty()) return true;
        if (date.length() != 10) return false;
        if (date[4] != '-' || date[7] != '-') return false;
        
        // 简单验证，实际项目中需要更复杂的验证
        return true;
    }
};

// 显示帮助信息
void showHelp() {
    cout << "\n📖 使用说明:" << endl;
    cout << "add <描述> [优先级] [截止日期] - 添加任务" << endl;
    cout << "delete <ID>                   - 删除任务" << endl;
    cout << "done <ID>                     - 标记任务完成" << endl;
    cout << "undo <ID>                     - 标记任务未完成" << endl;
    cout << "list                          - 显示所有任务" << endl;
    cout << "active                        - 显示未完成任务" << endl;
    cout << "priority <低/中/高>           - 按优先级筛选" << endl;
    cout << "stats                         - 显示统计信息" << endl;
    cout << "help                          - 显示帮助" << endl;
    cout << "exit                          - 退出程序" << endl;
    cout << "\n💡 示例:" << endl;
    cout << "add \"学习C++\" 高 2025-09-04" << endl;
    cout << "add \"买 groceries\" 中" << endl;
    cout << "priority 高" << endl;
}

int main() {
    TodoList todolist;
    string command;

    cout << "✅ 欢迎使用待办事项管理器!" << endl;
    cout << "输入 'help' 查看使用说明" << endl;
    
    while (true)
    {
        cout << "\n> ";
        getline(cin, command); //读取一整行输入，包括空格

        if (command.empty()) continue;

        stringstream ss(command);  //用用户输入的字符串创建stringstream对象
        string action;
        ss >> action;
        cout << ss.str() << endl;

        if (action == "exit" || action == "quit"){
            cout << "👋 再见！" << endl;
            break;
        }
        else if (action == "help")
        {
            showHelp();
        }
        else if (action == "add")
        {
            string description, priority = "中", dueDate = "";
            string token; //临时存储提取的字符串片段
            
            cout << "初始化ss内容：" << ss.str() << endl;
            // 读取描述
            getline(ss, token, '"');
            
            cout << "第一次getline后token: '" << token << "'" << endl;
            cout << "第一次getline后ss内容: " << ss.str() << endl;
            
            getline(ss, description,'"');
            cout << "第二次getline后description: '" << description << "'" << endl;
            cout << "第二次getline后ss内容: " << ss.str() << endl;
            if (description.empty()) {
                cout << "❌ 请输入任务描述" << endl;
                continue;
            }

            // 读取可选参数
            cout << "ss:" << ss.str() << endl; //ss.str()返回的是整个字符串流的原始内容;
            //读取位置已经移动
            
            while (ss >> token) {
                cout << "token:" << token << endl;
                if (token == "高" || token == "中" || token == "低") {
                    priority = token;
                } else if (todolist.isValidDate(token)) {
                    dueDate = token;
                }
            }




            todolist.addTask(description, priority, dueDate);
        }
    }
    

    return 0;
}
