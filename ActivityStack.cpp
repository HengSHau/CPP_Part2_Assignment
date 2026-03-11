#include "ActivityStack.hpp"

// --- ActivityStack 实现 ---
ActivityStack::ActivityStack() : top(nullptr) {}

ActivityStack::~ActivityStack() {
    while (!isEmpty()) pop();
}

void ActivityStack::push(int index) {
    StackNode* newNode = new StackNode{index, top};
    top = newNode;
}

int ActivityStack::pop() {
    if (isEmpty()) return -1;
    StackNode* temp = top;
    int index = temp->questionIndex;
    top = top->next;
    delete temp;
    return index;
}

bool ActivityStack::isEmpty() {
    return top == nullptr;
}

// --- Task2Manager 实现 ---
Task2Manager::Task2Manager() {
    // Easy 题目
    questions[0][0] = {"What is the output of the x?\nx = '1' + '1' ", "11"};
    questions[0][1] = {"C++ keyword for integer?", "int"};
    questions[0][2] = {"Is 'cout' for output? (yes/no)", "yes"};

    // Medium 题目
    questions[1][0] = {"Which principle does a Stack follow? (FIFO/LIFO)", "LIFO"};
    questions[1][1] = {"In a switch-case, which keyword runs if no cases match?", "default"};
    questions[1][2] = {"Which keyword is used to deallocate memory allocated with 'new'?", "delete"};

    questions[2][0] = {"The answer of 2 7 + 3 / 4 -", "-1"};
    questions[2][1] = {"Maximum children of binary tree", "2"};
    questions[2][2] = {"Which data structure allows insertion/deletion at both ends?", "deque"};

}

void Task2Manager::selectStudent(int choose, RegistrationQueue& regQueue) {
    if (regQueue.activeCount == 0) {
        cout << "[System] No learners in active session!\n";
        return;
    }
    if (choose < 1 || choose > regQueue.activeCount) {
        cout << "[Error] Invalid index!\n";
        return;
    }

    Learner selected = regQueue.activeSession[choose - 1];
    
    // 修改：只有当 startSession 返回 true (表示真正完成) 时，才移出列表
    if (startSession(selected.learnerID, selected.name, regQueue)) {
        regQueue.exitSession(selected.learnerID);
    } else {
        cout << "[System] Activity cancelled. Learner remains in active list.\n";
    }
}

bool Task2Manager::startSession(string studentID, string studentName, RegistrationQueue& regQueue) {
    while (true) { // 使用循环，方便从题目退回后重新选择难度
        int difficulty = -1;
        cout << "\n--- Select Difficulty for " << studentName << " ---" << endl;
        cout << "(0: Easy, 1: Medium, 2: Hard, -1: Back to Main Menu): ";
        cin >> difficulty;

        if (difficulty == -1) return false; // 返回 false，不移出 active list

        if (difficulty >= 0 && difficulty <= 2) {
            // 如果 runActivity 返回 true，说明做完了
            if (runActivity(difficulty, studentID, studentName)) {
                return true; 
            }
            // 如果 runActivity 返回 false (第一题按Q)，则继续 while 循环重新选难度
        }
    }
}

bool Task2Manager::runActivity(int diff, string id, string name) {
    int currentIndex = 0;
    int score = 0;
    int questionScores[3] = {0, 0, 0}; // 新增：记录每一题拿到的分数
    string input;

    while (!history.isEmpty()) history.pop();

    while (currentIndex < 3) {
        cout << "\n[Question " << currentIndex + 1 << "]: " << questions[diff][currentIndex].content << endl;
        cout << "Current Score: " << score << endl;
        cout << "Your Answer (or 'Q' to go back): ";
        cin >> input;

        if (input == "Q" || input == "q") {
            if (currentIndex == 0) {
                return false; // 第一题按Q，返回 false 回到难度选择
            } else {
                currentIndex = history.pop(); 
                // 修复刷分：回退时，扣除那一题之前加上的分数
                score -= questionScores[currentIndex]; 
                questionScores[currentIndex] = 0; // 重置该题分数记录
                cout << "[System] Back to previous question. Score adjusted." << endl;
                continue;
            }
        }

        if (input == questions[diff][currentIndex].answer) {
            questionScores[currentIndex] = 10; // 记录这题拿了10分
            score += 10;
            cout << ">> Correct!" << endl;
        } else {
            questionScores[currentIndex] = 0; // 没拿分
            cout << ">> Wrong answer." << endl;
        }

        history.push(currentIndex);
        currentIndex++;
    }

    completeSession(id, name, diff, score);
    return true; // 真正完成三道题，返回 true
}

void Task2Manager::completeSession(string id, string name, int diff, int score) {
   string dStr = (diff == 0) ? "Easy" : (diff == 1) ? "Medium" : "Hard";
    
    cout << "\n======================================" << endl;
    cout << "          ACTIVITY COMPLETED!         " << endl;
    cout << "======================================" << endl;
    cout << "Student: " << name << " (" << id << ")" << endl;
    cout << "Difficulty: " << dStr << endl;
    cout << "Final Score: " << score << "/30" << endl;
    cout << "======================================" << endl;
    
    cout << "\nPress Enter to return to Main Menu...";
    cin.ignore(); // 清除之前的回车
    cin.get();    // 等待用户按键
}