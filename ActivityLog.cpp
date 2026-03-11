#include "ActivityLog.hpp"
#include <iomanip>

using namespace std;

ActivityLog::ActivityLog() : head(0), count(0) {}

void ActivityLog::addLog(Activity newAct) {
    int nextIndex = (head + count) % 6;
    logs[nextIndex] = newAct;

    if (count < 6) {
        count++;
    } else {
        head = (head + 1) % 6;
    }
    cout << "[Task 3] Log added successfully to circular queue.\n";
    
    // 自动保存：确保每次加完日志都更新 CSV
    exportToCSV(); 
}

void ActivityLog::filterByLearner(string searchID) {
    bool found = false;
    cout << "\n--- Filtering Logs for: " << searchID << " ---\n";
    
    for (int i = 0; i < count; i++) {
        int index = (head + i) % 6;
        if (logs[index].learnerID == searchID) {
            // 修正：确保这里打印了 difficulty
            cout << "- Topic: " << logs[index].topic 
                 << " | Difficulty: " << logs[index].difficulty
                 << " | Score: " << logs[index].score << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "[System] No logs found for this student.\n";
    }
}

void ActivityLog::displayAll() {
    cout << "\n--- TASK 3 ACTIVITY LOGS (Circular Queue) ---\n";
    if (count == 0) {
        cout << "No logs available.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        int index = (head + i) % 6;
        // 修正：去掉了重复的 topic，确保 Diff 显示出来
        cout << i + 1 << ". [" << logs[index].learnerID << "] Topic: " 
             << logs[index].topic << " | Diff: " << logs[index].difficulty
             << " | Score: " << logs[index].score << "\n";
    }
}

void ActivityLog::exportToCSV() {
    ofstream file("ActivityHistory.csv");
    if (!file.is_open()) return;

    // 修正点 1：表头必须增加 Difficulty 这一列，否则数据会对不齐
    file << "ID,Topic,Difficulty,Score\n"; 
    
    for (int i = 0; i < count; i++) {
        int index = (head + i) % 6;
        // 修正点 2：确保逗号数量和表头一致
        file << logs[index].learnerID << "," 
             << logs[index].topic << "," 
             << logs[index].difficulty << "," 
             << logs[index].score << "\n";
    }
    file.close();
    cout << "[System] Logs exported to ActivityHistory.csv\n";
}