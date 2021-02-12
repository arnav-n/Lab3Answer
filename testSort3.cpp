#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {


  cout << "Testing demographic income sort..." << endl;

	dataAQ theAnswers;

  //read in a csv file and create a vector of objects representing each counties data
  std::vector<shared_ptr<demogData>> theDemogData = read_csv(
            "county_demographics.csv", DEMOG);

  theAnswers.createStateDemogData(theDemogData);

  std::vector<stateDemog*> povertyLevelLowToHigh;
  theAnswers.sortStateDemogPovLevelLowHigh(povertyLevelLowToHigh);

  // Test case #1
  string leastPov[] {"NH", "MD", "AK", "CT", "NJ"};
  for (int i=0; i < 5; i++) {
  	ASSERT_EQUALS(leastPov[i], povertyLevelLowToHigh.at(i)->getState());
  }

  return 0;
}
