#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include "dataAQ.h"
#include "demogData.h"
#include "stateDemog.h"
#include "hospitalData.h"
#include "stateHosp.h"
#include "parse.h"

using namespace std;

int main() {

	dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theDemogData = read_csv(
            "county_demographics.csv", DEMOG);

    //read in a csv file and create a vector of objects representing each hospital data
    std::vector<shared_ptr<hospitalData>> theHospitalData = read_csvHospital(
            "hospitals.csv", HOSPITAL);

    //helper functions to aggregate the data
    theAnswers.createStateDemogData(theDemogData);
    theAnswers.createStateHospData(theHospitalData);

    //set up output formating
    cout << std::setprecision(2) << std::fixed;
    
    /* 
    for (auto elem : theDemogData) {
        if (elem->getName().compare("AL")==0)
            cout << *elem << endl;
    }
    
    for (auto elem : theHospitalData) {
        if (elem->getName().compare("AL")==0)
            cout << *elem << endl;
    }

    cout << "state demogs: " <<endl;
    cout << *(theAnswers.allStateDemogData["AL"]) << endl;
    cout << "state hospitals: " <<endl;
    cout << *(theAnswers.allStateHospData["AL"]) << endl;
     */

    string stateLowHospRate = theAnswers.LowHospRating();
    cout<< "The state with the lowest hospital rating is: " << stateLowHospRate << endl;
    cout<< *(theAnswers.allStateHospData[stateLowHospRate]) << endl;
    cout << "\nDemographic data for that state is: \n";
    cout << *(theAnswers.allStateDemogData[stateLowHospRate]) << endl;

    string stateHighHospRate = theAnswers.HighHospRating();
    cout<< "\nThe state with the highest hospital rating is: " << stateHighHospRate << endl;
    cout << *(theAnswers.allStateHospData[stateHighHospRate]) << endl;
    cout << "\nDemographic data for that state is:\n";
    cout << *(theAnswers.allStateDemogData[stateHighHospRate]) << endl;

    string hightMortRate = theAnswers.HighMortHospRating();
    cout<< "\nThe state with the highest hospital mortality rating is: " << hightMortRate << endl;
    cout << *(theAnswers.allStateHospData[hightMortRate]) << endl;
    cout << "\nDemographic data for that state is:\n";
    cout << *(theAnswers.allStateDemogData[hightMortRate]) << endl;

    string hightReadmitRate = theAnswers.HighReadmitHospRating();
    cout<< "\nThe state with the highest hospital readmission rating is: " << hightReadmitRate << endl;
    cout << *(theAnswers.allStateHospData[hightReadmitRate]) << endl;
    cout << "\nDemographic data for that state is:\n";
    cout << *(theAnswers.allStateDemogData[hightReadmitRate]) << endl;

    std::vector<stateHosp*> hospHighToLow;
    theAnswers.sortStateHospRatingHighLow(hospHighToLow);
    cout << "the 10 states with highest hospital ratings sorted on overall: " << endl;
    for (int i=0; i < 10; i++) {
        cout << i<< " " << hospHighToLow.at(i)->getState();
        cout <<  " overall hospital rating: " << hospHighToLow.at(i)->getOverallRate() << endl;
    }

    std::vector<stateHosp*> hospLowHigh;
    theAnswers.sortStateHospRatingLowHigh(hospLowHigh);
    cout << "the 10 states with lowest hospital ratings sorted on overall: " << endl;
    for (int i=0; i < 10; i++) {
        cout << i<< " " << hospLowHigh.at(i)->getState();
        cout <<  " overall hospital rating: " << hospLowHigh.at(i)->getOverallRate() << endl;
    }

    std::vector<stateDemog*> povertyLevelLowToHigh;
    theAnswers.sortStateDemogPovLevelLowHigh(povertyLevelLowToHigh);
    cout << "the 10 states with lowest level of persons below the poverty line: " << endl;
    for (int i=0; i < 10; i++) {
        cout << i<< " " << povertyLevelLowToHigh.at(i)->getState();
        cout << " persons below poverty level: " << povertyLevelLowToHigh.at(i)->getBelowPoverty() << endl;
    }

    std::vector<stateDemog*> povertyLevelHighLow;
    theAnswers.sortStateDemogPovLevelHighLow(povertyLevelHighLow);
    cout << "the 10 states with highest level of persons below the poverty line: "  << endl;
    for (int i=0; i < 10; i++) {
        cout << i<< " " << povertyLevelHighLow.at(i)->getState();
        cout << " persons below poverty level: " << povertyLevelHighLow.at(i)->getBelowPoverty() << endl;
    }

    return 0;
}

