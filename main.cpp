#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype> // Added to ensure isdigit() works
#include "Types.hpp"
#include <cctype> 

#include "RegistrationQueue.hpp"
#include "ActivityStack.hpp"
#include "ActivityLog.hpp"
#include "RiskAnalysis.hpp" 


using namespace std;

bool isValidIDFormat(string id) {
    // 1. Check if it's exactly 7 characters long
    if (id.length() != 7) {
        return false;
    }
    
    // 2. Check if it starts with 'T' and 'P' (Case-insensitive)
    if (toupper(id[0]) != 'T' || toupper(id[1]) != 'P') {
        return false;
    }

    // 3. Check if the remaining 5 characters are numbers
    for (int i = 2; i < 7; i++) {
        if (!isdigit(id[i])) {
            return false; // Found a letter where a number should be!
        }
    }

    return true; 
}

void loadLearnerFromCSV(string filename,RegistrationQueue& queue){
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

int main() {
    RegistrationQueue systemQueue(100);
    Task2Manager systemActivity;
    ActivityLog systemLog;
    RiskAnalysis systemRisk;

    loadLearnerFromCSV("Learner.csv",systemQueue);

    int choice;

    do{
        cout<<"\n======================================\n";
        cout<<"       PLAPS Session Manager Menu       \n";
        cout<<"======================================\n";
        cout<<"1. Register New User to Waitlist\n";
        cout<<"2. Admit User to active session\n";
        cout<<"3. Remove user from Active Session\n";
        cout<<"4. Display Waitlist & Active Session\n";
        cout<<"5. Start Activity\n";
        cout<<"6. View All Activity Logs\n"; 
        cout<<"7. Filter Logs by Student ID \n"; 
        cout<<"8. Manually Export to CSV\n";
        cout<<"9. Run Risk analysis and show priority\n";
        cout<<"10. Export Risk Report\n";
        cout<<"11. View Exported Risk Report\n";
        cout<<"12. Exit System\n";


        cout<<"Enter choose: ";
        cin>>choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n'); 
            cout << "\n[System Error] Invalid input! Please enter a number.\n";
            continue;
        }
        
        cin.ignore(10000,'\n');

        switch (choice){
            case 1:{
                string newId,newName;
                cout<<"\n--- Register New Learner ---\n";
                cout<<"Enter Learner ID (e.g., TP12345): ";
                getline(cin,newId);

                if(!isValidIDFormat(newId)){
                    cout<<"Error!! Ivalid Format! ID must start from TP then 5 digits.";
                    break;
                }

                newId[0]=toupper(newId[0]);
                newId[1]=toupper(newId[1]);

                if(systemQueue.isLearnerExist(newId)){
                    cout<<"Error!! Learner ID"<<newId<<"already exists.";
                    break;
                }

                cout<<"Enter Leaner Name: ";
                getline(cin,newName);

                Learner manualStudent={newId,newName,0.0,0,0.0,0.0,""};
                systemQueue.enqueue(manualStudent);
                break;
            }

            case 2:{
                cout<<"\n--- Admitting Learner ---\n";
                systemQueue.admitToSession();
                break;
            }
            case 3:{
                string removeID;
                cout<<"\n --- Remove Active Learner ---\n";
                systemQueue.displayActiveSession();
                cout<<"Enter ID that you want to remove: ";
                getline(cin,removeID);
                systemQueue.exitSession(removeID);
                break;
            }
            case 4:{
                systemQueue.displayWaitlist();
                systemQueue.displayActiveSession();
                break;
            }
            case 5:{
                systemQueue.displayActiveSession(); 
                if (systemQueue.activeCount > 0) {
                    int choose;
                    cout << "\nEnter the student index (1, 2, 3...) to start: ";
                    cin >> choose;
                    systemActivity.selectStudent(choose, systemQueue, systemLog);
                }
                break;
            }
            case 12:{
                cout<<"Existing system.ByeBye!\n";
                break;
            }
            // 在 main.cpp 的 switch 语句里增加 case 7 和 8
            case 6: {
                systemLog.displayAll(); // 显示所有
                break;
            }
            case 7: {
                string sID;
                cout << "Enter Student ID to filter: ";
                getline(cin, sID);
                systemLog.filterByLearner(sID); // 筛选显示
                break;
            }
            case 8: {
                systemLog.exportToCSV();
                cout << "[System] Manual export successful!\n";
                break;
            }
            case 9:{
                systemRisk.runAnalysis();
                systemRisk.displayHighRisk();
                break;
            }
            case 10:{
                systemRisk.exportAnalysis();
                break;
            }
            case 11:{
                systemRisk.viewExportedReport();
                break;
            }
            default:
                cout<<"Invalid choice.Please choose within 1-12";
                break;
        }

    } while(choice!=12);

    return 0;

}