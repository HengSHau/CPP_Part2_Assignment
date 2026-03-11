// RegistrationQueue.hpp
#ifndef REGISTRATIONQUEUE_HPP
#define REGISTRATIONQUEUE_HPP

#include "Types.hpp"
#include <string> 

using namespace std; // Added exactly as you requested!

// The Node for our Linked List Queue
struct QueueNode {
    Learner data;
    QueueNode* next;
};

class RegistrationQueue {
private:
    QueueNode* front; // Points to the first person in line
    QueueNode* rear;  // Points to the last person in line
    int currentSize;
    int maxCapacity;  
   
public:
    Learner activeSession[5];
    int activeCount;
    // Constructor & Destructor
    RegistrationQueue(int capacity = 50);
    ~RegistrationQueue();

    // Core Queue Functions
    bool isWaitlistEmpty();
    bool isWaitlistFull();
    bool isActiveSessionFull();

    void enqueue(Learner l); 
    void admitToSession();
    void exitSession(string learnerID); // Now it's just 'string'

    void displayWaitlist();
    void displayActiveSession();

    bool isLearnerExist(string learnerID);
};

#endif