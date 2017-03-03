class ElectronMuon;
class HLT
{
    struct DATA
    {
       // string name;
        int HLTid;
        float decision,prescale;
        bool TRIGpass,TRIGprescl,all;
    };
    
    int cTHltEv;
public:
    vector<vector<DATA>*>*  v;
    HLT()
    {
        v = new vector<vector<DATA>*>;
    }
    HLT(vector<vector<DATA>*>* uv)
    {
        v=uv;
    }
    int getTHltEv(){return cTHltEv;}
    
    void setData(const char* fname)
    {
        TFile* inFile = TFile::Open(fname);
        if(!inFile)
        {
            cout<<"Input Root File not open in HLT class for processing"<<endl;
            return;
        }
        fwlite::Event ev(inFile);
        int evtID=0;
	
        for(ev.toBegin(); !ev.atEnd(); ++ev, evtID++)
        {
            edm::EventBase const & event = ev;
            
            // Handle to the pass decision of hlt
            edm::Handle<std::vector<float> > HLTdecision;
            event.getByLabel(std::string("TriggerUserData:triggerBitTree"), HLTdecision);
            // Handle to the prescale of hlt
            edm::Handle<std::vector<int> > HLTprescale;
            event.getByLabel(std::string("TriggerUserData:triggerPrescaleTree"), HLTprescale);
            // Handle to the hlt name
            edm::Handle<std::vector<string> > HLTname;
            event.getByLabel(std::string("TriggerUserData:triggerNameTree"), HLTname);
            
            vector<DATA>* dv = new vector<DATA>;
            DATA d;
            for(unsigned int i=0;i<HLTdecision->size();i++)
            {
                string presentTrigName=HLTname->at(i);
              //  string NameOFhlt1 = "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3";
                // string NameOFhlt2 = "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3";
                //d.TRIGname = (((d.name).compare(NameOFhlt1) == 0)||((d.name).compare(NameOFhlt2) == 0))?true:false;
                if((presentTrigName.compare("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3") != 0))
                {
                 //  cout<<"rejected. "<<endl;
                   continue;
                }
                if((presentTrigName.compare("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3") == 0))
                {
                    d.HLTid = i;
                    d.decision = HLTdecision->at(i);
                    d.prescale = HLTprescale->at(i);
                    dv->push_back(d);
                   // cout<<"hlt id: "<<i<<", decision: "<<(d.decision)<<", prescale: "<<(d.prescale)<<", name: "<<presentTrigName<<endl;
                }
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
        int events = 0;
        int noOfHLTapplied = 1;
        for(unsigned int i=0; i < v->size(); i++)
        {
            vector<int>* hlt_number = new vector<int>;
            vector<DATA>* fdv= new vector<DATA>;
            dv=v->at(i);
            bool isEventSelected=false;
            int noOfHltPassedinEvent=0;
            
            for(unsigned int j=0;j<dv->size();j++)
            {
              d=dv->at(j);
              if(d.all)
              {
                hlt_number->push_back(j);
                noOfHltPassedinEvent++;
                if(noOfHltPassedinEvent==noOfHLTapplied)
                {
                    isEventSelected=true;
                }
              }
            }
            
            if(isEventSelected)
            {
                events++;
                for(unsigned int k=0;k<hlt_number->size();k++)
                {
                    d=dv->at(hlt_number->at(k));
                    fdv->push_back(d);
                }
            }
            fv->push_back(fdv);
        }
        cTHltEv=events;
        return fv;
    }
    
    void setCuts()
    {
        vector<DATA>* dv;
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                DATA& d=dv->at(j);
                d.TRIGpass = (d.decision == 1)?true:false;
                d.TRIGprescl = (d.prescale >= 1)?true:false;
                d.all = d.TRIGpass && d.TRIGprescl;
            }
        }
        return;
    }
    
    ~HLT()
    {
        delete v;
        v=0;
    }
    
    friend class ElectronMuon;
    
};
