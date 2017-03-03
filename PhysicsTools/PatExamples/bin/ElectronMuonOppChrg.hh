class ElectronMuon;
class ElectronMuonExtraLoose;

class ElectronMuonOppChrg:public Histos
{
    
    int cOppChrg;
    
public:
    vector<Collection::DATA>*  v;
    ElectronMuonOppChrg()
    {
        v= new vector<Collection::DATA>;
    }
    
    int getEWOppChrg(){return cOppChrg;}
    
    vector<Collection::DATA>* setData(ElectronMuon& em)
    {
        int events = 0;
        Collection::DATA emd;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int c =0 ;
            if( (((em.v)->at(i)).ech * ((em.v)->at(i)).mch) < 0 )
            {
                emd=((em.v)->at(i));
                c++;
            }
            if(c == 1)
            {
                events++;
                v->push_back(emd);
            }
        }
        cOppChrg = events;
        return v;
    }
    
    ~ElectronMuonOppChrg()
    {
        delete v;
        v=0;
    }
    
    friend class ElectronMuonExtraLoose;
};
