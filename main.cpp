#include <iostream>
#include <fstream>
#include <sstream>
#include "Types.hpp"
#include <cctype> 

#include "RegistrationQueue.hpp"


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

int main() {
    RegistrationQueue systemQueue(100);

    loadLearnerFromCSV("Learner.csv",systemQueue);

    int choice;

    do{
        cout<<"\n======================================\n";
        cout<<"       PLAPS Session Manager Menu       \n";
        cout<<"\n======================================\n";
        cout<<"1. Register New User to Waitlist\n";
        cout<<"2. Admit User to active session\n";
        cout<<"3. Remove user from Active Session\n";
        cout<<"4. Display Waitlist & Active Session\n";
        cout<<"5. Exit System \n";

        cout<<"Enter choose: ";
        cin>>choice;
        cin.ignore();

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
                cout<<"Existing system.ByeBye!\n";
                break;
            }
            default:
                cout<<"Invalid choice.Please choose within 1-5";

        }

    } while(choice!=5);

    return 0;

}