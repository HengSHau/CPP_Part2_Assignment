// RegistrationQueue.cpp
#include "RegistrationQueue.hpp"
#include <iostream>

using namespace std;

// Constructor
RegistrationQueue::RegistrationQueue(int capacity) {
    front = nullptr;
    rear = nullptr;
    currentSize = 0;
    maxCapacity = capacity;
}

// Destructor to clean up memory
RegistrationQueue::~RegistrationQueue() {
    while (!isEmpty()) {
        dequeue(); 
    }
}

// Check if empty
bool RegistrationQueue::isEmpty() {
    return front == nullptr;
}

// Check if full (Limited to 50 as you requested)
bool RegistrationQueue::isFull() {
    return currentSize >= maxCapacity;
}

// 1. Register a new learner (Add to the back of the line)
void RegistrationQueue::enqueue(Learner l) {
    if (isFull()) {
        cout << "[System] Session is FULL (" << maxCapacity << "/" << maxCapacity << "). Cannot register Learner: " << l.name << "\n";
        return;
    }

    // Create the new node dynamically in Heap memory
    QueueNode* newNode = new QueueNode;
    newNode->data = l;
    newNode->next = nullptr;

    if (isEmpty()) {
        // If the queue is empty, the new node is both front and rear
        front = rear = newNode;
    } else {
        // Otherwise, attach it behind the current rear, then update rear
        rear->next = newNode;
        rear = newNode;
    }
    
    currentSize++;
    cout << "[System] " << l.name << " registered successfully. (Queue size: " << currentSize << ")\n";
}

// 2. Admit a learner into the session (Remove from the front of the line)
Learner RegistrationQueue::dequeue() {
    if (isEmpty()) {
        cout << "[System] Queue is empty. No learners to admit.\n";
        return {"EMPTY", "", 0, 0, 0, 0, ""}; // Return empty dummy learner
    }

    // Store the node we are removing
    QueueNode* temp = front;
    Learner admittedLearner = temp->data;

    // Move the front pointer to the next person
    front = front->next;

    // If we just removed the last person, rear must also become null
    if (front == nullptr) {
        rear = nullptr;
    }

    // Delete the old node from memory to prevent memory leaks
    delete temp;
    currentSize--;

    cout << "[System] " << admittedLearner.name << " has entered the learning session.\n";
    return admittedLearner;
}

// 3. Display all learners currently waiting
void RegistrationQueue::displayQueue() {
    if (isEmpty()) {
        cout << "Waiting List is empty.\n";
        return;
    }

    cout << "\n--- Current Registration Waiting List ---\n";
    QueueNode* current = front;
    int position = 1;
    while (current != nullptr) {
        cout << position << ". " << current->data.learnerID << " - " << current->data.name << "\n";
        current = current->next; // Move to the next node
        position++;
    }
    cout << "-----------------------------------------\n";
}