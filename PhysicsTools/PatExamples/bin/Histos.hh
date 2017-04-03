class Histos
{
public:
    
        static vector<double> electronPt_;
        static vector<double> electronEta_;
        static vector<double> electronPhi_;
        static vector<double> muonPt_;
        static vector<double> muonEta_;
        static vector<double> muonPhi_;
        static vector<double> MllDistri_;
        static vector<double> LeadingJetPt_;
        static vector<double> SubLeadingJetPt_;
        static vector<double> LeadingJetRapidity_;
        static vector<double> SubLeadingJetRapidity_;
        static vector<double> LeadingjetEta_;
        static vector<double> SubLeadingjetEta_;
        static vector<double> LeadingJetPhi_;
        static vector<double> SubLeadingJetPhi_;
        static vector<double> JetMult_;
        static vector<double> metPt_;
        static vector<double> vtxMult_;
        static vector<double> bJETMult_;
        static vector<double> GenEventInfo_;
        static vector<double> PUINFO_;
        static vector<double> LeadingLeptPt_;
        static vector<double> LeadingLeptEta_;
        static vector<double> LeadingLeptPhi_;
        static vector<double> SubLeadingLeptPt_;
        static vector<double> SubLeadingLeptEta_;
        static vector<double> SubLeadingLeptPhi_;
    
    static void fillHisto(TTree* t, int Case, vector<Collection::DATA>*  v)
    {
        for(unsigned int i=0; i < v->size(); i++)
        {
            if(Case==1)
            {
                electronPt_.push_back((v->at(i)).electronPt);
                electronEta_.push_back((v->at(i)).electronEta);
                electronPhi_.push_back((v->at(i)).electronPhi);
                muonPt_.push_back((v->at(i)).muonPt);
                muonEta_.push_back((v->at(i)).muonEta);
                muonPhi_.push_back((v->at(i)).muonPhi);
                MllDistri_.push_back((v->at(i)).mll);
                LeadingJetPt_.push_back((v->at(i)).jetPtLeading);
                SubLeadingJetPt_.push_back((v->at(i)).jetPtSubLeading);
                LeadingJetRapidity_.push_back((v->at(i)).jetRapidityLeading);
                SubLeadingJetRapidity_.push_back((v->at(i)).jetRapiditySubLeading);
                LeadingjetEta_.push_back((v->at(i)).jetEtaLeading);
                SubLeadingjetEta_.push_back((v->at(i)).jetEtaSubLeading);
                LeadingJetPhi_.push_back((v->at(i)).jetPhiLeading);
                SubLeadingJetPhi_.push_back((v->at(i)).jetPhiSubLeading);
                JetMult_.push_back((v->at(i)).loosejetMult);
                metPt_.push_back((v->at(i)).metPt);
                vtxMult_.push_back((v->at(i)).vtxMult);
                bJETMult_.push_back((v->at(i)).bJETMult);
                GenEventInfo_.push_back((v->at(i)).genProductWeight);
                PUINFO_.push_back((v->at(i)).PUinfo);
                LeadingLeptPt_.push_back((v->at(i)).LeadingLeptPt);
                LeadingLeptEta_.push_back((v->at(i)).LeadingLeptEta);
                LeadingLeptPhi_.push_back((v->at(i)).LeadingLeptPhi);
                SubLeadingLeptPt_.push_back((v->at(i)).SubLeadingLeptPt);
                SubLeadingLeptEta_.push_back((v->at(i)).SubLeadingLeptEta);
                SubLeadingLeptPhi_.push_back((v->at(i)).SubLeadingLeptPhi);
            }
            if(Case==2)
            {
                electronPt_.push_back((v->at(i)).electronPt);
                electronEta_.push_back((v->at(i)).electronEta);
                electronPhi_.push_back((v->at(i)).electronPhi);
                electronPt_.push_back((v->at(i)).muonPt);
                electronEta_.push_back((v->at(i)).muonEta);
                electronPhi_.push_back((v->at(i)).muonPhi);
                MllDistri_.push_back((v->at(i)).mll);
                LeadingJetPt_.push_back((v->at(i)).jetPtLeading);
                SubLeadingJetPt_.push_back((v->at(i)).jetPtSubLeading);
                LeadingJetRapidity_.push_back((v->at(i)).jetRapidityLeading);
                SubLeadingJetRapidity_.push_back((v->at(i)).jetRapiditySubLeading);
                LeadingjetEta_.push_back((v->at(i)).jetEtaLeading);
                SubLeadingjetEta_.push_back((v->at(i)).jetEtaSubLeading);
                LeadingJetPhi_.push_back((v->at(i)).jetPhiLeading);
                SubLeadingJetPhi_.push_back((v->at(i)).jetPhiSubLeading);
                JetMult_.push_back((v->at(i)).loosejetMult);
                metPt_.push_back((v->at(i)).metPt);
                vtxMult_.push_back((v->at(i)).vtxMult);
                bJETMult_.push_back((v->at(i)).bJETMult);
                GenEventInfo_.push_back((v->at(i)).genProductWeight);
                PUINFO_.push_back((v->at(i)).PUinfo);
                LeadingLeptPt_.push_back((v->at(i)).LeadingLeptPt);
                LeadingLeptEta_.push_back((v->at(i)).LeadingLeptEta);
                LeadingLeptPhi_.push_back((v->at(i)).LeadingLeptPhi);
                SubLeadingLeptPt_.push_back((v->at(i)).SubLeadingLeptPt);
                SubLeadingLeptEta_.push_back((v->at(i)).SubLeadingLeptEta);
                SubLeadingLeptPhi_.push_back((v->at(i)).SubLeadingLeptPhi);
            }
            
            if(Case==3)
            {
                muonPt_.push_back((v->at(i)).electronPt);
                muonEta_.push_back((v->at(i)).electronEta);
                muonPhi_.push_back((v->at(i)).electronPhi);
                muonPt_.push_back((v->at(i)).muonPt);
                muonEta_.push_back((v->at(i)).muonEta);
                muonPhi_.push_back((v->at(i)).muonPhi);
                MllDistri_.push_back((v->at(i)).mll);
                LeadingJetPt_.push_back((v->at(i)).jetPtLeading);
                SubLeadingJetPt_.push_back((v->at(i)).jetPtSubLeading);
                LeadingJetRapidity_.push_back((v->at(i)).jetRapidityLeading);
                SubLeadingJetRapidity_.push_back((v->at(i)).jetRapiditySubLeading);
                LeadingjetEta_.push_back((v->at(i)).jetEtaLeading);
                SubLeadingjetEta_.push_back((v->at(i)).jetEtaSubLeading);
                LeadingJetPhi_.push_back((v->at(i)).jetPhiLeading);
                SubLeadingJetPhi_.push_back((v->at(i)).jetPhiSubLeading);
                JetMult_.push_back((v->at(i)).loosejetMult);
                metPt_.push_back((v->at(i)).metPt);
                vtxMult_.push_back((v->at(i)).vtxMult);
                bJETMult_.push_back((v->at(i)).bJETMult);
                GenEventInfo_.push_back((v->at(i)).genProductWeight);
                PUINFO_.push_back((v->at(i)).PUinfo);
                LeadingLeptPt_.push_back((v->at(i)).LeadingLeptPt);
                LeadingLeptEta_.push_back((v->at(i)).LeadingLeptEta);
                LeadingLeptPhi_.push_back((v->at(i)).LeadingLeptPhi);
                SubLeadingLeptPt_.push_back((v->at(i)).SubLeadingLeptPt);
                SubLeadingLeptEta_.push_back((v->at(i)).SubLeadingLeptEta);
                SubLeadingLeptPhi_.push_back((v->at(i)).SubLeadingLeptPhi);
            }
        t->Fill();
        if(Case==1)
        {
            electronPt_.clear();
            electronEta_.clear();
            electronPhi_.clear();
            muonPt_.clear();
            muonEta_.clear();
            muonPhi_.clear();
            MllDistri_.clear();
            LeadingJetPt_.clear();
            SubLeadingJetPt_.clear();
            LeadingJetRapidity_.clear();
            SubLeadingJetRapidity_.clear();
            LeadingjetEta_.clear();
            SubLeadingjetEta_.clear();
            LeadingJetPhi_.clear();
            SubLeadingJetPhi_.clear();
            JetMult_.clear();
            metPt_.clear();
            vtxMult_.clear();
            bJETMult_.clear();
            GenEventInfo_.clear();
            PUINFO_.clear();
            LeadingLeptPt_.clear();
            LeadingLeptEta_.clear();
            LeadingLeptPhi_.clear();
            SubLeadingLeptPt_.clear();
            SubLeadingLeptEta_.clear();
            SubLeadingLeptPhi_.clear();
        }
        if(Case==2)
        {
            electronPt_.clear();
            electronEta_.clear();
            electronPhi_.clear();
            MllDistri_.clear();
            LeadingJetPt_.clear();
            SubLeadingJetPt_.clear();
            LeadingJetRapidity_.clear();
            SubLeadingJetRapidity_.clear();
            LeadingjetEta_.clear();
            SubLeadingjetEta_.clear();
            LeadingJetPhi_.clear();
            SubLeadingJetPhi_.clear();
            JetMult_.clear();
            metPt_.clear();
            vtxMult_.clear();
            bJETMult_.clear();
            GenEventInfo_.clear();
            PUINFO_.clear();
            LeadingLeptPt_.clear();
            LeadingLeptEta_.clear();
            LeadingLeptPhi_.clear();
            SubLeadingLeptPt_.clear();
            SubLeadingLeptEta_.clear();
            SubLeadingLeptPhi_.clear();
        }
        if(Case==3)
        {
            muonPt_.clear();
            muonEta_.clear();
            muonPhi_.clear();
            MllDistri_.clear();
            LeadingJetPt_.clear();
            SubLeadingJetPt_.clear();
            LeadingJetRapidity_.clear();
            SubLeadingJetRapidity_.clear();
            LeadingjetEta_.clear();
            SubLeadingjetEta_.clear();
            LeadingJetPhi_.clear();
            SubLeadingJetPhi_.clear();
            JetMult_.clear();
            metPt_.clear();
            vtxMult_.clear();
            bJETMult_.clear();
            GenEventInfo_.clear();
            PUINFO_.clear();
            LeadingLeptPt_.clear();
            LeadingLeptEta_.clear();
            LeadingLeptPhi_.clear();
            SubLeadingLeptPt_.clear();
            SubLeadingLeptEta_.clear();
            SubLeadingLeptPhi_.clear();
        }
        }
        //write
        return;
    }
     
   // static TTree* getHistPointers(fwlite::TFileService& fs, string treeName,int Case)
     static TTree* getHistPointers(fwlite::TFileService& fs, const char* treeName,int Case)
    {
       // TTree* t = new TTree(treeName,"");
        TTree* t  = fs.make<TTree>(treeName,"");
        if(Case==1 || Case==2)
        {
            t->Branch("electronPt_",&electronPt_);
            t->Branch("electronEta_",&electronEta_);
            t->Branch("electronPhi_",&electronPhi_);
        }
        if(Case==1 || Case==3)
        {
            t->Branch("muonPt_",&muonPt_);
            t->Branch("muonEta_",&muonEta_);
            t->Branch("muonPhi_",&muonPhi_);
        }
        if(Case==1 || Case==2 || Case==3)
        {
            t->Branch("MllDistri_",&MllDistri_);
            t->Branch("LeadingJetPt_",&LeadingJetPt_);
            t->Branch("SubLeadingJetPt_",&SubLeadingJetPt_);
            t->Branch("LeadingJetRapidity_",&LeadingJetRapidity_);
            t->Branch("SubLeadingJetRapidity_",&SubLeadingJetRapidity_);
            t->Branch("LeadingjetEta_",&LeadingjetEta_);
            t->Branch("SubLeadingjetEta_",&SubLeadingjetEta_);
            t->Branch("LeadingJetPhi_",&LeadingJetPhi_);
            t->Branch("SubLeadingJetPhi_",&SubLeadingJetPhi_);
            t->Branch("JetMult_",&JetMult_);
            t->Branch("metPt_",&metPt_);
            t->Branch("vtxMult_",&vtxMult_);
            t->Branch("bJETMult_",&bJETMult_);
            t->Branch("GenEventInfo_",&GenEventInfo_);
            t->Branch("PUINFO_",&PUINFO_);
            t->Branch("LeadingLeptPt_",&LeadingLeptPt_);
            t->Branch("LeadingLeptEta_",&LeadingLeptEta_);
            t->Branch("LeadingLeptPhi_",&LeadingLeptPhi_);
            t->Branch("SubLeadingLeptPt_",&SubLeadingLeptPt_);
            t->Branch("SubLeadingLeptEta_",&SubLeadingLeptEta_);
            t->Branch("SubLeadingLeptPhi_",&SubLeadingLeptPhi_);
        }
        return t;
    }
    
};
vector<double> Histos::electronPt_;
vector<double> Histos::electronEta_;
vector<double> Histos::electronPhi_;
vector<double> Histos::muonPt_;
vector<double> Histos::muonEta_;
vector<double> Histos::muonPhi_;
vector<double> Histos::MllDistri_;
vector<double> Histos::LeadingJetPt_;
vector<double> Histos::SubLeadingJetPt_;
vector<double> Histos::LeadingJetRapidity_;
vector<double> Histos::SubLeadingJetRapidity_;
vector<double> Histos::LeadingjetEta_;
vector<double> Histos::SubLeadingjetEta_;
vector<double> Histos::LeadingJetPhi_;
vector<double> Histos::SubLeadingJetPhi_;
vector<double> Histos::JetMult_;
vector<double> Histos::metPt_;
vector<double> Histos::vtxMult_;
vector<double> Histos::bJETMult_;
vector<double> Histos::GenEventInfo_;
vector<double> Histos::PUINFO_;
vector<double> Histos::LeadingLeptPt_;
vector<double> Histos::LeadingLeptEta_;
vector<double> Histos::LeadingLeptPhi_;
vector<double> Histos::SubLeadingLeptPt_;
vector<double> Histos::SubLeadingLeptEta_;
vector<double> Histos::SubLeadingLeptPhi_;


