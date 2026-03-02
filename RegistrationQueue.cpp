#include "RegistrationQueue.hpp"
#include <iostream>

using namespace std;

// ==========================================
// Constructor & Destructor
// ==========================================
RegistrationQueue::RegistrationQueue(int capacity) {
    front = nullptr;
    rear = nullptr;
    currentSize = 0;
    maxCapacity = capacity;
    activeCount = 0; // Starts with 0 students in the active lab
}

RegistrationQueue::~RegistrationQueue() {
    // Prevent memory leaks by deleting any remaining nodes in the waitlist
    while (!isWaitlistEmpty()) {
        QueueNode* temp = front;
        front = front->next;
        delete temp;
    }
}

// ==========================================
// Limit Checkers
// ==========================================
bool RegistrationQueue::isWaitlistEmpty() {
    return front == nullptr;
}

bool RegistrationQueue::isWaitlistFull() {
    return currentSize >= maxCapacity;
}

bool RegistrationQueue::isActiveSessionFull() {
    return activeCount >= 5; // We set the lab capacity to 5
}

// ==========================================
// Core Session Functions
// ==========================================

// 1. Join waiting line
void RegistrationQueue::enqueue(Learner l) {
    if (isWaitlistFull()) {
        cout << "[System] Waitlist is FULL (" << maxCapacity << "). Cannot register: " << l.name << "\n";
        return;
    }

    QueueNode* newNode = new QueueNode;
    newNode->data = l;
    newNode->next = nullptr;

    if (isWaitlistEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    currentSize++;
    cout << "[System] " << l.name << " registered successfully. (Waitlist: " << currentSize << ")\n";
}

// 2. Move from Waitlist -> Active Session Array
void RegistrationQueue::admitToSession() {
    if (isWaitlistEmpty()) {
        cout << "[System] No learners waiting in the queue.\n";
        return;
    }
    if (isActiveSessionFull()) {
        cout << "[System] Active session is FULL (5/5). Someone must exit first.\n";
        return;
    }

    // 1st Step: Safely remove from the Linked List
    QueueNode* temp = front;
    Learner admittedLearner = temp->data;

    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete temp; // Free memory!
    currentSize--;

    // 2nd Step: Put them into the Active Session Array
    activeSession[activeCount] = admittedLearner;
    activeCount++;

    cout << "[System] SUCCESS: " << admittedLearner.name << " has entered the active session!\n";
}

void RegistrationQueue::exitSession(string learnerID){
    bool found=false;

    for(int i=0;i<activeCount;i++){
        if(activeSession[i].learnerID==learnerID){
            cout<<"[System] " << activeSession[i].name << " finished and exited the session.\n";

            for(int j=i;j<activeCount-1;j++){
                activeSession[j]=activeSession[j+1];
            }
            activeCount--;
            found=true;
            break;
        }
    }

    if(!found){
        cout << "[System] Error: Learner ID '" << learnerID << "' not found in active session.\n";
    }
}

void RegistrationQueue::displayWaitlist() {
    cout << "\n--- WAITING LIST (" << currentSize << "/" << maxCapacity << ") ---\n";
    if (isWaitlistEmpty()) {
        cout << "No one is waiting.\n";
        return;
    }

    QueueNode* current = front;
    int position = 1;
    while (current != nullptr) {
        cout << position << ". [" << current->data.learnerID << "] " << current->data.name << "\n";
        current = current->next;
        position++;
    }
}

void RegistrationQueue::displayActiveSession() {
    cout << "\n--- ACTIVE SESSION (" << activeCount << "/5) ---\n";
    if (activeCount == 0) {
        cout << "Session is currently empty.\n";
        return;
    }

    for (int i = 0; i < activeCount; i++) {
        cout << i + 1 << ". [" << activeSession[i].learnerID << "] " << activeSession[i].name << "\n";
    }
}