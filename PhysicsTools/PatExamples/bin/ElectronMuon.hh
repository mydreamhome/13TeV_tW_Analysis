class Electron;
class genINFO;
class Muon;
class Met;
class Jet;
class Vertex;
class HLT;
class ElectronMuonOppChrg;

class ElectronMuon:public Histos
{
   
    int c1E1M, c2E, C2M;
    
public:
     vector<Collection::DATA>*  v;
    ElectronMuon()
    {
        v= new vector<Collection::DATA>;
    }
    
    int getEW1E1M(){return c1E1M;}
    int getEW2E(){return c2E;}
    int getEW2M(){return C2M;}
    
    vector<Collection::DATA>* setData1(Electron& fe,Muon& fm,Electron& ufe,Muon& ufm, Met& ufmet, Jet& ufj, Vertex& fvtx, Vertex& vtx, Jet& cleanfj, HLT& seeHLT, genINFO& yesEvWEight)
    {
  //  cout<<"entering emu setdata1:    "<<endl<<endl;
        int events = 0;
        TLorentzVector electron;
        TLorentzVector positron;
        TLorentzVector Zcand;
      //  cout<<"e mu channel:    "<<endl<<endl;
        for(unsigned int i=0;i<(fe.v->size());i++)//loop over all events
        {
            //if((seeHLT.v->at(i))->size()!=1) continue;
            if((fvtx.v->at(i))->size()!=1) continue;
            int c=0;
            int chargeSign = 0;
            if((fe.v->at(i))->size()!=1 || (fm.v->at(i))->size()!=1)continue;
            
            Collection::DATA emd;
            if( (fe.v->at(i))->size()==1 && (fm.v->at(i))->size()==1)
            {
                chargeSign = (((fe.v->at(i))->at(0)).charge < 0 )?(((fe.v->at(i))->at(0)).charge):1;
                if(chargeSign < 0)
                {
                    electron.SetPtEtaPhiE(((fe.v->at(i))->at(0)).pt,((fe.v->at(i))->at(0)).eta,((fe.v->at(i))->at(0)).phi,((fe.v->at(i))->at(0)).energy);
                    positron.SetPtEtaPhiE(((fm.v->at(i))->at(0)).pt,((fm.v->at(i))->at(0)).eta,((fm.v->at(i))->at(0)).phi,((fm.v->at(i))->at(0)).energy);
                }
                if(chargeSign > 0)
                {
                    electron.SetPtEtaPhiE(((fm.v->at(i))->at(0)).pt,((fm.v->at(i))->at(0)).eta,((fm.v->at(i))->at(0)).phi,((fm.v->at(i))->at(0)).energy);
                    positron.SetPtEtaPhiE(((fe.v->at(i))->at(0)).pt,((fe.v->at(i))->at(0)).eta,((fe.v->at(i))->at(0)).phi,((fe.v->at(i))->at(0)).energy);
                }
                
                Zcand = electron + positron;
                
             //   int ECountLooseLept10MultIso=0;
            //    int ECounttight10MultIso=0;
                int ECounttightLept10MultIso=0;
                int ECounttight20MultIso=0;
                int ECountLooseLept10MultIso=0;
                int ECountLooseLept10MultNonIso=0;
                int ECounttight10MultNonIso=0;
                
//int MCountLooseLept10MultIso=0;
              //  int MCounttight10MultIso=0;
                int MCounttightLept10MultIso=0;
                int MCounttight20MultIso=0;
                int MCountLooseLept10MultIso=0;
                int MCountLooseLept10MultNonIso=0;
                int MCounttight10MultNonIso=0;
                for(unsigned int k=0;k<((ufe.v->at(i))->size());k++)
                {
                 /*   if(((ufe.v->at(i))->at(k)).loose.all && ((ufe.v->at(i))->at(k)).loose.etac && ((ufe.v->at(i))->at(k)).iso < 0.11 && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECountLooseLept10MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).tight.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).iso < 0.11 && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECounttight10MultIso++;
                    }*/
                    if(((ufe.v->at(i))->at(k)).tight.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECounttightLept10MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).tight.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 20)
                    {
                        ECounttight20MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).loose.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECountLooseLept10MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).loose.vetoc && ((ufe.v->at(i))->at(k)).loose.mhitsc && ((ufe.v->at(i))->at(k)).loose.fullSigmaEtaEtac && ((ufe.v->at(i))->at(k)).loose.dEtaInc && ((ufe.v->at(i))->at(k)).loose.dPhiInc && ((ufe.v->at(i))->at(k)).loose.HoverEc && ((ufe.v->at(i))->at(k)).loose.ooEmooPc && ((ufe.v->at(i))->at(k)).loose.d0c && ((ufe.v->at(i))->at(k)).loose.dzc && !(((ufe.v->at(i))->at(k)).loose.isoc) && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECountLooseLept10MultNonIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).tight.vetoc && ((ufe.v->at(i))->at(k)).tight.mhitsc && ((ufe.v->at(i))->at(k)).tight.fullSigmaEtaEtac && ((ufe.v->at(i))->at(k)).tight.dEtaInc && ((ufe.v->at(i))->at(k)).tight.dPhiInc && ((ufe.v->at(i))->at(k)).tight.HoverEc && ((ufe.v->at(i))->at(k)).tight.ooEmooPc && ((ufe.v->at(i))->at(k)).tight.d0c && ((ufe.v->at(i))->at(k)).tight.dzc && !(((ufe.v->at(i))->at(k)).tight.isoc) && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECounttight10MultNonIso++;
                    }
                }
                for(unsigned int k=0;k<((ufm.v->at(i))->size());k++)
                {
                 /*   if(((ufm.v->at(i))->at(k)).loosec && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).isoc && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCountLooseLept10MultIso++;
                    }
                    if(((ufm.v->at(i))->at(k)).tightc && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).isoc && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCounttight10MultIso++;
                    }*/
                    if(((ufm.v->at(i))->at(k)).tightc && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCounttightLept10MultIso++;
                    }
                    if(((ufm.v->at(i))->at(k)).tightc && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 20)
                    {
                        MCounttight20MultIso++;
                    }
                    if(((ufm.v->at(i))->at(k)).loosec && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCountLooseLept10MultIso++;
                    }
                    if(((((ufm.v->at(i))->at(k)).loose != 0)?true:false) && !(((ufm.v->at(i))->at(k)).isolc) && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCountLooseLept10MultNonIso++;
                    }
                    if(((((ufm.v->at(i))->at(k)).tight != 0)?true:false) && !(((ufm.v->at(i))->at(k)).isotc) && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCounttight10MultNonIso++;
                    }
                }
               /* int CountLooseLept10MultIso=ECountLooseLept10MultIso + MCountLooseLept10MultIso;
                int Counttight10MultIso=ECounttight10MultIso + MCounttight10MultIso;*/
               
                int CounttightLept10MultIso=ECounttightLept10MultIso + MCounttightLept10MultIso;
                int Counttight20MultIso=ECounttight20MultIso + MCounttight20MultIso;
                int CountLooseLept10MultIso= ECountLooseLept10MultIso + MCountLooseLept10MultIso;
                int CountLooseLept10MultNonIso= ECountLooseLept10MultNonIso + MCountLooseLept10MultNonIso;
                int Counttight10MultNonIso= ECounttight10MultNonIso + MCounttight10MultNonIso;
                
                
                int CountLooseLept10MultNoIso=CountLooseLept10MultIso + CountLooseLept10MultNonIso;
                int Counttight10MultNoIso=CounttightLept10MultIso + Counttight10MultNonIso;
                
                emd.evtID=i;
                emd.vtxMult=(vtx.v->at(i))->size();
                emd.eID=((fe.v->at(i))->at(0)).eID;
                emd.mID=((fm.v->at(i))->at(0)).mID;
                emd.TotalLeptMult=((((ufe.v->at(i))->size())+((ufm.v->at(i))->size())));
                emd.ech=((fe.v->at(i))->at(0)).charge;
                emd.mch=((fm.v->at(i))->at(0)).charge;
                emd.electronPt=((fe.v->at(i))->at(0)).pt;
                emd.electronEta=((fe.v->at(i))->at(0)).eta;
                emd.electronPhi=((fe.v->at(i))->at(0)).phi;
                emd.muonPt=((fm.v->at(i))->at(0)).pt;
                emd.muonEta=((fm.v->at(i))->at(0)).eta;
                emd.muonPhi=((fm.v->at(i))->at(0)).phi;
                emd.electronEnergy=((fe.v->at(i))->at(0)).energy;
                emd.muonEnergy=((fm.v->at(i))->at(0)).energy;
                emd.mll=Zcand.M();
                emd.metPt=(ufmet.v->at(i)->at(0)).pt;
                if((ufj.v->at(i))->size() >=1 ) emd.jetPtLeading=(ufj.v->at(i)->at(0)).pt;
                else emd.jetPtLeading=-100.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetPtSubLeading=(ufj.v->at(i)->at(1)).pt;
                else emd.jetPtSubLeading=-100.0;
                if((ufj.v->at(i))->size() >=1 ) emd.jetRapidityLeading=(ufj.v->at(i)->at(0)).rapidit;
                else emd.jetRapidityLeading=1000.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetRapiditySubLeading=(ufj.v->at(i)->at(1)).rapidit;
                else emd.jetRapiditySubLeading=1000.0;
                if((ufj.v->at(i))->size() >=1 ) emd.jetEtaLeading=(ufj.v->at(i)->at(0)).eta;
                else emd.jetEtaLeading=1000.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetEtaSubLeading=(ufj.v->at(i)->at(1)).eta;
                else emd.jetEtaSubLeading=1000.0;
                if((ufj.v->at(i))->size() >=1 ) emd.jetPhiLeading=(ufj.v->at(i)->at(0)).phi;
                else emd.jetPhiLeading=1000.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetPhiSubLeading=(ufj.v->at(i)->at(1)).phi;
                else emd.jetPhiSubLeading=1000.0;
                emd.jetMult=(ufj.v->at(i))->size();
                emd.CLeanedJETMult=(cleanfj.v->at(i))->size();
                emd.LooseLept10MultIso=(CountLooseLept10MultIso);
                emd.tight10MultIso=(CounttightLept10MultIso);
                emd.tight10MultNonIso=(Counttight10MultNonIso);
                emd.tight20MultIso=(Counttight20MultIso);
                emd.LooseLept10MultNonIso=(CountLooseLept10MultNonIso);
                emd.LooseLept10MultNoIso=(CountLooseLept10MultNoIso);
                emd.tight10MultNoIso=(Counttight10MultNoIso);
                //if((yesEvWEight.v->at(i))->size() ==1 )emd.genProductWeight=((yesEvWEight.v->at(i))->at(0)).eWeight;
                emd.genProductWeight=((yesEvWEight.v->at(i))->at(0)).eWeight;
                emd.PUinfo=((yesEvWEight.v->at(i))->at(0)).puNtrueInteractons;
                c++;
            }
            if(c==1)
            {
                events++;
                v->push_back(emd);
               /* if(emd.muonPt < 23)
                {
                   cout<<"muon pt is less then 23 Gev"<<endl;
                }*/
            }
        }
        c1E1M = events;
        return v;
    }
    
    vector<Collection::DATA>* setData2(Electron& fe,Electron& ufe,Muon& ufm, Met& ufmet, Jet& ufj, Vertex& fvtx, Vertex& vtx)
    {
        int events = 0;
        TLorentzVector electron;
        TLorentzVector positron;
        TLorentzVector Zcand;
      //  cout<<"e e channel:    "<<endl<<endl;
        for(unsigned int i=0;i<(fe.v->size());i++)//loop over all events
        {
            if((fvtx.v->at(i))->size()!=1)continue;
            int c=0;
            int chargeSign = 0;
            if((fe.v->at(i))->size()!=2)continue;
            
            Collection::DATA emd;
            if( (fe.v->at(i))->size()==2)
            {
                chargeSign = (((fe.v->at(i))->at(0)).charge < 0 )?(((fe.v->at(i))->at(0)).charge):1;
                if(chargeSign < 0)
                {
                    electron.SetPtEtaPhiE(((fe.v->at(i))->at(0)).pt,((fe.v->at(i))->at(0)).eta,((fe.v->at(i))->at(0)).phi,((fe.v->at(i))->at(0)).energy);
                    positron.SetPtEtaPhiE(((fe.v->at(i))->at(1)).pt,((fe.v->at(i))->at(1)).eta,((fe.v->at(i))->at(1)).phi,((fe.v->at(i))->at(1)).energy);
                }
                if(chargeSign > 0)
                {
                    electron.SetPtEtaPhiE(((fe.v->at(i))->at(1)).pt,((fe.v->at(i))->at(1)).eta,((fe.v->at(i))->at(1)).phi,((fe.v->at(i))->at(1)).energy);
                    positron.SetPtEtaPhiE(((fe.v->at(i))->at(0)).pt,((fe.v->at(i))->at(0)).eta,((fe.v->at(i))->at(0)).phi,((fe.v->at(i))->at(0)).energy);
                }
                
                Zcand = electron + positron;
                
          //      int ECountLooseLept10MultIso=0;
            //    int ECounttight10MultIso=0;
                int ECounttightLept10MultIso=0;
                int ECounttight20MultIso=0;
                int ECountLooseLept10MultIso=0;
                int ECountLooseLept10MultNonIso=0;
                int ECounttight10MultNonIso=0;
                
           //     int MCountLooseLept10MultIso=0;
             //   int MCounttight10MultIso=0;
                int MCounttightLept10MultIso=0;
                int MCounttight20MultIso=0;
                int MCountLooseLept10MultIso=0;
                int MCountLooseLept10MultNonIso=0;
                int MCounttight10MultNonIso=0;
                for(unsigned int k=0;k<((ufe.v->at(i))->size());k++)
                {
                  /*  if(((ufe.v->at(i))->at(k)).loose.all && ((ufe.v->at(i))->at(k)).loose.etac && ((ufe.v->at(i))->at(k)).loose.isoc && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECountLooseLept10MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).tight.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).tight.isoc && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECounttight10MultIso++;
                    }*/
                    if(((ufe.v->at(i))->at(k)).tight.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECounttightLept10MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).tight.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 20)
                    {
                        ECounttight20MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).loose.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECountLooseLept10MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).loose.vetoc && ((ufe.v->at(i))->at(k)).loose.mhitsc && ((ufe.v->at(i))->at(k)).loose.fullSigmaEtaEtac && ((ufe.v->at(i))->at(k)).loose.dEtaInc && ((ufe.v->at(i))->at(k)).loose.dPhiInc && ((ufe.v->at(i))->at(k)).loose.HoverEc && ((ufe.v->at(i))->at(k)).loose.ooEmooPc && ((ufe.v->at(i))->at(k)).loose.d0c && ((ufe.v->at(i))->at(k)).loose.dzc && !(((ufe.v->at(i))->at(k)).loose.isoc) && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECountLooseLept10MultNonIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).tight.vetoc && ((ufe.v->at(i))->at(k)).tight.mhitsc && ((ufe.v->at(i))->at(k)).tight.fullSigmaEtaEtac && ((ufe.v->at(i))->at(k)).tight.dEtaInc && ((ufe.v->at(i))->at(k)).tight.dPhiInc && ((ufe.v->at(i))->at(k)).tight.HoverEc && ((ufe.v->at(i))->at(k)).tight.ooEmooPc && ((ufe.v->at(i))->at(k)).tight.d0c && ((ufe.v->at(i))->at(k)).tight.dzc && !(((ufe.v->at(i))->at(k)).tight.isoc) && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECounttight10MultNonIso++;
                    }
                }
                for(unsigned int k=0;k<((ufm.v->at(i))->size());k++)
                {
                  /*  if(((ufm.v->at(i))->at(k)).loosec && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).isoc && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCountLooseLept10MultIso++;
                    }
                    if(((ufm.v->at(i))->at(k)).tightc && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).isoc && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCounttight10MultIso++;
                    }*/
                    if(((ufm.v->at(i))->at(k)).tightc && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCounttightLept10MultIso++;
                    }
                    if(((ufm.v->at(i))->at(k)).tightc && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 20)
                    {
                        MCounttight20MultIso++;
                    }
                    if(((ufm.v->at(i))->at(k)).loosec && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCountLooseLept10MultIso++;
                    }
                    if(((((ufm.v->at(i))->at(k)).loose != 0)?true:false) && !(((ufm.v->at(i))->at(k)).isolc) && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCountLooseLept10MultNonIso++;
                    }
                    if(((((ufm.v->at(i))->at(k)).tight != 0)?true:false) && !(((ufm.v->at(i))->at(k)).isotc) && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCounttight10MultNonIso++;
                    }
                }
            //    int CountLooseLept10MultIso=ECountLooseLept10MultIso + MCountLooseLept10MultIso;
              //  int Counttight10MultIso=ECounttight10MultIso + MCounttight10MultIso;
                int CounttightLept10MultIso=ECounttightLept10MultIso + MCounttightLept10MultIso;
                int Counttight20MultIso=ECounttight20MultIso + MCounttight20MultIso;
                int CountLooseLept10MultIso= ECountLooseLept10MultIso + MCountLooseLept10MultIso;
                int CountLooseLept10MultNonIso= ECountLooseLept10MultNonIso + MCountLooseLept10MultNonIso;
                int Counttight10MultNonIso= ECounttight10MultNonIso + MCounttight10MultNonIso;
                
                int CountLooseLept10MultNoIso=CountLooseLept10MultIso + CountLooseLept10MultNonIso;
                int Counttight10MultNoIso=CounttightLept10MultIso + Counttight10MultNonIso;
                
                emd.evtID=i;
                emd.vtxMult=(vtx.v->at(i))->size();
                emd.eID=((fe.v->at(i))->at(0)).eID;
                emd.mID=((fe.v->at(i))->at(1)).eID;
                emd.TotalLeptMult=((((ufe.v->at(i))->size())+((ufm.v->at(i))->size())));
                emd.ech=((fe.v->at(i))->at(0)).charge;
                emd.mch=((fe.v->at(i))->at(1)).charge;
                emd.electronPt=((fe.v->at(i))->at(0)).pt;
                emd.electronEta=((fe.v->at(i))->at(0)).eta;
                emd.electronPhi=((fe.v->at(i))->at(0)).phi;
                emd.muonPt=((fe.v->at(i))->at(1)).pt;
                emd.muonEta=((fe.v->at(i))->at(1)).eta;
                emd.muonPhi=((fe.v->at(i))->at(1)).phi;
                emd.electronEnergy=((fe.v->at(i))->at(0)).energy;
                emd.muonEnergy=((fe.v->at(i))->at(1)).energy;
                emd.mll=Zcand.M();
                emd.metPt=(ufmet.v->at(i)->at(0)).pt;
                if((ufj.v->at(i))->size() >=1 ) emd.jetPtLeading=(ufj.v->at(i)->at(0)).pt;
                else emd.jetPtLeading=-100.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetPtSubLeading=(ufj.v->at(i)->at(1)).pt;
                else emd.jetPtSubLeading=-100.0;
                if((ufj.v->at(i))->size() >=1 ) emd.jetRapidityLeading=(ufj.v->at(i)->at(0)).rapidit;
                else emd.jetRapidityLeading=1000.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetRapiditySubLeading=(ufj.v->at(i)->at(1)).rapidit;
                else emd.jetRapiditySubLeading=1000.0;
                if((ufj.v->at(i))->size() >=1 ) emd.jetEtaLeading=(ufj.v->at(i)->at(0)).eta;
                else emd.jetEtaLeading=1000.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetEtaSubLeading=(ufj.v->at(i)->at(1)).eta;
                else emd.jetEtaSubLeading=1000.0;
                if((ufj.v->at(i))->size() >=1 ) emd.jetPhiLeading=(ufj.v->at(i)->at(0)).phi;
                else emd.jetPhiLeading=1000.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetPhiSubLeading=(ufj.v->at(i)->at(1)).phi;
                else emd.jetPhiSubLeading=1000.0;
                emd.jetMult=(ufj.v->at(i))->size();
                emd.LooseLept10MultIso=(CountLooseLept10MultIso);
                emd.tight10MultIso=(CounttightLept10MultIso);
                emd.tight10MultNonIso=(Counttight10MultNonIso);
                emd.tight20MultIso=(Counttight20MultIso);
                emd.LooseLept10MultNonIso=(CountLooseLept10MultNonIso);
                emd.LooseLept10MultNoIso=(CountLooseLept10MultNoIso);
                emd.tight10MultNoIso=(Counttight10MultNoIso);
                
             //   cout<<"LooseLept10MultIso  :  "<<CountLooseLept10MultIso<<"  tight10MultIso :  "<<Counttight10MultIso<<"  tight10MultNonIso : "<<Counttight10MultNonIso<<"  tight20MultNonIso :  "<<Counttight20MultNonIso<<endl;
                c++;
            }
            if(c==1)
            {
                events++;
                v->push_back(emd);
            }
        }
        c2E = events;
        return v;
    }
  
    vector<Collection::DATA>* setData3(Muon& fm,Electron& ufe,Muon& ufm, Met& ufmet, Jet& ufj, Vertex& fvtx, Vertex& vtx)
    {
        int events = 0;
        TLorentzVector electron;
        TLorentzVector positron;
        TLorentzVector Zcand;
      //  cout<<"mu mu channel:    "<<endl<<endl;
        for(unsigned int i=0;i<fm.v->size();i++)//loop over all events
        {
            if((fvtx.v->at(i))->size()!=1)continue;
            int c=0;
            int chargeSign = 0;
            if((fm.v->at(i))->size()!=2)continue;
            
            Collection::DATA emd;
            if( (fm.v->at(i))->size()==2)
            {
                chargeSign = (((fm.v->at(i))->at(0)).charge < 0 )?(((fm.v->at(i))->at(0)).charge):1;
                if(chargeSign < 0)
                {
                    electron.SetPtEtaPhiE(((fm.v->at(i))->at(0)).pt,((fm.v->at(i))->at(0)).eta,((fm.v->at(i))->at(0)).phi,((fm.v->at(i))->at(0)).energy);
                    positron.SetPtEtaPhiE(((fm.v->at(i))->at(1)).pt,((fm.v->at(i))->at(1)).eta,((fm.v->at(i))->at(1)).phi,((fm.v->at(i))->at(1)).energy);
                }
                if(chargeSign > 0)
                {
                    electron.SetPtEtaPhiE(((fm.v->at(i))->at(1)).pt,((fm.v->at(i))->at(1)).eta,((fm.v->at(i))->at(1)).phi,((fm.v->at(i))->at(1)).energy);
                    positron.SetPtEtaPhiE(((fm.v->at(i))->at(0)).pt,((fm.v->at(i))->at(0)).eta,((fm.v->at(i))->at(0)).phi,((fm.v->at(i))->at(0)).energy);
                }
                
                Zcand = electron + positron;
                
            //    int ECountLooseLept10MultIso=0;
              //  int ECounttight10MultIso=0;
                int ECounttightLept10MultIso=0;
                int ECounttight20MultIso=0;
                int ECountLooseLept10MultIso=0;
                int ECountLooseLept10MultNonIso=0;
                int ECounttight10MultNonIso=0;
                
            //    int MCountLooseLept10MultIso=0;
              //  int MCounttight10MultIso=0;
                int MCounttightLept10MultIso=0;
                int MCounttight20MultIso=0;
                int MCountLooseLept10MultIso=0;
                int MCountLooseLept10MultNonIso=0;
                int MCounttight10MultNonIso=0;
                for(unsigned int k=0;k<((ufe.v->at(i))->size());k++)
                {
                  /*  if(((ufe.v->at(i))->at(k)).loose.all && ((ufe.v->at(i))->at(k)).loose.etac && ((ufe.v->at(i))->at(k)).loose.isoc && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECountLooseLept10MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).tight.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).tight.isoc && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECounttight10MultIso++;
                    }*/
                    if(((ufe.v->at(i))->at(k)).tight.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECounttightLept10MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).tight.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 20)
                    {
                        ECounttight20MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).loose.all && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECountLooseLept10MultIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).loose.vetoc && ((ufe.v->at(i))->at(k)).loose.mhitsc && ((ufe.v->at(i))->at(k)).loose.fullSigmaEtaEtac && ((ufe.v->at(i))->at(k)).loose.dEtaInc && ((ufe.v->at(i))->at(k)).loose.dPhiInc && ((ufe.v->at(i))->at(k)).loose.HoverEc && ((ufe.v->at(i))->at(k)).loose.ooEmooPc && ((ufe.v->at(i))->at(k)).loose.d0c && ((ufe.v->at(i))->at(k)).loose.dzc && !(((ufe.v->at(i))->at(k)).loose.isoc) && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECountLooseLept10MultNonIso++;
                    }
                    if(((ufe.v->at(i))->at(k)).tight.vetoc && ((ufe.v->at(i))->at(k)).tight.mhitsc && ((ufe.v->at(i))->at(k)).tight.fullSigmaEtaEtac && ((ufe.v->at(i))->at(k)).tight.dEtaInc && ((ufe.v->at(i))->at(k)).tight.dPhiInc && ((ufe.v->at(i))->at(k)).tight.HoverEc && ((ufe.v->at(i))->at(k)).tight.ooEmooPc && ((ufe.v->at(i))->at(k)).tight.d0c && ((ufe.v->at(i))->at(k)).tight.dzc && !(((ufe.v->at(i))->at(k)).tight.isoc) && ((ufe.v->at(i))->at(k)).tight.etac && ((ufe.v->at(i))->at(k)).pt > 10)
                    {
                        ECounttight10MultNonIso++;
                    }
                }
                for(unsigned int k=0;k<((ufm.v->at(i))->size());k++)
                {
                   /* if(((ufm.v->at(i))->at(k)).loosec && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).isoc && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCountLooseLept10MultIso++;
                    }
                    if(((ufm.v->at(i))->at(k)).tightc && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).isoc && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCounttight10MultIso++;
                    }*/
                    if(((ufm.v->at(i))->at(k)).tightc && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCounttightLept10MultIso++;
                    }
                    if(((ufm.v->at(i))->at(k)).tightc && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 20)
                    {
                        MCounttight20MultIso++;
                    }
                    if(((ufm.v->at(i))->at(k)).loosec && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCountLooseLept10MultIso++;
                    }
                    if(((((ufm.v->at(i))->at(k)).loose != 0)?true:false) && !(((ufm.v->at(i))->at(k)).isolc) && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCountLooseLept10MultNonIso++;
                    }
                    if(((((ufm.v->at(i))->at(k)).tight != 0)?true:false) && !(((ufm.v->at(i))->at(k)).isotc) && ((ufm.v->at(i))->at(k)).etac && ((ufm.v->at(i))->at(k)).pt > 10)
                    {
                        MCounttight10MultNonIso++;
                    }
                }
          //      int CountLooseLept10MultIso=ECountLooseLept10MultIso + MCountLooseLept10MultIso;
            //    int Counttight10MultIso=ECounttight10MultIso + MCounttight10MultIso;
                int CounttightLept10MultIso=ECounttightLept10MultIso + MCounttightLept10MultIso;
                int Counttight20MultIso=ECounttight20MultIso + MCounttight20MultIso;
                int CountLooseLept10MultIso= ECountLooseLept10MultIso + MCountLooseLept10MultIso;
                int CountLooseLept10MultNonIso= ECountLooseLept10MultNonIso + MCountLooseLept10MultNonIso;
                int Counttight10MultNonIso= ECounttight10MultNonIso + MCounttight10MultNonIso;
                
                int CountLooseLept10MultNoIso=CountLooseLept10MultIso + CountLooseLept10MultNonIso;
                int Counttight10MultNoIso=CounttightLept10MultIso + Counttight10MultNonIso;
                
                emd.evtID=i;
                emd.vtxMult=(vtx.v->at(i))->size();
                emd.eID=((fm.v->at(i))->at(0)).mID;
                emd.mID=((fm.v->at(i))->at(1)).mID;
                emd.TotalLeptMult=((((ufe.v->at(i))->size())+((ufm.v->at(i))->size())));
                emd.ech=((fm.v->at(i))->at(0)).charge;
                emd.mch=((fm.v->at(i))->at(1)).charge;
                emd.electronPt=((fm.v->at(i))->at(0)).pt;
                emd.electronEta=((fm.v->at(i))->at(0)).eta;
                emd.electronPhi=((fm.v->at(i))->at(0)).phi;
                emd.muonPt=((fm.v->at(i))->at(1)).pt;
                emd.muonEta=((fm.v->at(i))->at(1)).eta;
                emd.muonPhi=((fm.v->at(i))->at(1)).phi;
                emd.electronEnergy=((fm.v->at(i))->at(0)).energy;
                emd.muonEnergy=((fm.v->at(i))->at(1)).energy;
                emd.mll=Zcand.M();
                emd.metPt=(ufmet.v->at(i)->at(0)).pt;
                if((ufj.v->at(i))->size() >=1 ) emd.jetPtLeading=(ufj.v->at(i)->at(0)).pt;
                else emd.jetPtLeading=-100.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetPtSubLeading=(ufj.v->at(i)->at(1)).pt;
                else emd.jetPtSubLeading=-100.0;
                if((ufj.v->at(i))->size() >=1 ) emd.jetRapidityLeading=(ufj.v->at(i)->at(0)).rapidit;
                else emd.jetRapidityLeading=1000.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetRapiditySubLeading=(ufj.v->at(i)->at(1)).rapidit;
                else emd.jetRapiditySubLeading=1000.0;
                if((ufj.v->at(i))->size() >=1 ) emd.jetEtaLeading=(ufj.v->at(i)->at(0)).eta;
                else emd.jetEtaLeading=1000.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetEtaSubLeading=(ufj.v->at(i)->at(1)).eta;
                else emd.jetEtaSubLeading=1000.0;
                if((ufj.v->at(i))->size() >=1 ) emd.jetPhiLeading=(ufj.v->at(i)->at(0)).phi;
                else emd.jetPhiLeading=1000.0;
                if((ufj.v->at(i))->size() >=2 ) emd.jetPhiSubLeading=(ufj.v->at(i)->at(1)).phi;
                else emd.jetPhiSubLeading=1000.0;
                emd.jetMult=(ufj.v->at(i))->size();
                emd.LooseLept10MultIso=(CountLooseLept10MultIso);
                emd.tight10MultIso=(CounttightLept10MultIso);
                emd.tight10MultNonIso=(Counttight10MultNonIso);
                emd.tight20MultIso=(Counttight20MultIso);
                emd.LooseLept10MultNonIso=(CountLooseLept10MultNonIso);
                emd.LooseLept10MultNoIso=(CountLooseLept10MultNoIso);
                emd.tight10MultNoIso=(Counttight10MultNoIso);
                
              //  cout<<"LooseLept10MultIso  :  "<<CountLooseLept10MultIso<<"  tight10MultIso :  "<<Counttight10MultIso<<"  tight10MultNonIso : "<<Counttight10MultNonIso<<"  tight20MultNonIso :  "<<Counttight20MultNonIso<<endl;
                c++;
            }
            if(c==1)
            {
                events++;
                v->push_back(emd);
            }
        }
        C2M = events;
        return v;
    }
    
    ~ElectronMuon()
    {
        delete v;
        v=0;
    }
    
    friend class ElectronMuonOppChrg;
};
