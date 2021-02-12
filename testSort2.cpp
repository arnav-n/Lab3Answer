#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {


cout << "Testing hospital sort..." << endl;

	dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing hospital data
    std::vector<shared_ptr<hospitalData>> theHospitalData = read_csvHospital(
            "hospitals.csv", HOSPITAL);

    theAnswers.createStateHospData(theHospitalData);

    std::vector<stateHosp*> hospLowToHigh;
    theAnswers.sortStateHospRatingLowHigh(hospLowToHigh);

  // Test case #1
  string lowHosp[] {"DC", "NY", "NV", "VI", "FL"};
  for (int i=0; i < 5; i++) {
  	ASSERT_EQUALS(lowHosp[i], hospLowToHigh.at(i)->getState());
  }

  return 0;
}
