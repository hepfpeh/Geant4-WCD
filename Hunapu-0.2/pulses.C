// root script file

#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"
#include <cmath>
#include <algorithm>

void GetHunapuPulse(const char* HunapuRootFileName, Int_t PulseNumber){
	Long64_t Entries;
	std::vector<double> *PulseData = new std::vector<double>();

	TFile *HunapuRootFile = new TFile( HunapuRootFileName );
	TTree *Hunapu = (TTree*)HunapuRootFile->Get("WCDtank;1");
	Entries = Hunapu->GetEntriesFast();	
	Hunapu->SetBranchAddress("Photon_Arrival_Time",&PulseData);

	if (PulseNumber < Entries ) Hunapu->GetEntry(PulseNumber);
	else { 
		std::cout << "Invalid pulse Number" << std::endl;
		return;
	}
	
	Int_t DataEntries = PulseData->size();
	std::cout << "Number of photons: " << DataEntries << std::endl;
	
	// Ordenando por tiempo

	std::sort( PulseData->begin(), PulseData->end() );


	Double_t DataMax = -100.0;
	Double_t DataMin = 50000.0;

// Parametros para calculo de curva de carga
	Double_t Circuit_R = 50; // en ohms.
	Double_t Circuit_C = 0.4; // en ns/ohm = nF.
	Double_t Circuit_V = 1500.0; // en V.
	Double_t Const_k = 1.0 / ( Circuit_R * Circuit_C ); // en 1/ns.
	Double_t Dep_q = 1.6e-13; // en C. ( se fija como e x 10^6)
	Double_t Sample_Rate = 125.0; // en MHz.

// Parametros ADC
	Double_t ADC_Vref = 1.0; // en Volts. (GND=0)
	Int_t ADC_bits = 14;

	Long_t ADC_bins = std::pow( 2, ADC_bits );
	Double_t ADC_Dv = ADC_Vref / ADC_bins;

	std::vector < std::vector<Double_t> > *Data_table = new std::vector < std::vector<Double_t> >();
	std::vector<Double_t> *vect_tmp = new std::vector<Double_t>(2);
	Double_t t_cur = 0;
	Double_t t_ant;
	Double_t A_cur = 0;
	Double_t A_ant;

	vect_tmp->push_back(t_cur);
	vect_tmp->push_back(A_cur);

	Data_table->push_back( *vect_tmp );

	vect_tmp->clear();

	t_ant = t_cur;
	A_ant = A_cur;

	for( int i = 0 ; i < DataEntries ; i++ ){
		t_cur = PulseData->at( i );
		A_cur = 1.0 + A_ant * exp( -Const_k * (t_cur - t_ant) );
		vect_tmp->push_back(t_cur);
		vect_tmp->push_back(A_cur);
//		std::cout << "Time: " << t_cur << " A_cur: "<< A_cur << std::endl;
		Data_table->push_back(*vect_tmp);
		vect_tmp->clear();

//		DataHist->Fill( t_cur );
		if ( t_cur > DataMax ) DataMax = t_cur;
		if ( t_cur < DataMin ) DataMin = t_cur;

		t_ant = t_cur;
		A_ant = A_cur;
	}


	TH1 *DataHist = new TH1D("H1","Photon arrival time",25,0,DataMax);
	for( int i = 0 ; i < DataEntries ; i++ )
		DataHist->Fill( PulseData->at( i ) );


	std::cout << "Max time: " << DataMax << std::endl;
	std::cout << "Min time: " << DataMin << std::endl;

	Double_t Time_increment = 1000.0 / Sample_Rate;
	Long_t NumberOfSamples = floor( (DataMax-DataMin) / Time_increment );

	Double_t Time_array[ NumberOfSamples ];
	Double_t Carge_array[ NumberOfSamples ];
	Double_t ADC_array[ NumberOfSamples ];
	Double_t ADC_Vtmp = 0;

	t_cur = DataMin;

	Double_t t_n=0;
	Double_t A_n=0;
	Double_t Carge_tmp;

	Int_t Table_pos = 0;

	for( Long_t i = 0 ; i < NumberOfSamples ; i++ ){

		while( (Data_table->at( Table_pos )).at(0) < t_cur ) {
			t_n = (Data_table->at( Table_pos )).at(0);
			A_n = (Data_table->at( Table_pos )).at(1);
			Table_pos++;
		}

		Time_array[ i ] = t_cur;
//		std::cout << "Time: " << t_cur << " t_n: " << t_n << " A_n: "<< A_n << std::endl;
		Carge_array[ i ] = -Dep_q * A_n * exp( -Const_k * (t_cur - t_n) ) + Circuit_V * Circuit_C * (1.0e-9);
		ADC_Vtmp =  1 / ( Circuit_C * 1.0e-9 ) * Dep_q * A_n * exp( -Const_k * (t_cur - t_n) );
		if( ADC_Vtmp <= 0)
			ADC_array[ i ] = 0.0;
		else if( ADC_Vtmp >= ADC_Vref )
			ADC_array[ i ] = ADC_bins - 1.0;
		else
			ADC_array[ i ] = std::floor( ADC_Vtmp / ADC_Dv );
//		std::cout << "Charge: " << Carge_array[ i ] << std::endl;

		t_cur += Time_increment;
	}

//	TH1 *DataHistCumulative = DataHist->GetCumulative();
	TGraph *Circuit_C_Carge = new TGraph( NumberOfSamples, Time_array, ADC_array);
	Circuit_C_Carge->GetXaxis()->SetLimits(0,DataMax);
	
	TCanvas *ShowHists = new TCanvas("Algo", "otro", 600, 400);
	ShowHists->Divide(1,2);
	
	ShowHists->cd(1);
	DataHist->Draw();
	ShowHists->cd(2);
//	DataHistCumulative->Draw();
//    Circuit_C_Carge->Draw("acp");
    Circuit_C_Carge->Draw("AC*");
	ShowHists->Update();
} 

