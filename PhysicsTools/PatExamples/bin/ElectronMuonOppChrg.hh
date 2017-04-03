class ElectronMuon;
class genINFO;
class Met;
class Jet;
class Mllcut;
class Vertex;

class ElectronMuonOppChrg
{
    int c1E1M, c2E, C2M;
    
public:
    vector<Collection::DATA>*  v;
    
    ElectronMuonOppChrg()
    {
        v= new vector<Collection::DATA>;
    }
    
    int getEW1E1M(){return c1E1M;}
    int getEW2E(){return c2E;}
    int getEW2M(){return C2M;}
    
    vector<Collection::DATA>* setData(Vertex& vtx, ElectronMuon& em, Met& ufmet, Jet& loosefj, Jet& bfj, genINFO& yesEvWEight)
    {
        int Events1e1m = 0;
        int Events2e = 0;
        int Events2m = 0;
        
        TLorentzVector electron;
        TLorentzVector positron;
        TLorentzVector Zcand;
        
        for(unsigned int i=0;i<(em.v->size());i++)//loop over all events
        {
            if((ufmet.v->at(i))->size() == 0) continue;
            if((((em.v->at(i))->size())) < 2) continue;
            if((((em.v->at(i))->at(0)).pt) < 25) continue;
            if((((em.v->at(i))->at(0)).charge * ((em.v->at(i))->at(1)).charge) > 0) continue;
            
            electron.SetPtEtaPhiE(((em.v->at(i))->at(0)).pt,((em.v->at(i))->at(0)).eta,((em.v->at(i))->at(0)).phi,((em.v->at(i))->at(0)).energy);
            positron.SetPtEtaPhiE(((em.v->at(i))->at(1)).pt,((em.v->at(i))->at(1)).eta,((em.v->at(i))->at(1)).phi,((em.v->at(i))->at(1)).energy);
            Zcand = electron + positron;
            if(Zcand.M() < 20) continue;
            
            Collection::DATA emd;
            
            emd.evtID=i;
            emd.vtxMult=(vtx.v->at(i))->size();
            if((((((em.v->at(i))->at(0)).PID) == 0) && ((((em.v->at(i))->at(1)).PID) == 1)) || (((((em.v->at(i))->at(0)).PID) == 1) && ((((em.v->at(i))->at(1)).PID) == 0)))
            {
                emd.Catogary=1;//emu
                Events1e1m++;
            }
            if(((((em.v->at(i))->at(0)).PID) == 1) && ((((em.v->at(i))->at(1)).PID) == 1))
            {
                emd.Catogary=2;//2mu
                Events2m++;
            }
            if(((((em.v->at(i))->at(0)).PID) == 0) && ((((em.v->at(i))->at(1)).PID) == 0))
            {
                emd.Catogary=3;//2e
                Events2e++;
            }
            
            emd.P1ID=((em.v->at(i))->at(0)).PID;
            emd.P2ID=((em.v->at(i))->at(1)).PID;
            emd.P1ch=((em.v->at(i))->at(0)).charge;
            emd.P2ch=((em.v->at(i))->at(1)).charge;
            emd.LeadingLeptPt=((em.v->at(i))->at(0)).pt;
            emd.LeadingLeptEta=((em.v->at(i))->at(0)).eta;
            emd.LeadingLeptPhi=((em.v->at(i))->at(0)).phi;
            emd.LeadingLeptEnergy=((em.v->at(i))->at(0)).energy;
            emd.SubLeadingLeptPt=((em.v->at(i))->at(1)).pt;
            emd.SubLeadingLeptEta=((em.v->at(i))->at(1)).eta;
            emd.SubLeadingLeptPhi=((em.v->at(i))->at(1)).phi;
            emd.SubLeadingLeptEnergy=((em.v->at(i))->at(1)).energy;
            
            if((((em.v->at(i))->at(0)).PID) == 0)
            {
                emd.electronPt=((em.v->at(i))->at(0)).pt;
                emd.electronEta=((em.v->at(i))->at(0)).eta;
                emd.electronPhi=((em.v->at(i))->at(0)).phi;
                emd.electronEnergy=((em.v->at(i))->at(0)).energy;
            }
            else
            {
                emd.electronPt=0.0;
                emd.electronEta=10.4;
                emd.electronPhi=10.4;
                emd.electronEnergy=0.0;
            }
            if((((em.v->at(i))->at(0)).PID) == 1)
            {
                emd.muonPt=((em.v->at(i))->at(0)).pt;
                emd.muonEta=((em.v->at(i))->at(0)).eta;
                emd.muonPhi=((em.v->at(i))->at(0)).phi;
                emd.muonEnergy=((em.v->at(i))->at(0)).energy;
            }
            else
            {
                emd.muonPt=0.0;
                emd.muonEta=10.4;
                emd.muonPhi=10.4;
                emd.muonEnergy=0.0;
            }
            
            emd.mll=Zcand.M();
            emd.metPt=(ufmet.v->at(i)->at(0)).pt;
            if((loosefj.v->at(i))->size() >=1 ) emd.jetPtLeading=(loosefj.v->at(i)->at(0)).pt;
            else emd.jetPtLeading=-100.0;
            if((loosefj.v->at(i))->size() >=2 ) emd.jetPtSubLeading=(loosefj.v->at(i)->at(1)).pt;
            else emd.jetPtSubLeading=-100.0;
            if((loosefj.v->at(i))->size() >=1 ) emd.jetRapidityLeading=(loosefj.v->at(i)->at(0)).rapidit;
            else emd.jetRapidityLeading=1000.0;
            if((loosefj.v->at(i))->size() >=2 ) emd.jetRapiditySubLeading=(loosefj.v->at(i)->at(1)).rapidit;
            else emd.jetRapiditySubLeading=1000.0;
            if((loosefj.v->at(i))->size() >=1 ) emd.jetEtaLeading=(loosefj.v->at(i)->at(0)).eta;
            else emd.jetEtaLeading=1000.0;
            if((loosefj.v->at(i))->size() >=2 ) emd.jetEtaSubLeading=(loosefj.v->at(i)->at(1)).eta;
            else emd.jetEtaSubLeading=1000.0;
            if((loosefj.v->at(i))->size() >=1 ) emd.jetPhiLeading=(loosefj.v->at(i)->at(0)).phi;
            else emd.jetPhiLeading=1000.0;
            if((loosefj.v->at(i))->size() >=2 ) emd.jetPhiSubLeading=(loosefj.v->at(i)->at(1)).phi;
            else emd.jetPhiSubLeading=1000.0;
            emd.loosejetMult=(loosefj.v->at(i))->size();
            emd.bJETMult=(bfj.v->at(i))->size();
            emd.genProductWeight=((yesEvWEight.v->at(i))->at(0)).eWeight;
            emd.PUinfo=((yesEvWEight.v->at(i))->at(0)).puNtrueInteractons;
            
            v->push_back(emd);
        }
        c1E1M = Events1e1m;
        c2E = Events2e;
        C2M = Events2m;
        return v;
    }
    
    ~ElectronMuonOppChrg()
    {
        delete v;
        v=0;
    }
    
    friend class Mllcut;
};
