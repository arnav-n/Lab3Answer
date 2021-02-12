#include "hospitalData.h"
#include <sstream>


/* print hospital data */
std::ostream& operator<<(std::ostream &out, const hospitalData &HD) {
    out << "Hosptial Info: " << HD.name << ", " << HD.state;
    out << "\nType: " << HD.type;
    out << "\nOverall rating (out of 5): " << HD.overallRating;
    out << "\nmortality rating: " << HD.mortality.getRating();
    out << "\nreadmit rating: " << HD.readmission.getRating();
	return out;
}
