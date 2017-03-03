class Electron;
class Muon;
class ElectronMuonOppChrg;
class Mllcut;

class ElectronMuonExtraLoose:public Histos
{
    int cExLoose1e1m,cExLoose2e,cExLoose2m;
    
public:
    vector<Collection::DATA>*  v;
    ElectronMuonExtraLoose()
    {
        v= new vector<Collection::DATA>;
    }
   
    int getEWExLoose1e1m(){return cExLoose1e1m;}
    int getEWExLoose2e(){return cExLoose2e;}
    int getEWExLoose2m(){return cExLoose2m;}
    
    vector<Collection::DATA>* setData1(ElectronMuonOppChrg& em, Electron& elect, Muon& mu)
    {
        int sselected_events = 0;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            bool isEventSelected=true;
            
           /* for(unsigned int j=0;j<(elect.v->at(evtID))->size();j++)
            {
                if(!((((elect.v->at(evtID))->at(j)).tight.all==true && ((elect.v->at(evtID))->at(j)).loose.all==true && ((elect.v->at(evtID))->at(j)).loose.allNew == true)  || (((elect.v->at(evtID))->at(j)).tight.all==false && ((elect.v->at(evtID))->at(j)).loose.all==false && ((elect.v->at(evtID))->at(j)).loose.allNew == true)))
                {
                    isEventSelected=false;
                    break; //////////ask why break? can use continue?
                }
            }*/
            
          /*  for(unsigned int j=0;j<(elect.v->at(evtID))->size();j++)
            {
                if(!((((elect.v->at(evtID))->at(j)).tight.extraLoose==true && ((elect.v->at(evtID))->at(j)).loose.extraLoose==true)  || (((elect.v->at(evtID))->at(j)).tight.extraLoose==false && ((elect.v->at(evtID))->at(j)).loose.extraLoose==false)))
                {
                    isEventSelected=false;
                    break; //////////ask why break? can use continue?
                }
            }
            */
            for(unsigned int j=0;j<(elect.v->at(evtID))->size();j++)
            {
                if(!((((elect.v->at(evtID))->at(j)).tight.extraLoose==true && ((elect.v->at(evtID))->at(j)).loose.extraLoose==true)  || (((elect.v->at(evtID))->at(j)).tight.extraLoose==false && ((elect.v->at(evtID))->at(j)).loose.extraLoose==false)))
                {
                    isEventSelected=false;
                    break; //////////ask why break? can use continue?
                }
            }
           /* for(unsigned int j=0;j<(mu.v->at(evtID))->size();j++)
            {
                if(!((((mu.v->at(evtID))->at(j)).all==true && ((mu.v->at(evtID))->at(j)).tightc==true && ((mu.v->at(evtID))->at(j)).loosec==true)  || (((mu.v->at(evtID))->at(j)).all==true && ((mu.v->at(evtID))->at(j)).tightc==false && ((mu.v->at(evtID))->at(j)).loosec==false)))
                {
                    isEventSelected=false;
                    break;
                }
            }*/
            
           /* for(unsigned int j=0;j<(mu.v->at(evtID))->size();j++)
            {
                if(!((((mu.v->at(evtID))->at(j)).tightc==true && ((mu.v->at(evtID))->at(j)).loosec==true)  || (((mu.v->at(evtID))->at(j)).tightc==false && ((mu.v->at(evtID))->at(j)).loosec==false)))
                {
                    isEventSelected=false;
                    break;
                }
            }*/
            
            for(unsigned int j=0;j<(mu.v->at(evtID))->size();j++)
            {
                if(!((((mu.v->at(evtID))->at(j)).textraloose==true && ((mu.v->at(evtID))->at(j)).lextraloose==true)  || (((mu.v->at(evtID))->at(j)).textraloose==false && ((mu.v->at(evtID))->at(j)).lextraloose==false)))
                {
                    isEventSelected=false;
                    break;
                }
            }
            
            if (isEventSelected)
            {
                sselected_events++;
                Collection::DATA emelc;
                emelc = em.v->at(i);
                v->push_back(emelc);
            }
        }
        cExLoose1e1m = sselected_events;
        return v;
    }

    vector<Collection::DATA>* setData2(ElectronMuonOppChrg& em, Electron& elect,Muon& ufm)
    {
        int sselected_events = 0;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            bool isEventSelected=true;
            
          /*  for(unsigned int j=0;j<(elect.v->at(evtID))->size();j++)
            {
                if(!((((elect.v->at(evtID))->at(j)).tight.all==true && ((elect.v->at(evtID))->at(j)).loose.all==true && ((elect.v->at(evtID))->at(j)).loose.allNew == true)  || (((elect.v->at(evtID))->at(j)).tight.all==false && ((elect.v->at(evtID))->at(j)).loose.all==false && ((elect.v->at(evtID))->at(j)).loose.allNew == true)))
                {
                    isEventSelected=false;
                    break;
                }
            }*/
            
            for(unsigned int j=0;j<(elect.v->at(evtID))->size();j++)
            {
                if(!((((elect.v->at(evtID))->at(j)).tight.extraLoose==true && ((elect.v->at(evtID))->at(j)).loose.extraLoose==true)  || (((elect.v->at(evtID))->at(j)).tight.extraLoose==false && ((elect.v->at(evtID))->at(j)).loose.extraLoose==false)))
                {
                    isEventSelected=false;
                    break; //////////ask why break? can use continue?
                }
            }
            
            if (isEventSelected)
            {
                sselected_events++;
                Collection::DATA emelc;
                emelc = em.v->at(i);
                v->push_back(emelc);
            }
        }
        cExLoose2e = sselected_events;
        return v;
    }

    vector<Collection::DATA>* setData3(ElectronMuonOppChrg& em,Electron& ufe, Muon& mu)
    {
        int sselected_events = 0;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            bool isEventSelected=true;
            
            for(unsigned int j=0;j<(mu.v->at(evtID))->size();j++)
            {
                if(!((((mu.v->at(evtID))->at(j)).all==true && ((mu.v->at(evtID))->at(j)).tightc==true && ((mu.v->at(evtID))->at(j)).loosec==true)  || (((mu.v->at(evtID))->at(j)).all==true && ((mu.v->at(evtID))->at(j)).tightc==false && ((mu.v->at(evtID))->at(j)).loosec==false)))
                {
                    isEventSelected=false;
                    break;
                }
            }
            
            if (isEventSelected)
            {
                sselected_events++;
                Collection::DATA emelc;
                emelc = em.v->at(i);
                v->push_back(emelc);
            }
        }
        cExLoose2m = sselected_events;
        return v;
    }
    
    ~ElectronMuonExtraLoose()
    {
        delete v;
        v=0;
    }
    
    friend class Mllcut;
};
