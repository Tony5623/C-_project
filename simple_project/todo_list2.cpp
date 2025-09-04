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
    TodoList() : nextId(1) // 将nextId初始化为1
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
        for ( const auto& task : tasks)
        {
            file << task.id << "|"
                 << task.description << "|"
                 << task.priority << "|"
                 << task.deueDate << "|"
                 << (task.completed ? "1" : "0") << "\n";
        }
        
    }
};

int main() {
    TodoList todolist;
    string command;

    cout << "✅ 欢迎使用待办事项管理器!" << endl;
    cout << "输入 'help' 查看使用说明" << endl;
    
    while (true)
    {
        cout << "\n> ";
        getline(cin, command);
    }
    

    return 0;
}
