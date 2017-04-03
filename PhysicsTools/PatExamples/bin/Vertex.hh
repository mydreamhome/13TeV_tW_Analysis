class ElectronMuonOppChrg;
class Vertex
{
    struct DATA
    {
        float  vertexID,z,dof,RHO;
    };
    
public:
    vector<vector<DATA>*>*  v;
    Vertex()
    {
        v = new vector<vector<DATA>*>;
    }
    Vertex(vector<vector<DATA>*>* uv)
    {
        v=uv;
    }
    
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
       // setCuts();
        return;
    }
    
    ~Vertex()
    {
        delete v;
        v=0;
    }
    
    friend class ElectronMuonOppChrg;
    
};


