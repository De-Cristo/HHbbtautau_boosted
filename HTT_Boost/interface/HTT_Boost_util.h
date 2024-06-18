#ifndef HTT_Boost_util_h
#define HTT_Boost_util_h

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
#include "Math/SpecFuncMathCore.h"
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

// general functions

bool check_bit(int number, int bitpos);
double self_Phi_mpi_pi(double angle);
bool isNumberInList(RVecI myList, int target);
std::pair<int, int> findLeadingAndSubleading(cRVecF vec);
std::vector<int> findIndicesOfValue(cRVecF vec, int value);
float min_result(cRVecF vec);
float max_result(cRVecF vec);
float deltaR(float eta_1, float eta_2, float phi_1, float phi_2);
float deltaR2(float eta_1, float eta_2, float phi_1, float phi_2);

// physical functions
int FatJetFilter(cRVecF FatJet_pt, cRVecF FatJet_eta, double pt_threshold, double eta_threshold);
int JetID_MaxPNetscore(cRVecF score);
int veto_e_muon(cRVecF Lep_pt, 
                cRVecF Lep_eta, 
                cRVecF Lep_dxy, 
                cRVecF Lep_dz, 
                float pt_cut, 
                float eta_cut, 
                float dxy_cut, 
                float dz_cut);

void DecomposeMomentum(
    const ROOT::Math::PtEtaPhiMVector& p, 
    const ROOT::Math::PtEtaPhiMVector& a, 
    const ROOT::Math::PtEtaPhiMVector& b,
    ROOT::Math::PtEtaPhiMVector& pa,
    ROOT::Math::PtEtaPhiMVector& pb
);

#endif // HTT_Boost_util_h
