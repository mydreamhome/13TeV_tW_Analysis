class ElectronMuon;
class Vertex
{
    struct DATA
    {
        float  vertexID,z,dof,RHO;
        bool   zc,dofc,RHOc,all;
    };
    
    vector<int>* VERTEXMult;
    int cTVertexEv;
public:
    static vector<double> vtxMult_;
    static vector<double> allvtxMult_;
    vector<vector<DATA>*>*  v;
    Vertex()
    {
        v = new vector<vector<DATA>*>;
        VERTEXMult = new vector<int>;
    }
    Vertex(vector<vector<DATA>*>* uv)
    {
        v=uv;
        VERTEXMult = new vector<int>;
    }
    int getTVerEv(){return cTVertexEv;}
    
    void setData(const char* fname)
    {
        TFile* inFile = TFile::Open(fname);
        if(!inFile)
        {
            cout<<"Input Root File not open in vertex class for processing"<<endl;
            return;
        }
        fwlite::Event ev(inFile);
        int evtID=0;
        for(ev.toBegin(); !ev.atEnd(); ++ev, evtID++)
        {
            edm::EventBase const & event = ev;
            // Handle to the z of vertex
            edm::Handle<std::vector<float> > vtxZ;
            event.getByLabel(std::string("vertexInfo:z"), vtxZ);
            // Handle to the dof of vertex
            edm::Handle<std::vector<int> > dof;
            event.getByLabel(std::string("vertexInfo:ndof"), dof);
            // Handle to the rho
            edm::Handle<std::vector<float> > rhoo;
            event.getByLabel(std::string("vertexInfo:rho"), rhoo);
            
            vector<DATA>* dv = new vector<DATA>;
            DATA d;
            for(unsigned int i=0;i<vtxZ->size();i++)
            {
                d.vertexID = i;
                d.z = vtxZ->at(i);
                d.dof = dof->at(i);
                d.RHO  = rhoo->at(i);
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
        int events =0;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            int vertex_number = 0;
            vector<DATA>* fdv= new vector<DATA>;
            dv=v->at(i);
            bool isEventSelected=false;
            int Vcount=0;
            for(unsigned int j=0;j<dv->size();j++)
            {
              d=dv->at(j);
              if(d.all)
              {
                  if(!isEventSelected)
                  {
                      vertex_number = j;
                  }
                 isEventSelected=true;
                 
                 Vcount++;
              }
            }
            VERTEXMult->push_back(Vcount);
            if(isEventSelected)
            {
                events++;
                d=dv->at(vertex_number);
                fdv->push_back(d);
            }
            fv->push_back(fdv);
        }
        cTVertexEv=events;
        return fv;
    }
    
    void setCuts()
    {
        vector<DATA>* dv;
        
        double Vtx_Cut_z = 24.0;
        int Vtx_Cut_ndof = 4;
        double Vtx_Cut_rho = 2.0;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                DATA& d=dv->at(j);
                d.zc = (fabs(d.z) < Vtx_Cut_z)?true:false;
                d.dofc = (d.dof > Vtx_Cut_ndof)?true:false;
                d.RHOc = (d.RHO < Vtx_Cut_rho)?true:false;
                d.all = d.zc && d.dofc && d.RHOc;
            }
        }
        return;
    }
    
    void fillHisto(TTree* t)
    {
        for(unsigned int i=0; i < v->size(); i++)
        {
            if(VERTEXMult->at(i)){vtxMult_.push_back(VERTEXMult->at(i));}
            if(v->at(i)){allvtxMult_.push_back((v->at(i))->size());}
            t->Fill();
            vtxMult_.clear();
            allvtxMult_.clear();
        }
        return;
    }
    
    ~Vertex()
    {
        delete v;
        v=0;
    }
    
    static TTree* getHistPointers(fwlite::TFileService& fs, const char* treeName)
    {
        TTree* t  = fs.make<TTree>(treeName,"");
        t->Branch("vtxMult_",&vtxMult_);
        t->Branch("allvtxMult_",&allvtxMult_);
        return t;
    }
    
    friend class ElectronMuon;
    
};

vector<double> Vertex::vtxMult_;
vector<double> Vertex::allvtxMult_;


