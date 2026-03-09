// ActivityStack.hpp
#ifndef ACTIVITYSTACK_HPP
#define ACTIVITYSTACK_HPP

#include <iostream>
#include <string>

using namespace std;

#include "Types.hpp"
// The Node for our Linked List Stack
struct StackNode {
    Activity data;
    StackNode* next;
};

class ActivityStack {
private:
    StackNode* top; // Points to the current (newest) activity
    int currentSize;

public:
    ActivityStack();
    ~ActivityStack();

    bool isEmpty();
    
    // Core Stack Functions for Task 2
    void push(Activity a);      // Move forward to the next activity
    Activity pop();             // "Undo" / Go back to previous activity
    Activity peek();            // Look at the current activity
    void displayStack();        // Show the sequence of activities
    void selectionFlow(int choice, std::string LearnerID);
};

#endif