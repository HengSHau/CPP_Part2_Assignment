// ActivityStack.cpp
#include "ActivityStack.hpp"

using namespace std;

// Constructor
ActivityStack::ActivityStack() {
    top = nullptr;
    currentSize = 0;
}

// Destructor to clean up memory and prevent leaks
ActivityStack::~ActivityStack() {
    while (!isEmpty()) {
        pop(); // Delete all nodes when the session ends
    }
}

// Check if the stack is empty
bool ActivityStack::isEmpty() {
    return top == nullptr;
}

// 1. Move to a new activity (Add to TOP of stack)
void ActivityStack::push(Activity a) {
    StackNode* newNode = new StackNode;
    newNode->data = a;
    
    // The new node's next points to the old top
    newNode->next = top;
    
    // The top pointer now points to our new node
    top = newNode;
    currentSize++;
    
    cout << "[Session] Started new activity: " << a.topic << " (" << a.difficulty << ")\n";
}

// 2. Undo / Go back (Remove from TOP of stack)
Activity ActivityStack::pop() {
    if (isEmpty()) {
        cout << "[Session] No previous activities to go back to.\n";
        return {"EMPTY", "None", "None", 0.0};
    }

    // Store the top node temporarily
    StackNode* temp = top;
    Activity poppedActivity = temp->data;

    // Move the top pointer down to the next node
    top = top->next;

    // Delete the old top from memory
    delete temp;
    currentSize--;

    cout << "[Session] 'Undo' triggered. Went back from: " << poppedActivity.topic << "\n";
    return poppedActivity;
}

// 3. Look at the current (top) activity without removing it
Activity ActivityStack::peek() {
    if (isEmpty()) {
        return {"EMPTY", "None", "None", 0.0};
    }
    return top->data;
}

// 4. Display the sequence of activities (From top to bottom)
void ActivityStack::displayStack() {
    if (isEmpty()) {
        cout << "Activity history is empty.\n";
        return;
    }

    cout << "\n--- Current Activity Sequence (Top = Current) ---\n";
    StackNode* current = top;
    int position = currentSize;
    
    while (current != nullptr) {
        if (current == top) {
            cout << position << ". [" << current->data.activityID << "] " 
                 << current->data.topic << " (Score: " << current->data.score << ") <-- CURRENT\n";
        } else {
            cout << position << ". [" << current->data.activityID << "] " 
                 << current->data.topic << " (Score: " << current->data.score << ")\n";
        }
        current = current->next;
        position--;
    }
    cout << "-------------------------------------------------\n";
}

void ActivityStack::selectionFlow(int choice) {   
    if (choice == 1) {
        string topic, diff;
        float score;
        cout << "Enter Topic: "; cin >> topic;
        cout << "Enter Difficulty: "; cin >> diff;
        cout << "Enter Score: "; cin >> score;

        // 生成 ID 并直接 push 到当前对象 (this)
        Activity newAct = {"ACT_" + to_string(rand() % 100), topic, diff, score};
        this->push(newAct); // 使用 this-> 或者直接调用 push [cite: 30]

    } else if (choice == 2) {
        // 直接在当前对象上操作 pop [cite: 31]
        Activity prev = this->pop(); 
        if (prev.topic != "None") {
            cout << "Backtracking from " << prev.topic << "..." << endl;
        }

    } else if (choice == 3) {
        // 展示当前对象的栈状态 [cite: 39]
        this->displayStack(); 

    } else if (choice == 4) {
        cout << "Ending session. Data sent to logging system." << endl;
        // 这里应调用 Task 3 的接口 [cite: 33]
    }
}