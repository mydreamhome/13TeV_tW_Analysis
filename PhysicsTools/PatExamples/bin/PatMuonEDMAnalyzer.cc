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
//#include "HLT.hh"
#include "ElectronMuon.hh"
#include "ElectronMuonOppChrg.hh"
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
    
    int n=7;
    //int s=atoi(argv[2]);
    //int n=atoi(argv[3]);
    //int jobid=atoi(argv[1]);
    
    char fname[160];
    
    Electron*  ep=0;
    Electron*  epf=0;
    Muon*  mp=0;
    Muon*  mpf=0;
    Met* metp=0;
    Jet* jp=0;
    Jet* jploose=0;
    Jet* jpBjet=0;
    Vertex* vtx=0;
    //HLT* uhlt=0;
    //HLT* fhlt=0;
    genINFO* genWeiInf=0;
    //All channels
    ElectronMuon*  emp=0;
    ElectronMuonOppChrg* empOppChrg=0;
    Mllcut* obpMllCut=0;
    ElectronMuonMet* obpEMM=0;
    JetSelection* emp1jet1b=0;
    JetSelection* emp2jet1b=0;
    JetSelection* emp2jet2b=0;
    
    fwlite::TFileService fs = fwlite::TFileService("antiTop.root");
   // char ofname[200];
   // sprintf(ofname,"ttBar_%d.root",jobid);
   // fwlite::TFileService fs = fwlite::TFileService(ofname);
    
   // TTree* t1 = Vertex::getHistPointers(fs, "VertexClass");
    TTree* t2 = genINFO::getHistPointers(fs, "GenInfoClass");
    
   /* TTree* t3 = Histos::getHistPointers(fs, "oppositeCharge_class_EMu", 1);
    TTree* t4 = Histos::getHistPointers(fs, "oppositeCharge_class_2e", 2);
    TTree* t5 = Histos::getHistPointers(fs, "oppositeCharge_class_2mu", 3);
    TTree* t6 = Histos::getHistPointers(fs, "mllCut_class_EMu", 1);
    TTree* t7 = Histos::getHistPointers(fs, "mllCut_class_2e", 2);
    TTree* t8 = Histos::getHistPointers(fs, "mllCut_class_2mu", 3);
    TTree* t9 = Histos::getHistPointers(fs, "metCut_class_EMu", 1);
    TTree* t10 = Histos::getHistPointers(fs, "metCut_class_2e", 2);
    TTree* t11 = Histos::getHistPointers(fs, "metCut_class_2mu", 3);
    TTree* t12 = Histos::getHistPointers(fs, "em1Jet1tagSelection_EMu", 1);
    TTree* t13 = Histos::getHistPointers(fs, "em2Jet1tagSelection_EMu", 1);
    TTree* t14 = Histos::getHistPointers(fs, "em2Jet2tagSelection_EMu", 1);
    TTree* t15 = Histos::getHistPointers(fs, "em1Jet1tagSelection_2e", 2);
    TTree* t16 = Histos::getHistPointers(fs, "em2Jet1tagSelection_2e", 2);
    TTree* t17 = Histos::getHistPointers(fs, "em2Jet2tagSelection_2e", 2);
    TTree* t18 = Histos::getHistPointers(fs, "em1Jet1tagSelection_2mu", 3);
    TTree* t19 = Histos::getHistPointers(fs, "em2Jet1tagSelection_2mu", 3);
    TTree* t20 = Histos::getHistPointers(fs, "em2Jet2tagSelection_2mu", 3);*/
    
    int ctotalevts=0,oppChrgc1E1M=0, oppChrgc2E=0, oppChrgC2M=0, mllCutc1E1M=0, mllCutc2E=0, mllCutC2M=0, metCutc1E1M=0, metCutc2E=0, metCutC2M=0, cnjg2emu=0, cnjg22mu=0, cnjg22e=0, cnjg1emu=0, cnjg12mu=0, cnjg12e=0, cnbjg1emu=0, cnbjg12mu=0, cnbjg12e=0, cnjeq1emu=0, cnjeq12mu=0, cnjeq12e=0, cnbjeq1emu=0, cnbjeq12mu=0, cnbjeq12e=0, cSelect1j1tem=0, cSelect1j1t2m=0, cSelect1j1t2e=0, cSelect2j1tem=0, cSelect2j1t2m=0, cSelect2j1t2e=0, cSelect2j2tem=0, cSelect2j2t2m=0, cSelect2j2t2e=0;
    double cNetEvWt=0.0;
    bool wantBUG = true;
    for(int i=7;i<=n;i++)
    {
    char constName[]="root://eoscms//eos/cms/store/group/phys_top/Priyanka/ttBar/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_ttBar/170302_080613/0000/B2GEDMNtuple_";
    try
        {
        sprintf(fname,"%s%d.root",constName,i);
        cout<<"File Name:"<<fname<<endl;
        if(wantBUG) cout<<"1        :"<< endl;
        genWeiInf = new genINFO();
        genWeiInf->setData(fname);
        genWeiInf->fillHisto(t2);
        cNetEvWt += genWeiInf->getcnetEvWt();
        if(wantBUG) cout<<"2        :"<< endl;
        vtx = new Vertex();
        vtx->setData(fname);
        if(wantBUG) cout<<"3        :"<< endl;
        ep = new Electron();
        ep->setData(fname);
        epf = new Electron(ep->selectData());
        if(wantBUG) cout<<"4        :"<< endl;
        mp = new Muon();
        mp->setData(fname);
        mpf = new Muon(mp->selectData());
        if(wantBUG) cout<<"5        :"<< endl;
        metp = new Met();
        metp->setData(fname);
        if(wantBUG) cout<<"6        :"<< endl;
        emp = new ElectronMuon();
        emp->setData(*epf,*mpf);
        if(wantBUG) cout<<"7        :"<< endl;
        jp = new Jet();
        jp->setData(fname);
        ctotalevts += jp->gettotalevts();
        if(wantBUG) cout<<"8        :"<< endl;
        jploose = new Jet(jp->selectDataLooseJet(*emp));
        if(wantBUG) cout<<"9        :"<< endl;
        jpBjet = new Jet(jp->selectDatabj(*jploose));
        if(wantBUG) cout<<"10        :"<< endl;
        empOppChrg = new ElectronMuonOppChrg();
        empOppChrg->setData(*vtx,*emp,*metp,*jploose,*jpBjet,*genWeiInf);
        oppChrgc1E1M += empOppChrg->getEW1E1M();
        oppChrgc2E += empOppChrg->getEW2E();
        oppChrgC2M += empOppChrg->getEW2M();
        if(wantBUG) cout<<"11        :"<< endl;
        obpMllCut = new Mllcut();
        obpMllCut->setData(*empOppChrg);
        mllCutc1E1M += obpMllCut->getEW1E1M();
        mllCutc2E += obpMllCut->getEW2E();
        mllCutC2M += obpMllCut->getEW2M();
        if(wantBUG) cout<<"12        :"<< endl;
        obpEMM = new ElectronMuonMet();
        obpEMM->setData(*obpMllCut);
        metCutc1E1M += obpEMM->getEW1E1M();
        metCutc2E += obpEMM->getEW2E();
        metCutC2M += obpEMM->getEW2M();
        if(wantBUG) cout<<"13        :"<< endl;
        emp1jet1b = new JetSelection();
        emp1jet1b->setData1j1t(*obpEMM,*jploose);
        cSelect1j1tem += emp1jet1b->get1j1tem();
        cSelect1j1t2m += emp1jet1b->get1j1t2m();
        cSelect1j1t2e += emp1jet1b->get1j1t2e();
        if(wantBUG) cout<<"14        :"<< endl;
        cnjg2emu += emp1jet1b->getcnjg2emu();
        cnjg22mu += emp1jet1b->getcnjg22mu();
        cnjg22e += emp1jet1b->getcnjg22e();
        cnjg1emu += emp1jet1b->getcnjg1emu();
        cnjg12mu += emp1jet1b->getcnjg12mu();
        cnjg12e += emp1jet1b->getcnjg12e();
        cnbjg1emu += emp1jet1b->getcnbjg1emu();
        cnbjg12mu += emp1jet1b->getcnbjg12mu();
        cnbjg12e += emp1jet1b->getcnbjg12e();
        cnjeq1emu += emp1jet1b->getcnjeq1emu();
        cnjeq12mu += emp1jet1b->getcnjeq12mu();
        cnjeq12e += emp1jet1b->getcnjeq12e();
        cnbjeq1emu += emp1jet1b->getcnbjeq1emu();
        cnbjeq12mu += emp1jet1b->getcnbjeq12mu();
        cnbjeq12e += emp1jet1b->getcnbjeq12e();
        if(wantBUG) cout<<"15        :"<< endl;
        emp2jet1b = new JetSelection();
        emp2jet1b->setData2j1t(*obpEMM,*jploose);
        cSelect2j1tem += emp2jet1b->get2j1tem();
        cSelect2j1t2m += emp2jet1b->get2j1t2m();
        cSelect2j1t2e += emp2jet1b->get2j1t2e();
        if(wantBUG) cout<<"16        :"<< endl;
        emp2jet2b = new JetSelection();
        emp2jet2b->setData2j2t(*obpEMM,*jploose);
        cSelect2j2tem += emp2jet2b->get2j2tem();
        cSelect2j2t2m += emp2jet2b->get2j2t2m();
        cSelect2j2t2e += emp2jet2b->get2j2t2e();
        if(wantBUG) cout<<"17        :"<< endl;
        
        delete ep;
        delete epf;
        delete mp;
        delete mpf;
        delete metp;
        delete jp;
        delete jploose;
        delete jpBjet;
        delete vtx;
        //delete uhlt;
        //delete fhlt;
        delete genWeiInf;
        //All channel
        delete emp;
        delete empOppChrg;
        delete obpMllCut;
        delete obpEMM;
        delete emp1jet1b;
        delete emp2jet1b;
        delete emp2jet2b;
        }
        catch(exception& e)
        {
            cout<<"error:"<<e.what()<<endl;
            cout<<"File Name:"<<fname<<"is correpted"<<endl<<endl<<endl;
        }
    }
    cout<<"Total number of events processed: "<< ctotalevts <<endl;
    cout<<"Total number of events Weight : "<< cNetEvWt <<endl;
    cout<<"Total number of events having ooposite charge leptons 1e1mu: " << oppChrgc1E1M <<endl;
    cout<<"Total number of events having ooposite charge leptons 2e: " << oppChrgc2E <<endl;
    cout<<"Total number of events having ooposite charge leptons 2mu: " << oppChrgC2M <<endl;
    cout<<"total number of selected events after mll cuts in 1e 1mu : "<<mllCutc1E1M<<endl;
    cout<<"total number of selected events after mll cuts in 2e : "<<mllCutc2E<<endl;
    cout<<"total number of selected events after mll cuts in 2mu : "<<mllCutC2M<<endl;
    cout<<"total number of selected events due to met passing cut 1e1mu :"<<metCutc1E1M<<endl;
    cout<<"total number of selected events due to met passing cut 2e :"<<metCutc2E<<endl;
    cout<<"total number of selected events due to met passing cut 2mu :"<<metCutC2M<<endl;
    cout<<"total number of selected events due to 1j1b jet for emu :"<<cSelect1j1tem<<endl;
    cout<<"total number of selected events due to 1j1b jet for 2e :"<<cSelect1j1t2e<<endl;
    cout<<"total number of selected events due to 1j1b jet for 2mu :"<<cSelect1j1t2m<<endl;
    cout<<"total number of selected events due to 2j1b jet for emu :"<<cSelect2j1tem<<endl;
    cout<<"total number of selected events due to 2j1b jet for 2e :"<<cSelect2j1t2e<<endl;
    cout<<"total number of selected events due to 2j1b jet for 2mu :"<<cSelect2j1t2m<<endl;
    cout<<"total number of selected events due to 2j2b jet for emu :"<<cSelect2j2tem<<endl;
    cout<<"total number of selected events due to 2j2b jet for 2e :"<<cSelect2j2t2e<<endl;
    cout<<"total number of selected events due to 2j2b jet for 2mu :"<<cSelect2j2t2m<<endl;
    cout<<"jet > 2 for emu :"<<cnjg2emu<<endl;
    cout<<"jet > 2 for 2mu :"<<cnjg22mu<<endl;
    cout<<"jet > 2 for 2e :"<<cnjg22e<<endl;
    cout<<"jet > 1 for emu :"<<cnjg1emu<<endl;
    cout<<"jet > 1 for 2mu :"<<cnjg12mu<<endl;
    cout<<"jet > 1 for 2e :"<<cnjg12e<<endl;
    cout<<"b-jet > 1 for emu :"<<cnbjg1emu<<endl;
    cout<<"b-jet > 1 for 2mu :"<<cnbjg12mu<<endl;
    cout<<"b-jet > 1 for 2e :"<<cnbjg12e<<endl;
    cout<<"jet = 1 for emu :"<<cnjeq1emu<<endl;
    cout<<"jet = 1 for 2mu :"<<cnjeq12mu<<endl;
    cout<<"jet = 1 for 2e :"<<cnjeq12e<<endl;
    cout<<"b-jet = 1 for emu :"<<cnbjeq1emu<<endl;
    cout<<"b-jet = 1 for 2mu :"<<cnbjeq12mu<<endl;
    cout<<"b-jet = 1 for 2e :"<<cnbjeq12e<<endl;
    return 0;
}

                        


