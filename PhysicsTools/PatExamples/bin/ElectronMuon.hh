class Electron;
class Muon;
class Jet;
class ElectronMuonOppChrg;

class ElectronMuon
{
    struct DATA
    {
        float PID,PIDinEVT,phi,eta,pt,charge,energy;
    };
    //PID = 0 for e and 1 for mu
    
public:
    vector<vector<DATA>*>* v;
    
    ElectronMuon()
    {
        v = new vector<vector<DATA>*>;
    }
    
    vector<vector<DATA>*>* setData(Electron& fe,Muon& fm)
    {
        for(unsigned int i=0;i<(fe.v->size());i++)//loop over all events
        {
            vector<DATA>* dv = new vector<DATA>;
            DATA d;
            
            for(unsigned int j=0;j<((fe.v->at(i))->size());j++)//loop over all selected electrons <=2
            {
                d.PID = 0;
                d.PIDinEVT = ((fe.v->at(i))->at(j)).eID;
                d.phi = ((fe.v->at(i))->at(j)).phi;
                d.eta = ((fe.v->at(i))->at(j)).eta;
                d.pt = ((fe.v->at(i))->at(j)).pt;
                d.charge = ((fe.v->at(i))->at(j)).charge;
                d.energy = ((fe.v->at(i))->at(j)).energy;
                dv->push_back(d);
            }
            for(unsigned int k=0;k<((fm.v->at(i))->size());k++)//loop over all selected muons <=2
            {
                d.PID = 1;
                d.PIDinEVT = ((fm.v->at(i))->at(k)).mID;
                d.phi = ((fm.v->at(i))->at(k)).phi;
                d.eta = ((fm.v->at(i))->at(k)).eta;
                d.pt = ((fm.v->at(i))->at(k)).pt;
                d.charge = ((fm.v->at(i))->at(k)).charge;
                d.energy = ((fm.v->at(i))->at(k)).energy;
                dv->push_back(d);
            }
            
            for(unsigned int mn=0;mn<(dv->size());++mn)//number of leptons
            {
                for(unsigned int p=(mn+1);p<(dv->size());++p)
                {
                    //d=dv->at(j);
                    if(((dv->at(mn)).pt) < ((dv->at(p)).pt))//check leptons pt
                    {// Sorting in decending order of pt
                        d = (dv->at(mn));
                        (dv->at(mn)) = (dv->at(p));
                        (dv->at(p)) = d;
                    }
                }
            }
           //we can put 25GeV cut here also  if(((dv->at(0)).pt)<25) {make dv empty} count;
           v->push_back(dv);//at end of event loop
        }
        return v;
    }
    
    ~ElectronMuon()
    {
        delete v;
        v=0;
    }
    
    friend class Jet;
    friend class ElectronMuonOppChrg;
};
