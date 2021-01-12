/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include <iostream>
#include <algorithm>

dataAQ::dataAQ() {}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
void dataAQ::createStateData(std::vector<shared_ptr<demogData>> theData) {
	    //process the vector in our county data aggregate 
    for (const auto &obj : theData) {
        string stateName = obj->getState();
        //if first state entry, create it
        if (allStateData.count(stateName) < 1) {
           //cout << "Making a new state entry: " << stateName << endl;
           allStateData[stateName] = new stateDemog(stateName);
        }
        //either way now add this county info 
        //this keeps a running total
        allStateData[stateName]->addCountytoState(obj);
    }
    //now that all the data is aggrgated, compute average
    for (const auto &entry : allStateData) {
    	entry.second->averageOut();
    }
}

//Many ways this could be implemented (predicate and llambda below)
//These are just examples - first one simple loop
//return the name of the state with the largest population under age 5
string dataAQ::youngestPop() {
	double youngestPop = allStateData.begin()->second->getpopUnder5();
	string state = allStateData.begin()->first;
	for (auto const& entry : allStateData) {
		if (youngestPop < entry.second->getpopUnder5() ) {
			youngestPop = entry.second->getpopUnder5();
			state = entry.second->getState();
		}
	}
	return state;
} 

//predicates all sort for smaller
bool compareTeen(std::pair<std::string, stateDemog *> left, std::pair<std::string, stateDemog *> right) {
        return left.second->getpopUnder18() < right.second->getpopUnder18();
}

//predicate version
//return the name of the state with the largest population under age 18
string dataAQ::teenPop()  {
  std::pair<std::string, stateDemog *> min 
      = *max_element(allStateData.begin(), allStateData.end(), compareTeen);
  return min.first; 
}

//lambda version
//return the name of the state with the largest population over age 65
string dataAQ::wisePop()  {
  std::pair<std::string, stateDemog *> min 
      = *max_element(allStateData.begin(), allStateData.end(), [](std::pair<std::string, stateDemog *> l, std::pair<std::string, stateDemog *> r){
			return l.second->getpopOver65() < r.second->getpopOver65();
      }
      );
  return min.first; 
}

//lambda version
//return the name of the state with the largest population who did not receive high school diploma
string dataAQ::underServeHS() {
  //note min element not max
  std::pair<std::string, stateDemog *> min 
      = *min_element(allStateData.begin(), allStateData.end(), [](std::pair<std::string, stateDemog *> l, std::pair<std::string, stateDemog *> r){
			return l.second->getHSup() < r.second->getHSup();
      }
      );
  return min.first; 
} 

//lambda version
//return the name of the state with the largest population who did receive bachelors degree and up
string dataAQ::collegeGrads() {
  std::pair<std::string, stateDemog *> min 
      = *max_element(allStateData.begin(), allStateData.end(), [](std::pair<std::string, stateDemog *> l, std::pair<std::string, stateDemog *> r){
			return l.second->getBAup() < r.second->getBAup();
      }
      );
  return min.first; 
}

/* print all state data */
std::ostream& operator<<(std::ostream &out, const dataAQ &theAnswers) {
	for (auto const& entry : theAnswers.allStateData) {
    	out << "State Info: " << entry.first << "\n  data: ";
    	out << *(entry.second) << "\n";
	}
    return out;
}