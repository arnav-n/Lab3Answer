#include "stateDemog.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>

 //note this stores a running total until averageOut 
//just adds the current county info to the running total
void stateDemog::addCountytoState(shared_ptr<demogData> CI) {
	assert(state.compare(CI->getState()) == 0);
	popOver65 += CI->getpopOver65();
	popUnder18 += CI->getpopUnder18();
	popUnder5 += CI->getpopUnder5();
	bachelorDegreeUp += CI->getBAup();
	highSchoolUp += CI->getHSup();
	numCounties++;
}

//do once after all running total added (divide by total counties)
void stateDemog::averageOut() {
	popOver65 /= numCounties;
	popUnder18 /= numCounties;
	popUnder5 /= numCounties;
	bachelorDegreeUp /= numCounties;
	highSchoolUp /= numCounties;
}


/* print state data - as average of all the county data */
std::ostream& operator<<(std::ostream &out, const stateDemog&SD) {
    out << "State Info: " << SD.state;
    out << "\nNumber of Counties: " << SD.numCounties;
    out << "\nPopulation info: \n(over 65): " << SD.popOver65;
    out << "\n(under 18): " << SD.popUnder18;
    out << "\n(under 5): " << SD.popUnder5;
    out << "\nEducation info: \n(Bachelor or more): " << SD.bachelorDegreeUp;
    out << "\n(high school or more): " << SD.highSchoolUp;
    return out;
}
