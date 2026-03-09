#include "RiskAnalysis.hpp"
#include <iostream>
#include <fstream>


void RiskAnalysis:: runAnalysis(ActivityLog& log){
        CountProfile = 0;

    //Calculate Risk score 
    for(int i=0; i<log.currentTotal; i++){
        bool found = false;
        int index = -1;

        for(int j=0; j<CountProfile; j++){
            if (profiles[j].LearnerID == log.logs[i].learnerID)
            {
                found = true;
                index = j;
                break;
            }
            
        }
        if (found == false){
            profiles[CountProfile].LearnerID = log.logs[i].learnerID;
            
            //If score < 60, high risk 
            if (log.logs[i].score < 60)
            {
                if (log.logs[i].difficulty == "Easy")
                {
                    profiles[CountProfile].RiskValue = 50.0;
                }
                                
                else if (log.logs[i].difficulty == "Normal")
                {
                    profiles[CountProfile].RiskValue = 40.0;
                }

                 else if (log.logs[i].difficulty == "Hard"){
                    profiles[CountProfile].RiskValue =  30.0;
                 }

                 else {
                    profiles[CountProfile].RiskValue = 40.0;
                }       
        }
            else
            {
                profiles[CountProfile].RiskValue = 10.0; 
            }
            CountProfile = CountProfile + 1;
        }
        else{
            // SCENARIO 2: We found them again in the log
            if (log.logs[i].score < 60) {
                // They failed AGAIN! Add a penalty based on difficulty:
                if (log.logs[i].difficulty == "Easy") {
                    profiles[index].RiskValue = profiles[index].RiskValue + 40.0;
                } 
                else if (log.logs[i].difficulty == "Normal") {
                    profiles[index].RiskValue = profiles[index].RiskValue + 30.0;
                } 
                else if (log.logs[i].difficulty == "Hard") {
                    profiles[index].RiskValue = profiles[index].RiskValue + 15.0;
                }
            }
        }
    }
    
    // Attach recommended action 
    for (int i = 0; i<CountProfile; i++){
        if (profiles[i].RiskValue >= 60)
        {
            profiles[i].Recommendation = "Repeat the topic and attempt the easier version";
        }

        else if (profiles[i].RiskValue >=30)
        {
            profiles[i].Recommendation = "Review the current topic before attempt the next activity";
        }
        
        else{ profiles[i].Recommendation = "All good, proceed to the next activity";}
    }
    
    //Rank learner according to their risk level, high risk level more higher 
    for (int i=0; i<CountProfile - 1; i++){
        for (int j = 0; j < CountProfile - 1; j++)
        {
            if (profiles[j].RiskValue < profiles[j+1].RiskValue)
            {
                RiskProfile temp = profiles[j];
                profiles[j] = profiles[j +1];
                profiles[j + 1 ] = temp;
            } 
            
        }
        
    }

    //Display the high priority learner who require attention 
    cout << "\nLEARNER PRIORITY LIST - (RISK)\n";
    for (int i = 0; i <CountProfile; i ++){
        cout << "\nRANK:" << (i + 1) << "\n";
        cout << "ID:" << profiles[i].LearnerID << "\n";
        cout << "Risk Score:" << profiles[i].RiskValue << "\n";
        cout << "RECOMMENDATION:" << profiles[i].Recommendation << "\n";
        cout << "--------------------\n";
    }
}

//Export the data to csv 
void RiskAnalysis::exportAnalysis(){
    if (CountProfile == 0)
    {
        cout << "No data to export.";
        return;
    }

    else 
    {
        ofstream outFile("RiskReport.csv");
outFile << "Rank,LearnerID,RiskScore,Recommendation\n";
for (int i = 0; i < CountProfile; i++)
{
    outFile << (i+1) << "," << profiles[i].LearnerID << "," << profiles[i].RiskValue << "," << profiles[i].Recommendation << "\n";
}
    outFile.close();
cout << "\nRisk analysis export to 'RiskReport.csv'. \n";
    }
}