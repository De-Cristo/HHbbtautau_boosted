from analysis_tools.utils import import_root
import os

ROOT = import_root()

class HtautauMassRDFProducer():
    def __init__(self, *args, **kwargs):
        self.isMC = kwargs.pop("isMC", True)
        self.FatJetpTCut = kwargs.pop("FatJetpTCut", 180.0)
        
        base = "{}/src/HHbbtautau_boosted".format(os.getenv("CMSSW_BASE"))
        ROOT.gROOT.ProcessLine(".L {}/interface/HtautauMass.h".format(base))
        ROOT.gInterpreter.Declare(
            '#include "{}/interface/HtautauMass.h"'.format(base)
        )
        
    def run(self, df):
        if not self.isMC:
            return df, []
        else:
            
            df = df.Filter("nFatJet >1")
            df = df.Filter("min_result(FatJet_pt) > {0}".format(self.FatJetpTCut))
            df = df.Define("HttJet_id", "JetID_PNetscore(FatJet_particleNet_XttVsQCD)")
            df = df.Define("Htt_mass","FatJet_mass[HttJet_id]")
            df = df.Define("Htt_mass_vis_forHtt","FatJet_mass[HttJet_id]*FatJet_particleNet_massCorr[HttJet_id]")
            df = df.Define("Htt_mass_vis","FatJet_msoftdrop[HttJet_id]*FatJet_particleNet_massCorr[HttJet_id]")
            df = df.Define("Htt_mass_vis_sd","FatJet_msoftdrop[HttJet_id]")
            
            branches = ["HttJet_id", "Htt_mass", "Htt_mass_vis", "Htt_mass_vis_sd", "Htt_mass_vis_forHtt"]
            return df, branches

def HtautauMassRDF(*args, **kwargs):
    return lambda: HtautauMassRDFProducer(*args, **kwargs)
