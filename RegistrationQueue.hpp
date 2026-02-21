// RegistrationQueue.hpp
#ifndef REGISTRATIONQUEUE_HPP
#define REGISTRATIONQUEUE_HPP

#include "Types.hpp"

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
    // Constructor & Destructor
    RegistrationQueue(int capacity = 50);
    ~RegistrationQueue();

    // Core Queue Functions
    bool isEmpty();
    bool isFull();
    void enqueue(Learner l); // Add to back
    Learner dequeue();       // Remove from front
    void displayQueue();     // Show all waiting learners
};

#endif