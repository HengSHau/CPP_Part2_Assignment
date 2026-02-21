#include <iostream>
#include "Types.hpp"
#include "RegistrationQueue.hpp"
#include "ActivityStack.hpp"

using namespace std;

int main() {
    cout << "=================================================\n";
    cout << "   PLAPS Prototype - Task 1 & 2 Testing          \n";
    cout << "=================================================\n\n";

    // ==========================================
    // TASK 1: LEARNER REGISTRATION (QUEUE)
    // ==========================================
    RegistrationQueue waitlist(50); // Max capacity of 50

    // 1. Generate Dummy Students
    Learner s1 = {"TP01001", "Ali Bin Ahmad", 0.0, 0, 0.0, 0.0, ""};
    Learner s2 = {"TP01002", "Chong Wei Jie", 0.0, 0, 0.0, 0.0, ""};

    cout << "--- Students Arriving at System ---\n";
    waitlist.enqueue(s1);
    waitlist.enqueue(s2);
    waitlist.displayQueue();

    // 2. Admit a student into the session (Dequeue)
    cout << "\n--- Admitting Student to Session ---\n";
    Learner activeLearner = waitlist.dequeue(); 
    
    // Check who is left in the queue
    waitlist.displayQueue();

    // ==========================================
    // TASK 2: ACTIVITY NAVIGATION (STACK)
    // ==========================================
    cout << "\n--- " << activeLearner.name << " Starts Learning Session ---\n";
    
    // Create a Stack specifically for the active learner's session
    ActivityStack sessionStack; 

    // 3. Create dummy activities
    // Format: {ActivityID, Topic, Difficulty, Score}
    Activity act1 = {"A01", "Introduction to Variables", "Easy", 100.0};
    Activity act2 = {"A02", "If-Else Conditions", "Medium", 85.0};
    Activity act3 = {"A03", "Nested For Loops", "Hard", 40.0}; // Student struggles here

    // 4. Student moves forward through activities (Push)
    sessionStack.push(act1);
    sessionStack.push(act2);
    sessionStack.push(act3);

    // Show current sequence
    sessionStack.displayStack();

    // 5. Student uses the "Undo/Go Back" feature (Pop)
    cout << "\n--- Learner clicks 'Go Back' to retry a topic ---\n";
    Activity undoneActivity = sessionStack.pop(); 

    // Show the sequence again to confirm the top activity was removed
    sessionStack.displayStack();

    cout << "\n[System] Test complete. Exiting program...\n";
    return 0; // Destructors will run automatically here to clean up memory!
}