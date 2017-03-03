class ElectronMuonExtraLoose;
class ElectronMuonMet;

class Mllcut:public Histos
{
    
    int cmllc;
    
public:
    vector<Collection::DATA>*  v;
    Mllcut()
    {
        v= new vector<Collection::DATA>;
    }
    
    int getEWcmllc(){return cmllc;}
  
    vector<Collection::DATA>* setData1e1m(ElectronMuonExtraLoose& em)
    {
        int events = 0;
        Collection::DATA emd;
        
        for(unsigned int i=0;i<em.v->size();i++)
        {
            if(((em.v)->at(i)).mll < 20)
            {
                continue;
            }
            else
            {
                emd=((em.v)->at(i));
                events++;
                v->push_back(emd);
            }
        }
        cmllc = events;
        return v;
    }
    
    vector<Collection::DATA>* setData(ElectronMuonExtraLoose& em)
    {
        int events = 0;
        Collection::DATA emd;
        
        for(unsigned int i=0;i<em.v->size();i++)
        {
            if(((em.v)->at(i)).mll < 20 || (((em.v)->at(i)).mll > 81 && ((em.v)->at(i)).mll < 101))
            {
                continue;
            }
            else
            {
                emd=((em.v)->at(i));
                events++;
                v->push_back(emd);
            }
        }
        cmllc = events;
        return v;
    }
    
    ~Mllcut()
    {
        delete v;
        v=0;
    }
    
    friend class ElectronMuonMet;
};
