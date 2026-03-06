#ifndef ACTIVITYLOG_HPP
#define ACTIVITYLOG_HPP

#include "Types.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ActivityLog {
    public:
    Activity logs [5];
    int nextIndex;
    int currentTotal;

    ActivityLog() {
        nextIndex = 0;
        currentTotal = 0;
    }

void addLog (Activity data) {
    logs [nextIndex] = data;

    nextIndex = nextIndex+1;

    if (nextIndex==5) {
        nextIndex = 0;
    }

    if (currentTotal<5) {
        currentTotal = currentTotal+1;
    }
}

void displayAll() {
    cout << "\n---RECENT ACTIVITY LOGS (Task 3)---" << endl;
    if (currentTotal==0){
        cout << "No logs recorded yet."<< endl;
        return;
    }

    for(int i = 0; i< currentTotal; i++) {
        cout <<"["<< i + 1 <<"] Student: "<< logs[i].learnerID
        << " | Topic:" << logs[i].topic
        << " | Score:" << logs[i].score << endl;
    }
}

void exportToCSV(){
    ofstream myFile("ActivityHistory.csv");
    myFile << "LearnerID, Topic, Dicfficulty, Score" << endl;

    for (int i = 0 ; i < currentTotal; i++) {
        myFile << logs[i].learnerID <<","
               << logs[i].topic<< ","
               << logs[i].difficulty<<","
               << logs[i].score<< endl;
    }
    myFile.close();
    cout << "[System] History exported to 'ActivityHistory.csv'!"<< endl;
    }   
};

#endif