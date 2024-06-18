#ifndef HtautauMass_h
#define HtautauMass_h

// -------------------------------------------------------------------------------------------------------------- //
//                                                                                                                //
//   class HtautauMass                                                                                            //
//       For H(tautau) mass reconstruction for the HH->bbtautau analysis in the boosted topology                  //
//       Using Collinear Approximation to reconstruct the visible+invisible mass for tautau Jets                  //
//                                                                                                                //
//   Author: Licheng Zhang, Jin Wang                                                                              //
//   PKU, UMD, June 2024                                                                                          //
//                                                                                                                //
// -------------------------------------------------------------------------------------------------------------- //

#include "ROOT/RVec.hxx"
#include "ROOT/RDataFrame.hxx"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLatex.h"
#include "Math/Vector4D.h"
#include "Math/VectorUtil.h"
#include "TStyle.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <algorithm> // for std::max_element
#include <cmath>

using namespace ROOT;
using namespace ROOT::VecOps;
using RNode = ROOT::RDF::RNode;
using str = const std::string &;

using cRVecF = const ROOT::RVecF &;
using cRVecI = const ROOT::RVecI &;
using cRVecC = const ROOT::RVecC &;
using cRVecU = const ROOT::RVecU &;
using cRVecB = const ROOT::RVecB &;

class HtautauMass {
    
    public:
    
        HtautauMass();
        ~HtautauMass(); // destructor
    
        std::vector<int> find_pillars(
            cRVecF FatJet_eta, 
            cRVecF FatJet_phi, 
            int SelJet_id, 
            cRVecF pillar_eta, 
            cRVecF pillar_phi, 
            cRVecF pillar_pt);
        // The pillar can be BoostedTau or SubJet
        
    
};

#endif // HtautauMass_h
