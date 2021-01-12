#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "stateDemog.h"

/*
  data aggregator and query for testing
*/
class dataAQ {
  public:
    dataAQ();

    /* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
    void createStateData(std::vector<shared_ptr<demogData>> theData);

    //return the name of the state with the largest population under age 5
    string youngestPop();
    //return the name of the state with the largest population under age 18
    string teenPop();
    //return the name of the state with the largest population over age 65
    string wisePop();
    //return the name of the state with the largest population who did not finish high school
    string underServeHS();
    //return the name of the state with the largest population who completed college
    string collegeGrads();


    string getMinTeenPop();
    
    friend std::ostream& operator<<(std::ostream &out, const dataAQ &allStateData);

    //For testing, ok to have data be public
    //implementation could vary
    //students could also make a map<string, vector<demogData>>
    std::map<string, stateDemog*> allStateData;

};
#endif
