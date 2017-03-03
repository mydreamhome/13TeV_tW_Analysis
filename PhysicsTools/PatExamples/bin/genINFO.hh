class ElectronMuon;

class genINFO
{
    struct DATA
    {
        int puNtrueInteractons;
        double  eID,eWeight;
    };
    
    vector<vector<DATA>*>* v;
    double cnetEvWt;
    
public:
    static vector<double> genWtinfo_;
    static vector<double> pileUP_;
    
    genINFO()
    {
        v = new vector<vector<DATA>*>;
    }
    genINFO(vector<vector<DATA>*>* uv)
    {
        v=uv;
    }
    double getcnetEvWt(){return cnetEvWt;}
    
    void setData(const char* fname)
    {
        TFile* inFile = TFile::Open(fname);
        
        if(!inFile)
        {
            cout<<"Input Root File not opened for processing in genInfo class "<<endl;
            return;
        }
        
        fwlite::Event ev(inFile);
        int evtID=0;
        double netWtEv = 0.0;
        
        for(ev.toBegin(); !ev.atEnd(); ++ev, evtID++)
        {
            edm::EventBase const & event = ev;
            
            // Handle to the genEventWeight, which I added in eventUSerData class
            edm::Handle<double> genEventWeight;
            event.getByLabel(std::string("eventUserData:eventWeight"), genEventWeight);
            
            // Handle to the pu, which I added in eventUSerData class
            edm::Handle<int> puNtrueIntMC;
            event.getByLabel(std::string("eventUserData:puNtrueInt"), puNtrueIntMC);
            
            vector<DATA>* dv = new vector<DATA>;
            DATA d;
            
            //if((genEventWeight.size())>0)
            {
                d.eID = evtID;
                d.eWeight = *genEventWeight;
                d.puNtrueInteractons = *puNtrueIntMC;
                //cout<<d.eID<<"  evt weight is: "<< d.eWeight <<endl;
                //cout<<d.eID<<"  evt weight is: "<< d.puNtrueInteractons <<endl;
                dv->push_back(d);
            }
            netWtEv = netWtEv + (d.eWeight);
            v->push_back(dv);
        }
        inFile->Close();
        cnetEvWt=netWtEv;
        return;
    }
    
    void fillHisto(TTree* t)
    {
        for(unsigned int i=0; i < v->size(); i++)
        {
            if(v->at(i)) genWtinfo_.push_back(((v->at(i))->at(0)).eWeight);
            if(v->at(i)) pileUP_.push_back(((v->at(i))->at(0)).puNtrueInteractons);
            t->Fill();
            genWtinfo_.clear();
            pileUP_.clear();
        }
        return;
    }
    
    ~genINFO()
    {
        delete v;
        v=0;
    }
    
    static TTree* getHistPointers(fwlite::TFileService& fs, const char* treeName)
    {
        TTree* t  = fs.make<TTree>(treeName,"");
        t->Branch("genWtinfo_",&genWtinfo_);
        t->Branch("pileUP_",&pileUP_);
        return t;
    }
    
    friend class ElectronMuon;
};

vector<double> genINFO::genWtinfo_;
vector<double> genINFO::pileUP_;


