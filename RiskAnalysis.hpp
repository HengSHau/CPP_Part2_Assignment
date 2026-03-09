#ifndef RiskAnalysis_HPP
#define RiskAnalysis_HPP

#include <string>
#include "ActivityLog.hpp"

using namespace std;

//Structure to hold analysis result 
struct RiskProfile 
{
    string LearnerID;
    float RiskValue;
    string Recommendation;
};

class RiskAnalysis{
public: 
    void runAnalysis(ActivityLog& log);
    void exportAnalysis();
    int  CountProfile = 0;

private:
RiskProfile profiles[1000];
int ProfileCount = 0;
};


#endif