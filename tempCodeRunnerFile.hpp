// Types.hpp
#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>

// The standard Learner profile
struct Learner {
    std::string learnerID;
    std::string name;
    
    // Performance Indicators
    float averageScore;
    int failedAttempts;
    float timeSpent; // in minutes
    
    // Task 4 specific outputs
    float riskScore;
    std::string recommendation;
};

// The Activity data (Used later for Task 2 and Task 3)
struct Activity {
    std::string learnerID;
    std::string activityID;
    std::string topic;
    std::string difficulty;
    float score;
};

#endif