#ifndef STATEH_H
#define STATEH_H

#include <memory>
#include <string>
#include <iostream>
#include "hospitalData.h"

/*
  class to represent state hospital data - fairly redundent at this point but will use
  inheritence next
*/
class stateHosp {
  public:
    stateHosp(string inS) :
            state(inS),
            overallRating(0), mortality(0), readmission(0),
            numHospitals(0),  numNZOHospitals(0), numNZMHospitals(0), numNZRHospitals(0) {
    }

  string getState() const { return state; }
  double getOverallRate() const { 
    if (numNZOHospitals > 0)
      return overallRating/(double)numNZOHospitals; 
    return overallRating;
  } // zero means none
  rating getMortality() const {
    if (numNZMHospitals > 0) 
      return rating(mortality.getRatingNum()/(double)numNZMHospitals); 
    return rating(mortality.getRatingNum());
  }
  rating getReadmit() const { 
    if (numNZRHospitals > 0) 
      return rating(readmission.getRatingNum()/(double)numNZRHospitals); 
    return rating(readmission.getRatingNum());
  }
  int getNumH() const { return numHospitals; }

  //note this stores a running total until averageOut - lots of ways to do this
  void addHospitaltoState(shared_ptr<hospitalData>  HI);

  friend std::ostream& operator<<(std::ostream &out, const stateHosp &SD);

private:

   // note no 'name' or 'type' because this is aggregate data
    const string state;
    int overallRating;
    rating mortality;
    rating readmission;

    int numHospitals;
    /* a bit ugly but accurate averages without 'unknown' */
    int numNZOHospitals;
    int numNZMHospitals; //number of hospitals with known mortality data
    int numNZRHospitals;//number of hospitals with known readmission data
};
#endif
