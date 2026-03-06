#include <iostream>
#include <fstream>
#include <sstream>
#include "Types.hpp"
#include "RegistrationQueue.hpp"
#include "ActivityStack.hpp"
#include "ActivityLog.hpp"

using namespace std;

void loadLearnerFromCSV(string filename,RegistrationQueue& queue)
{
    ifstream file(filename);
    string line;

    if(!file.is_open()){
        cout<<"Error!! Could Not open file"<<filename<<endl;
        return;
    }

    cout<<"Reading data from "<<filename<<endl;

    while(getline(file,line)){
        stringstream ss(line);
        string id,name;

        getline(ss,id,',');
        getline(ss,name,',');

        Learner newStudent={id,name,0.0,0,0.0,0.0,""};
        queue.enqueue(newStudent);
    }
    file.close();
}

int main() 
{
    cout << "=================================================\n";
    cout << "   PLAPS Prototype - Task 1 Full Test            \n";
    cout << "=================================================\n\n";

    RegistrationQueue systemQueue(100); // Set waitlist max capacity to 50
    ActivityStack activityStack;
    ActivityLog myActivityLog;

    loadLearnerFromCSV("Learner.csv",systemQueue);
    
    systemQueue.displayWaitlist();

    // 3. Admit Students to the Active Lab (Capacity is 5)
    cout << "\n--- Phase 2: Opening the Lab (5 Computers) ---\n";
    systemQueue.admitToSession();
    systemQueue.admitToSession(); 
    systemQueue.admitToSession(); 
    systemQueue.admitToSession(); 
    systemQueue.admitToSession(); 
    
    // This 6th attempt should trigger your "FULL" warning!
    cout << "\n[Attempting to admit 6th student...]\n";
    systemQueue.admitToSession(); 

    // 4. Show the current state of both lists
    systemQueue.displayActiveSession(); // Should have 5 students
    systemQueue.displayWaitlist();      // Should have 2 left (David and Sarah)

    int choice;
    do{
        cout << endl;
        cout << "=================================================\n";
        cout << "   PLAPS Prototype - Task 2 Full Test            \n";
        cout << "=================================================\n";
        cout << "1. Next Activity\n2. Go Back (Undo)\n3. View Current Progress\n4. Exit Session\n5. View Task 3 Logs\n6. Export Task 3 CSV\nChoice: ";
        
        if (!(cin >> choice)) { // 检查输入是否为数字 
            cout << "[Error] Please enter a valid numeric value.\n";
            cin.clear(); // 清除错误状态 
            cin.ignore(1000, '\n'); // 丢弃缓冲区中的错误字符 
            continue;
        }
        if (choice == 1 )
        {
            string currentID="TP001001";
            cout << "[System] Auto-linked to Active Learner: " << currentID << endl;
    
            activityStack.selectionFlow(choice);

            Activity newLog = activityStack.peek(); 
            newLog.learnerID = currentID; 
    
            myActivityLog.addLog(newLog);

             cout << "[System] Activity recorded for " << currentID << ".\n"; 
        }
        else if (choice == 2 || choice == 3)\
        {
            activityStack.selectionFlow(choice);
        }    
        else if(choice == 4){
            cout << "[System] Exiting Task 2 Test...\n";
        }
        else if (choice == 5) {
            myActivityLog.displayAll();
        }
        else if (choice == 6){
            myActivityLog.exportToCSV();
        }
        else{
            cout << "Please enter the number from 1 to 6.\n";
        }
        
    }while(choice != 4);
    
    return 0;

}