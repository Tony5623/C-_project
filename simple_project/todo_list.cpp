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
struct Task {
    int id;
    string description;
    string priority; // 低、中、高
    string dueDate;  // 截止日期 (格式: YYYY-MM-DD)
    bool completed;
    
    Task(int i, string desc, string pri = "中", string date = "", bool comp = false)
        : id(i), description(desc), priority(pri), dueDate(date), completed(comp) {}
};

class TodoList {
private:
    vector<Task> tasks;
    int nextId;
    const string filename = "todo_data-test.txt";

public:
    TodoList() : nextId(1) {
        loadFromFile();
    }

    // 从文件加载任务
    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "未找到保存文件，创建新的待办列表..." << endl;
            return;
        }

        tasks.clear();
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string token;
            vector<string> tokens;
            
            while (getline(ss, token, '|')) {
                tokens.push_back(token);
            }
            
            if (tokens.size() >= 5) {
                int id = stoi(tokens[0]);
                string desc = tokens[1];
                string pri = tokens[2];
                string date = tokens[3];
                bool comp = (tokens[4] == "1");
                
                tasks.emplace_back(id, desc, pri, date, comp);
                nextId = max(nextId, id + 1);
            }
        }
        file.close();
    }

    // 保存任务到文件
    void saveToFile() {
        ofstream file(filename);
        for (const auto& task : tasks) {
            file << task.id << "|"
                 << task.description << "|"
                 << task.priority << "|"
                 << task.dueDate << "|"
                 << (task.completed ? "1" : "0") << "\n";
        }
        file.close();
    }

    // 添加任务
    void addTask(const string& description, const string& priority = "中", const string& dueDate = "") {
        tasks.emplace_back(nextId++, description, priority, dueDate);
        saveToFile();
        cout << "✅ 任务添加成功! (ID: " << (nextId - 1) << ")" << endl;
    }

    // 删除任务
    void deleteTask(int id) {
        auto it = find_if(tasks.begin(), tasks.end(), 
            [id](const Task& task) { return task.id == id; });
        
        if (it != tasks.end()) {
            tasks.erase(it);
            saveToFile();
            cout << "✅ 任务删除成功!" << endl;
        } else {
            cout << "❌ 未找到ID为 " << id << " 的任务" << endl;
        }
    }

    // 标记任务完成/未完成
    void toggleTask(int id) {
        auto it = find_if(tasks.begin(), tasks.end(), 
            [id](const Task& task) { return task.id == id; });
        
        if (it != tasks.end()) {
            it->completed = !it->completed;
            saveToFile();
            cout << "✅ 任务状态已更新!" << endl;
        } else {
            cout << "❌ 未找到ID为 " << id << " 的任务" << endl;
        }
    }

    // 显示所有任务
    void showTasks(bool showCompleted = true, const string& filterPriority = "") {
        if (tasks.empty()) {
            cout << "📝 当前没有待办任务!" << endl;
            return;
        }

        cout << "\n📋 待办事项列表:" << endl;
        cout << "==============================================" << endl;
        cout << left << setw(4) << "ID" << setw(8) << "状态" 
             << setw(6) << "优先级" << setw(12) << "截止日期" 
             << "描述" << endl;
        cout << "==============================================" << endl;

        for (const auto& task : tasks) {
            if (!showCompleted && task.completed) continue;
            if (!filterPriority.empty() && task.priority != filterPriority) continue;

            string status = task.completed ? "✅" : "⏳";
            string priorityEmoji;
            if (task.priority == "高") priorityEmoji = "🔴";
            else if (task.priority == "中") priorityEmoji = "🟡";
            else priorityEmoji = "🟢";

            cout << left << setw(4) << task.id 
                 << setw(8) << status
                 << setw(6) << (priorityEmoji + task.priority)
                 << setw(12) << (task.dueDate.empty() ? "无" : task.dueDate)
                 << task.description << endl;
        }
        cout << "==============================================" << endl;
    }

    // 显示统计信息
    void showStats() {
        int total = tasks.size();
        int completed = count_if(tasks.begin(), tasks.end(), 
            [](const Task& task) { return task.completed; });
        
        cout << "\n📊 任务统计:" << endl;
        cout << "总任务: " << total << endl;
        cout << "已完成: " << completed << endl;
        cout << "未完成: " << (total - completed) << endl;
        cout << "完成率: " << (total > 0 ? (completed * 100 / total) : 0) << "%" << endl;
    }

    // 获取当前日期（用于日期验证）
    string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
        return string(buffer);
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
    cout << "add \"学习C++\" 高 2024-01-15" << endl;
    cout << "add \"买 groceries\" 中" << endl;
    cout << "priority 高" << endl;
}

int main() {
    TodoList todoList;
    string command;
    
    cout << "✅ 欢迎使用待办事项管理器!" << endl;
    cout << "输入 'help' 查看使用说明" << endl;

    while (true) {
        cout << "\n> ";
        getline(cin, command);

        if (command.empty()) continue;

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "exit" || action == "quit") {
            cout << "👋 再见！" << endl;
            break;
        }
        else if (action == "help") {
            showHelp();
        }
        else if (action == "list") {
            todoList.showTasks(true);
        }
        else if (action == "active") {
            todoList.showTasks(false);
        }
        else if (action == "stats") {
            todoList.showStats();
        }
        else if (action == "add") {
            string description, priority = "中", dueDate = "";
            string token;
            
            // 读取描述（可能包含空格）
            getline(ss, token, '"');
            getline(ss, description, '"');
            
            if (description.empty()) {
                cout << "❌ 请输入任务描述" << endl;
                continue;
            }

            // 读取可选参数
            while (ss >> token) {
                if (token == "高" || token == "中" || token == "低") {
                    priority = token;
                } else if (todoList.isValidDate(token)) {
                    dueDate = token;
                }
            }

            todoList.addTask(description, priority, dueDate);
        }
        else if (action == "delete") {
            int id;
            if (ss >> id) {
                todoList.deleteTask(id);
            } else {
                cout << "❌ 请输入有效的任务ID" << endl;
            }
        }
        else if (action == "done" || action == "undo") {
            int id;
            if (ss >> id) {
                todoList.toggleTask(id);
            } else {
                cout << "❌ 请输入有效的任务ID" << endl;
            }
        }
        else if (action == "priority") {
            string priority;
            if (ss >> priority && (priority == "高" || priority == "中" || priority == "低")) {
                todoList.showTasks(true, priority);
            } else {
                cout << "❌ 请输入有效的优先级(高/中/低)" << endl;
            }
        }
        else {
            cout << "❌ 未知命令，输入 'help' 查看使用说明" << endl;
        }
    }

    return 0;
}