from analysis_tools.utils import import_root
import os

ROOT = import_root()

class HtautauMassRDFProducer():
    def __init__(self, *args, **kwargs):
        self.isMC = kwargs.pop("isMC", True)
        self.FatJetpTCut = str(kwargs.pop("FatJetpTCut", 180.0))
        self.FatJetEtaCut = str(kwargs.pop("FatJetEtaCut", 2.4))
        
        self.VetoElepTCut = str(kwargs.pop("VetoElepTCut", 20))
        self.VetoEleEtaCut = str(kwargs.pop("VetoEleEtaCut", 2.5))
        self.VetoEleDxyCut = str(kwargs.pop("VetoEleDxyCut", 0.05))
        self.VetoEleDzCut = str(kwargs.pop("VetoEleDzCut", 0.2))
        
        self.VetoMuonpTCut = str(kwargs.pop("VetoMuonpTCut", 10))
        self.VetoMuonEtaCut = str(kwargs.pop("VetoMuonEtaCut", 2.4))
        self.VetoMuonDxyCut = str(kwargs.pop("VetoMuonDxyCut", 0.05))
        self.VetoMuonDzCut = str(kwargs.pop("VetoMuonDzCut", 0.2))
        
        
        base = "{}/{}/src/HHbbtautau_boosted/HTT_Boost".format(os.getenv("CMT_CMSSW_BASE"), os.getenv("CMT_CMSSW_VERSION"))
        library_path = "libHHbbtautau_boostedHTT_Boost.so"
            
        if "/libHHbbtautau_boostedHTT_Boost.so" not in ROOT.gSystem.GetLibraries():
            if ROOT.gSystem.Load(library_path) == -1: print(f"Error loading library: {library_path}")
            else: print(f"Library loaded: {library_path}")
        
        ROOT.gROOT.ProcessLine(".L {}/interface/HtautauMass.h".format(base))
        ROOT.gROOT.ProcessLine(".L {}/interface/HTT_Boost_util.h".format(base))
        
        # here is the way to use a c++ class
        ROOT.gInterpreter.Declare("""
                                    auto _htt_mass = HtautauMass();
                                  """)
        
    def run(self, df):
        if not self.isMC:
            return df, []
        else:
            
            ## One can use the following method to test the availability of the c++ functions
            # if hasattr(ROOT, 'min_result'): print("min_result is available")
            # else: print("min_result is not declared")
            
            df = df.Filter("nFatJet >1")
            df = df.Define("FatJetFilter", "FatJetFilter(FatJet_pt, FatJet_eta, {0}, {1})"\
                           .format(self.FatJetpTCut, self.FatJetEtaCut)).Filter("FatJetFilter>0")
            
            df = df.Define("HttJet_id", "JetID_MaxPNetscore(FatJet_particleNet_XttVsQCD)")
            df = df.Define("Htt_rawmass", "FatJet_mass[HttJet_id]")
            df = df.Define("Htt_vismass_corr", "FatJet_mass[HttJet_id]*FatJet_particleNet_massCorr[HttJet_id]")
            df = df.Define("Htt_vismass_corr_fromsd", "FatJet_msoftdrop[HttJet_id]*FatJet_particleNet_massCorr[HttJet_id]")
            df = df.Define("Htt_vismass_sd", "FatJet_msoftdrop[HttJet_id]")
            df = df.Define("HttJet_particleNet_XttVsQCD", "FatJet_particleNet_XttVsQCD[HttJet_id]")
            
            df = df.Define("n_veto_ele", "veto_e_muon(Electron_pt, Electron_eta, Electron_dxy, Electron_dz, {0}, {1}, {2}, {3})"\
                           .format(self.VetoElepTCut, self.VetoEleEtaCut, self.VetoEleDxyCut, self.VetoEleDzCut))
            df = df.Define("n_veto_muon", "veto_e_muon(Muon_pt, Muon_eta, Muon_dxy, Muon_dz, {0}, {1}, {2}, {3})"\
                           .format(self.VetoMuonpTCut, self.VetoMuonEtaCut, self.VetoMuonDxyCut, self.VetoMuonDzCut))
            
            df = df.Define("SubJet_vector", "_htt_mass.find_pillars(FatJet_eta, FatJet_phi, HttJet_id, SubJet_eta, SubJet_phi, SubJet_pt)")
            df = df.Define("N_SubJet_Matched", "SubJet_vector[0]")
            
            branches = ["HttJet_id", "Htt_rawmass", "Htt_vismass_corr", "Htt_vismass_corr_fromsd", "Htt_vismass_sd", 
                        "HttJet_particleNet_XttVsQCD",
                        "n_veto_ele", "n_veto_muon",
                        "N_SubJet_Matched"]
            
            return df, branches

def HtautauMassRDF(*args, **kwargs):
    return lambda: HtautauMassRDFProducer(*args, **kwargs)
