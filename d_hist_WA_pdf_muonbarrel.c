#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>

using namespace std;

TH2D*th2[104];
void run(std::string filename);
void run(std::string filename){
    
    std::string file = "/home/pku/yangheng/VBSWgamma/VBS-WGamma-makesmall/"+filename+".root";//gai
    TFile* f1 = TFile::Open(file.c_str());
    
    TTree* t = (TTree*)f1->Get("demo");
    /*
    Double_t Mla;//gai
    Double_t Mjj;
    Double_t detajj;
    Double_t theWeight,lumiWeight,scalef,pweight[113];//gai
    Double_t actualWeight[9];
    
    t->SetBranchAddress("Mla", &Mla);//gai
    t->SetBranchAddress("Mjj", &Mjj);
    t->SetBranchAddress("deltaetajj", &detajj);
    t->SetBranchAddress("pweight", pweight);
    t->SetBranchAddress("scalef", &scalef);
    t->SetBranchAddress("theWeight", &theWeight);
    t->SetBranchAddress("lumiWeight", &lumiWeight);
    */
    Double_t lumi=35.857; 
    Double_t        WGmass;
    Double_t        Mjj;
    Double_t        photonet;
    Double_t        scalef;
    Double_t        deltaeta;
    Double_t        L1prefiring;
    Double_t        Dphiwajj;
    Double_t        zepp;
    Double_t        photonsceta;
    Double_t        mtVlepJECnew;
    Double_t        ptlep1;
    Double_t        etalep1;
    Double_t        jet1pt;
    Double_t        jet1eta;
    Double_t        jet2pt;
    Double_t        jet2eta;
    Double_t        drj1a;
    Double_t        drj2a;
    Double_t        drj1l;
    Double_t        drj2l;
    Double_t        j1metPhi;
    Double_t        j2metPhi;
    Double_t        Mla;
    //Double_t        absphotonsceta=fabs(photonsceta);
    
    Double_t actualWeight[104];//gai
    Double_t pweight[113];//gai
    Double_t lumiWeight;//gai
    Double_t pileupWeight;//gai
    Int_t lep,nlooseeles,nloosemus,HLT_Mu2;
    //Double_t mtVlepJECnew;
    Double_t drla;
    Double_t MET_et;
    Double_t jet1icsv;
    Double_t jet2icsv;
    Bool_t photonhaspixelseed;
    
    t->SetBranchAddress("ptlep1", &ptlep1);
    t->SetBranchAddress("etalep1", &etalep1);
    t->SetBranchAddress("jet1pt", &jet1pt);
    t->SetBranchAddress("jet1eta", &jet1eta);
    t->SetBranchAddress("jet2pt", &jet2pt);
    t->SetBranchAddress("jet2eta", &jet2eta);
    t->SetBranchAddress("drj1a", &drj1a);
    t->SetBranchAddress("drj2a", &drj2a);
    t->SetBranchAddress("drj1l", &drj1l);
    t->SetBranchAddress("drj2l", &drj2l);
    t->SetBranchAddress("j1metPhi", &j1metPhi);
    t->SetBranchAddress("j2metPhi", &j2metPhi);
    t->SetBranchAddress("Mla", &Mla);
    t->SetBranchAddress("photonsceta", &photonsceta);
    //    Outtree1->SetBranchAddress("mtVlepJECnew", &mtVlepJECnew);
    t->SetBranchAddress("L1prefiring",&L1prefiring);
    t->SetBranchAddress("Dphiwajj",&Dphiwajj);
    t->SetBranchAddress("zepp",&zepp);
    t->SetBranchAddress("WGmass",&WGmass);
    t->SetBranchAddress("Mjj",&Mjj);
    t->SetBranchAddress("photonet",&photonet);
    t->SetBranchAddress("deltaeta",&deltaeta);
    t->SetBranchAddress("scalef", &scalef);
    
    
    t->SetBranchAddress("pweight", pweight);//gai
    t->SetBranchAddress("pileupWeight",&pileupWeight);//gai
    t->SetBranchAddress("lumiWeight",&lumiWeight);//gai
    t->SetBranchAddress("mtVlepJECnew", &mtVlepJECnew);//gai
    t->SetBranchAddress("lep", &lep);//gai
    t->SetBranchAddress("nlooseeles", &nlooseeles);//gai
    t->SetBranchAddress("nloosemus", &nloosemus);//gai
    t->SetBranchAddress("HLT_Mu2", &HLT_Mu2);//gai
    t->SetBranchAddress("drla", &drla);//gai
    t->SetBranchAddress("MET_et", &MET_et);//gai
    //t->SetBranchAddress("absphotonsceta", &absphotonsceta);//gai
    t->SetBranchAddress("jet1icsv", &jet1icsv);//gai
    t->SetBranchAddress("jet2icsv", &jet2icsv);//gai
    t->SetBranchAddress("photonhaspixelseed", &photonhaspixelseed);
    int y=0;  
    //Double_t lumi=35.857;
    double count=0;//gai
    Double_t mjj_bins[5]={500, 800, 1200, 1800, 2000};//gai
    Double_t mla_bins[4]={30, 80, 130, 200};//gai
    //Double_t detajj_bins[4]={2.5, 4.5, 6, 6.5};
    char th2name[104];
    for(Int_t i=0;i<104;i++){
        sprintf(th2name,"th2_%d",i);
        th2[i] = new TH2D(th2name, th2name, 4, mjj_bins, 3, mla_bins);
        th2[i]->Sumw2();}
    Int_t p;
    for(Int_t j=0; j<t->GetEntries();j++)
    {
        p=0;
        t->GetEntry(j);
        //gai
        for(Int_t i=0;i<104;i++){
            //if(p==0)  actualWeight[p]=scalef*L1prefiring*lumiWeight*pileupWeight*pweight[i];
         //else  actualWeight[p]=2*scalef*L1prefiring*lumiWeight*pileupWeight*pweight[i];
	actualWeight[p]=scalef*L1prefiring*lumiWeight*pileupWeight*pweight[i];//gai
            //actualWeight[p]=scalef*L1prefiring*lumiWeight*pileupWeight*pweight[i];//gai
            //actualWeight[p]=scalef*lumiWeight*pweight[i];
            //cout<<"yes1"<<endl;
            //cout<<"i = "<<i<<endl; 
           // cout<<"p = "<<p<<endl;
            //cout<<"L1prefiring= "<<L1prefiring<<endl;
            //cout<<"pileupweight= "<<pileupWeight<<endl;
            //cout<<"lumiWeight= "<<lumiWeight<<endl;
           // cout<<"pweight ["<<i<<"] = "<<pweight[i]<<endl;
           // cout<<"actualWeight ["<<p<<"] = "<<actualWeight[p]<<endl;
            
            if(Mjj>1900)Mjj=1900;
            if(Mla>190)Mla=190;
        // if(fabs(photonsceta)<1.4442&&ptlep1>35&&fabs(etalep1)<2.4&&photonet>30&&jet1pt>50&&jet2pt>40&&fabs(jet1eta)<4.7&&fabs(jet2eta)<4.7&&drj1a>2&&drj2a>2&&drj1l>2&&drj2l>2&&j1metPhi>0.5&&j2metPhi>0.5&&WGmass>100&&Mla>30&&zepp<1.5&&Dphiwajj>2&&deltaeta>2.5&& lep==13&&nlooseeles<1&&nloosemus<2&&HLT_Mu2 ==1&&mtVlepJECnew>30&&drla>0.5&&MET_et>30&&fabs(photonsceta)<1.4442&&!photonhaspixelseed&&Mjj>500&&jet1icsv<0.8484&&jet2icsv<0.8484)
          if(!photonhaspixelseed && lep==13 && nlooseeles<1 && nloosemus<2 && HLT_Mu2 ==1 && mtVlepJECnew>30 && ptlep1>30 && fabs(etalep1)<2.4 && drla>0.5 && MET_et>30 && photonet>25 && fabs(photonsceta)<1.4442 && jet1pt>40 && jet2pt>30 && fabs(jet1eta)<4.7 && fabs(jet2eta)<4.7  && drj1a>0.5 && drj2a>0.5 && drj1l>0.5 && drj2l>0.5 && j1metPhi>0.4 && j2metPhi>0.4 && jet1icsv<0.8484 && jet2icsv<0.8484 && WGmass>100 && Mla>30 && deltaeta>2.5 && Mjj>500)  
            {
               // th2[p]->Fill(Mjj, Mla,actualWeight[p]);
                th2[p]->Fill(Mjj, Mla,lumi* actualWeight[p]);
                y=y+1;
		cout<<"yes2"<<endl;
                cout<<"y="<<y<<endl;
		// cout<<"scalef = "<<scalef<<endl;    
                //cout<<"p = "<<p<<endl;
                //cout<<"Mjj = "<<Mjj<<endl;
                //cout<<"Mla = "<<Mla<<endl;
                cout<<"actualWeight ["<<p<<"] = "<<actualWeight[p]<<endl;
                //cout<<"L1prefiring= "<<L1prefiring<<endl;
                //cout<<"pileupweight= "<<pileupWeight<<endl;
                //cout<<"lumiWeight= "<<lumiWeight<<endl;
                cout<<"pweight ["<<i<<"] = "<<pweight[i]<<endl;
                
                if(deltaeta>4 && Mjj>800)count+=scalef*L1prefiring*35.865;
            }
            p++;
        }
        //cout<<filename<<"  "<<count<<endl;
        /*for(Int_t i=104;i<113;i++){
            actualWeight[p]=scalef*lumiWeight*pweight[i];
            
            if(Mjj<2000 && detajj<6.5) th2[p]->Fill(Mjj, Mla, actualWeight[p]);
            if(Mjj>=2000 && detajj<6.5) th2[p]->Fill(1999, Mla, actualWeight[p]);
            if(Mjj<2000 && detajj>=6.5) th2[p]->Fill(Mjj, 6.1, actualWeight[p]);
            if(Mjj>=2000 && detajj>=6.5) th2[p]->Fill(1999, 6.1, actualWeight[p]);
            p++;}*/
        //cout<<"p = "<<p<<endl;
        //cout<<"entry "<<j<<endl;
        //cout<<"scalef = "<<scalef<<endl;
        /*
        for(Int_t k=104;k<113;k++){
            cout<<"scalef = "<<scalef<<endl;
        }
        //cout<<"L1prefiring= "<<L1prefiring<<endl;
        //cout<<"pileupweight= "<<pileupWeight<<endl;
        
        for(Int_t k=104;k<113;k++){
            cout<<"pweight ["<<k<<"] = "<<pweight[k]<<endl;
        }
        for(Int_t k=0;k<9;k++){
            cout<<"actualWeight ["<<k<<"] = "<<actualWeight[k]<<endl;
        }*/
        //cout<<"######################################"<<endl;
    }
}

int d_hist_WA_pdf_muonbarrel(){
    run("outWA");
    //TFile* f4=new TFile("2d_WA.root","RECREATE");
    
    TFile* f4=new TFile("th2-histo-WA-pdf-muonbarrel-tmp.root","RECREATE");
    for(Int_t i=0;i<104;i++){
        th2[i]->Write();}
    f4->Close();
    //f5->Close();
    return 0;
    
}
