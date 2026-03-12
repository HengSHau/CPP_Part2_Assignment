#ifndef ACTIVITYLOG_HPP
#define ACTIVITYLOG_HPP

#include "Types.hpp"
#include <iostream>
#include <fstream>

class ActivityLog {
private:
    Activity logs[6]; // 循环队列大小为 6，达到 6 条后会自动覆盖第一条
    int head;         // 队列头部索引
    int count;        // 当前存储的日志条数

public:
    ActivityLog();
    void addLog(Activity newAct); // 添加日志的核心逻辑
    void displayAll();           // 打印所有日志到屏幕
    void exportToCSV();          // 导出到 CSV 文件
    void filterByLearner(std::string searchID);
};

#endif