/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include <iostream>
#include <algorithm>

dataAQ::dataAQ() {}

/* necessary function to aggregate the data  */
void dataAQ::createStateDemogData(std::vector<shared_ptr<demogData>> theData) {
	    //process the vector in our county data aggregate 
    for (const auto &obj : theData) {
        string stateName = obj->getState();
        //if first state entry, create it
        if (allStateDemogData.count(stateName) < 1) {
           //cout << "Making a new state entry: " << stateName << endl;
           allStateDemogData[stateName] = new stateDemog(stateName);
        }
        //either way now add this county info 
        //this keeps a running total
        allStateDemogData[stateName]->addCountytoState(obj);

    }

}

/* necessary function to aggregate the data  */
void dataAQ::createStateHospData(std::vector<shared_ptr<hospitalData>> theData) {
      //process the vector in our county data aggregate 
    for (const auto &obj : theData) {
        string stateName = obj->getState();
        //if first state entry, create it
        if (allStateHospData.count(stateName) < 1) {
           //cout << "Making a new state entry: " << stateName << endl;
           allStateHospData[stateName] = new stateHosp(stateName);
        }
        //either way now add this county info 
        //this keeps a running total
        allStateHospData[stateName]->addHospitaltoState(obj);
    }

}

string dataAQ::HighHospRating() {
  std::pair<std::string, stateHosp *> max
      = *max_element(allStateHospData.begin(), allStateHospData.end(), [](std::pair<std::string, stateHosp *> l, std::pair<std::string, stateHosp *> r){
      return l.second->getOverallRate() < r.second->getOverallRate();
      }
      );
  return max.first; 
}

string dataAQ::LowHospRating() {
  std::pair<std::string, stateHosp *> min
      = *max_element(allStateHospData.begin(), allStateHospData.end(), [](std::pair<std::string, stateHosp *> l, std::pair<std::string, stateHosp *> r){
      return l.second->getOverallRate() > r.second->getOverallRate();
      }
      );
  return min.first; 
}

string dataAQ::HighMortHospRating() {
  std::pair<std::string, stateHosp *> min
      = *max_element(allStateHospData.begin(), allStateHospData.end(), [](std::pair<std::string, stateHosp *> l, std::pair<std::string, stateHosp *> r){
      return l.second->getMortality() < r.second->getMortality();
      }
      );
  return min.first; 
}

string dataAQ::HighReadmitHospRating() {
  std::pair<std::string, stateHosp *> min
      = *max_element(allStateHospData.begin(), allStateHospData.end(), [](std::pair<std::string, stateHosp *> l, std::pair<std::string, stateHosp *> r){
      return l.second->getReadmit() < r.second->getReadmit();
      }
      );
  return min.first; 
}

bool compareHospRating(stateHosp * left, stateHosp * right) {
        return left->getOverallRate() > right->getOverallRate();
}

bool compareHospRatingInv(stateHosp * left, stateHosp * right) {
        return left->getOverallRate() < right->getOverallRate();
}

void dataAQ::sortStateHospRatingHighLow(std::vector<stateHosp *>& hospHighToLow) {

  for (auto entry : allStateHospData){
    hospHighToLow.push_back(entry.second);
  }
  sort(hospHighToLow.begin(), hospHighToLow.end(), compareHospRating);
}

void dataAQ::sortStateHospRatingLowHigh(std::vector<stateHosp *>& hospLowToHigh) {

  for (auto entry : allStateHospData){
    hospLowToHigh.push_back(entry.second);
  }
  sort(hospLowToHigh.begin(), hospLowToHigh.end(), compareHospRatingInv);
}


bool comparePovLevel(stateDemog * left, stateDemog * right) {
        return left->getBelowPoverty() < right->getBelowPoverty();
}

 void dataAQ::sortStateDemogPovLevelLowHigh(std::vector<stateDemog *>& povLevelLowHigh) {

  for (auto entry : allStateDemogData){
    povLevelLowHigh.push_back(entry.second);
  }

  sort(povLevelLowHigh.begin(), povLevelLowHigh.end(), comparePovLevel);

}


bool comparePovLevelInv(stateDemog * left, stateDemog * right) {
        return left->getBelowPoverty() > right->getBelowPoverty();
}

 void dataAQ::sortStateDemogPovLevelHighLow(std::vector<stateDemog *>& povLevelHighLow) {

  for (auto entry : allStateDemogData){
    povLevelHighLow.push_back(entry.second);
  }

  sort(povLevelHighLow.begin(), povLevelHighLow.end(), comparePovLevelInv);

}



//Many ways this could be implemented (predicate and llambda below)
//These are just examples - first one simple loop
//return the name of the state with the largest population under age 5
string dataAQ::youngestPop() {
	double youngestPop = allStateDemogData.begin()->second->getpopUnder5();
	string state = allStateDemogData.begin()->first;
	for (auto const& entry : allStateDemogData) {
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
      = *max_element(allStateDemogData.begin(), allStateDemogData.end(), compareTeen);
  return min.first; 
}

//lambda version
//return the name of the state with the largest population over age 65
string dataAQ::wisePop()  {
  std::pair<std::string, stateDemog *> min 
      = *max_element(allStateDemogData.begin(), allStateDemogData.end(), [](std::pair<std::string, stateDemog *> l, std::pair<std::string, stateDemog *> r){
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
      = *min_element(allStateDemogData.begin(), allStateDemogData.end(), [](std::pair<std::string, stateDemog *> l, std::pair<std::string, stateDemog *> r){
			return l.second->getHSup() < r.second->getHSup();
      }
      );
  return min.first; 
} 

//lambda version
//return the name of the state with the largest population who did receive bachelors degree and up
string dataAQ::collegeGrads() {
  std::pair<std::string, stateDemog *> min 
      = *max_element(allStateDemogData.begin(), allStateDemogData.end(), [](std::pair<std::string, stateDemog *> l, std::pair<std::string, stateDemog *> r){
			return l.second->getBAup() < r.second->getBAup();
      }
      );
  return min.first; 
}

/* print all state data */
std::ostream& operator<<(std::ostream &out, const dataAQ &theAnswers) {
	for (auto const& entry : theAnswers.allStateDemogData) {
    	out << "State Info: " << entry.first << "\n  data: ";
    	out << *(entry.second) << "\n";
	}
  for (auto const& entry : theAnswers.allStateHospData) {
      out << "State Info: " << entry.first << "\n  data: ";
      out << *(entry.second) << "\n";
  }
    return out;
}