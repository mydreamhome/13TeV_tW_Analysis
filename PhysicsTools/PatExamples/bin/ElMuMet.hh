class Met;
class Mllcut;
class JetSelection;

class ElectronMuonMet:public Histos
{
    int cEMuMet;
    
public:
    vector<Collection::DATA>* v;
	ElectronMuonMet()
	{
        v = new vector<Collection::DATA>;
    }

    int getEMuMet(){return cEMuMet;}
    
    vector<Collection::DATA>* setData(Mllcut& emel, Met& met)
    {
        int events = 0;
        for(unsigned int i=0;i<emel.v->size();i++)
        {
            int evtID=((emel.v)->at(i)).evtID;
            
            if((met.v->at(evtID))->size() == 0)
            {
                continue;
            }
            
            for(unsigned int j=0;j<(met.v->at(evtID))->size();j++)
            {
                events++;
                Collection::DATA d;
                d = emel.v->at(i);
                d.metPt=((met.v->at(evtID))->at(j)).pt;
                v->push_back(d);
            }
        }
        cEMuMet = events;
        return v;
    }
    
    ~ElectronMuonMet()
    {
        delete v;
        v=0;
    }
    friend class JetSelection;
};
