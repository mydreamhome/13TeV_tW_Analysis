class Electron;
class Muon;
class ElectronMuon;
class Jet
{
    struct DATA
    {
        float  jetID,csv,charge,energy,eta,rapidit,mass,phi,pt,area,neutralHadronEnergyFrac,neutralEmEnergyFrac,NumConstituents,chargedHadronEnergyFrac,chargedMultiplicity,chargedEmEnergyFrac,NumNeutralParticle;
        bool   csvc,nonCsvc,etac,ptc,all,neutralHadronEnergyFraccc,neutralEmEnergyFraccc,NumConstituentscc,chargedHadronEnergyFraccc,chargedMultiplicitycc,chargedEmEnergyFraccc,loosec;
    };
    
    vector<int>* JETMult;
    vector<int>* JETCLEANEDMult;
    int cTLj,cEwanyLj,cE1Lj,cE1j1t,cE2Lj,cE2j1t,cE2j2t,totalevts,cToClj,cEClj;
public:
    static vector<int> jetMult_;
    static vector<int> beforeJetMult_;
    static vector<int> CllleanedJetMult_;
    //beforeJetMult_ is total jet mult
    //jetMult_ OR JETMult is Loose jet mult
    //CllleanedJetMult_ OR JETCLEANEDMult is cleaned jet mult
    
    vector<vector<DATA>*>*  v;
    Jet()
    {
        v = new vector<vector<DATA>*>;
        JETMult = new vector<int>;
        JETCLEANEDMult = new vector<int>;
    }
    Jet(vector<vector<DATA>*>* uv)
    {
        v=uv;
        JETMult = new vector<int>;
        JETCLEANEDMult = new vector<int>;
    }
    int gettotalevts(){return totalevts;}
    int getTLj(){return cTLj;}
    int getEwanyLj(){return cEwanyLj;}
    int getEwCleanedj(){return cEClj;}
    int getTotalCleanedj(){return cToClj;}
    int getE1Lj(){return cE1Lj;}
    int getE1j1t(){return cE1j1t;}
    int getE2Lj(){return cE2Lj;}
    int getE2j1t(){return cE2j1t;}
    int getE2j2t(){return cE2j2t;}
    
    void setData(const char* fname)
    {
        TFile* inFile = TFile::Open(fname);
        
        if(!inFile)
        {
            cout<<"Input Root File not open in jet class for processing"<<endl;
            return;
        }
        
        fwlite::Event ev(inFile);
        int evtID=0;
        
        for(ev.toBegin(); !ev.atEnd(); ++ev, evtID++)
        {
            edm::EventBase const & event = ev;
            
            // Handle to the jet CSV
            edm::Handle<std::vector<float> > jetCSV;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSCSVv2"), jetCSV);
            // Handle to the jet charge
            edm::Handle<std::vector<float> > jetCharge;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSCharge"), jetCharge);
            // Handle to the jet energy
            edm::Handle<std::vector<float> > jetEn;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSE"), jetEn);
            // Handle to the jet eta
            edm::Handle<std::vector<float> > jetEta;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSEta"), jetEta);
            // Handle to the jet rapidity
            edm::Handle<std::vector<float> > jetRapidity;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSY"), jetRapidity);
            // Handle to the jet mass
            edm::Handle<std::vector<float> > jetMass;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSMass"), jetMass);
            // Handle to the jet phi
            edm::Handle<std::vector<float> > jetPhi;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSPhi"), jetPhi);
            // Handle to the jet pt
            edm::Handle<std::vector<float> > jetPt;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSPt"), jetPt);
            // Handle to the jet Area
            edm::Handle<std::vector<float> > jetArea;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSjetArea"), jetArea);
            ///////////////Jet Loose criteria//////////////////////////////////////////////////////////////////////
            // Handle to the Neutral hadron fraction
            edm::Handle<std::vector<float> > jetneutralHadronEnergyFrac;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSneutralHadronEnergyFrac"), jetneutralHadronEnergyFrac);
            // Handle to the Neutral EM fraction
            edm::Handle<std::vector<float> > jetneutralEmEnergyFrac;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSneutralEmEnergyFrac"), jetneutralEmEnergyFrac);
            // Handle to the Number of constituents
            edm::Handle<std::vector<float> > jetNumConstituents;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSNumConstituents"), jetNumConstituents);
            // Handle to the Charged Hadron fraction
            edm::Handle<std::vector<float> > jetchargedHadronEnergyFrac;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSchargedHadronEnergyFrac"), jetchargedHadronEnergyFrac);
            // Handle to the Charged Multiplicity
            edm::Handle<std::vector<float> > jetchargedMultiplicity;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSchargedMultiplicity"), jetchargedMultiplicity);
            // Handle to the Charged EM fraction
            edm::Handle<std::vector<float> > jetchargedEmEnergyFrac;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSchargedEmEnergyFrac"), jetchargedEmEnergyFrac);
            // Handle to the Neutral particle multiplicity
            edm::Handle<std::vector<float> > jetNumNeutralParticle;
            event.getByLabel(std::string("jetsAK4CHS:jetAK4CHSneutralMultiplicity"), jetNumNeutralParticle);
            
            vector<DATA>* dv = new vector<DATA>;
            DATA d;
            
            for(unsigned int i=0;i<jetPt->size();i++)
            {
                d.jetID = i;
                d.csv = jetCSV->at(i);
                d.charge = jetCharge->at(i);
                d.energy  = jetEn->at(i);
                d.eta = jetEta->at(i);
                d.rapidit=jetRapidity->at(i);
                d.mass = jetMass->at(i);
                d.phi = jetPhi->at(i);
                d.pt = jetPt->at(i);
                d.area = jetArea->at(i);
                d.neutralHadronEnergyFrac = jetneutralHadronEnergyFrac->at(i);
                d.neutralEmEnergyFrac = jetneutralEmEnergyFrac->at(i);
                d.NumConstituents = jetNumConstituents->at(i);
                d.chargedHadronEnergyFrac = jetchargedHadronEnergyFrac->at(i);
                d.chargedMultiplicity = jetchargedMultiplicity->at(i);
                d.chargedEmEnergyFrac = jetchargedEmEnergyFrac->at(i);
                d.NumNeutralParticle = jetNumNeutralParticle->at(i);
                dv->push_back(d);
            }
            v->push_back(dv);
            
        }
        inFile->Close();
        totalevts = v->size();
        setCuts();
        return;
    }
    
    vector<vector<DATA>*>* selectDataLooseJet()
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events = 0;
        int totalLooseJets = 0;
        for(unsigned int i=0; i < v->size(); i++)
        {
            vector<int>* jet_number;
            jet_number = new vector<int>;
            vector<DATA>* fdv= new vector<DATA>;
            dv=v->at(i);
            bool isEventSelected=false;
            int LooseJetsinEvent=0;
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                if(d.loosec)
                {
                    totalLooseJets++;
                    jet_number->push_back(j);
                    LooseJetsinEvent++;
                    isEventSelected=true;
                }
            }
            
            JETMult->push_back(LooseJetsinEvent);
            if(isEventSelected)
            {
                events++;
                for(unsigned int k=0;k<jet_number->size();k++)
                {
                    d=dv->at(jet_number->at(k));
                    fdv->push_back(d);
                }
            }
            fv->push_back(fdv);
        }
        cTLj=totalLooseJets;
        cEwanyLj=events;
        return fv;
    }
 
    vector<vector<DATA>*>* selectDataCleaning(Electron& el,Muon& muon,Jet& looseJet)
    {
        vector<DATA>* dv;
        DATA d;
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events = 0;
        int totalCleanedJets = 0;
        for(unsigned int i=0; i < (looseJet.v->size()); i++)
        {
            vector<int>* jet_number;
            jet_number = new vector<int>;
            vector<DATA>* fdv= new vector<DATA>;
            int CleanedJetsinEvent=0;
            if((looseJet.v->at(i))->size() >= 1)
            {
                dv=(looseJet.v->at(i));
                bool isEventSelected=false;
                
                for(unsigned int j=0;j<dv->size();j++)
                {
                    d=dv->at(j);
                    bool cleaned=true;
                    for(unsigned int k3=0; k3 < (el.v->at(i)->size()); k3++)
                    {
                        if((el.v->at(i))->size()!=1 || (muon.v->at(i))->size()!=1)continue;
                        if((el.v->at(i))->size()==1 && (muon.v->at(i))->size()==1)
                        {
                            float dR = deltaR(((el.v->at(i))->at(k3)).eta,((el.v->at(i))->at(k3)).phi,d.eta,d.phi);
                            if(dR<0.4)
                            {
                                //reject jet
                                cleaned=false;
                                break;
                            }
                        }
                    }
                   /* if(!cleaned)
                    {
                        continue;
                    }*/
                    if(cleaned)
                    {
                        for(unsigned int k4=0; k4 < (muon.v->at(i)->size()); k4++)
                        {
                            if((el.v->at(i))->size()!=1 || (muon.v->at(i))->size()!=1)continue;
                            if((el.v->at(i))->size()==1 && (muon.v->at(i))->size()==1)
                            {
                                float dR = deltaR(((muon.v->at(i))->at(k4)).eta,((muon.v->at(i))->at(k4)).phi,d.eta,d.phi);
                                if(dR<0.4)
                                {
                                    //reject jet
                                    cleaned=false;
                                    break;
                                }
                            }
                        }
                    }
                    if(cleaned)
                    {
                        totalCleanedJets++;
                        jet_number->push_back(j);
                        CleanedJetsinEvent++;
                        isEventSelected=true;
                    }
                }
                
                if(isEventSelected)
                {
                    events++;
                    for(unsigned int k=0;k<jet_number->size();k++)
                    {
                        d=dv->at(jet_number->at(k));
                        fdv->push_back(d);
                    }
                }
            }
            JETCLEANEDMult->push_back(CleanedJetsinEvent);
            fv->push_back(fdv);
        }
        cToClj=totalCleanedJets;
        cEClj=events;
        return fv;
    }
    
    vector<vector<DATA>*>* selectData1ljPtEta(Jet& looseJet)
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events = 0;
        for(unsigned int i=0; i < (looseJet.v->size()); i++)
        {
            int jet_number = 0;
            vector<DATA>* fdv= new vector<DATA>;
            //if((looseJet.v->at(i))->size() < 1) continue;
            if((looseJet.v->at(i))->size() >= 1)
            {
                dv=(looseJet.v->at(i));
                bool isEventSelected=false;
                int PassedJetsinEvent=0;
                for(unsigned int j=0;j<dv->size();j++)
                {
                    d=dv->at(j);
                    if(d.ptc && d.etac && d.loosec)
                    {
                        jet_number = j;
                        PassedJetsinEvent++;
                    }
                }
                if(PassedJetsinEvent==1)
                {
                    isEventSelected=true;
                }
                if(isEventSelected)
                {
                    events++;
                    d=dv->at(jet_number);
                    fdv->push_back(d);
                }
            }
            fv->push_back(fdv);
        }
        cE1Lj=events;
        return fv;
    }
    
    vector<vector<DATA>*>* selectData1j1b(Jet& j1lPtEta)
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events = 0;
        int totalPassedBJets = 0;
        for(unsigned int i=0; i < (j1lPtEta.v->size()); i++)
        {
            int jet_number = 0;
            vector<DATA>* fdv= new vector<DATA>;
           // if((j1lPtEta.v->at(i))->size() != 1) continue;
            if((j1lPtEta.v->at(i))->size() == 1)
            {
                dv=(j1lPtEta.v->at(i));
                bool isEventSelected=false;
                int PassedBJetsinEvent=0;
                for(unsigned int j=0;j<dv->size();j++)
                {
                    d=dv->at(j);
                    if(d.all && d.loosec)
                    {
                        totalPassedBJets++;
                        jet_number = j;
                        PassedBJetsinEvent++;
                    }
                }
                if(PassedBJetsinEvent==1)
                {
                    isEventSelected=true;
                }
                if(isEventSelected)
                {
                    events++;
                    d=dv->at(jet_number);
                    fdv->push_back(d);
                }
            }
            fv->push_back(fdv);
        }
        cE1j1t=events;
        return fv;
    }
    
    vector<vector<DATA>*>* selectData2ljPtEta(Jet& looseJet)
    {
        vector<DATA>* dv;
        DATA d;
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events =0;
        
        for(unsigned int i=0; i < (looseJet.v->size()); i++)
        {
            int jet_number1 = 0;
            int jet_number2 = 0;
            vector<DATA>* fdv= new vector<DATA>;
            
            //if((looseJet.v->at(i))->size() < 2) continue;
            if((looseJet.v->at(i))->size() >= 2)
            {
                dv=(looseJet.v->at(i));
                bool isEventSelected=false;
                int PassedBJetsinEvent=0;
                for(unsigned int j=0;j<dv->size();j++)
                {
                    d=dv->at(j);
                    if(d.ptc && d.etac && d.loosec)
                    {
                    
                        if(PassedBJetsinEvent==0) jet_number1 = j;
                        if(PassedBJetsinEvent==1) jet_number2 = j;
                        PassedBJetsinEvent++;
                    }
                }
            
                if(PassedBJetsinEvent==2){isEventSelected=true;
                }
                if(isEventSelected)
                {
                    events++;
                    d=dv->at(jet_number1);
                    fdv->push_back(d);
                    d=dv->at(jet_number2);
                    fdv->push_back(d);
                }
            }
            fv->push_back(fdv);
        }
        cE2Lj=events;
        return fv;
    }
    
    vector<vector<DATA>*>* selectData2j1b(Jet& j2lPtEta)
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events =0;
        for(unsigned int i=0; i < (j2lPtEta.v->size()); i++)
        {
            int bjet_number1 = 0;
            int jet_number2 = 0;
            vector<DATA>* fdv= new vector<DATA>;
          //  if((j2lPtEta.v->at(i))->size() != 2) continue;
            if((j2lPtEta.v->at(i))->size() == 2)
            {
                dv=(j2lPtEta.v->at(i));
                bool isEventSelected=false;
                int PassedBJetsinEvent=0;
                for(unsigned int j=0;j<dv->size();j++)
                {
                    d=dv->at(j);
                    if(d.all && d.loosec)
                    {
                    
                        bjet_number1 = j;
                        PassedBJetsinEvent++;
                    }
                    else if(!(d.all && d.loosec))
                    {
                        jet_number2 = j;
                    }
                }
            
                if(PassedBJetsinEvent==1){isEventSelected=true;
                }
                if(isEventSelected)
                {
                    events++;
                    d=dv->at(bjet_number1);
                    fdv->push_back(d);
                    d=dv->at(jet_number2);
                    fdv->push_back(d);
                }
            }
            fv->push_back(fdv);
        }
        cE2j1t=events;
        return fv;
    }
    
    vector<vector<DATA>*>* selectData2j2b(Jet& j2lPtEta)
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events =0;
        for(unsigned int i=0; i < (j2lPtEta.v->size()); i++)
        {
            int jet_number1 = 0;
            int jet_number2 = 0;
            vector<DATA>* fdv= new vector<DATA>;
         //   if((j2lPtEta.v->at(i))->size() != 2) continue;
            if((j2lPtEta.v->at(i))->size() == 2)
            {
                dv=(j2lPtEta.v->at(i));
                bool isEventSelected=false;
                int PassedBJetsinEvent=0;
                for(unsigned int j=0;j<dv->size();j++)
                {
                    d=dv->at(j);
                    if(d.all)
                    {
                    
                        if(PassedBJetsinEvent==0) jet_number1 = j;
                        if(PassedBJetsinEvent==1) jet_number2 = j;
                        PassedBJetsinEvent++;
                    }
                }
            
                if(PassedBJetsinEvent==2){isEventSelected=true;
                }
                if(isEventSelected)
                {
                    events++;
                    d=dv->at(jet_number1);
                    fdv->push_back(d);
                    d=dv->at(jet_number2);
                    fdv->push_back(d);
                }
            }
            fv->push_back(fdv);
        }
        cE2j2t=events;
        return fv;
    }
    
    void setCuts()
    {
        vector<DATA>* dv;
        float jet_Cut_pt = 30.0;
        float jet_Cut_ptl = 20.0;
        float jet_Cut_eta = 2.4;
        float jet_Cut_etal = 4.9;
        float jet_Cut_csv = 0.9535;
        
        float jet_Cut_neutralHadronEnergyFrac = 0.99;
        float jet_Cut_neutralEmEnergyFrac1 = 0.99;
        float jet_Cut_neutralEmEnergyFrac2 = 0.90;
        float jet_Cut_NumConstituents = 1;
        
        float jet_Cut_chargedHadronEnergyFrac = 0.0;
        float jet_Cut_chargedMultiplicity = 0;
        float jet_Cut_chargedEmEnergyFrac = 0.99;
        
        float jet_Cut_NumNeutralParticle = 10;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                DATA& d=dv->at(j);
                d.ptc = (d.pt > jet_Cut_pt)?true:false;
                d.etac = (fabs( d.eta ) < jet_Cut_eta)?true:false;
                d.csvc = (d.csv > jet_Cut_csv)?true:false;
                d.nonCsvc = (d.csv < jet_Cut_csv)?true:false;
                d.all = d.ptc && d.etac && d.csvc;
                
                d.neutralHadronEnergyFraccc = (d.neutralHadronEnergyFrac < jet_Cut_neutralHadronEnergyFrac)?true:false;
                d.neutralEmEnergyFraccc = (d.neutralEmEnergyFrac < jet_Cut_neutralEmEnergyFrac1)?true:false;
                d.NumConstituentscc = (d.NumConstituents > jet_Cut_NumConstituents)?true:false;
                d.chargedHadronEnergyFraccc = (d.chargedHadronEnergyFrac > jet_Cut_chargedHadronEnergyFrac)?true:false;
                d.chargedMultiplicitycc = (d.chargedMultiplicity > jet_Cut_chargedMultiplicity)?true:false;
                d.chargedEmEnergyFraccc = (d.chargedEmEnergyFrac < jet_Cut_chargedEmEnergyFrac)?true:false;
                
                bool within24eta = false;
                if(fabs( d.eta ) <= 2.4)
                {
                    within24eta = d.chargedHadronEnergyFraccc && d.chargedMultiplicitycc && d.chargedEmEnergyFraccc;
                }
                else if(fabs( d.eta ) > 2.4) within24eta = true;
                
                bool Outside3 = false;
                if(fabs( d.eta ) > 3.0)
                {
                    Outside3 = (d.NumNeutralParticle > jet_Cut_NumNeutralParticle) && (d.chargedMultiplicitycc < jet_Cut_neutralEmEnergyFrac2);
                }
                else if(fabs( d.eta ) <= 3.0) Outside3 = true;
                
                d.loosec = within24eta && Outside3 && d.neutralHadronEnergyFraccc && d.neutralEmEnergyFraccc && d.NumConstituentscc && ((d.pt > jet_Cut_ptl)?true:false) && ((fabs( d.eta ) < jet_Cut_etal)?true:false);
            }
        }
        return;
    }
    
    void fillHisto(TTree* t)
    {
   // cout<<"Entering fill histo in jet class"<<endl;
        for(unsigned int i=0; i < v->size(); i++)
        {
          /*  if(JETMult->at(i)){jetMult_.push_back(JETMult->at(i));}
            if(JETCLEANEDMult->at(i)){CllleanedJetMult_.push_back(JETCLEANEDMult->at(i));}
            if(v->at(i)){beforeJetMult_.push_back((v->at(i))->size());}
            */
          //  cout<<"311111111111    :"<<endl;
            jetMult_.push_back(JETMult->at(i));
           // cout<<"311111111112    & size is :"<<(JETCLEANEDMult->at(i))<<endl;
            CllleanedJetMult_.push_back(JETCLEANEDMult->at(i));
           // cout<<"311111111113    :"<<endl;
            beforeJetMult_.push_back((v->at(i))->size());
           // cout<<"311111111114    :"<<endl;
            t->Fill();
            jetMult_.clear();
            CllleanedJetMult_.clear();
            beforeJetMult_.clear();
        }
       // cout<<"Exiting fill histo in jet class"<<endl;
        return;
    }
    
    ~Jet()
    {
        delete v;
        v=0;
    }
    
    static TTree* getHistPointers(fwlite::TFileService& fs, const char* treeName)
    {
        TTree* t  = fs.make<TTree>(treeName,"");
        t->Branch("jetMult_",&jetMult_);
        t->Branch("CllleanedJetMult_",&CllleanedJetMult_);
        t->Branch("beforeJetMult_",&beforeJetMult_);
        return t;
    }
    
    friend class ElectronMuon;
    
};

vector<int> Jet::jetMult_;
vector<int> Jet::CllleanedJetMult_;
vector<int> Jet::beforeJetMult_;



