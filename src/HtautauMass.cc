#include "HHbbtautau_boosted/interface/HtautauMass.h"
#include <iostream>

HtautauMass::HtautauMass() {}

HtautauMass::~HtautauMass() {}

int HtautauMass::JetID_PNetscore(cRVecF score){
            // find the index of the jet with maximum Pnet score(depending on which score is used)
            auto JetID = std::distance(score.begin(), std::max_element(score.begin(), score.end()));
            return JetID;
}
