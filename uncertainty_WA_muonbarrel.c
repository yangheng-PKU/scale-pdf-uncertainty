#include "TArrow.h"
#include "TLatex.h"
#include "TCanvas.h"

void open(Int_t i);
Int_t p=12;//the amount of bin
Int_t histo_number=6;//the histo_number equals the amount of pdf except the central value
Double_t central_value[12],nlo_value[6][12];//[the amount of pdf][the amout of bin]
ofstream f1("./result_muonbarrel/WA-muonbarrel-scale-uncertainty.txt");
vector<Double_t> vector_nlo,vector_center;
vector<Double_t>:: iterator biggest_nlo;
vector<Double_t>:: iterator smallest_nlo;
Double_t biggest[12],smallest[12];
void open(Int_t i){
    ifstream file(Form("./scale-txt-WA-muonbarrel/content-hist_no%d",i));
    if(!file.is_open()){cout<<"can not open the "<<i<<" file"<<endl;   }
	for(Int_t j=0;j<p;j++){
        if(i==1){
            file>>central_value[j];
            cout<<"histo "<<i<<"; bin"<<j+1<<"; central_value = "<<central_value[j]<<endl;  }
        if(i>1){
            file>>nlo_value[i-2][j];
            cout<<"hist "<<i<<"; bin"<<j<<"; nlo_value = "<<nlo_value[i-2][j]<<endl;
            //nlo_value[i][j]代表第几个histo的第几个bin的值
        }
    }
   
}


int uncertainty_WA_muonbarrel(){
    gStyle->SetOptStat(0);
    f1<<"Bins"<<"\t"<<"scale uncertainty"<<endl;
    for(Int_t i=1;i<=histo_number+1;i++){
        open(i);
        //对于第j个bin，把每个histo的bincontent输出
        cout<<"*****************************"<<endl;
    }
    for(Int_t j=0;j<p;j++){
        for(Int_t i=0;i<histo_number-1;i++){
        //for(Int_t i=0;i<histo_number;i++){  
	  vector_nlo.push_back(nlo_value[i][j]);
        }
        biggest_nlo = max_element(begin(vector_nlo),end(vector_nlo));
        smallest_nlo = min_element(begin(vector_nlo),end(vector_nlo));
        biggest[j]=*biggest_nlo;
        smallest[j]=*smallest_nlo;
        cout<<j <<" bin "<<"; biggest = "<<biggest[j]<<"; smallest = "<<smallest[j]<<"; 2*central value = "<<2*central_value[j]<<endl;
        //cout<<"begin(vector_nlo)"<<begin(vector_nlo)<<";begin(vector_nlo) "<<begin(vector_nlo)<<endl;
        vector_nlo.clear();
        cout<<"*****************************"<<endl;
    }
    Double_t single,sum,average,uncertainty[p],mean=0,uncertainty_other[p];
    for(Int_t j=0;j<p;j++){
        sum=0;
        mean=0;
        for(Int_t i=0;i<histo_number;i++){
            single = pow(nlo_value[i][j]-central_value[j],2);
            sum = sum+single;
            mean = (mean + nlo_value[i][j]);
            if(i==histo_number-1){
                mean = (mean + central_value[j])/(histo_number+1);
                average = sum/histo_number;
                uncertainty[j]=sqrt(sum/6)/mean;
            }
        }
        //uncertainty_other[j]=(biggest[j]-smallest[j])/(2*central_value[j]);
        //uncertainty_other[j]=fabs(biggest[j]-central_value[j])/central_value[j];
        uncertainty_other[j]=max(fabs(biggest[j]-central_value[j]),fabs(smallest[j]-central_value[j]))/central_value[j];
	cout<<"bin "<<j+1<<"; mean = "<<mean<<endl;
        cout<<"bin "<<j+1<<"; sum = "<<sum<<endl;
        cout<<"bin "<<j+1<<"; uncertainty_other["<<j<<"] = "<<uncertainty_other[j]<<"; uncertainty["<<j<<"] = "<<uncertainty[j]<<endl;
        cout<<"biggest-central_value="<<fabs(biggest[j]-central_value[j])<<";smallest-central_value="<<fabs(smallest[j]-central_value[j])<<";max="<<max(fabs(biggest[j]-central_value[j]),fabs(smallest[j]-central_value[j]))<<endl;
	f1<<"bin "<<j+1<<"\t"<<uncertainty_other[j]<<endl;
//	f1<<"bin "<<j+1<<"\t"<<uncertainty_other[j]<<endl;
    
}
    
    const char *name[12]={"500~800","800~1200","1200~1700","1700~inf","500~800","800~1200","1200~1700","1700~inf","500~800","800~1200","1200~1700","1700~inf"};
    //const char *name[9]={"Mjj 500~750","Mjj 750~1000","Mjj 1000~2000","Mjj 500~750","Mjj 750~1000","Mjj 1000~2000","Mjj 500~750","Mjj 750~1000","Mjj 1000~2000"};
    TCanvas* cc = new TCanvas("cc","",900,600);
    cc->SetGrid();
   
    TH1D* h1 =new TH1D("h1","uncertainty",12,0,12);
    for(Int_t i=0;i<12;i++){
   // for(Int_t i=1;i<=12;i++){
        h1->SetBinContent(i+1,uncertainty_other[i]);
        h1->SetTitle("WA scale uncertainty_muonbarrel;;uncertainty");
        h1->GetXaxis()->SetBinLabel(i+1,name[i]);
        h1->GetYaxis()->CenterTitle();
        h1->GetYaxis()->SetTitleFont(32);
        h1->GetYaxis()->SetLabelFont(22);
        h1->GetYaxis()->SetLabelSize(0.05);
        h1->GetYaxis()->SetTitleSize(0.06);
        h1->GetYaxis()->SetTitleOffset(0.85);
        h1->GetXaxis()->SetLabelFont(22);
        h1->GetXaxis()->SetLabelSize(0.05);
        h1->SetMarkerStyle(2);
        h1->SetMarkerSize(3);
        h1->SetMarkerColor(2); 
        h1->Draw("p");
        
        TArrow* line1 = new TArrow(h1->GetBinLowEdge(5),0.055,h1->GetBinLowEdge(5),0.205,0.07,"") ;
        TArrow* line2 = new TArrow(h1->GetBinLowEdge(9),0.055,h1->GetBinLowEdge(9),0.205,0.07,"") ;
        line1->SetLineColor(4);
        line1->SetLineWidth(2);
        line1->SetLineStyle(2);
        line2->SetLineColor(4);
        line2->SetLineWidth(2);
        line2->SetLineStyle(2);

	TLatex latex1;
        latex1.SetTextAlign(12);
        latex1.SetTextSize(0.04);
	latex1.DrawLatexNDC(0.15,0.5,"#font[12]{M_{l#gamma} #in (30, 80)}");
        latex1.DrawLatexNDC(0.45,0.5,"#font[12]{M_{l#gamma} #in (80, 130)}");
        latex1.DrawLatexNDC(0.75,0.5,"#font[12]{M_{l#gamma} > 130}");

	line1->Draw();
        line2->Draw();      
     
    /* Double_t x[12]={"500~800","800~1200","1200~1700","1700~inf","500~800","800~1200","1200~1700","1700~inf","500~800","800~1200","1200~1700","1700~inf"};  
    // Double_t x[12]={1,2,,3,4,5,6,7,8,9,10,11,12};
     TGraph* h1=new TGraph(12,x,uncertainty_other);
     h1->SetTitle("WA scale uncertainty;;uncertainty");
     for(Int_t i=0;i<12;i++){
     h1->GetXaxis()->SetBinLabel(i+1,name[i]);}
     h1->Draw("A*");
    */
}
    return 0;
}
