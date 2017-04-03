class ElectronMuonMet;
class Jet;

class JetSelection
{
    int cSelect1j1tem,cSelect1j1t2m,cSelect1j1t2e,cSelect2j1tem,cSelect2j1t2m,cSelect2j1t2e,cSelect2j2tem,cSelect2j2t2m,cSelect2j2t2e;
    int cnjg2emu,cnjg22mu,cnjg22e,cnjg1emu,cnjg12mu,cnjg12e,cnbjg1emu,cnbjg12mu,cnbjg12e,cnjeq1emu,cnjeq12mu,cnjeq12e,cnbjeq1emu,cnbjeq12mu,cnbjeq12e;
    
public:
    vector<Collection::DATA>*  v;
    JetSelection()
    {
        v= new vector<Collection::DATA>;
    }
   
    int get1j1tem(){return cSelect1j1tem;}
    int get1j1t2m(){return cSelect1j1t2m;}
    int get1j1t2e(){return cSelect1j1t2e;}
    
    int get2j1tem(){return cSelect2j1tem;}
    int get2j1t2m(){return cSelect2j1t2m;}
    int get2j1t2e(){return cSelect2j1t2e;}
    
    int get2j2tem(){return cSelect2j2tem;}
    int get2j2t2m(){return cSelect2j2t2m;}
    int get2j2t2e(){return cSelect2j2t2e;}
    
    int getcnjg2emu(){return cnjg2emu;}
    int getcnjg22mu(){return cnjg22mu;}
    int getcnjg22e(){return cnjg22e;}
    int getcnjg1emu(){return cnjg1emu;}
    int getcnjg12mu(){return cnjg12mu;}
    int getcnjg12e(){return cnjg12e;}
    int getcnbjg1emu(){return cnbjg1emu;}
    int getcnbjg12mu(){return cnbjg12mu;}
    int getcnbjg12e(){return cnbjg12e;}
    int getcnjeq1emu(){return cnjeq1emu;}
    int getcnjeq12mu(){return cnjeq12mu;}
    int getcnjeq12e(){return cnjeq12e;}
    int getcnbjeq1emu(){return cnbjeq1emu;}
    int getcnbjeq12mu(){return cnbjeq12mu;}
    int getcnbjeq12e(){return cnbjeq12e;}
    
    vector<Collection::DATA>* setData1j1t(ElectronMuonMet& em, Jet& fj)
    {
        //int events = 0;
        int Events1e1m = 0;
        int Events2e = 0;
        int Events2m = 0;
        int njg2emu = 0;
        int njg22mu = 0;
        int njg22e = 0;
        int njg1emu = 0;
        int njg12mu = 0;
        int njg12e = 0;
        int nbjg1emu = 0;
        int nbjg12mu = 0;
        int nbjg12e = 0;
        int njeq1emu = 0;
        int njeq12mu = 0;
        int njeq12e = 0;
        int nbjeq1emu = 0;
        int nbjeq12mu = 0;
        int nbjeq12e = 0;
        
        Collection::DATA emd;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            if((((em.v)->at(i)).loosejetMult) >= 2)
            {
                if((((em.v)->at(i)).Catogary) == 1) njg2emu++;
                if((((em.v)->at(i)).Catogary) == 2) njg22mu++;
                if((((em.v)->at(i)).Catogary) == 3) njg22e++;
            }
            if((((em.v)->at(i)).loosejetMult) >= 1)
            {
                if((((em.v)->at(i)).Catogary) == 1) njg1emu++;
                if((((em.v)->at(i)).Catogary) == 2) njg12mu++;
                if((((em.v)->at(i)).Catogary) == 3) njg12e++;
            }
            if((((em.v)->at(i)).bJETMult) >= 1)
            {
                if((((em.v)->at(i)).Catogary) == 1) nbjg1emu++;
                if((((em.v)->at(i)).Catogary) == 2) nbjg12mu++;
                if((((em.v)->at(i)).Catogary) == 3) nbjg12e++;
            }
            if((((em.v)->at(i)).loosejetMult) == 1)
            {
                if((((em.v)->at(i)).Catogary) == 1) njeq1emu++;
                if((((em.v)->at(i)).Catogary) == 2) njeq12mu++;
                if((((em.v)->at(i)).Catogary) == 3) njeq12e++;
            }
            if((((em.v)->at(i)).bJETMult) == 1 )
            {
                if((((em.v)->at(i)).Catogary) == 1) nbjeq1emu++;
                if((((em.v)->at(i)).Catogary) == 2) nbjeq12mu++;
                if((((em.v)->at(i)).Catogary) == 3) nbjeq12e++;
            }
            cnjg2emu = njg2emu;
            cnjg22mu = njg22mu;
            cnjg22e = njg22e;
            cnjg1emu = njg1emu;
            cnjg12mu = njg12mu;
            cnjg12e = njg12e;
            cnbjg1emu = nbjg1emu;
            cnbjg12mu = nbjg12mu;
            cnbjg12e = nbjg12e;
            cnjeq1emu = njeq1emu;
            cnjeq12mu = njeq12mu;
            cnjeq12e = njeq12e;
            cnbjeq1emu = nbjeq1emu;
            cnbjeq12mu = nbjeq12mu;
            cnbjeq12e = nbjeq12e;
            
            int evtID=((em.v)->at(i)).evtID;
            if(!(((((em.v)->at(i)).loosejetMult) == 1) && ((((em.v)->at(i)).bJETMult) == 1))) continue;
            if(((((em.v)->at(i)).loosejetMult) == 1) && ((((em.v)->at(i)).bJETMult) == 1))
            {
                //events++;
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
            if((((em.v)->at(i)).Catogary)==1) Events1e1m++;
            if((((em.v)->at(i)).Catogary)==2) Events2m++;
            if((((em.v)->at(i)).Catogary)==3) Events2e++;
        }
            cSelect1j1tem = Events1e1m;
            cSelect1j1t2m = Events2m;
            cSelect1j1t2e = Events2e;
            return v;
    }
    
    vector<Collection::DATA>* setData2j1t(ElectronMuonMet& em, Jet& fj)
    {
        //int events = 0;
        int Events1e1m = 0;
        int Events2e = 0;
        int Events2m = 0;
        Collection::DATA emd;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            if(!(((((em.v)->at(i)).loosejetMult) == 2) && ((((em.v)->at(i)).bJETMult) == 1))) continue;
            if(((((em.v)->at(i)).loosejetMult) == 2) && ((((em.v)->at(i)).bJETMult) == 1))
            {
                //events++;
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
            if((((em.v)->at(i)).Catogary)==1) Events1e1m++;
            if((((em.v)->at(i)).Catogary)==2) Events2m++;
            if((((em.v)->at(i)).Catogary)==3) Events2e++;
        }
        cSelect2j1tem = Events1e1m;
        cSelect2j1t2m = Events2m;
        cSelect2j1t2e = Events2e;
        return v;
    }
    
    vector<Collection::DATA>* setData2j2t(ElectronMuonMet& em, Jet& fj)
    {
        //int events = 0;
        int Events1e1m = 0;
        int Events2e = 0;
        int Events2m = 0;
        Collection::DATA emd;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            if(!(((((em.v)->at(i)).loosejetMult) == 2) && ((((em.v)->at(i)).bJETMult) == 2))) continue;
            if(((((em.v)->at(i)).loosejetMult) == 2) && ((((em.v)->at(i)).bJETMult) == 2))
            {
               // events++;
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
            if((((em.v)->at(i)).Catogary)==1) Events1e1m++;
            if((((em.v)->at(i)).Catogary)==2) Events2m++;
            if((((em.v)->at(i)).Catogary)==3) Events2e++;
        }
        cSelect2j2tem = Events1e1m;
        cSelect2j2t2m = Events2m;
        cSelect2j2t2e = Events2e;
        return v;
    }
    
    ~JetSelection()
    {
        delete v;
        v=0;
    }
    
};
