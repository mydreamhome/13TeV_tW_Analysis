class ElectronMuonOppChrg;
class ElectronMuonMet;

class Mllcut
{
    int c1E1M, c2E, C2M;
public:
    vector<Collection::DATA>*  v;
    Mllcut()
    {
        v= new vector<Collection::DATA>;
    }
    
    int getEW1E1M(){return c1E1M;}
    int getEW2E(){return c2E;}
    int getEW2M(){return C2M;}
  
    vector<Collection::DATA>* setData(ElectronMuonOppChrg& em)
    {
        int Events1e1m = 0;
        int Events2e = 0;
        int Events2m = 0;
        
        Collection::DATA emd;
        
        for(unsigned int i=0;i<em.v->size();i++)
        {
           // if(((em.v)->at(i)).mll < 20) continue;
            if(((((em.v)->at(i)).Catogary)!=1) && (((em.v)->at(i)).mll > 76 && ((em.v)->at(i)).mll < 106)) continue;
            else
            {
                emd=((em.v)->at(i));
                v->push_back(emd);
            }
            if((((em.v)->at(i)).Catogary)==1) Events1e1m++;
            if((((em.v)->at(i)).Catogary)==2) Events2m++;
            if((((em.v)->at(i)).Catogary)==3) Events2e++;
        }
        c1E1M = Events1e1m;
        c2E = Events2e;
        C2M = Events2m;
        return v;
    }
    
    ~Mllcut()
    {
        delete v;
        v=0;
    }
    
    friend class ElectronMuonMet;
};
