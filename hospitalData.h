#ifndef HOSP_H
#define HOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"

using namespace std;

/*
  class to represent hospital data
  from CORGIS
*/
class hospitalData {
  public:
    hospitalData(string inN, string inS, string inType, int inRating,
        rating inMort, rating inReAdmit) :
            name(inN), state(inS), type(inType), overallRating(inRating),
            mortality(inMort), readmission(inReAdmit){
    }

    string getName() const { return name; }
    string getState() const { return state; }
    string getType() const { return type; }
    int getOverallRate() const { return overallRating; } // zero means none
    rating getMortality() const { return mortality; }
    rating getReadmit() const { return readmission; }

   friend std::ostream& operator<<(std::ostream &out, const hospitalData &HD);

private:
    const string name;
    const string state;
    const string type;
    const int overallRating;
    rating mortality;
    rating readmission;
};

#endif
