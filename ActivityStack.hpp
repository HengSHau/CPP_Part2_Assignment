#ifndef ACTIVITYSTACK_HPP
#define ACTIVITYSTACK_HPP

#include <iostream>
#include <string>
#include "RegistrationQueue.hpp" // 必须包含 Task 1 的头文件以识别 Learner 和 RegistrationQueue

using namespace std;

// 题目结构体
struct Question {
    string content;
    string answer;
};

// 栈节点：用于实现后退 (Backtracking)
struct StackNode {
    int questionIndex;
    StackNode* next;
};

// 手动实现栈，严禁使用 STL <stack>
class ActivityStack {
private:
    StackNode* top;
public:
    ActivityStack();
    ~ActivityStack();
    void push(int index);
    int pop();
    bool isEmpty();
};

// Task 2 管理类
class Task2Manager {
private:
    Question questions[3][3]; // [难度][题目]
    ActivityStack history;    // 记录答题历史路径

public:
    Task2Manager();

    // 核心：显示并选择学生
    void selectStudent(int choose, RegistrationQueue& regQueue);

    // 开始会话
    bool startSession(string studentID, string studentName, RegistrationQueue& regQueue);

    // 运行题目逻辑
    bool runActivity(int diff, string id, string name);

    // 完成后的清理和数据记录
    void completeSession(string id, string name, int diff, int score);
};

#endif