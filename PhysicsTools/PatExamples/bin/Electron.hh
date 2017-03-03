class ElectronMuon;
class ElectronMuonOppChrg;
class ElectronMuonExtraLoose;
class ElectronMuonMet;
class Mllcut;
class Jet;

class Electron
{
    struct CUT
    {
        bool   etac,ptc,dxyc,vetoc,mhitsc,isoc,fullSigmaEtaEtac,dEtaInc,dPhiInc,HoverEc,ooEmooPc,d0c,dzc,all,allNew,extraLoose;
    };
    struct DATA
    {
        float  eID,phi,dxy,eta,pt,veto,mhits,iso,charge,scEta,fullSigmaEtaEta,dEtaIn,dPhiIn,HoverE,ooEmooP,d0,dz,energy;
        CUT    loose,tight;
    };
    
    vector<vector<DATA>*>* v;
    vector<int>* LeptMult;
    int cTTE,cEW1E,CEW2E;
    
public:
    static vector<double> electronMult_;
    static vector<double> beforeElectronMult_;
    
    Electron()
    {
        v = new vector<vector<DATA>*>;
        LeptMult = new vector<int>;
    }
    Electron(vector<vector<DATA>*>* uv)
    {
        v=uv;
        LeptMult = new vector<int>;
    }
    
    int getTTE(){return cTTE;}
    int getEW1E(){return cEW1E;}
    int getEW2E(){return CEW2E;}    
    
    void setData(const char* fname)
    {
        TFile* inFile = TFile::Open(fname);
        
        if(!inFile)
        {
            cout<<"Input Root File not opened for processing in electron class "<<endl;
            return;
        }
        
        fwlite::Event ev(inFile);
        int evtID=0;
        
        for(ev.toBegin(); !ev.atEnd(); ++ev, evtID++)
        {
            edm::EventBase const & event = ev;
            
            // Handle to the electron pt
            edm::Handle<std::vector<float> > electronPt;
            event.getByLabel(std::string("electrons:elPt"), electronPt);
            // Handle to the electron eta
            edm::Handle<std::vector<float> > electronEta;
            event.getByLabel(std::string("electrons:elEta"), electronEta);
            // Handle to the electron eta
            edm::Handle<std::vector<float> > electronPhi;
            event.getByLabel(std::string("electrons:elPhi"), electronPhi);
            // Handle to the electron impact parameter
            edm::Handle<std::vector<float> > electronDxy;
            event.getByLabel(std::string("electrons:elDxy"), electronDxy);
            // Handle to the electron veto
            edm::Handle<std::vector<float> > electronisVeto;
            event.getByLabel(std::string("electrons:elvidVeto"), electronisVeto);
            // Handle to the electron missing hits
            edm::Handle<std::vector<float> > electronmissHits;
            event.getByLabel(std::string("electrons:elmissHits"), electronmissHits);
            // Handle to the electron isolation of cone of radius 0.03
            edm::Handle<std::vector<float> > electronIso03;
            event.getByLabel(std::string("electrons:elIso03"), electronIso03);
            // Handle to the electron charge
            edm::Handle<std::vector<float> > electronCharge;
            event.getByLabel(std::string("electrons:elCharge"), electronCharge);
            
            
            // Handle to the electron electronSCeta
            edm::Handle<std::vector<float> > electronSCeta;
            event.getByLabel(std::string("electrons:elSCEta"), electronSCeta);
            // Handle to the electron electronfullSigmaEtaEta
            edm::Handle<std::vector<float> > electronfullSigmaEtaEta;
            event.getByLabel(std::string("electrons:elfull5x5siee"), electronfullSigmaEtaEta);
            // Handle to the electron electrondEtaIn
            edm::Handle<std::vector<float> > electrondEtaIn;
            event.getByLabel(std::string("electrons:eldEtaIn"), electrondEtaIn);
            // Handle to the electron electrondPhiIn
            edm::Handle<std::vector<float> > electrondPhiIn;
            event.getByLabel(std::string("electrons:eldPhiIn"), electrondPhiIn);
            // Handle to the electron electronHOverE
            edm::Handle<std::vector<float> > electronHOverE;
            event.getByLabel(std::string("electrons:elHoE"), electronHOverE);
            // Handle to the electron electronooEmooP
            edm::Handle<std::vector<float> > electronooEmooP;
            event.getByLabel(std::string("electrons:elooEmooP"), electronooEmooP);
            // Handle to the electron electronD0
            edm::Handle<std::vector<float> > electronD0;
            event.getByLabel(std::string("electrons:elDxy"), electronD0);
            // Handle to the electron electronDz
            edm::Handle<std::vector<float> > electronDz;
            event.getByLabel(std::string("electrons:elDz"), electronDz);
            // Handle to the electron energy
            edm::Handle<std::vector<float> > electronEn;
            event.getByLabel(std::string("electrons:elE"), electronEn);
            
            vector<DATA>* dv = new vector<DATA>;
            DATA d;

            for(unsigned int i=0;i<electronPt->size();i++)
            {
                d.eID = i;
                d.pt = electronPt->at(i);
                d.eta = electronEta->at(i);
                d.phi = electronPhi->at(i);
                d.dxy = electronDxy->at(i);
                d.veto = electronisVeto->at(i);
                d.mhits = electronmissHits->at(i);
                d.iso  = electronIso03->at(i);
                d.charge = electronCharge->at(i);
                
                d.scEta = electronSCeta->at(i);
                d.fullSigmaEtaEta = electronfullSigmaEtaEta->at(i);
                d.dEtaIn = electrondEtaIn->at(i);
                d.dPhiIn = electrondPhiIn->at(i);
                d.HoverE = electronHOverE->at(i);
                d.ooEmooP = electronooEmooP->at(i);
                d.d0 = electronD0->at(i);
                d.dz = electronDz->at(i);
                d.energy = electronEn->at(i);
                
                dv->push_back(d);
                
            }
            v->push_back(dv);
        }
        inFile->Close();
        
        setCuts();
        
        return;
    }
    
    vector<vector<DATA>*>* selectData1()
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events =0;
        int totalTightelectrons =0;

        for(unsigned int i=0; i < v->size(); i++)
        {
            int elctron_number = 0;
            vector<DATA>* fdv= new vector<DATA>;
            
            dv=v->at(i);
            
            bool isEventSelected=false;
            int tightCount=0;
            
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                
                if(d.tight.all && d.tight.allNew)
                {
                    totalTightelectrons++;
                elctron_number = j;
                  tightCount++;
                }
            }
            
            LeptMult->push_back(tightCount);
            
            if(tightCount==1){isEventSelected=true;//cout<<i<<" Reject2"<<endl;
            }
            //-----------------------
            if(isEventSelected)
            {
                events++;
                    d=dv->at(elctron_number);
                
                      //  cout<<"Selected (on basis of only 1 tight electron) EventID: "<<i<<"  S ElectronID: "<<elctron_number<<endl;
                        fdv->push_back(d);
                    // only fill one tight electron's information

            }
            //-------------------------
            fv->push_back(fdv);
        }
        //cout<<"Total number of tight electrons: "<< totalTightelectrons <<endl;
        //cout<<"Total number of events having only one tight electron: "<< events <<endl;
        cTTE=totalTightelectrons;
        cEW1E=events;
        return fv;
    }
 
    vector<vector<DATA>*>* selectData2()
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events =0;
        int totalTightelectrons =0;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            int elctron_number1 = 0;
            int elctron_number2 = 0;

            vector<DATA>* fdv= new vector<DATA>;
            
            dv=v->at(i);
            
            bool isEventSelected=false;
            int tightCount=0;
            
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                
                if(d.tight.all && d.tight.allNew)
                {
                    totalTightelectrons++;
                    if(tightCount==0) elctron_number1 = j;
                    if(tightCount==1) elctron_number2 = j;
                    tightCount++;
                }
            }
            
            if(tightCount==2){isEventSelected=true;//cout<<i<<" Reject2"<<endl;
            }
            //-----------------------
            if(isEventSelected)
            {
                events++;
                d=dv->at(elctron_number1);
                fdv->push_back(d);
                d=dv->at(elctron_number2);
                //  cout<<"Selected (on basis of only 1 tight electron) EventID: "<<i<<"  S ElectronID: "<<elctron_number<<endl;
                fdv->push_back(d);
                // only fill one tight electron's information
                
            }
            //-------------------------
            fv->push_back(fdv);
        }
       // cout<<"Total number of tight electrons: "<< totalTightelectrons <<endl;
        //cout<<"Total number of events having exactly two tight electrons: "<< events <<endl;
        CEW2E=events;
        return fv;
    }
    
    void setCuts()
    {
        
        vector<DATA>* dv;
        
        float tElectron_Cut_pt = 20.0;
        float tElectron_Cut_eta = 2.4;
      //  float tTransverse_Impact_Parameter_Cut = 0.04;
        
 
        float lElectron_Cut_pt = 10.0;
        float lElectron_Cut_eta = 2.5;
      //  float lTransverse_Impact_Parameter_Cut = 0.04;
        
        
        float bscEta = 1.4442;
        float btfullSigmaEtaEta = 0.00998;
        float btdEtaIn = 0.00308;
        float btdPhiIn = 0.0816;
        float btHoverE = 0.0414;
        float btElectron_Relative_Isolation_Cut = 0.0588;
        float btooEmooP = 0.0129;
        float btd0 = 0.05;
        float btdz = 0.10;
        float btElectron_Missing_Hits_Cut = 1;
        float btPassing_Conversion_Veto_Electron_Cut = 1;
        
        float blfullSigmaEtaEta = 0.011;
        float bldEtaIn = 0.00477;
        float bldPhiIn = 0.222;
        float blHoverE = 0.298;
        float blElectron_Relative_Isolation_Cut = 0.0994;
        float blooEmooP = 0.241;
        float bld0 = 0.05;
        float bldz = 0.10;
        float blElectron_Missing_Hits_Cut = 1;
        float blPassing_Conversion_Veto_Electron_Cut = 1;
        
        float e1scEta = 1.5660;
        float e2scEta = 2.5;
        float etfullSigmaEtaEta = 0.0292;
        float etdEtaIn = 0.00605;
        float etdPhiIn = 0.0394;
        float etHoverE = 0.0641;
        float etElectron_Relative_Isolation_Cut = 0.0571;
        float etooEmooP = 0.0129;
        float etd0 = 0.10;
        float etdz = 0.20;
        float etElectron_Missing_Hits_Cut = 1;
        float etPassing_Conversion_Veto_Electron_Cut = 1;
        
        float elfullSigmaEtaEta = 0.0314;
        float eldEtaIn = 0.00868;
        float eldPhiIn = 0.213;
        float elHoverE = 0.101;
        float elElectron_Relative_Isolation_Cut = 0.107;
        float elooEmooP = 0.14;
        float eld0 = 0.10;
        float eldz = 0.20;
        float elElectron_Missing_Hits_Cut = 1;
        float elPassing_Conversion_Veto_Electron_Cut = 1;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                DATA& d=dv->at(j);
                
                d.tight.ptc = (d.pt > tElectron_Cut_pt)?true:false;
                d.tight.etac = (fabs( d.eta )< tElectron_Cut_eta)?true:false;
               // d.tight.dxyc = (d.dxy < tTransverse_Impact_Parameter_Cut)?true:false;
                
              //  d.tight.scEtac = (fabs(d.scEta) < escEta)?true:false;
                
                if(fabs(d.scEta) <= bscEta)
                {
                d.tight.fullSigmaEtaEtac = (d.fullSigmaEtaEta < btfullSigmaEtaEta)?true:false;
                d.tight.dEtaInc = (fabs(d.dEtaIn) < btdEtaIn)?true:false;
                d.tight.dPhiInc = (fabs(d.dPhiIn) < btdPhiIn)?true:false;
                d.tight.HoverEc = (d.HoverE < btHoverE)?true:false;
                d.tight.ooEmooPc = (fabs(d.ooEmooP) < btooEmooP)?true:false;
                d.tight.d0c = (fabs(d.d0) < btd0)?true:false;
                d.tight.dzc = (fabs(d.dz) < btdz)?true:false;
                d.tight.mhitsc = (d.mhits <= btElectron_Missing_Hits_Cut)?true:false;
                d.tight.vetoc = (d.veto == btPassing_Conversion_Veto_Electron_Cut)?true:false;
                d.tight.isoc   = (d.iso < btElectron_Relative_Isolation_Cut)?true:false;
                }
                if(fabs(d.scEta) > e1scEta && fabs(d.scEta) < e2scEta)
                {
                d.tight.fullSigmaEtaEtac = (d.fullSigmaEtaEta < etfullSigmaEtaEta)?true:false;
                d.tight.dEtaInc = (fabs(d.dEtaIn) < etdEtaIn)?true:false;
                d.tight.dPhiInc = (fabs(d.dPhiIn) < etdPhiIn)?true:false;
                d.tight.HoverEc = (d.HoverE < etHoverE)?true:false;
                d.tight.ooEmooPc = (fabs(d.ooEmooP) < etooEmooP)?true:false;
                d.tight.d0c = (fabs(d.d0) < etd0)?true:false;
                d.tight.dzc = (fabs(d.dz) < etdz)?true:false;
                d.tight.mhitsc = (d.mhits <= etElectron_Missing_Hits_Cut)?true:false;
                d.tight.vetoc = (d.veto == etPassing_Conversion_Veto_Electron_Cut)?true:false;
                d.tight.isoc   = (d.iso < etElectron_Relative_Isolation_Cut)?true:false;
                }
                
                d.tight.allNew = d.tight.ptc && d.tight.etac;
                d.tight.all = d.tight.vetoc && d.tight.mhitsc && d.tight.fullSigmaEtaEtac && d.tight.dEtaInc && d.tight.dPhiInc && d.tight.HoverEc && d.tight.ooEmooPc && d.tight.d0c && d.tight.dzc && d.tight.isoc;
                d.tight.extraLoose = d.tight.allNew && d.tight.all;
                
                d.loose.ptc = (d.pt > lElectron_Cut_pt)?true:false;
                d.loose.etac = (fabs( d.eta )< lElectron_Cut_eta)?true:false;
              //  d.loose.dxyc = (d.dxy < lTransverse_Impact_Parameter_Cut)?true:false;
                
               // d.loose.scEtac = (fabs(d.scEta) < escEta)?true:false;

                if(fabs(d.scEta) <= bscEta)
                {
                    d.loose.fullSigmaEtaEtac = (d.fullSigmaEtaEta < blfullSigmaEtaEta)?true:false;
                    d.loose.dEtaInc = (fabs(d.dEtaIn) < bldEtaIn)?true:false;
                    d.loose.dPhiInc = (fabs(d.dPhiIn) < bldPhiIn)?true:false;
                    d.loose.HoverEc = (d.HoverE < blHoverE)?true:false;
                    d.loose.ooEmooPc = (fabs(d.ooEmooP) < blooEmooP)?true:false;
                    d.loose.d0c = (fabs(d.d0) < bld0)?true:false;
                    d.loose.dzc = (fabs(d.dz) < bldz)?true:false;
                    d.loose.mhitsc = (d.mhits <= blElectron_Missing_Hits_Cut)?true:false;
                    d.loose.vetoc = (d.veto == blPassing_Conversion_Veto_Electron_Cut)?true:false;
                    d.loose.isoc   = (d.iso < blElectron_Relative_Isolation_Cut)?true:false;
                }
                if(fabs(d.scEta) > e1scEta && fabs(d.scEta) < e2scEta)
                {
                    d.loose.fullSigmaEtaEtac = (d.fullSigmaEtaEta < elfullSigmaEtaEta)?true:false;
                    d.loose.dEtaInc = (fabs(d.dEtaIn) < eldEtaIn)?true:false;
                    d.loose.dPhiInc = (fabs(d.dPhiIn) < eldPhiIn)?true:false;
                    d.loose.HoverEc = (d.HoverE < elHoverE)?true:false;
                    d.loose.ooEmooPc = (fabs(d.ooEmooP) < elooEmooP)?true:false;
                    d.loose.d0c = (fabs(d.d0) < eld0)?true:false;
                    d.loose.dzc = (fabs(d.dz) < eldz)?true:false;
                    d.loose.mhitsc = (d.mhits <= elElectron_Missing_Hits_Cut)?true:false;
                    d.loose.vetoc = (d.veto == elPassing_Conversion_Veto_Electron_Cut)?true:false;
                    d.loose.isoc   = (d.iso < elElectron_Relative_Isolation_Cut)?true:false;
                }
                d.loose.allNew = d.loose.ptc && d.loose.etac;
                d.loose.all = d.loose.vetoc && d.loose.mhitsc && d.loose.fullSigmaEtaEtac && d.loose.dEtaInc && d.loose.dPhiInc && d.loose.HoverEc && d.loose.ooEmooPc && d.loose.d0c && d.loose.dzc && d.loose.isoc;
                d.loose.extraLoose = d.loose.allNew && d.loose.all;
            }
        }
        return;
    }

    void fillHisto(TTree* t)
    {
        for(unsigned int i=0; i < v->size(); i++)
        {
            if(LeptMult->at(i)){electronMult_.push_back(LeptMult->at(i));}
            if(v->at(i)){beforeElectronMult_.push_back((v->at(i))->size());}
            t->Fill();
            electronMult_.clear();
            beforeElectronMult_.clear();
        }
        return;
    }
    
    ~Electron()
    {
        delete v;
        v=0;
    }
    
    static TTree* getHistPointers(fwlite::TFileService& fs, const char* treeName)
    {
        TTree* t  = fs.make<TTree>(treeName,"");
        t->Branch("electronMult_",&electronMult_);
        t->Branch("beforeElectronMult_",&beforeElectronMult_);
        return t;
    }
    friend class Jet;
    friend class ElectronMuon;
    friend class ElectronMuonOppChrg;
    friend class ElectronMuonExtraLoose;
    friend class Mllcut;
    friend class ElectronMuonMet;
};

vector<double> Electron::electronMult_;
vector<double> Electron::beforeElectronMult_;


