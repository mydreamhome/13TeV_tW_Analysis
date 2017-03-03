#include <memory>
#include"stdio.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include <TH1F.h>
#include <TROOT.h>
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"
#include <TSystem.h>
#include <TLorentzVector.h>

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"

using namespace std;

#include "Electron.hh"
#include "genINFO.hh"
#include "Muon.hh"
#include "Met.hh"
#include "Jet.hh"
#include "Collection.hh"
#include "Histos.hh"
#include "Vertex.hh"
#include "HLT.hh"
#include "ElectronMuon.hh"
#include "ElectronMuonOppChrg.hh"
#include "ElectronMuonExtraLoose.hh"
#include "Mllcut.hh"
#include "ElMuMet.hh"
#include "JetSelection.hh"

int main(int argc, char* argv[])
{
  // ----------------------------------------------------------------------
  // First Part: 
  //
  //  * enable the AutoLibraryLoader 
  //  * book the histograms of interest 
  //  * open the input file
  // ----------------------------------------------------------------------

  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  FWLiteEnabler::enable();
    
    int n=2;
    //int s=atoi(argv[2]);
    //int n=atoi(argv[3]);
    //int jobid=atoi(argv[1]);
    
    char fname[160];
    
    Electron*  ep=0;
    Electron*  epf1=0;
    Electron*  epf2=0;
    Muon*  mp=0;
    Muon*  mpf1=0;
    Muon*  mpf2=0;
    Met* metp=0;
    Met* metpf=0;
    Jet* jp=0;
    Jet* jploose=0;
    Jet* jpcleaning=0;
    Jet* jp1j=0;
    Jet* jp1j1b=0;
    Jet* jp2j=0;
    Jet* jp2j1b=0;
    Jet* jp2j2b=0;
    Vertex* vtx=0;
    Vertex* fvtx=0;
    HLT* uhlt=0;
    HLT* fhlt=0;
    genINFO* genWeiInf=0;
    //EMu channel
    ElectronMuon*  emp=0;
    ElectronMuonOppChrg* empOppChrg=0;
    ElectronMuonExtraLoose* empel=0;
    Mllcut* obpMllCut=0;
    ElectronMuonMet* obpEMM=0;
    JetSelection* empAtleast1Ljet=0;
    JetSelection* empAtleast1Cljet=0;
    JetSelection* emp1jet=0;
    JetSelection* emp1jet1b=0;
    JetSelection* empAtleast2Ljet=0;
    JetSelection* empAtleast2Cljet=0;
    JetSelection* emp2jet=0;
    JetSelection* emp2jet1b=0;
    JetSelection* emp2jet2b=0;
 /*   //2e channel
    ElectronMuon*  emp2e=0;
    ElectronMuonOppChrg* empOppChrg2e=0;
    ElectronMuonExtraLoose* empel2e=0;
    Mllcut* obpMllCut2e=0;
    ElectronMuonMet* obpEMM2e=0;
    JetSelection* emp1jet2e=0;
    JetSelection* emp1jet1b2e=0;
    JetSelection* emp2jet2e=0;
    JetSelection* emp2jet1b2e=0;
    JetSelection* emp2jet2b2e=0;
    //2mu channel
    ElectronMuon*  emp2mu=0;
    ElectronMuonOppChrg* empOppChrg2mu=0;
    ElectronMuonExtraLoose* empel2mu=0;
    Mllcut* obpMllCut2mu=0;
    ElectronMuonMet* obpEMM2mu=0;
    JetSelection* emp1jet2mu=0;
    JetSelection* emp1jet1b2mu=0;
    JetSelection* emp2jet2mu=0;
    JetSelection* emp2jet1b2mu=0;
    JetSelection* emp2jet2b2mu=0;
    */
    fwlite::TFileService fs = fwlite::TFileService("antiTop.root");
    //char ofname[200];
    //sprintf(ofname,"ttBar_%d.root",jobid);
    //fwlite::TFileService fs = fwlite::TFileService(ofname);
    
    TTree* t1 = Histos::getHistPointers(fs, "electronMuon_class_EMu", 1);
   // TTree* t2 = Histos::getHistPointers(fs, "electronMuon_class_2e", 2);
   // TTree* t3 = Histos::getHistPointers(fs, "electronMuon_class_2mu", 3);
    TTree* t4 = Histos::getHistPointers(fs, "oppositeCharge_class_EMu", 1);
   // TTree* t5 = Histos::getHistPointers(fs, "oppositeCharge_class_2e", 2);
   // TTree* t6 = Histos::getHistPointers(fs, "oppositeCharge_class_2mu", 3);
    TTree* t7 = Histos::getHistPointers(fs, "extraLooseVeto_class_EMu", 1);
   // TTree* t8 = Histos::getHistPointers(fs, "extraLooseVeto_class_2e", 2);
   // TTree* t9 = Histos::getHistPointers(fs, "extraLooseVeto_class_2mu", 3);
    TTree* t10 = Histos::getHistPointers(fs, "mllCut_class_EMu", 1);
   // TTree* t11 = Histos::getHistPointers(fs, "mllCut_class_2e", 2);
   // TTree* t12 = Histos::getHistPointers(fs, "mllCut_class_2mu", 3);
    TTree* t13 = Histos::getHistPointers(fs, "metCut_class_EMu", 1);
   // TTree* t14 = Histos::getHistPointers(fs, "metCut_class_2e", 2);
   // TTree* t15 = Histos::getHistPointers(fs, "metCut_class_2mu", 3);
    
    TTree* t16 = Electron::getHistPointers(fs, "ElectronClass");
    TTree* t17 = Muon::getHistPointers(fs, "MuonClass");
    TTree* t18 = Jet::getHistPointers(fs, "JetClass");
    TTree* t34 = Vertex::getHistPointers(fs, "VertexClass");
    TTree* t39 = genINFO::getHistPointers(fs, "GenInfoClass");
    
    TTree* t19 = Histos::getHistPointers(fs, "em1JetSelection_EMu", 1);
    TTree* t20 = Histos::getHistPointers(fs, "em1Jet1tagSelection_EMu", 1);
    TTree* t21 = Histos::getHistPointers(fs, "em2JetSelection_EMu", 1);
    TTree* t22 = Histos::getHistPointers(fs, "em2Jet1tagSelection_EMu", 1);
    TTree* t23 = Histos::getHistPointers(fs, "em2Jet2tagSelection_EMu", 1);
    
   // TTree* t24 = Histos::getHistPointers(fs, "em1JetSelection_2e", 2);
   // TTree* t25 = Histos::getHistPointers(fs, "em1Jet1tagSelection_2e", 2);
  //  TTree* t26 = Histos::getHistPointers(fs, "em2JetSelection_2e", 2);
   /* TTree* t27 = Histos::getHistPointers(fs, "em2Jet1tagSelection_2e", 2);
    TTree* t28 = Histos::getHistPointers(fs, "em2Jet2tagSelection_2e", 2);
    
    TTree* t29 = Histos::getHistPointers(fs, "em1JetSelection_2mu", 3);
    TTree* t30 = Histos::getHistPointers(fs, "em1Jet1tagSelection_2mu", 3);
    TTree* t31 = Histos::getHistPointers(fs, "em2JetSelection_2mu", 3);
    TTree* t32 = Histos::getHistPointers(fs, "em2Jet1tagSelection_2mu", 3);
    TTree* t33 = Histos::getHistPointers(fs, "em2Jet2tagSelection_2mu", 3);
    */
    
    TTree* t35 = Histos::getHistPointers(fs, "emAtleast1LJetSelection_EMu", 1);
    TTree* t36 = Histos::getHistPointers(fs, "emAtleast1ClJetSelection_EMu", 1);
    TTree* t37 = Histos::getHistPointers(fs, "emAtleast2LJetSelection_EMu", 1);
    TTree* t38 = Histos::getHistPointers(fs, "emAtleast2ClJetSelection_EMu", 1);
    
    int ctotalevts=0,cVertexEv=0,cTTE=0,cEW1e=0,cEW2e=0,cTTM=0,cEW1m=0,cEW2m=0,cTLj=0,cEwanyLj=0,cE1Lj=0,cE1j1t=0,cE2Lj=0,cE2j1t=0,cE2j2t=0,c1E1M=0,c2E=0,c2M=0,cOppChrg1e1m=0,cOppChrg2e=0,cOppChrg2m=0,cExLoose1e1m=0,cExLoose2e=0,cExLoose2m=0,cmllc1e1m=0, cmllc2e=0, cmllc2m=0, cMetCut=0,cEMuMet1e1m=0,cEMuMet2e=0,cEMuMet2m=0,cSelect1jem=0,cSelect1j1btem=0,cSelect2jem=0,cSelect2j1btem=0,cSelect2j2btem=0,cSelect1j2e=0,cSelect1j1bt2e=0,cSelect2j2e=0,cSelect2j1bt2e=0,cSelect2j2bt2e=0,cSelect1j2m=0,cSelect1j1bt2m=0,cSelect2j2m=0,cSelect2j1bt2m=0,cSelect2j2bt2m=0,cToClj=0,cEClj=0,cEwAtleast1jLemu=0,cEwAtleast2jLemu=0,cEwAtleast1jClemu=0,cEwAtleast2jClemu=0,cTHltEv=0;
    double cNetEvWt=0.0;
    
   // for(int i=s;i<=n;i++)
    for(int i=1;i<=n;i++)
    {
	//char constName[]="/afs/cern.ch/work/p/ppriyank/private/816Code/CMSSW_8_0_16/src/B2GEDMNtuple_";
    ///////datas
    //char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/2016B/MuonEG/crab_2016B/170209_115443/0000/B2GEDMNtuple_";
    //char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/2016C/MuonEG/crab_2016C/170209_120857/0000/B2GEDMNtuple_";
    //char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/2016D/MuonEG/crab_2016D/170209_121828/0000/B2GEDMNtuple_";
    //char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/2016E/MuonEG/crab_2016E/170209_130319/0000/B2GEDMNtuple_";
  //  char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/2016F/MuonEG/crab_2016F/170209_134155/0000/B2GEDMNtuple_";
  //  char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/2016G/MuonEG/crab_2016G/170209_142904/0000/B2GEDMNtuple_";
  //  char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/2016H2/MuonEG/crab_2016H2/170209_180745/0000/B2GEDMNtuple_";
  //  char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/2016H3/MuonEG/crab_2016H3/170209_182434/0000/B2GEDMNtuple_";
    
    ///////////mcs
    char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/tWtop/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_tWtop/170301_124858/0000/B2GEDMNtuple_";
	//char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/tWtop/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/crab_tWtop/170207_130603/0000/B2GEDMNtuple_";
    //char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/tWantiTop/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/crab_tWantiTop/170207_130746/0000/B2GEDMNtuple_";
    //char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/ttBar/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_ttBar/170207_130836/0000/B2GEDMNtuple_";
    //char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/DY10to50/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DY10to50/170207_131035/0000/B2GEDMNtuple_";
    //char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/DYabove50/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYabove50/170207_130929/0000/B2GEDMNtuple_";
    //char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/WPjets/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WPjets/170207_131406/0000/B2GEDMNtuple_";
   // char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/WW/WW_TuneCUETP8M1_13TeV-pythia8/crab_WW/170207_131132/0000/B2GEDMNtuple_";
   // char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/ZZ/ZZ_TuneCUETP8M1_13TeV-pythia8/crab_ZZ/170207_131315/0000/B2GEDMNtuple_";
   // char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/WZ/WZ_TuneCUETP8M1_13TeV-pythia8/crab_WZ/170207_131224/0000/B2GEDMNtuple_";
    //char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/tChnlTop/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/crab_tChnlTop/170207_131459/0000/B2GEDMNtuple_";
   // char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/tChnlAntiTop/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/crab_tChnlAntiTop/170208_055151/0000/B2GEDMNtuple_";
   // char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/sChnl/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_sChnl/170207_131653/0000/B2GEDMNtuple_";
        
    try
        {
        sprintf(fname,"%s%d.root",constName,i);
        cout<<"File Name:"<<fname<<endl;
        
        genWeiInf = new genINFO();
        genWeiInf->setData(fname);
        genWeiInf->fillHisto(t39);
        cNetEvWt += genWeiInf->getcnetEvWt();
        
        uhlt = new HLT();
        uhlt->setData(fname);
        fhlt = new HLT(uhlt->selectData());
        cTHltEv += uhlt->getTHltEv();
        
        vtx = new Vertex();
        vtx->setData(fname);
        fvtx = new Vertex(vtx->selectData());
        vtx->fillHisto(t34);
        cVertexEv += vtx->getTVerEv();
            
        ep = new Electron();
        ep->setData(fname);
        epf1 = new Electron(ep->selectData1());
        epf2 = new Electron(ep->selectData2());
        ep->fillHisto(t16);
        cTTE += ep->getTTE();
        cEW1e += ep->getEW1E();
        cEW2e += ep->getEW2E();
        
        mp = new Muon();
        mp->setData(fname);
        mpf1 = new Muon(mp->selectData1());
        mpf2 = new Muon(mp->selectData2());
        mp->fillHisto(t17);
        cTTM += mp->getTTM();
        cEW1m += mp->getEW1M();
        cEW2m += mp->getEW2M();
        
        metp = new Met();
        metp->setData(fname);
        metpf = new Met(metp->selectData());
        cMetCut += metp->getEWMetCut();
        
        jp = new Jet();
        jp->setData(fname);
   //     cout<<"1             :"<< endl;
        jploose = new Jet(jp->selectDataLooseJet());
   //     cout<<"2             :"<< endl;
        jpcleaning = new Jet(jp->selectDataCleaning(*epf1,*mpf1,*jploose));
   //     cout<<"3             :"<< endl;
        jp->fillHisto(t18);
    //    cout<<"4             :"<< endl;
        jp1j = new Jet(jp->selectData1ljPtEta(*jpcleaning));
     //   cout<<"5             :"<< endl;
        jp1j1b = new Jet(jp->selectData1j1b(*jp1j));
      //  cout<<"6             :"<< endl;
        jp2j = new Jet(jp->selectData2ljPtEta(*jpcleaning));
        jp2j1b = new Jet(jp->selectData2j1b(*jp2j));
        jp2j2b = new Jet(jp->selectData2j2b(*jp2j));
     //   cout<<"7             :"<< endl;
        ctotalevts += jp->gettotalevts();
        cTLj += jp->getTLj();
        cEwanyLj += jp->getEwanyLj();
        cToClj += jp->getTotalCleanedj();
        cEClj += jp->getEwCleanedj();
        cE1Lj += jp->getE1Lj();
        cE1j1t += jp->getE1j1t();
        cE2Lj += jp->getE2Lj();
        cE2j1t += jp->getE2j1t();
        cE2j2t += jp->getE2j2t();
            
        //EMu channel
        emp = new ElectronMuon();
       // cout<<"8             :"<< endl;
        emp->setData1(*epf1,*mpf1,*ep,*mp,*metp,*jploose,*fvtx,*vtx,*jpcleaning,*fhlt,*genWeiInf);
        emp->Histos::fillHisto(t1, 1,emp->v);
        c1E1M += emp->getEW1E1M();
      //  cout<<"9             :"<< endl;
        empOppChrg = new ElectronMuonOppChrg();
        empOppChrg->setData(*emp);
        empOppChrg->Histos::fillHisto(t4, 1,empOppChrg->v);
        cOppChrg1e1m += empOppChrg->getEWOppChrg();
        
        empel = new ElectronMuonExtraLoose();
        empel->setData1(*empOppChrg,*ep,*mp);
        empel->Histos::fillHisto(t7, 1,empel->v);
        cExLoose1e1m += empel->getEWExLoose1e1m();
        
        obpMllCut = new Mllcut();
        obpMllCut->setData1e1m(*empel);
        obpMllCut->Histos::fillHisto(t10, 1,obpMllCut->v);
        cmllc1e1m += obpMllCut->getEWcmllc();
        
        obpEMM = new ElectronMuonMet();
        obpEMM->setData(*obpMllCut,*metp);
        obpEMM->Histos::fillHisto(t13, 1,obpEMM->v);
        cEMuMet1e1m += obpEMM->getEMuMet();
       // cout<<"10             :"<< endl;
            
        empAtleast1Ljet = new JetSelection();
        empAtleast1Ljet->setDataAtleast1j(*obpEMM,*jploose);
        empAtleast1Ljet->Histos::fillHisto(t35, 1,empAtleast1Ljet->v);
        cEwAtleast1jLemu += empAtleast1Ljet->getAtleast1j();
        
        empAtleast1Cljet = new JetSelection();
        empAtleast1Cljet->setDataAtleast1j(*obpEMM,*jpcleaning);
        empAtleast1Cljet->Histos::fillHisto(t36, 1,empAtleast1Cljet->v);
        cEwAtleast1jClemu += empAtleast1Cljet->getAtleast1j();
        
      /*  emp1jet = new JetSelection();
        emp1jet->setData1j(*obpEMM,*jp1j);
        emp1jet->Histos::fillHisto(t19, 1,emp1jet->v);
        cSelect1jem += emp1jet->get1j();*/
        
            emp1jet = new JetSelection();
            emp1jet->setData1j(*obpEMM,*jp1j);
            emp1jet->Histos::fillHisto(t19, 1,emp1jet->v);
            cSelect1jem += emp1jet->get1j();
      
        emp1jet1b = new JetSelection();
        emp1jet1b->setData1j(*obpEMM,*jp1j1b);
        emp1jet1b->Histos::fillHisto(t20, 1,emp1jet1b->v);
        cSelect1j1btem += emp1jet1b->get1j();
        
        empAtleast2Ljet = new JetSelection();
        empAtleast2Ljet->setDataAtleast2j(*obpEMM,*jploose);
        empAtleast2Ljet->Histos::fillHisto(t37, 1,empAtleast2Ljet->v);
        cEwAtleast2jLemu += empAtleast2Ljet->getAtleast2j();
        
        empAtleast2Cljet = new JetSelection();
        empAtleast2Cljet->setDataAtleast2j(*obpEMM,*jpcleaning);
        empAtleast2Cljet->Histos::fillHisto(t38, 1,empAtleast2Cljet->v);
        cEwAtleast2jClemu += empAtleast2Cljet->getAtleast2j();
        
       /* emp2jet = new JetSelection();
        emp2jet->setData2j(*obpEMM,*jp2j);
        emp2jet->Histos::fillHisto(t21, 1,emp2jet->v);
        cSelect2jem += emp2jet->get2j();*/
        
            emp2jet = new JetSelection();
            emp2jet->setData2j(*obpEMM,*jp2j);
            emp2jet->Histos::fillHisto(t21, 1,emp2jet->v);
            cSelect2jem += emp2jet->get2j();
        
        emp2jet1b = new JetSelection();
        emp2jet1b->setData2j(*obpEMM,*jp2j1b);
        emp2jet1b->Histos::fillHisto(t22, 1,emp2jet1b->v);
        cSelect2j1btem += emp2jet1b->get2j();
        
        emp2jet2b = new JetSelection();
        emp2jet2b->setData2j(*obpEMM,*jp2j2b);
        emp2jet2b->Histos::fillHisto(t23, 1,emp2jet2b->v);
        cSelect2j2btem += emp2jet2b->get2j();
        
        /*//2e channel
        emp2e = new ElectronMuon();
        emp2e->setData2(*epf2,*ep,*mp,*metp,*jploose,*fvtx,*vtx);
        emp2e->Histos::fillHisto(t2, 2,emp2e->v);
        c2E += emp2e->getEW2E();
        
        empOppChrg2e = new ElectronMuonOppChrg();
        empOppChrg2e->setData(*emp2e);
        empOppChrg2e->Histos::fillHisto(t5, 2,empOppChrg2e->v);
        cOppChrg2e += empOppChrg2e->getEWOppChrg();
        
        empel2e = new ElectronMuonExtraLoose();
        empel2e->setData2(*empOppChrg2e,*ep,*mp);
        empel2e->Histos::fillHisto(t8, 2,empel2e->v);
        cExLoose2e += empel2e->getEWExLoose2e();
        
        obpMllCut2e = new Mllcut();
        obpMllCut2e->setData(*empel2e);
        obpMllCut2e->Histos::fillHisto(t11, 2,obpMllCut2e->v);
        cmllc2e += obpMllCut2e->getEWcmllc();
        
        obpEMM2e = new ElectronMuonMet();
        obpEMM2e->setData(*obpMllCut2e,*metpf);
        obpEMM2e->Histos::fillHisto(t14, 2,obpEMM2e->v);
        cEMuMet2e += obpEMM2e->getEMuMet();
        
        emp1jet2e = new JetSelection();
        emp1jet2e->setData1j(*obpEMM2e,*jp1j);
        emp1jet2e->Histos::fillHisto(t24, 2,emp1jet2e->v);
        cSelect1j2e += emp1jet2e->get1j();
        
        emp1jet1b2e = new JetSelection();
        emp1jet1b2e->setData1j(*obpEMM2e,*jp1j1b);
        emp1jet1b2e->Histos::fillHisto(t25, 2,emp1jet1b2e->v);
        cSelect1j1bt2e += emp1jet1b2e->get1j();
        
        emp2jet2e = new JetSelection();
        emp2jet2e->setData2j(*obpEMM2e,*jp2j);
        emp2jet2e->Histos::fillHisto(t26, 2,emp2jet2e->v);
        cSelect2j2e += emp2jet2e->get2j();
        
        emp2jet1b2e = new JetSelection();
        emp2jet1b2e->setData2j(*obpEMM2e,*jp2j1b);
        emp2jet1b2e->Histos::fillHisto(t27, 2,emp2jet1b2e->v);
        cSelect2j1bt2e += emp2jet1b2e->get2j();
        
        emp2jet2b2e = new JetSelection();
        emp2jet2b2e->setData2j(*obpEMM2e,*jp2j2b);
        emp2jet2b2e->Histos::fillHisto(t28, 2,emp2jet2b2e->v);
        cSelect2j2bt2e += emp2jet2b2e->get2j();
            
        //2mu channel
        emp2mu = new ElectronMuon();
        emp2mu->setData3(*mpf2,*ep,*mp,*metp,*jploose,*fvtx,*vtx);
        emp2mu->Histos::fillHisto(t3, 3,emp2mu->v);
        c2M += emp2mu->getEW2M();
        
        empOppChrg2mu = new ElectronMuonOppChrg();
        empOppChrg2mu->setData(*emp2mu);
        empOppChrg2mu->Histos::fillHisto(t6, 3,empOppChrg2mu->v);
        cOppChrg2m += empOppChrg2mu->getEWOppChrg();
        
        empel2mu = new ElectronMuonExtraLoose();
        empel2mu->setData3(*empOppChrg2mu,*ep,*mp);
        empel2mu->Histos::fillHisto(t9, 3,empel2mu->v);
        cExLoose2m += empel2mu->getEWExLoose2m();
        
        obpMllCut2mu = new Mllcut();
        obpMllCut2mu->setData(*empel2mu);
        obpMllCut2mu->Histos::fillHisto(t12, 3,obpMllCut2mu->v);
        cmllc2m += obpMllCut2mu->getEWcmllc();
        
        obpEMM2mu = new ElectronMuonMet();
        obpEMM2mu->setData(*obpMllCut2mu,*metpf);
        obpEMM2mu->Histos::fillHisto(t15, 3,obpEMM2mu->v);
        cEMuMet2m += obpEMM2mu->getEMuMet();
        
        emp1jet2mu = new JetSelection();
        emp1jet2mu->setData1j(*obpEMM2mu,*jp1j);
        emp1jet2mu->Histos::fillHisto(t29, 3,emp1jet2mu->v);
        cSelect1j2m += emp1jet2mu->get1j();
        
        emp1jet1b2mu = new JetSelection();
        emp1jet1b2mu->setData1j(*obpEMM2mu,*jp1j1b);
        emp1jet1b2mu->Histos::fillHisto(t30, 3,emp1jet1b2mu->v);
        cSelect1j1bt2m += emp1jet1b2mu->get1j();
        
        emp2jet2mu = new JetSelection();
        emp2jet2mu->setData2j(*obpEMM2mu,*jp2j);
        emp2jet2mu->Histos::fillHisto(t31, 3,emp2jet2mu->v);
        cSelect2j2m += emp2jet2mu->get2j();
        
        emp2jet1b2mu = new JetSelection();
        emp2jet1b2mu->setData2j(*obpEMM2mu,*jp2j1b);
        emp2jet1b2mu->Histos::fillHisto(t32, 3,emp2jet1b2mu->v);
        cSelect2j1bt2m += emp2jet1b2mu->get2j();
        
        emp2jet2b2mu = new JetSelection();
        emp2jet2b2mu->setData2j(*obpEMM2mu,*jp2j2b);
        emp2jet2b2mu->Histos::fillHisto(t33, 3,emp2jet2b2mu->v);
        cSelect2j2bt2m += emp2jet2b2mu->get2j();
       */ 
        delete ep;
        delete epf1;
        delete epf2;
        delete mp;
        delete mpf1;
        delete mpf2;
        delete metp;
        delete metpf;
        delete jp;
        delete jploose;
        delete jpcleaning;
        delete jp1j;
        delete jp1j1b;
        delete jp2j;
        delete jp2j1b;
        delete jp2j2b;
        delete vtx;
        delete fvtx;
        delete uhlt;
        delete fhlt;
        delete genWeiInf;
        //EMu channel
        delete emp;
        delete empOppChrg;
        delete empel;
        delete obpMllCut;
        delete obpEMM;
        delete empAtleast1Ljet;
        delete empAtleast1Cljet;
        delete emp1jet;
        delete emp1jet1b;
        delete empAtleast2Ljet;
        delete empAtleast2Cljet;
        delete emp2jet;
        delete emp2jet1b;
        delete emp2jet2b;
      /*  //2e channel
        delete emp2e;
        delete empOppChrg2e;
        delete empel2e;
        delete obpMllCut2e;
        delete obpEMM2e;
        delete emp1jet2e;
        delete emp1jet1b2e;
        delete emp2jet2e;
        delete emp2jet1b2e;
        delete emp2jet2b2e;
        //2mu channel
        delete emp2mu;
        delete empOppChrg2mu;
        delete empel2mu;
        delete obpMllCut2mu;
        delete obpEMM2mu;
        delete emp1jet2mu;
        delete emp1jet1b2mu;
        delete emp2jet2mu;
        delete emp2jet1b2mu;
        delete emp2jet2b2mu;*/
        }
        catch(exception& e)
        {
            cout<<"error:"<<e.what()<<endl;
            cout<<"File Name:"<<fname<<"is correpted"<<endl<<endl<<endl;
        }
    }
    cout<<"Total number of events processed: "<< ctotalevts <<endl;
    cout<<"Total number of events Weight : "<< cNetEvWt <<endl;
    cout<<"Total number of events passed HLT cuts: "<< cTHltEv <<endl;
    cout<<"Total number of events passed vertex cuts: "<< cVertexEv << endl;
    cout<<"Total number of tight electrons: "<< cTTE <<endl;
    cout<<"Total number of events having only one tight electron: "<< cEW1e <<endl;
    cout<<"Total number of events having exactly two tight electrons: "<< cEW2e <<endl;
    cout<<"Total number of tight muons: "<< cTTM << endl;
    cout<<"Total number of events having only one tight muon: "<< cEW1m << endl;
    cout<<"Total number of events having exactly two tight muons: "<< cEW2m <<endl;
    cout<<"Total number of Mets passing cuts: "<< cMetCut <<endl;
    cout<<"Total number of Loose jets: "<< cTLj << endl;
    cout<<"Total number of events having atleast one Loose jet: "<< cEwanyLj << endl;
    cout<<"Total number of Cleaned jets: "<< cToClj << endl;
    cout<<"Total number of events having atleast one Cleaned jet: "<< cEClj << endl;
    cout<<"Total number of events having exactly 1j: "<< cE1Lj << endl;
    cout<<"Total number of events having exactly 1j1b: "<< cE1j1t << endl;
    cout<<"Total number of events having exactly 2j: "<< cE2Lj << endl;
    cout<<"Total number of events having exactly 2j1b: "<< cE2j1t << endl;
    cout<<"Total number of events having exactly 2j2b: "<< cE2j2t << endl;
    cout<<"Total number of events having only one tight electron and only one tight muon: " << c1E1M <<endl;
    cout<<"Total number of events having only two tight electrons: " << c2E <<endl;
    cout<<"Total number of events having only two tight muons: " << c2M <<endl;
    cout<<"Total number of events having ooposite charge leptons 1e1mu: " << cOppChrg1e1m <<endl;
    cout<<"Total number of events having ooposite charge leptons 2e: " << cOppChrg2e <<endl;
    cout<<"Total number of events having ooposite charge leptons 2mu: " << cOppChrg2m <<endl;
    cout<<"total number of selected events due to extra loose cuts in 1e 1mu : "<<cExLoose1e1m<<endl;
    cout<<"total number of selected events due to extra loose cuts in 2e : "<<cExLoose2e<<endl;
    cout<<"total number of selected events due to extra loose cuts in 2mu : "<<cExLoose2m<<endl;
    cout<<"total number of selected events after mll cuts in 1e 1mu : "<<cmllc1e1m<<endl;
    cout<<"total number of selected events after mll cuts in 2e : "<<cmllc2e<<endl;
    cout<<"total number of selected events after mll cuts in 2mu : "<<cmllc2m<<endl;
    cout<<"total number of selected events due to met passing cut 1e1mu :"<<cEMuMet1e1m<<endl;
    cout<<"total number of selected events due to met passing cut 2e :"<<cEMuMet2e<<endl;
    cout<<"total number of selected events due to met passing cut 2mu :"<<cEMuMet2m<<endl;
    cout<<"total number of selected events due to atleast 1 Loose jet for emu :"<<cEwAtleast1jLemu<<endl;
    cout<<"total number of selected events due to atleast 1 Cleaned jet for emu :"<<cEwAtleast1jClemu<<endl;
    cout<<"total number of selected events due to 1j jet for emu :"<<cSelect1jem<<endl;
    cout<<"total number of selected events due to 1j1b jet for emu :"<<cSelect1j1btem<<endl;
    cout<<"total number of selected events due to atleast 2 Loose jet for emu :"<<cEwAtleast2jLemu<<endl;
    cout<<"total number of selected events due to atleast 2 Cleaned jet for emu :"<<cEwAtleast2jClemu<<endl;
    cout<<"total number of selected events due to 2j jet for emu :"<<cSelect2jem<<endl;
    cout<<"total number of selected events due to 2j1b jet for emu :"<<cSelect2j1btem<<endl;
    cout<<"total number of selected events due to 2j2b jet for emu :"<<cSelect2j2btem<<endl;
    cout<<"total number of selected events due to 1j jet for 2e :"<<cSelect1j2e<<endl;
    cout<<"total number of selected events due to 1j1b jet for 2e :"<<cSelect1j1bt2e<<endl;
    cout<<"total number of selected events due to 2j jet for 2e :"<<cSelect2j2e<<endl;
    cout<<"total number of selected events due to 2j1b jet for 2e :"<<cSelect2j1bt2e<<endl;
    cout<<"total number of selected events due to 2j2b jet for 2e :"<<cSelect2j2bt2e<<endl;
    cout<<"total number of selected events due to 1j jet for 2mu :"<<cSelect1j2m<<endl;
    cout<<"total number of selected events due to 1j1b jet for 2mu :"<<cSelect1j1bt2m<<endl;
    cout<<"total number of selected events due to 2j jet for 2mu :"<<cSelect2j2m<<endl;
    cout<<"total number of selected events due to 2j1b jet for 2mu :"<<cSelect2j1bt2m<<endl;
    cout<<"total number of selected events due to 2j2b jet for 2mu :"<<cSelect2j2bt2m<<endl;
    return 0;
}

                        


