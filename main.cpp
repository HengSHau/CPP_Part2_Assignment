#include <iostream>
#include "Types.hpp"
#include "RegistrationQueue.hpp"

using namespace std;

int main() {
    cout << "=================================================\n";
    cout << "   PLAPS Prototype - Task 1 Full Test            \n";
    cout << "=================================================\n\n";

    RegistrationQueue systemQueue(50); // Set waitlist max capacity to 50

    // 1. Create Dummy Learners
    Learner s1 = {"TP01001", "Ali Bin Ahmad", 0.0, 0, 0.0, 0.0, ""};
    Learner s2 = {"TP01002", "Chong Wei Jie", 0.0, 0, 0.0, 0.0, ""};
    Learner s3 = {"TP01003", "Sita Muthu", 0.0, 0, 0.0, 0.0, ""};
    Learner s4 = {"TP01004", "John Doe", 0.0, 0, 0.0, 0.0, ""};
    Learner s5 = {"TP01005", "Jane Smith", 0.0, 0, 0.0, 0.0, ""};
    Learner s6 = {"TP01006", "David Lee", 0.0, 0, 0.0, 0.0, ""};
    Learner s7 = {"TP01007", "Sarah Tan", 0.0, 0, 0.0, 0.0, ""};

    // 2. Register Everyone (They all go to the Waitlist first)
    cout << "--- Phase 1: Students Arriving ---\n";
    systemQueue.enqueue(s1);
    systemQueue.enqueue(s2);
    systemQueue.enqueue(s3);
    systemQueue.enqueue(s4);
    systemQueue.enqueue(s5);
    systemQueue.enqueue(s6);
    systemQueue.enqueue(s7);
    
    systemQueue.displayWaitlist();

    // 3. Admit Students to the Active Lab (Capacity is 5)
    cout << "\n--- Phase 2: Opening the Lab (5 Computers) ---\n";
    systemQueue.admitToSession(); // Admits Ali
    systemQueue.admitToSession(); // Admits Chong
    systemQueue.admitToSession(); // Admits Sita
    systemQueue.admitToSession(); // Admits John
    systemQueue.admitToSession(); // Admits Jane
    
    // This 6th attempt should trigger your "FULL" warning!
    cout << "\n[Attempting to admit 6th student...]\n";
    systemQueue.admitToSession(); 

    // 4. Show the current state of both lists
    systemQueue.displayActiveSession(); // Should have 5 students
    systemQueue.displayWaitlist();      // Should have 2 left (David and Sarah)

    // 5. Simulate a student finishing and leaving the lab
    cout << "\n--- Phase 3: Student Completes Session ---\n";
    systemQueue.exitSession("TP01002"); // Chong Wei Jie finishes and leaves

    systemQueue.displayActiveSession(); // Should now only have 4 students

    // 6. Admit the next student from the Waitlist into the empty slot
    cout << "\n--- Phase 4: Admitting Next Student ---\n";
    systemQueue.admitToSession(); // Admits David

    systemQueue.displayActiveSession(); // Full again (5 students)
    systemQueue.displayWaitlist();      // Only Sarah Tan left waiting

    cout << "\n[System] Task 1 Final Test Complete! Exiting...\n";
    return 0; // Destructor will safely clean up Sarah from the waitlist
}