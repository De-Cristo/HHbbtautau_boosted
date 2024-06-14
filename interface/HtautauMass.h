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
        ~HtautauMass();
    
        bool check_bit(int number, int bitpos) {
            int res = number & (1 << bitpos);
            return res != 0;
        }

        bool isNumberInList(RVecI myList, int target) {
            for (int i = 0; i < myList.size(); ++i) {
                if (myList[i] == target) { return true; }
            }
            return false;
        }

        std::pair<int, int> findLeadingAndSubleading(cRVecF vec) {
            // Initialize variables to store the indices of leading and subleading elements
            int leadingIdx = 0;
            int subleadingIdx = 0;

            // Find the index of the leading element
            auto leadingIter = std::max_element(vec.begin(), vec.end());
            leadingIdx = std::distance(vec.begin(), leadingIter);

            // Find the index of the subleading element
            int leadingValue = *leadingIter;
            auto subleadingIter = std::max_element(vec.begin(), vec.end(), [&](int a, int b) {
                return a < b && b < leadingValue;
            });
            subleadingIdx = std::distance(vec.begin(), subleadingIter);

            // Return a pair containing the indices of leading and subleading elements
            return std::make_pair(leadingIdx, subleadingIdx);
        }


        std::vector<int> findIndicesOfValue(cRVecF vec, int value) {
            std::vector<int> indices;
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i] == value) { indices.push_back(i); }
            }
            return indices;
        }

        float deltaR2(float eta_1, float eta_2, float phi_1, float phi_2){
            const float deta = eta_1 - eta_2;
            const float dphi = ROOT::Math::VectorUtil::Phi_mpi_pi(phi_1 - phi_2);
            const float dRsq = std::pow(deta,2) + std::pow(dphi,2);
            return dRsq;
        }

        float deltaR(float eta_1, float eta_2, float phi_1, float phi_2){
            const float deta = eta_1 - eta_2;
            const float dphi = ROOT::Math::VectorUtil::Phi_mpi_pi(phi_1 - phi_2);
            const float dRsq = std::pow(deta,2) + std::pow(dphi,2);
            return sqrt(dRsq);
        }


        float min_result(cRVecF vec){
            auto leadingIter = *std::min_element(vec.begin(), vec.end());
            return leadingIter;
        }


        float max_result(cRVecF vec){
            auto leadingIter = *std::max_element(vec.begin(), vec.end());
            return leadingIter;
        }
    
    
    private:
    
        int JetID_PNetscore(cRVecF score);
    
}

#endif // HtautauMass_h
