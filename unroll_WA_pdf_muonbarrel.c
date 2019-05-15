#include "TH1.h"
#include "TFile.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include "TLegend.h"
#include "THStack.h"
#include "CMSTDRStyle.h"
#include "CMS_lumi.C"
#include "TGraphErrors.h"
#include "TArrow.h"
#include "TLatex.h"
using namespace std;
void cmsLumi(bool channel);
ofstream file1("scalefactor.txt");
TH1D* unroll(TH2D* th2_in,Double_t* xbin, Double_t* ybin,  Int_t xbins_in, Int_t ybins_in,char *hname);
void cmsLumi(bool channel)
{
    TLatex latex;
    latex.SetNDC();
    latex.SetTextSize(0.04);
    latex.SetLineWidth(2);
    float lumiel=35.8;
    float lumimu=35.8;
    int beamcomenergytev=13;
    latex.SetTextAlign(31);
    latex.SetTextAlign(11);
    latex.DrawLatex(0.18,0.82,"Preliminary");
    latex.DrawLatex(0.18,0.86,"CMS");
    latex.SetTextSize(0.03);
    latex.DrawLatex(0.76,0.92,Form("35.9 fb^{-1} (%d TeV)", (beamcomenergytev)));
}

TH1D* unroll(TH2D* th2_in,Double_t* xbin, Double_t* ybin,  Int_t xbins_in, Int_t ybins_in,char *hname)//,char* htitle)
{
    TH2D* th2 = th2_in;
    Int_t nbinsx =xbins_in;//2D histo的bin的数量,x
    Int_t nbinsy =ybins_in;////2D histo的bin的数量,y
    Int_t nbins = nbinsx*nbinsy;// 2d histo一共被分为多少区域
    
    //TH1D* h1 = new TH1D("hist", "hist", nbins, 0, nbins);
    TH1D* h1_out = new TH1D("unrolled hist", "unrolled hist", nbins, 0, nbins);
    
    for(Int_t iy=1; iy<=nbinsy; iy++){
        for(Int_t ix=1; ix<=nbinsx; ix++){
            Double_t x_temp = 0.5*(xbin[ix-1]+xbin[ix]);//取一个bin两个端点的均值,x direction,得到the BinContent
            Double_t y_temp = 0.5*(ybin[iy-1]+ybin[iy]);////取一个bin两个端点的均值,y direction
            h1_out->SetBinContent(ix+(iy-1)*nbinsx,th2->GetBinContent(th2->FindBin(x_temp, y_temp)));//void SetBinContent(Int_t bin, Double_t content),the FindBin function can return Global bin number corresponding to x,y
            h1_out->SetBinError(ix+(iy-1)*nbinsx,th2->GetBinError(th2->FindBin(x_temp, y_temp)));
            //cout<<"ix = "<<ix<<", iy = "<<iy<<"; bin = "<<ix+(iy-1)*nbinsx<<", BinContent"<<th2->GetBinContent(th2->FindBin(x_temp, y_temp))<<endl;
        }
    }
    /*
    for(Int_t ii=1; ii<=nbins-2;ii++){
        if(ii<9){
            h1_out->SetBinContent(ii, h1->GetBinContent(ii));
            h1_out->SetBinError(ii,h1->GetBinError(ii));
        }
        if(ii==9){
            h1_out->SetBinContent(ii, h1->GetBinContent(ii)+h1->GetBinContent(ii+1)+h1->GetBinContent(ii+2));
            h1_out->SetBinError(ii,sqrt(h1->GetBinError(ii)*h1->GetBinError(ii)+h1->GetBinError(ii+1)*h1->GetBinError(ii+1)+h1->GetBinError(ii+2)*h1->GetBinError(ii+2)));
        }
        if(ii==10){
            h1_out->SetBinContent(ii, h1->GetBinContent(ii+2));
            h1_out->SetBinError(ii,h1->GetBinError(ii+2));
        }
    }*/
    return h1_out;
}

int unroll_WA_pdf_muonbarrel(){
    setTDRStyle();
    gStyle->SetPadBorderMode(0);
    gStyle->SetOptStat(0);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetAxisColor(1, "XYZ");
    gStyle->SetStripDecimals(kTRUE);
    gStyle->SetTickLength(0.03, "XYZ");
    gStyle->SetNdivisions(510, "XYZ");
    
    TFile* fout = new TFile("Wa_pdf.root","RECREATE");
    Double_t WA_scale= 1.0;
    std::ostringstream strs;
    std::string lumivalue = strs.str();
    Double_t lumi=35.857;
    Double_t mjj_bins[5]={500, 800, 1200, 1700, 2000};
    Double_t detajj_bins[4]={30,80,130,200};
    //Double_t mjj_bins[2]={150, 400};
    //Double_t detajj_bins[4]={2.5,4.5,6,6.5};
    //const char *name[9]={"Mjj 150~400","Mjj 150~400","Mjj 150~400"};
    const char *name[12]={"500~800","800~1200","1200~1700","1700~inf","500~800","800~1200","1200~1700","1700~inf","500~800","800~1200","1200~1700","1700~inf"};
    
    TFile* f_WA=TFile::Open("./th2-histo-WA-pdf-muonbarrel.root");
    TH2D* th2_WA[104];
    TH1D* t_WA[104];
    TCanvas* cc = new TCanvas("cc","Mjj vs Mla",900,600);
    //TCanvas* cc[9];
    //TLegend *ll[9];
    //TLegend *ll = new TLegend(0.55,0.4,0.8,0.9);
    for(Int_t i=0;i<104;i++){
        //ll[i] = new TLegend(0.55,0.4,0.8,0.9);
        //cc[i] = new TCanvas(Form("cc_%d",i),Form("Mjj vs deltajj %d",i+1),900,600);
        th2_WA[i]=(TH2D*)f_WA->Get(Form("th2_%d",i));
        t_WA[i]= unroll(th2_WA[i], mjj_bins, detajj_bins, 4,3,Form("hist_%d",i+1));//Form("%d central scale pdf variable",i+1));
        ofstream file2(Form("./scale-txt-WA-pdf-muonbarrel/content-hist_no%d",i+1));
        t_WA[i]->SetLineWidth(3);
        t_WA[i]->SetLineColor(i+1);
        for(Int_t j=1;j<=12;j++){ t_WA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
        t_WA[i]->Scale(lumi*WA_scale);
        //t_WA[i]->Draw("HIST,SAME");
        //t_WA[i]->DrawNormalized("HIST");
        
        //ll->AddEntry(t_WA[i],Form("%d central scale pdf variable",i+1));
        //ll[i]->Draw();
        //cc[i]->Print(Form("tmp-hist2d_%d.eps",i+1));
        for(Int_t k=0;k<12;k++){
            file2<<t_WA[i]->GetBinContent(k+1)<<endl;}
    }
    //ll->Draw();
    //cc->Print("hist-2d.eps");
    TCanvas* c1 = new TCanvas("c1","Mjj vs Mla",900,600);
    c1->SetFrameFillColor(41);
    //TLegend *l2 = new TLegend(0.55,0.4,0.8,0.9);
    TLegend *l2 = new TLegend(0.6,0.2,0.9,0.9);
    t_WA[0]->SetTitle("Mjj vs Mla");
    t_WA[0]->SetLineWidth(3);
    t_WA[0]->Draw("HIST");
    file1<<"histo 1 1"<<endl;
    for(Int_t i=1;i<104;i++){
        //         t_ZA[i]->SetFillColor(kMagenta);
        //         t_ZA[i]->SetMarkerColor(kMagenta);
        t_WA[i]->SetLineColor(i+1);
        t_WA[i]->SetLineWidth(1);
        t_WA[i]->SetLineStyle(2);
        //t_WA[i]->Scale(lumi*WA_scale);
        file1<<"histo "<<i+1<<"\t"<<t_WA[0]->Integral()/t_WA[i]->Integral()<<endl;
        cout<<"histo "<<i+1<<" "<<t_WA[0]->Integral()/t_WA[i]->Integral()<<endl;
        t_WA[i]->Scale(t_WA[0]->Integral()/t_WA[i]->Integral());
        for(Int_t j=1;j<=12;j++){ t_WA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
        //t_ZA[i]->Draw("HIST,SAME");
        t_WA[i]->Draw("HIST,SAME");
        //t_WA[i]->DrawNormalized("HIST");
        //l2->AddEntry(t_WA[i],Form("%d central scale pdf variations",i+1));
        // delete t_ZA[i];
        // delete cc[i];
    }
        //l2->AddEntry(t_WA[0],Form("%d central scale pdf variations",1));
	//l2->Draw();
    //c1->Print("unroll-WA.eps");
    
    //    TH1D* t_ZA=unroll(th2_ZA, mjj_bins, detajj_bins, 3,3);
    //    for(Int_t i=0;i<9;i++){
    //      t_ZA[i]->SetFillColor(i+1);
    //      t_ZA[i]->SetMarkerColor(i+1);
    //      t_ZA[i]->SetLineColor(i+1);
    //      t_ZA[i]->Scale(lumi*ZA_scale);
    //    }
    
    THStack* hs = new THStack("hs", "");
    TLegend *l1 = new TLegend(0.8,0.2,0.9,1.2);
    // TLegend *l1 = new TLegend(0.55,0.4,0.8,0.9);
    for(Int_t i=0;i<104;i++){
        hs->Add(t_WA[i]);
        l1->AddEntry(t_WA[i],Form("%d central scale pdf variations",i+1));
    }
    /*
    TCanvas* c = new TCanvas("c","Mjj vs deltajj",800,600);
    c->cd();
    TPad* fPad1 = new TPad("pad1", "", 0.00, 0.00, 0.99, 0.99);
    fPad1->Draw();
    CMS_lumi(fPad1, 4, 0, lumivalue);
    c->SetFrameFillColor(41);
    hs->Draw("HIST");
    hs->GetYaxis()->SetTitleOffset(0.8);
    hs->GetYaxis()->SetTitle("Events /bin");
    for(Int_t i=1;i<=9;i++){ hs->GetXaxis()->SetBinLabel(i,name[i-1]);}
    l1->Draw();
    c->Print("tmp.eps");
    */
    
    cmsLumi(0);
    
    fout->cd();
    
    for(Int_t i=0;i<104;i++){
        t_WA[i]->Write();}
    hs->Write();
    fout->Close();
    return 0;
    
    
}
