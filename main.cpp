#include <iostream>
#include <fstream>
#include <sstream>
#include "Types.hpp"
#include "RegistrationQueue.hpp"


using namespace std;

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
    cout << "=================================================\n";
    cout << "   PLAPS Prototype - Task 1 Full Test            \n";
    cout << "=================================================\n\n";

    RegistrationQueue systemQueue(100); // Set waitlist max capacity to 50

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

    return 0;

}