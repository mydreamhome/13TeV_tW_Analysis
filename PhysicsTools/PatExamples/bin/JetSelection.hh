class ElectronMuonMet;
class Jet;

class JetSelection:public Histos
{
    int cSelect1j,cSelect2j,cSelectAtleast1j,cSelectAtleast2j;
    
public:
    vector<Collection::DATA>*  v;
    JetSelection()
    {
        v= new vector<Collection::DATA>;
    }
   
    int get1j(){return cSelect1j;}
    int get2j(){return cSelect2j;}
    int getAtleast1j(){return cSelectAtleast1j;}
    int getAtleast2j(){return cSelectAtleast2j;}
    
    vector<Collection::DATA>* setDataAtleast1j(ElectronMuonMet& em, Jet& fj)
    {
        int events = 0;
        Collection::DATA emd;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            if((fj.v->at(evtID))->size()<1) continue;
            if( (fj.v->at(evtID))->size()>=1)
            {
                events++;
                emd = em.v->at(i);
                emd.jetPtLeading=((fj.v->at(evtID))->at(0)).pt;
                if( (fj.v->at(evtID))->size()>=2) emd.jetPtSubLeading=((fj.v->at(evtID))->at(1)).pt;
                else emd.jetPtSubLeading=-100.0;
                emd.jetRapidityLeading=((fj.v->at(evtID))->at(0)).rapidit;
                if( (fj.v->at(evtID))->size()>=2) emd.jetRapiditySubLeading=((fj.v->at(evtID))->at(1)).rapidit;
                else emd.jetRapiditySubLeading=1000.0;
                emd.jetEtaLeading=((fj.v->at(evtID))->at(0)).eta;
                if( (fj.v->at(evtID))->size()>=2) emd.jetEtaSubLeading=((fj.v->at(evtID))->at(1)).eta;
                else emd.jetEtaSubLeading=1000.0;
                emd.jetPhiLeading=((fj.v->at(evtID))->at(0)).phi;
                if( (fj.v->at(evtID))->size()>=2) emd.jetPhiSubLeading=((fj.v->at(evtID))->at(1)).phi;
                else emd.jetPhiSubLeading=1000.0;
                v->push_back(emd);
            }
        }
        cSelectAtleast1j = events;
        return v;
    }
    
    vector<Collection::DATA>* setData1j(ElectronMuonMet& em, Jet& fj)
    {
        int events = 0;
        Collection::DATA emd;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            if((fj.v->at(evtID))->size()!=1) continue;
            if( (fj.v->at(evtID))->size()==1)
            {
                events++;
                emd = em.v->at(i);
                emd.jetPtLeading=((fj.v->at(evtID))->at(0)).pt;
                emd.jetPtSubLeading=-100.0;
                emd.jetRapidityLeading=((fj.v->at(evtID))->at(0)).rapidit;
                emd.jetRapiditySubLeading=1000.0;
                emd.jetEtaLeading=((fj.v->at(evtID))->at(0)).eta;
                emd.jetEtaSubLeading=1000.0;
                emd.jetPhiLeading=((fj.v->at(evtID))->at(0)).phi;
                emd.jetPhiSubLeading=1000.0;
                v->push_back(emd);
            }
        }
            cSelect1j = events;
            return v;
    }
    
    vector<Collection::DATA>* setDataAtleast2j(ElectronMuonMet& em, Jet& fj)
    {
        int events = 0;
        Collection::DATA emd;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            if((fj.v->at(evtID))->size()<2)continue;
            if( (fj.v->at(evtID))->size()>=2)
            {
                events++;
                emd = em.v->at(i);
                emd.jetPtLeading=((fj.v->at(evtID))->at(0)).pt;
                emd.jetPtSubLeading=((fj.v->at(evtID))->at(1)).pt;
                emd.jetRapidityLeading=((fj.v->at(evtID))->at(0)).rapidit;
                emd.jetRapiditySubLeading=((fj.v->at(evtID))->at(1)).rapidit;
                emd.jetEtaLeading=((fj.v->at(evtID))->at(0)).eta;
                emd.jetEtaSubLeading=((fj.v->at(evtID))->at(1)).eta;
                emd.jetPhiLeading=((fj.v->at(evtID))->at(0)).phi;
                emd.jetPhiSubLeading=((fj.v->at(evtID))->at(1)).phi;
                v->push_back(emd);
            }
        }
        cSelectAtleast2j = events;
        return v;
    }
    
    vector<Collection::DATA>* setData2j(ElectronMuonMet& em, Jet& fj)
    {
        int events = 0;
        Collection::DATA emd;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            if((fj.v->at(evtID))->size()!=2)continue;
            if( (fj.v->at(evtID))->size()==2)
            {
                events++;
                emd = em.v->at(i);
                emd.jetPtLeading=((fj.v->at(evtID))->at(0)).pt;
                emd.jetPtSubLeading=((fj.v->at(evtID))->at(1)).pt;
                emd.jetRapidityLeading=((fj.v->at(evtID))->at(0)).rapidit;
                emd.jetRapiditySubLeading=((fj.v->at(evtID))->at(1)).rapidit;
                emd.jetEtaLeading=((fj.v->at(evtID))->at(0)).eta;
                emd.jetEtaSubLeading=((fj.v->at(evtID))->at(1)).eta;
                emd.jetPhiLeading=((fj.v->at(evtID))->at(0)).phi;
                emd.jetPhiSubLeading=((fj.v->at(evtID))->at(1)).phi;
                v->push_back(emd);
            }
        }
        cSelect2j = events;
        return v;
    }
    
    ~JetSelection()
    {
        delete v;
        v=0;
    }
    
};
