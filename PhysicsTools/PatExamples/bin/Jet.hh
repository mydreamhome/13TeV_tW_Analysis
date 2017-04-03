class ElectronMuon;
class ElectronMuonOppChrg;
class Jet
{
    struct DATA
    {
        float  jetID,csv,charge,energy,eta,rapidit,mass,phi,pt,area,neutralHadronEnergyFrac,neutralEmEnergyFrac,NumConstituents,chargedHadronEnergyFrac,chargedMultiplicity,chargedEmEnergyFrac,NumNeutralParticle;
        bool   csvc,nonCsvc,etac,ptc,neutralHadronEnergyFraccc,neutralEmEnergyFraccc,NumConstituentscc,chargedHadronEnergyFraccc,chargedMultiplicitycc,chargedEmEnergyFraccc,loosec;
    };
    int totalevts;
public:
    
    vector<vector<DATA>*>*  v;
    Jet()
    {
        v = new vector<vector<DATA>*>;
    }
    Jet(vector<vector<DATA>*>* uv)
    {
        v=uv;
    }
    int gettotalevts(){return totalevts;}
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
    
    vector<vector<DATA>*>* selectDataLooseJet(ElectronMuon& em)//atleast 1 loose jet
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        for(unsigned int i=0; i < v->size(); i++)
        {
            vector<int>* jet_number;
            jet_number = new vector<int>;
            vector<DATA>* fdv= new vector<DATA>;
            dv=v->at(i);
            bool isEventSelected=false;
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                
                bool cleaned=false;
                if(((((em.v->at(i))->size())) < 2) || ((((em.v->at(i))->at(0)).pt) < 25) || ((((em.v->at(i))->at(0)).charge * ((em.v->at(i))->at(1)).charge) > 0))
                {
                    cleaned = true;
                }
                else
                {
                    float dR1 = deltaR(((em.v->at(i))->at(0)).eta,((em.v->at(i))->at(0)).phi,d.eta,d.phi);
                    float dR2 = deltaR(((em.v->at(i))->at(1)).eta,((em.v->at(i))->at(1)).phi,d.eta,d.phi);
                    if((dR1>0.4) && (dR2>0.4))
                    {
                        //accept jet
                        cleaned=true;
                    }
                }
                
                if((d.loosec) && cleaned)
                {
                    jet_number->push_back(j);
                    isEventSelected=true;
                }
            }
            
            if(isEventSelected)
            {
                for(unsigned int k=0;k<jet_number->size();k++)
                {
                    d=dv->at(jet_number->at(k));
                    fdv->push_back(d);
                }
            }
            fv->push_back(fdv);
        }
        return fv;
    }
    
    vector<vector<DATA>*>* selectDatabj(Jet& looseJet)//atleast 1 b jet
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        for(unsigned int i=0; i < (looseJet.v->size()); i++)
        {
            vector<int>* jet_number;
            jet_number = new vector<int>;
            vector<DATA>* fdv= new vector<DATA>;
            dv=(looseJet.v->at(i));
            bool isEventSelected=false;
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                if(d.csvc)
                {
                    jet_number->push_back(j);
                    isEventSelected=true;
                }
            }
            
            if(isEventSelected)
            {
                for(unsigned int k=0;k<jet_number->size();k++)
                {
                    d=dv->at(jet_number->at(k));
                    fdv->push_back(d);
                }
            }
            fv->push_back(fdv);
        }
        return fv;
    }
    
    void setCuts()
    {
        vector<DATA>* dv;
        float jet_Cut_pt = 30.0;
        float jet_Cut_eta = 2.4;
        float jet_Cut_csv = 0.8484;
        
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
                
                d.loosec = within24eta && Outside3 && d.neutralHadronEnergyFraccc && d.neutralEmEnergyFraccc && d.NumConstituentscc && d.ptc && d.etac;
            }
        }
        return;
    }
    
    ~Jet()
    {
        delete v;
        v=0;
    }
    
    friend class ElectronMuonOppChrg;
    
};

