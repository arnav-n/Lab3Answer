#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"

/*
  class to represent state data - fairly redundent at this point but will use
  inheritence next
*/
class stateDemog {
  public:
    stateDemog(string inS) :
            state(inS),
            numCounties(0),popOver65(0), popUnder18(0),
            popUnder5(0), bachelorDegreeUp(0), highSchoolUp(0) {
    }

  string getState() const { return state; }
  double getpopOver65() const { return popOver65; }
  double getpopUnder18() const { return popUnder18; }
  double getpopUnder5() const { return popUnder5; }
  double getBAup() const { return bachelorDegreeUp; }
  double getHSup() const { return highSchoolUp; }
  int getNumC() const { return numCounties; }

  //note this stores a running total until averageOut - lots of ways to do this
  void addCountytoState(shared_ptr<demogData>  CI);
  //do once after all running total added (divide by total counties)
  void averageOut();

  friend std::ostream& operator<<(std::ostream &out, const stateDemog &SD);

private:

    const string state;
    double popOver65;
    double popUnder18;
    double popUnder5;
    double bachelorDegreeUp;
    double highSchoolUp;
    int numCounties;
};
#endif
