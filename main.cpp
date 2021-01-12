#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "dataAQ.h"
#include "demogData.h"
#include "stateDemog.h"
#include "parse.h"

using namespace std;

int main() {

	dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics.csv", DEMOG);

    theAnswers.createStateData(theData);

    cout << "the States: " << endl;
    cout << theAnswers << endl;

    //naive way to answer Qs
    cout << "*** the state that needs the most pre-schools**" << endl;
    string needPK = theAnswers.youngestPop();
    cout << *(theAnswers.allStateData[needPK]) << endl;
    cout << "*** the state that needs the most high schools**" << endl;
    string needHS = theAnswers.teenPop();
    cout << *(theAnswers.allStateData[needHS]) << endl;
    cout << "*** the state that needs the most vaccines**" << endl;
    string needV = theAnswers.wisePop();
    cout << *(theAnswers.allStateData[needV]) << endl;

    cout << "*** the state that needs the most help with education**" << endl;
    string noHS = theAnswers.underServeHS();
    cout << *(theAnswers.allStateData[noHS]) << endl;
    cout << "*** the state with most college grads**" << endl;
    string grads = theAnswers.collegeGrads();
    cout << *(theAnswers.allStateData[grads]) << endl;

    return 0;
}

