#include "HHbbtautau_boosted/HTT_Boost/interface/HTT_Boost_util.h"
#include "HHbbtautau_boosted/HTT_Boost/interface/HtautauMass.h"

#include "Math/VectorUtil.h"

bool check_bit(int number, int bitpos) {
    int res = number & (1 << bitpos);
    return res != 0;
}

double self_Phi_mpi_pi(double angle) {
   // returns phi angle in the interval (-PI,PI]
   if ( angle <= ROOT::Math::Pi() && angle > -ROOT::Math::Pi() ) return angle;
 
   if ( angle > 0 ) {
      int n = static_cast<int>( (angle+ROOT::Math::Pi())/(2.*ROOT::Math::Pi()) );
      angle -= 2*ROOT::Math::Pi()*n;
   } else {
      int n = static_cast<int>( -(angle-ROOT::Math::Pi())/(2.*ROOT::Math::Pi()) );
      angle += 2*ROOT::Math::Pi()*n;
   }
   return angle;
}

bool isNumberInList(RVecI myList, int target) {

    for (int i = 0; i < int(myList.size()); ++i) {
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
    for (int i = 0; i < int(vec.size()); ++i) {
        if (vec[i] == value) { indices.push_back(i); }
    }
    return indices;
}

float min_result(cRVecF vec){
    auto leadingIter = *std::min_element(vec.begin(), vec.end());
    return leadingIter;
}

float max_result(cRVecF vec){
    auto leadingIter = *std::max_element(vec.begin(), vec.end());
    return leadingIter;
}

float deltaR2(float eta_1, float eta_2, float phi_1, float phi_2){
    const float deta = eta_1 - eta_2;
    const float dphi = self_Phi_mpi_pi(phi_1 - phi_2);
    const float dRsq = std::pow(deta,2) + std::pow(dphi,2);
    return dRsq;
}

float deltaR(float eta_1, float eta_2, float phi_1, float phi_2){
    float dRsq = deltaR2(eta_1, eta_2, phi_1, phi_2);
    return sqrt(dRsq);
}

int FatJetFilter(cRVecF FatJet_pt, cRVecF FatJet_eta, double pt_threshold, double eta_threshold) {
    if (FatJet_pt.size() != FatJet_eta.size()) {
        throw std::invalid_argument("The vectors FatJet_pt and FatJet_eta must have the same size.");
    }

    int count = 0;

    for (int i = 0; i < int(FatJet_pt.size()); ++i) {
        if (FatJet_pt[i] > pt_threshold && std::abs(FatJet_eta[i]) < eta_threshold) {
            ++count;
        }
    }

    return count;
}

int JetID_MaxPNetscore(cRVecF score){
    // find the index of the jet with maximum Pnet score(depending on which score is used)
    auto JetID = std::distance(score.begin(), std::max_element(score.begin(), score.end()));
    return JetID;
}

int veto_e_muon(cRVecF Lep_pt, 
                cRVecF Lep_eta, 
                cRVecF Lep_dxy, 
                cRVecF Lep_dz, 
                float pt_cut, 
                float eta_cut, 
                float dxy_cut, 
                float dz_cut)
{
    int e_mu_number = 0;

    for (int i = 0; i < int(Lep_pt.size()); ++i) {
        if((Lep_pt[i] > pt_cut) && (std::abs(Lep_eta[i]) < eta_cut) && (std::abs(Lep_dxy[i]) < dxy_cut) && (std::abs(Lep_dz[i]) < dz_cut)){
            e_mu_number += 1;
        }
    }

    return e_mu_number;
}

void DecomposeMomentum(
    const ROOT::Math::PtEtaPhiMVector& p, 
    const ROOT::Math::PtEtaPhiMVector& a, 
    const ROOT::Math::PtEtaPhiMVector& b,
    ROOT::Math::PtEtaPhiMVector& pa,
    ROOT::Math::PtEtaPhiMVector& pb
) {
    //
    typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double>> CartesianVector;

    //
    CartesianVector p_xyz(p.Px(), p.Py(), p.Pz(), p.E());
    CartesianVector a_xyz(a.Px(), a.Py(), a.Pz(), a.E());
    CartesianVector b_xyz(b.Px(), b.Py(), b.Pz(), b.E());

    //
    double a_magnitude = a_xyz.R();
    double b_magnitude = b_xyz.R();

    // 
    CartesianVector a_unit = a_xyz / a_magnitude;
    CartesianVector b_unit = b_xyz / b_magnitude;

    //
    double p_dot_a = p_xyz.Dot(a_unit);
    double p_dot_b = p_xyz.Dot(b_unit);

    CartesianVector p_a = p_dot_a * a_unit;
    CartesianVector p_b = p_dot_b * b_unit;

    //
    pa = ROOT::Math::PtEtaPhiMVector(p_a.Pt(), p_a.Eta(), p_a.Phi(), p_a.M());
    pb = ROOT::Math::PtEtaPhiMVector(p_b.Pt(), p_b.Eta(), p_b.Phi(), p_b.M());
}

