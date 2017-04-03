class ElectronMuonOppChrg;

class Met
{
    struct DATA
    {
        
        float  pt;
    };
    
    vector<vector<DATA>*>* v;
    
public:
    Met()
    {
       v = new vector<vector<DATA>*>;
    }
    Met(vector<vector<DATA>*>* uv)
    {
     v=uv;
    }
    
    void setData(const char* fname)
    {
        TFile* inFile = TFile::Open(fname);
        
        if(!inFile)
        {
            cout<<"Input Root File not open for processing\n";
            return;
        }
        
        fwlite::Event ev(inFile);
        int evtID=0;
        
        for(ev.toBegin(); !ev.atEnd(); ++ev, evtID++)
        {
            edm::EventBase const & event = ev;
            
            edm::Handle<std::vector<float> > MetPt;
            event.getByLabel(std::string("metFull:metFullPt"), MetPt);
            
            vector<DATA>* dv = new vector<DATA>;
            DATA d;
            
            for(unsigned int i=0;i<MetPt->size();i++)
            {
                d.pt = MetPt->at(i);
                
                dv->push_back(d);
                
            }
            
            
            v->push_back(dv);
            
        }
        inFile->Close();
        
        //setCuts();
        
        return;
    }
    
    friend class ElectronMuonOppChrg;
};

