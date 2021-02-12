#include "stateHosp.h"
#include "hospitalData.h"
#include <sstream>
#include <string>
#include <assert.h>

void stateHosp::addHospitaltoState(shared_ptr<hospitalData> HI) {
	assert(state.compare(HI->getState()) == 0);
	overallRating += HI->getOverallRate();
	mortality += HI->getMortality().getRatingNum();
	readmission += HI->getReadmit().getRatingNum();
	numHospitals++;
	/* don't count 'unknown' data in averages */
	if (HI->getOverallRate() > 0)
		numNZOHospitals++;
	if (HI->getMortality().getRatingNum() > 0)
		numNZMHospitals++;
	if (HI->getReadmit().getRatingNum() > 0)
		numNZRHospitals++;
}


/* print state hospital data - as average of all the state hospital data */
std::ostream& operator<<(std::ostream &out, const stateHosp &SH) {
    out << "State Hospital info: " << SH.getState();
    out << "\n Number of hospitals: " << SH.numHospitals;
    out << "\n  overall rating: " << SH.getOverallRate();
    out << "\n  mortality rating: " << SH.getMortality();
    out << "\n  readmission rating: " << SH.getReadmit();
    //DEBUG:out << "\n  numnon-zero O, M R: " <<  SH.numNZOHospitals << " " << SH.numNZMHospitals << " " << SH.numNZRHospitals;
    return out;
}
