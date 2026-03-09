#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype> // Added to ensure isdigit() works
#include "Types.hpp"
#include "RegistrationQueue.hpp"
#include "ActivityStack.hpp"
#include "ActivityLog.hpp"
#include "RiskAnalysis.hpp"

using namespace std;

void loadLearnerFromCSV(string filename, RegistrationQueue& queue)
{
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error!! Could Not open file" << filename << endl;
        return;
    }

    cout << "Reading data from " << filename << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name;

        getline(ss, id, ',');
        getline(ss, name, ',');

        Learner newStudent = {id, name, 0.0, 0, 0.0, 0.0, ""};
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
    RiskAnalysis riskanalysis;

    loadLearnerFromCSV("Learner.csv", systemQueue);
    
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
    do {
        cout << endl;
        cout << "=================================================\n";
        cout << "                  PLAPS Prototype                \n";
        cout << "=================================================\n";
        cout << "1. Add Student\n2. Go Back (Undo)\n3. View Current Progress\n4. Exit Session\n5. View Task 3 Logs\n6. Export Task 3 CSV \n7. View Risk analysis: \n8. Export Risk Analysis\n 9. Choice:";
        
        if (!(cin >> choice)) { 
            cout << "[Error] Please enter a valid numeric value.\n";
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            continue;
        }

        if (choice == 1)
        {
            string LearnerID;
            bool validID = false;

            // 1. Ask and validate the ID here in main
            while (!validID)
            {
                cout << "\nEnter Student ID (e.g. TP082318): ";
                cin >> LearnerID;

                if (LearnerID.length() == 8 && LearnerID.substr(0, 2) == "TP") {
                    bool AllDigit = true;
                    bool AllSame = true; 
                    
                    for (int i = 2; i < 8; i++) {
                        if (!isdigit(LearnerID[i])) { 
                            AllDigit = false; 
                            break; 
                        }
                        if (LearnerID[i] != LearnerID[2]) { 
                            AllSame = false; 
                        }
                    }
                    
                    if (AllDigit && !AllSame) { 
                        validID = true; 
                    } else if (AllDigit && AllSame) { 
                        cout << "ID cannot be 6 same numbers.\n"; 
                    } else { 
                        cout << "The last 6 characters must be numbers.\n"; 
                    }
                } else {
                    cout << "Must start with 'TP' and be 8 characters.\n";
                }
            }

            // 2. Pass parameters to the Stack
            activityStack.selectionFlow(choice, LearnerID);

            // 3. Log it to Task 3
            Activity newLog = activityStack.peek(); 
            newLog.learnerID = LearnerID; 
            myActivityLog.addLog(newLog);

            cout << "[System] Activity recorded for " << LearnerID << ".\n"; 
        }
        else if (choice == 2 || choice == 3)
        {
            activityStack.selectionFlow(choice, "");
        }    
        else if (choice == 4)
        {
            cout << "[System] Exiting Task 2 Test...\n";
        }
        else if (choice == 5) 
        {
            myActivityLog.displayAll();
        }
        else if (choice == 6)
        {
            myActivityLog.exportToCSV();
        }

        else if (choice == 7)
        {
            riskanalysis.runAnalysis(myActivityLog);
        }

        else if (choice == 8){
            riskanalysis.exportAnalysis();
        }
        
        else
        {
            cout << "Please enter the number from 1 to 8.\n";
        }
        
    } while (choice != 4);
    
    return 0;

}