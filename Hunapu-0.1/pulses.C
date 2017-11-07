// root script file

#include "TFile.h"
#include "TTree.h"
#include <cmath>

void GetHunapuPulse(const char* HunapuRootFileName, Int_t PulseNumber){
	Long64_t Entries;
	std::vector<double> *PulseData = new std::vector<double>();

	TFile *HunapuRootFile = new TFile( HunapuRootFileName );
	TTree *Hunapu = (TTree*)HunapuRootFile->Get("Hunapu;1");
	Entries = Hunapu->GetEntriesFast();	
	Hunapu->SetBranchAddress("Photon_Arrival_Time",&PulseData);

	if (PulseNumber < Entries ) Hunapu->GetEntry(PulseNumber);
	else { 
		cout << "Invalid pulse Number" << endl;
		return;
	}
	
	Int_t DataEntries = PulseData->size();
	
	TH1 *DataHist = new TH1D("H1","Photon arrival time",25,0,0);	
	Double_t DataMax = -100.0;
	Double_t DataMin = 50000.0;

	for( int i = 0 ; i < DataEntries ; i++ ){
		DataHist->Fill( PulseData->at( i ) );
		if ( PulseData->at( i ) > DataMax ) DataMax = PulseData->at( i );
		if ( PulseData->at( i ) < DataMin ) DataMin = PulseData->at( i );
	}

	cout << "Max time: " << DataMax << endl;
	cout << "Min time: " << DataMin << endl;


	TH1 *DataHistCumulative = DataHist->GetCumulative();
	
	TCanvas *ShowHists = new TCanvas();
	ShowHists->Divide(1,2);
	
	ShowHists->cd(1);
	DataHist->Draw();
	ShowHists->cd(2);
	DataHistCumulative->Draw();
	ShowHists->Update();
} 

