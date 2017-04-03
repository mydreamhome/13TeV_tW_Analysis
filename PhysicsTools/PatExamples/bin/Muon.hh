class ElectronMuon;

class Muon
{
    struct DATA
    {
        float  mID,eta,pt,iso,charge,phi,tight,energy;
        bool   etac,ptc,isotc,tightc,all;
    };
    
    vector<vector<DATA>*>*  v;
    
public:
    
    Muon()
    {
        v = new vector<vector<DATA>*>;
    }
    Muon(vector<vector<DATA>*>* uv)
    {
        v=uv;
    }
    
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
            edm::Handle<std::vector<float> > muonTight;
            event.getByLabel(std::string("muons:muIsTightMuon"), muonTight);
            // Handle to the muon energy
            edm::Handle<std::vector<float> > muonEn;
            event.getByLabel(std::string("muons:muE"), muonEn);
            
            vector<DATA>* dv = new vector<DATA>;
            DATA d;
            
            for(unsigned int i=0;i<muonPt->size();i++)
            {
                d.mID = i;
                d.pt = muonPt->at(i);
                d.eta = muonEta->at(i);
                d.iso  = muonIso04->at(i);
                d.charge = muonCharge->at(i);
                d.phi = muonPhi->at(i);
                d.tight = muonTight->at(i);
                d.energy = muonEn->at(i);
                dv->push_back(d);
                
            }
            v->push_back(dv);
        }
        inFile->Close();
        
        setCuts();
        
        return;
    }
    
    vector<vector<DATA>*>* selectData()
    {
        vector<DATA>* dv;
        DATA d;
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        for(unsigned int i=0; i < v->size(); i++)
        {
            int totalTightMuons = 0;
            vector<int>* muon_number;
            muon_number = new vector<int>;
            
            vector<DATA>* fdv= new vector<DATA>;
            dv=v->at(i);
            
            for(unsigned int j=0;j<dv->size();j++)
            {
                if(totalTightMuons >= 2) break;
                d=dv->at(j);
                
                if(d.all)
                {
                    totalTightMuons++;
                    muon_number->push_back(j);
                }
            }
            
            for(unsigned int k=0;k<muon_number->size();k++)
            {
                d=dv->at(muon_number->at(k));
                fdv->push_back(d);
            }
            fv->push_back(fdv);
        }
        return fv;
    }

    void setCuts()
    {
        vector<DATA>* dv;
        
        float tMuon_Tight_Cut_pt = 20.0;
        float tMuon_Tight_Cut_eta = 2.4;
        float tMuon_Relative_Isolation_Cut = 0.15;
       // float lMuon_Relative_Isolation_Cut = 0.25;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                DATA& d=dv->at(j);
                
                d.ptc = (d.pt > tMuon_Tight_Cut_pt)?true:false;
                d.etac = (fabs( d.eta ) < tMuon_Tight_Cut_eta)?true:false;
                d.isotc = (d.iso < tMuon_Relative_Isolation_Cut)?true:false;
                
                d.tightc = ((d.tight != 0)?true:false) && d.isotc;
                d.all = d.ptc && d.etac && d.tightc;
            }
        }
        
        return;
    }
    
    ~Muon()
    {
        delete v;
        v=0;
    }
    
    friend class ElectronMuon;
};



