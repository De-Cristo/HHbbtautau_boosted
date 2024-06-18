#include "HHbbtautau_boosted/HTT_Boost/interface/HtautauMass.h"
#include "HHbbtautau_boosted/HTT_Boost/interface/HTT_Boost_util.h"
#include <iostream>

HtautauMass::HtautauMass() {}

HtautauMass::~HtautauMass() {} // Destructor


std::vector<int> HtautauMass::find_pillars(
                                            cRVecF FatJet_eta, 
                                            cRVecF FatJet_phi, 
                                            int SelJet_id, 
                                            cRVecF pillar_eta, 
                                            cRVecF pillar_phi, 
                                            cRVecF pillar_pt)
{

    std::vector<int> output_FaJet;

    std::vector<int> dr_taujet_lessthan8;
    std::vector<int> taujet_pt;

    for(int i = 0; i < int(pillar_eta.size()); i++){
        if(deltaR(FatJet_eta[SelJet_id],pillar_eta[i],FatJet_phi[SelJet_id],pillar_phi[i])<0.8){
            dr_taujet_lessthan8.push_back(i);
            taujet_pt.push_back(pillar_pt[i]);
        }
    }
    
    std::vector<int> indices(dr_taujet_lessthan8.size());
    for (size_t i = 0; i < indices.size(); ++i) {
        indices[i] = i;
    }
    
    std::sort(indices.begin(), indices.end(), [&taujet_pt](int a, int b) {
        return taujet_pt[a] > taujet_pt[b];
    });

    std::vector<int> sorteddr_taujet_lessthan8(dr_taujet_lessthan8.size());
    std::vector<int> sortedtaujet_pt(taujet_pt.size());

    for (size_t i = 0; i < indices.size(); ++i) {
        sorteddr_taujet_lessthan8[i] = dr_taujet_lessthan8[indices[i]];
        sortedtaujet_pt[i] = taujet_pt[indices[i]];
    }

    dr_taujet_lessthan8 = sorteddr_taujet_lessthan8;
    taujet_pt = sortedtaujet_pt;

    output_FaJet.push_back(dr_taujet_lessthan8.size());
    output_FaJet.insert(output_FaJet.end(), dr_taujet_lessthan8.begin(), dr_taujet_lessthan8.end());
    return output_FaJet;
}
