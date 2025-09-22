#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <memory>

using namespace std;

class Contact {

protected:
    std::string name;
    string phone;
    string email;
    string type;

public:
    Contact(const string& n, const string& p, const string& e, const string& t)
        : name(n), phone(p), email(e), type(t) {}

    virtual ~Contact() {}

    // 获取器
    string getName() const {return name;}
    string getPhone() const { return phone;}
    string getEmail() const { return email; }
    string getType() const { return type; }

    //设置器
    void setPhone(const string& p) { phone = p; }
    void setEmail(const string& e) { email = e; }


    //制作联系人表格，显示联系人信息，虚函数，允许子类重写
    virtual void display() const{
        cout << "📇 " << setw(15) << left << type << " | "
             << setw(20) << name << " | "
             << setw(15) << phone << " | "
             << setw(25) << email << endl;
    }

    //转换为字符串用于文件存储
    virtual string toString() const {
        return type + "|" + name + "|" + phone + "|" + email;
    }
    
    // 验证电话号码格式
    static bool isValidPhone(const string& phone) {
        if (phone.empty()) return false;
        // 简单验证：只包含数字、空格、括号和连字符
        for (char c : phone) {
            if (!isdigit(c) && c != ' ' && c != '(' && c != ')' && c != '-') {
                return false;
            }
        }
        return true;
    }

    // 验证邮箱格式
    static bool isValidEmail(const string& email) {
        if (email.empty()) return true; // 邮箱可选
        return email.find('@') != string::npos && email.find('.') != string::npos;
    }

};

class FamilyContact : public Contact {

private:
    string relationship;

public:
    FamilyContact(const string& n, const string& p, const string& e, const string& rel)
        : Contact(n, p, e, "家人"), relationship(rel) {}  // 派生类FamilyContact不能直接初始化基类的私有成员; 必须通过基类的构造函数来初始化

    void display() const override {
        cout << "👨‍👩‍👧 " << setw(15) << left << ("家人(" + relationship + ")") << " | "
             << setw(20) << name << " | "
             << setw(15) << phone << " | "
             << setw(25) << email << endl;
    }

    string toString() const override{
        return Contact::toString() + "|" + relationship;
    }
};


class ColleagueContact : public Contact{
private:
    string department;
    string position;

public:
    ColleagueContact(const string& n, const string& p, const string& e, const string& dept, const string& pos)
        : Contact(n, p, e, "同事"), department(dept), position(pos) {}
        
    void display() const override {
        cout << "💼 " << setw(15) << left << ("同事(" + department + ")") << " | "
             << setw(20) << name << " | "
             << setw(15) << phone << " | "
             << setw(25) << email << " | "
             << setw(15) << position << endl;
    }

    string toString() const override {
        return Contact::toString() + "|" + department + "|" + position;
    }
};

class FriendContact : public Contact {
private:
    string knownfrom;

public:
    FriendContact(const string&n, const string& p, const string& e, const string& from)
        : Contact(n, p, e, "朋友"), knownfrom(from) {}

    void display() const override {
        cout << "👥 " << setw(15) << left << ("朋友") << " | "
             << setw(20) << name << " | "
             << setw(15) << phone << " | "
             << setw(25) << email << " | "
             << setw(15) << knownfrom << endl;
    }

    string toString() const override {
        return Contact::toString() + "|" + knownfrom;
    }
};

// 联系人管理系统
class ContactManager {
private:
    vector<unique_ptr<Contact>> contacts;
    const string filename = "contact_data.txt";

    // 检查是否存在同名联系人
    bool contactExists(const string& name) {
        for (const auto& contact : contacts) {
            if (contact->getName() == name) {
                return true;
            }
        }
        return false;
    }

    // 字符串转换为小写（用于不区分大小写的搜索）
    string toLower(const string& str) const {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower); // ::的作用：使用全局命名空间中的tolower函数，避免与其他可能同名的函数冲突
        return lowerStr;
    }

public:
    ContactManager() {
        loadFromFile();
    }

    //从文件加载联系人
    void loadFromFile() {
        ifstream file(filename);  //输入文件流
        if (!file.is_open()) {
            cout << "📁 未找到联系人文件，创建新的通讯录..." << endl;
            return;
        }

        contacts.clear();
        string line;
        while (getline(file, line))
        {
            if (line.empty()) continue;

            stringstream ss(line);
            string token; //存储单个字段
            vector<string> tokens;  // 存储所有字段

            while (getline(ss, token, '|'))
            {
                tokens.push_back(token);
            }

            if (tokens.size() >=4) {
                string type = tokens[0];
                string name = tokens[1];
                string phone = tokens[2];
                string email = tokens[3];

                if (type == "家人" && tokens.size() >=5) {
                    contacts.push_back(make_unique<FamilyContact>(name, phone, email, tokens[4]));
                }
                else if (type == "同事" && tokens.size() >= 6) {
                    contacts.push_back(make_unique<ColleagueContact>(name, phone, email, tokens[4], tokens[5]));
                }
                else if (type == "朋友" && tokens.size() >= 5) {
                    contacts.push_back(make_unique<FriendContact>(name, phone, email, tokens[4]));
                }
                else {
                    // 普通联系人
                    contacts.push_back(make_unique<Contact>(name, phone, email, "普通"));
                }

            }
            
        }
        file.close();
        cout << "✅ 已加载 " << contacts.size() << " 个联系人" << endl;
        
    }
    // 保存联系人到文件
    void saveToFile() {
        ofstream file(filename);
        for (const auto& contact : contacts) {
            file << contact->toString() << "\n";
        }
        file.close();
    }

    // 添加联系人
    void addContact() {
        string name, phone, email, type;

        cout << "\n➕ 添加新联系人" << endl;
        cout << "请输入姓名: ";
        getline(cin, name);

        // 防止重复添加
        if (contactExists(name)) {
            cout << "❌ 已存在同名联系人！" << endl;
            return; 
        }

        cout << "请输入电话号码： ";
        getline(cin, phone);
        if (!Contact::isValidPhone(phone)) {
            cout << "❌ 电话号码格式无效！" << endl;
            return;
        }

        cout << "请输入邮箱（可选）： ";
        getline(cin, email);
        if (!email.empty() && !Contact::isValidEmail(email)) {
            cout << "❌ 邮箱格式无效！" << endl;
            return;
        }

        cout << "选择联系人类型 (1.普通 2.家人 3.同事 4.朋友): ";
        getline(cin, type);

        if (type == "2") {
            string relationship;
            cout << "请输入关系： ";
            getline(cin, relationship);
            contacts.push_back(make_unique<FamilyContact>(name, phone, email, relationship));
        
        }
        else if (type == "3")
        {
            string department, position;
            cout << "请输入部门： ";
            getline(cin, department);
            cout << "请输入职位： ";
            getline(cin, position);
            contacts.push_back(make_unique<ColleagueContact>(name, phone, email, department, position));

        }
        else if (type == "4") {
            string knownFrom;
            cout << "请输入认识途径: ";
            getline(cin, knownFrom);
            contacts.push_back(make_unique<FriendContact>(name, phone, email, knownFrom));
        }
        else {
            contacts.push_back(make_unique<Contact>(name, phone, email, "普通"));
        }

        saveToFile();
        cout << "✅ 联系人添加成功！" << endl;
    }

    // 显示所有联系人
    void diaplayAll() const {
        if (contacts.empty()) {
            cout << "📝 通讯录为空！" << endl;
            return;
        }
        cout << "\n📋 联系人列表 (" << contacts.size() << " 个):" << endl;
        cout << "====================================================================" << endl;
        for (const auto& contact : contacts) {
            contact->display();
        }
        cout << "====================================================================" << endl;
        
    }


};