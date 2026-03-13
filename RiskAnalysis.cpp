#include "RiskAnalysis.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// risk value, high to low (Priority Queue)
void RiskAnalysis::enqueuePriority(RiskProfile p){ 
    if (ProfileCount >= 1000) {
        return; // if array full, cannot insert
    }

    int i = ProfileCount - 1; //check from the bottom
    // count from back, lower risk level go back 
    while (i >= 0 && profiles[i].RiskValue < p.RiskValue) 
    {
        profiles[i+1] = profiles[i]; //move old data to the back 
        i--;
    }
    profiles[i+1] = p; // put the data on the correct place 
    ProfileCount++;
    CountProfile = ProfileCount;
}

void RiskAnalysis::runAnalysis(){
    ProfileCount = 0; // clear the queue before running
    CountProfile = 0;

    // read activity csv
    ifstream file("ActivityHistory.csv");
    if (!file.is_open()) { //no file
        cout << "\n 'ActivityHistory.csv' not found. Please complete and export activities first.\n";
        return;
    }

    string line;
    //read the first line(CSV header)
    if (!getline(file, line)) {
        cout << "\n 'ActivityHistory.csv' is empty. No data to analyze.\n";
        file.close();
        return;
    }

    cout << "\n --- Risk Learner Analysis (Reading from CSV) --- \n";
    bool hasData = false;

    // readt the csv file 
    while (getline(file, line)) {
        if (line.empty()) continue; // skip the enpty line

        stringstream ss(line); // change CSV to stream
        string id, topic, diff, scoreSTR;

        //split with comma 
        getline(ss, id, ',');
        getline(ss, topic, ',');
        getline(ss, diff, ',');
        getline(ss, scoreSTR, ',');

        //create score variable 
        float score = 0.0f;

        try {
        score = stof(scoreSTR); //convert score from csv to float for risk calculation 
        }
        catch (...) {
        score = 0.0f;
        }

        RiskProfile p;
        p.LearnerID = id;

        //risk calculation, convert score 
        float maxScore = 30.0f; //max 3分 convert 2位数才能算
        float rawScoreFloat = static_cast<float>(score); // force score to be float, prevent calculation bug
        float percentage = (rawScoreFloat / maxScore); // calculate (10.0/30.0 = 0.333)
        float BaseRisk = (1.0f - percentage) * 100.0f; //convert score to risk 
        float Difficulty = 1.0f; // default difficulty 

        // adjust the risk based on difficulty 
        if (diff == "Hard") {
            Difficulty = 0.8f; //if hard, lower the risk 
        } else if (diff == "Easy") {
            Difficulty = 1.2f; 
        }
        else if (diff == "Medium")
        {
            Difficulty = 1.0f;
        }
        
        //final risk score
        p.RiskValue = BaseRisk * Difficulty;

        // limit 0 -100
        if (p.RiskValue > 100.0f) p.RiskValue = 100.0f; //(if risk >100, limit to 100)
        if (p.RiskValue < 0.0f) p.RiskValue = 0.0f; //(if risk <0, risk = 0 )

        // Generate recommendation 
        if (p.RiskValue >= 80.0f) {
            p.Recommendation = "Repeat topic and request tutorial support";
        } 
        else if (p.RiskValue >= 60.0f)
        {
            p.Recommendation = "Repeat the topic and attemp the additional practice";
        }
        else if (p.RiskValue >= 40.0f) {
            p.Recommendation = "Attempt easier activities for this topic";
        }        
        else {
            p.Recommendation = "All Good. Proceed to next topic.";
        }

        // put the profile into array (sorted)
        enqueuePriority(p);
        hasData = true; //successfully record data
    }

    file.close();

    if (!hasData) {
        cout << "No valid activity logs found in the CSV file\n";
        return;
    }

    cout << "Analysis complete. High-risk learners have been prioritized based on the data.\n";
}

// display the learner (high risk top at top)
void RiskAnalysis::displayHighRisk() {
    if (ProfileCount == 0) {
        cout << "\nNo risk profiles generated. Run analysis first.\n";
        return;
    }

    cout << "\n========================================================\n";
    cout << "AT-RISK LEARNER PRIORITY RANKING (high risk appear at top)\n";
    cout << "========================================================\n";
    
    for (int i = 0; i < ProfileCount; i++) {
        cout << fixed << setprecision(2); //fixed to 2 number after . 
        cout << "Rank " << (i + 1) << " | ID: " << profiles[i].LearnerID 
             << " | Risk Score: " << profiles[i].RiskValue << " / 100\n"
             << "  -> Action: " << profiles[i].Recommendation << "\n"
             << "--------------------------------------------------------\n";
    }
}

// export the data to risk report csv
void RiskAnalysis::exportAnalysis() {
    if (ProfileCount == 0) {
        cout << "\n No data to export. Run analysis first.\n";
        return;
    }

    ofstream file("RiskReport.csv");
    if (!file) {
        cout << "Error opening file for export.\n";
        return;
    }

    file << "Rank,LearnerID,RiskScore,Recommendation\n"; //write header 
    for (int i = 0; i < ProfileCount; i++) { // write in csv
        file << fixed << setprecision(2);
        file << (i + 1) << ","
             << profiles[i].LearnerID << ","
             << profiles[i].RiskValue << ","
             << profiles[i].Recommendation << "\n";
    }
    
    file.close();
    cout << "\nRisk Analysis successfully exported to 'RiskReport.csv'\n";
}

//additional: view exported analysis
void RiskAnalysis::viewExportedReport(){
    ifstream file("RiskReport.csv"); 
    if (!file.is_open()){
        cout << "'Risk Report.Csv' not found";
        return;
    }
    
    cout << "\n========================================================================\n";
    cout << "                 VIEWING EXPORTED RISK REPORT                           \n";
    cout << "========================================================================\n";

    string line;
    bool isHeader = true;

    while (getline(file, line)) { //read data line by line
        if (line.empty()) continue;

        stringstream ss(line); // change csv to string 
        string rank, id, score, rec;

        // split with coma
        getline(ss, rank, ',');
        getline(ss, id, ',');
        getline(ss, score, ',');
        getline(ss, rec, ',');

        if (isHeader) {
            // output
            cout << "Rank | Learner ID | Risk Score | Recommendation\n";
            cout << "------------------------------------------------------------------------\n";
            isHeader = false;
        } else {
            cout << "  " << rank << "  |  " << id << "   |   " << score << "    | " << rec << "\n";
        }
    }

    file.close();
    cout << "========================================================================\n";
}