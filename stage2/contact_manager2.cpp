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
};