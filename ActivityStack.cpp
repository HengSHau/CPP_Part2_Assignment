#include "ActivityStack.hpp"

// --- ActivityStack 实现 (保持不变) ---
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

    // Hard 题目
    questions[2][0] = {"The answer of 2 7 + 3 / 4 -", "-1"};
    questions[2][1] = {"Maximum children of binary tree", "2"};
    questions[2][2] = {"Which data structure allows insertion/deletion at both ends?", "deque"};
}

// 修正点 1: 增加 ActivityLog& task3 参数
void Task2Manager::selectStudent(int choose, RegistrationQueue& regQueue, ActivityLog& task3) {
    if (regQueue.activeCount == 0) {
        cout << "[System] No learners in active session!\n";
        return;
    }
    if (choose < 1 || choose > regQueue.activeCount) {
        cout << "[Error] Invalid index!\n";
        return;
    }

    Learner selected = regQueue.activeSession[choose - 1];
    
    // 修正点 2: 传递 task3 给 startSession
    if (startSession(selected.learnerID, selected.name, regQueue, task3)) {
        regQueue.exitSession(selected.learnerID);
    } else {
        cout << "[System] Activity cancelled. Learner remains in active list.\n";
    }
}

// 修正点 3: 增加 ActivityLog& task3 参数
bool Task2Manager::startSession(string studentID, string studentName, RegistrationQueue& regQueue, ActivityLog& task3) {
    while (true) { 
        int difficulty = -1;
        cout << "\n--- Select Difficulty for " << studentName << " ---" << endl;
        cout << "(0: Easy, 1: Medium, 2: Hard, -1: Back to Main Menu): ";
        cin >> difficulty;

        if (difficulty == -1) return false;

        if (difficulty >= 0 && difficulty <= 2) {
            // 修正点 4: 传递 task3 给 runActivity
            if (runActivity(difficulty, studentID, studentName, task3)) {
                return true; 
            }
        }
    }
}

// 修正点 5: 增加 ActivityLog& task3 参数
bool Task2Manager::runActivity(int diff, string id, string name, ActivityLog& task3) {
    int currentIndex = 0;
    int score = 0;
    int questionScores[3] = {0, 0, 0}; 
    string input;

    while (!history.isEmpty()) history.pop();

    while (currentIndex < 3) {
        cout << "\n[Question " << currentIndex + 1 << "]: " << questions[diff][currentIndex].content << endl;
        cout << "Current Score: " << score << endl;
        cout << "Your Answer (or 'Q' to go back): ";
        cin >> input;

        if (input == "Q" || input == "q") {
            if (currentIndex == 0) {
                return false; 
            } else {
                currentIndex = history.pop(); 
                score -= questionScores[currentIndex]; 
                questionScores[currentIndex] = 0; 
                cout << "[System] Back to previous question. Score adjusted." << endl;
                continue;
            }
        }

        if (input == questions[diff][currentIndex].answer) {
            questionScores[currentIndex] = 10; 
            score += 10;
            cout << ">> Correct!" << endl;
        } else {
            questionScores[currentIndex] = 0; 
            cout << ">> Wrong answer." << endl;
        }

        history.push(currentIndex);
        currentIndex++;
    }

    // 修正点 6: 传递 task3 给 completeSession
    completeSession(id, name, diff, score, task3);
    return true; 
}

// 修正点 7: 这里的逻辑已经帮你整合好了
void Task2Manager::completeSession(string id, string name, int diff, int score, ActivityLog& task3) {
    string dStr = (diff == 0) ? "Easy" : (diff == 1) ? "Medium" : "Hard";
    
    cout << "\n======================================" << endl;
    cout << "          ACTIVITY COMPLETED!         " << endl;
    cout << "======================================" << endl;
    cout << "Student: " << name << " (" << id << ")" << endl;
    cout << "Difficulty: " << dStr << endl;
    cout << "Final Score: " << score << "/30" << endl;
    cout << "======================================" << endl;
    
    cout << "\nPress Enter to return to Main Menu...";
    cin.ignore(); 
    cin.get();    

    // --- 自动存入 Task 3 ---
    Activity newRecord;
    newRecord.learnerID = id;
    newRecord.topic = "General Programming"; 
    newRecord.difficulty = dStr; // 记录难度
    newRecord.score = (float)score;
    
    task3.addLog(newRecord); // 这会自动触发 exportToCSV
}