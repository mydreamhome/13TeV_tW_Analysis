class ElectronMuon;

class Electron
{
    struct DATA
    {
        float  eID,phi,eta,pt,charge,tightID,scEta,energy;
        bool   etac,ptc,tightc,all;
    };
    vector<vector<DATA>*>* v;
public:
    Electron()
    {
        v = new vector<vector<DATA>*>;
    }
    Electron(vector<vector<DATA>*>* uv)
    {
        v=uv;
    }
    
    void setData(const char* fname)
    {
        TFile* inFile = TFile::Open(fname);
        
        if(!inFile)
        {
            cout<<"Input Root File not opened for processing in electron class "<<endl;
            return;
        }
        
        fwlite::Event ev(inFile);
        int evtID=0;
        
        for(ev.toBegin(); !ev.atEnd(); ++ev, evtID++)
        {
            edm::EventBase const & event = ev;
            
            // Handle to the electron pt
            edm::Handle<std::vector<float> > electronPt;
            event.getByLabel(std::string("electrons:elPt"), electronPt);
            // Handle to the electron eta
            edm::Handle<std::vector<float> > electronEta;
            event.getByLabel(std::string("electrons:elEta"), electronEta);
            // Handle to the electron eta
            edm::Handle<std::vector<float> > electronPhi;
            event.getByLabel(std::string("electrons:elPhi"), electronPhi);
            // Handle to the electron charge
            edm::Handle<std::vector<float> > electronCharge;
            event.getByLabel(std::string("electrons:elCharge"), electronCharge);
            // Handle to the electron charge
            edm::Handle<std::vector<float> > electronTightID;
            event.getByLabel(std::string("electrons:elvidTight"), electronTightID);
            // Handle to the electron electronSCeta
            edm::Handle<std::vector<float> > electronSCeta;
            event.getByLabel(std::string("electrons:elSCEta"), electronSCeta);
            // Handle to the electron energy
            edm::Handle<std::vector<float> > electronEn;
            event.getByLabel(std::string("electrons:elE"), electronEn);
            
            vector<DATA>* dv = new vector<DATA>;
            DATA d;

            for(unsigned int i=0;i<electronPt->size();i++)
            {
                d.eID = i;
                d.pt = electronPt->at(i);
                d.eta = electronEta->at(i);
                d.phi = electronPhi->at(i);
                d.charge = electronCharge->at(i);
                d.tightID = electronTightID->at(i);
                d.scEta = electronSCeta->at(i);
                d.energy = electronEn->at(i);
                
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
            int totalTightelectrons =0;
            vector<int>* elctron_number;
            elctron_number = new vector<int>;
            
            vector<DATA>* fdv= new vector<DATA>;
            dv=v->at(i);
            
            for(unsigned int j=0;j<dv->size();j++)
            {
                if(totalTightelectrons >= 2) break;
                d=dv->at(j);
                
                if(d.all)
                {
                    totalTightelectrons++;
                    elctron_number->push_back(j);
                }
            }
            
            for(unsigned int k=0;k<elctron_number->size();k++)
            {
                d=dv->at(elctron_number->at(k));
                fdv->push_back(d);
            }
            fv->push_back(fdv);
        }
        return fv;
    }
    
    void setCuts()
    {
        vector<DATA>* dv;
        
        bool wantGapVeto = true;
        float tElectron_Cut_pt = 20.0;
        float tElectron_Cut_eta = 2.4;
        float vetoEtal = 1.4442;
        float vetoEtat = 1.5660;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                DATA& d=dv->at(j);
                
                d.ptc = (d.pt > tElectron_Cut_pt)?true:false;
                d.etac = (fabs( d.eta )< tElectron_Cut_eta)?true:false;
                d.tightc = (d.tightID != 0)?true:false;
                
                bool betweenGapVetoed = false;
                if(wantGapVeto)
                {
                    if(fabs(d.scEta) > vetoEtal && fabs(d.scEta) < vetoEtat)
                    {
                        betweenGapVetoed = true;
                    }
                }
                
                d.all = d.ptc && d.etac && d.tightc && (!betweenGapVetoed);
            }
        }
        return;
    }
    
    ~Electron()
    {
        delete v;
        v=0;
    }
    
    friend class ElectronMuon;
};


