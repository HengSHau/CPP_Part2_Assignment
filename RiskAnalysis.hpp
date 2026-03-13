#ifndef RiskAnalysis_HPP
#define RiskAnalysis_HPP

#include <string>

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
    void runAnalysis(); 
    void exportAnalysis();
    void displayHighRisk();
    void viewExportedReport();
    int  CountProfile = 0;

private:
RiskProfile profiles[1000]; //create array (1000) to record 
int ProfileCount = 0; //count how many learner in array 

void enqueuePriority(RiskProfile p);  //rank risk value, from urgent to not urgent 
};

#endif