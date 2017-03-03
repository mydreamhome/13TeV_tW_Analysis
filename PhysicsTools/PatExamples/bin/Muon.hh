class ElectronMuon;
class ElectronMuonOppChrg;
class ElectronMuonExtraLoose;
class ElectronMuonMet;
class Mllcut;
class Jet;

class Muon
{
   /* struct CUT
    {
        bool   particleFlowc,globalMuonc,trackerMuonc,etac,ptc,isoc,all;
    };*/
    struct DATA
    {
        float  mID,eta,pt,iso,charge,phi,tight,loose,energy;
        bool   etac,ptc,letac,lptc,isolc,isotc,tightc,loosec,all,lall,lextraloose,textraloose;
       // CUT    loose,tight;
    };
    
    vector<vector<DATA>*>*  v;
    vector<int>* LeptMult;
    int cTTM,cEW1M,cEW2M;
public:
    static vector<double> muonMult_;
    static vector<double> beforeMuonMult_;
    
    Muon()
    {
        v = new vector<vector<DATA>*>;
        LeptMult = new vector<int>;
    }
    Muon(vector<vector<DATA>*>* uv)
    {
        v=uv;
        LeptMult = new vector<int>;
    }
    int getTTM(){return cTTM;}
    int getEW1M(){return cEW1M;}
    int getEW2M(){return cEW2M;}
    
    void setData(const char* fname)
    {
        TFile* inFile = TFile::Open(fname);
        
        if(!inFile)
        {
            cout<<"Input Root File not open in muon class for processing"<<endl;
            return;
        }
        
        fwlite::Event ev(inFile);
        int evtID=0;
        
        for(ev.toBegin(); !ev.atEnd(); ++ev, evtID++)
        {
            edm::EventBase const & event = ev;
            
         /*   // Handle to the muon ParticleFlow
            edm::Handle<std::vector<float> > ParticleFlow;
            event.getByLabel(std::string("muons:muIsPFMuon"), ParticleFlow);
            // Handle to the muon GlobalMuon
            edm::Handle<std::vector<float> > GlobalMuon;
            event.getByLabel(std::string("muons:muIsGlobalMuon"), GlobalMuon);
            // Handle to the muon TrackerMuon
            edm::Handle<std::vector<float> > TrackerMuon;
            event.getByLabel(std::string("muons:muIsTrackerMuon"), TrackerMuon);*/
            // Handle to the muon muonPt
            edm::Handle<std::vector<float> > muonPt;
            event.getByLabel(std::string("muons:muPt"), muonPt);
            // Handle to the muon muonEta
            edm::Handle<std::vector<float> > muonEta;
            event.getByLabel(std::string("muons:muEta"), muonEta);
            // Handle to the muon muonIso04
            edm::Handle<std::vector<float> > muonIso04;
            event.getByLabel(std::string("muons:muIso04"), muonIso04);
            // Handle to the muon charge
            edm::Handle<std::vector<float> > muonCharge;
            event.getByLabel(std::string("muons:muCharge"), muonCharge);
            // Handle to the muon charge
            edm::Handle<std::vector<float> > muonPhi;
            event.getByLabel(std::string("muons:muPhi"), muonPhi);
            // Handle to the muon tight
           /* edm::Handle<std::vector<float> > muonTight;
            event.getByLabel(std::string("muons:muIsMediumMuon"), muonTight);*/
            edm::Handle<std::vector<float> > muonTight;
            event.getByLabel(std::string("muons:muIsTightMuon"), muonTight);
            // Handle to the muon loose
           /* edm::Handle<std::vector<float> > muonLoose;
            event.getByLabel(std::string("muons:muIsLooseMuon"), muonLoose);*/
            edm::Handle<std::vector<float> > muonLoose;
            event.getByLabel(std::string("muons:muIsMediumMuon"), muonLoose);
            // Handle to the muon energy
            edm::Handle<std::vector<float> > muonEn;
            event.getByLabel(std::string("muons:muE"), muonEn);
            
            vector<DATA>* dv = new vector<DATA>;
            DATA d;
            
            for(unsigned int i=0;i<muonPt->size();i++)
            {
                d.mID = i;
             /*   d.particleFlow = ParticleFlow->at(i);
                d.globalMuon = GlobalMuon->at(i);
                d.trackerMuon = TrackerMuon->at(i);*/
                d.pt = muonPt->at(i);
                d.eta = muonEta->at(i);
                d.iso  = muonIso04->at(i);
                d.charge = muonCharge->at(i);
                d.phi = muonPhi->at(i);
                d.tight = muonTight->at(i);
                d.loose = muonLoose->at(i);
                d.energy = muonEn->at(i);
                dv->push_back(d);
                
            }
            
            
            v->push_back(dv);
            
        }
        inFile->Close();
        
        setCuts();
        
        return;
    }
    
    vector<vector<DATA>*>* selectData1()
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events = 0;
        int totalTightMuons = 0;
        for(unsigned int i=0; i < v->size(); i++)
        {
            int muon_number = 0;
            vector<DATA>* fdv= new vector<DATA>;
            
            dv=v->at(i);
            
            bool isEventSelected=false;
            int tightCount=0;
            
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                
                if(d.tightc && d.all)
                {
                    totalTightMuons++;
                    muon_number = j;
                  tightCount++;
                }
            }
            
            LeptMult->push_back(tightCount);
            
            if(tightCount==1){isEventSelected=true;//cout<<i<<" Reject2"<<endl;
            }
            //-----------------------
            if(isEventSelected)
            {
                events++;
                    d=dv->at(muon_number);
                    
                      //  cout<<"Selected (on basis of only 1 tight muon) EventID: "<<i<<"  S MuonID: "<<muon_number<<endl;
                        fdv->push_back(d);
                        // only fill one tight muon's information
                
            }
            //-------------------------
            fv->push_back(fdv);
        }
    //    cout<<"Total number of tight muons: "<< totalTightMuons << endl;
      //  cout<<"Total number of events having only one tight muon: "<< events << endl;
        cTTM=totalTightMuons;
        cEW1M=events;
        return fv;
    }
    
    vector<vector<DATA>*>* selectData2()
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events =0;
        int totalTightMuons =0;
        for(unsigned int i=0; i < v->size(); i++)
        {
            int muon_number1 = 0;
            int muon_number2 = 0;
            
            vector<DATA>* fdv= new vector<DATA>;
            
            dv=v->at(i);
            
            bool isEventSelected=false;
            int tightCount=0;
            
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                
                if(d.tightc && d.all)
                {
                    totalTightMuons++;
                    if(tightCount==0) muon_number1 = j;
                    if(tightCount==1) muon_number2 = j;
                    tightCount++;
                }
            }
            
            if(tightCount==2){isEventSelected=true;//cout<<i<<" Reject2"<<endl;
            }
            //-----------------------
            if(isEventSelected)
            {
                events++;
                d=dv->at(muon_number1);
                fdv->push_back(d);
                d=dv->at(muon_number2);
                //  cout<<"Selected (on basis of only 1 tight electron) EventID: "<<i<<"  S ElectronID: "<<elctron_number<<endl;
                fdv->push_back(d);
                // only fill one tight electron's information
                
            }
            //-------------------------
            fv->push_back(fdv);
        }
       // cout<<"Total number of tight muons: "<< totalTightMuons <<endl;
    //    cout<<"Total number of events having exactly two tight muons: "<< events <<endl;
        cEW2M=events;
        return fv;
    }
    
    void setCuts()
    {
        
        vector<DATA>* dv;
        
     /*   int tParticle_Flow_Muon_Cut = 1;
        int tGlobal_Muon_Cut = 1;
        int tTracker_Muon_Cut = 1;*/
        float tMuon_Tight_Cut_pt = 20.0;
        float tMuon_Tight_Cut_eta = 2.4;
        float lMuon_Tight_Cut_pt = 10.0;
        float lMuon_Tight_Cut_eta = 2.5;
        float tMuon_Relative_Isolation_Cut = 0.15;
        float lMuon_Relative_Isolation_Cut = 0.25;
        
       /* int lParticle_Flow_Muon_Cut = 1;
        int lGlobal_Muon_Cut = 1;
        int lTracker_Muon_Cut = 1;*/
   //     float lMuon_Tight_Cut_pt = 10.0;
   //     float lMuon_Tight_Cut_eta = 2.4;
    //    float lMuon_Relative_Isolation_Cut = 0.20;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                DATA& d=dv->at(j);
                
    //            d.tight.particleFlowc = (d.particleFlow == tParticle_Flow_Muon_Cut)?true:false;
      //          d.tight.globalMuonc = (d.globalMuon == tGlobal_Muon_Cut)?true:false;
        //        d.tight.trackerMuonc = (d.trackerMuon == tTracker_Muon_Cut)?true:false;
                d.ptc = (d.pt > tMuon_Tight_Cut_pt)?true:false;
                d.etac = (fabs( d.eta ) < tMuon_Tight_Cut_eta)?true:false;
                d.lptc = (d.pt > lMuon_Tight_Cut_pt)?true:false;
                d.letac = (fabs( d.eta ) < lMuon_Tight_Cut_eta)?true:false;
                d.isotc = (d.iso < tMuon_Relative_Isolation_Cut)?true:false;
                d.isolc = (d.iso < lMuon_Relative_Isolation_Cut)?true:false;
                d.all = d.ptc && d.etac;
                d.lall = d.lptc && d.letac;
                
                d.tightc = ((d.tight != 0)?true:false) && d.isotc;
                d.loosec = ((d.loose != 0)?true:false) && d.isolc;
                
                d.lextraloose = d.lall && d.loosec;
                d.textraloose = d.all && d.tightc;
                
                
  //              d.loose.particleFlowc = (d.particleFlow == lParticle_Flow_Muon_Cut)?true:false;
    //            d.loose.globalMuonc = (d.globalMuon == lGlobal_Muon_Cut)?true:false;
      //          d.loose.trackerMuonc = (d.trackerMuon == lTracker_Muon_Cut)?true:false;
   //             d.loose.ptc = (d.pt > lMuon_Tight_Cut_pt)?true:false;
 //               d.loose.etac = (fabs( d.eta ) < lMuon_Tight_Cut_eta)?true:false;
     //           d.loose.isoc = (d.iso < lMuon_Relative_Isolation_Cut)?true:false;
       //         d.loose.all = d.loose.particleFlowc && d.loose.globalMuonc && d.loose.trackerMuonc && d.loose.ptc && d.loose.etac && d.loose.isoc;
            }
        }
        
        return;
    }
    
    void fillHisto(TTree* t)
    {
        for(unsigned int i=0; i < v->size(); i++)
        {
            if(LeptMult->at(i)){muonMult_.push_back(LeptMult->at(i));}
            if(v->at(i)){beforeMuonMult_.push_back((v->at(i))->size());}
            t->Fill();
            muonMult_.clear();
            beforeMuonMult_.clear();
        }
        return;
    }
    
    ~Muon()
    {
        delete v;
        v=0;
    }
    
    static TTree* getHistPointers(fwlite::TFileService& fs, const char* treeName)
    {
        TTree* t  = fs.make<TTree>(treeName,"");
        t->Branch("muonMult_",&muonMult_);
        t->Branch("beforeMuonMult_",&beforeMuonMult_);
        return t;
    }
    friend class Jet;
    friend class ElectronMuon;
    friend class ElectronMuonOppChrg;
    friend class ElectronMuonExtraLoose;
    friend class Mllcut;
    friend class ElectronMuonMet;
};

vector<double> Muon::muonMult_;
vector<double> Muon::beforeMuonMult_;




