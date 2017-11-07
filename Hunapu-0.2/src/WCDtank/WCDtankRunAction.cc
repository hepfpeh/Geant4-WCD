#include "WCDtankRunAction.hh"
#include "WCDtankPrimaryGeneratorAction.hh"
#include "WCDtankDetectorConstruction.hh"
#include "WCDtankRun.hh"
#include "WCDtankAnalysis.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <ctime>
#include <string>
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCDtankRunAction::WCDtankRunAction()
: G4UserRunAction()
{
	G4dVectorPointer = new std::vector<G4double>;
//	G4dVectorPointer = &G4dVector;
//	G4dVectorPointer = 0;

	//G4cout << "Pointer: " << G4dVectorPointer << G4endl;
	// Create analysis manager
	// The choice of analysis technology is done via selectin of a namespace
	// in B4Analysis.hh
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetNtupleMerging(true);
	//G4cout << "Using " << analysisManager->GetType() << G4endl;

	// Create directories
	//analysisManager->SetHistoDirectoryName("histograms");
	//analysisManager->SetNtupleDirectoryName("ntuple");
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetFirstHistoId(1);

	// Book histograms, ntuple
	//

	// Creating histograms
	//analysisManager->CreateH1("1","Photon count at PMT", 40, 0., 400);

	// Creating ntuple
	//

	analysisManager->CreateNtuple("WCDtank", "Data");
	analysisManager->CreateNtupleDColumn("Primary_Energy");
	analysisManager->CreateNtupleDColumn("Azimuth_angle");
	analysisManager->CreateNtupleIColumn("Direction");
	analysisManager->CreateNtupleDColumn("Deposited_Energy");
	analysisManager->CreateNtupleDColumn("Track_Length");
	analysisManager->CreateNtupleDColumn("Photon_Count");
//	analysisManager->CreateNtupleDColumn("Photon_Arrival_Time", G4dVector );
	analysisManager->CreateNtupleDColumn("Photon_Arrival_Time", *G4dVectorPointer );
	analysisManager->FinishNtuple();


}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*
void WCDtankRunAction::SetVectorPointer( std::vector<G4double>* aVectorPointer )
{
	G4dVectorPointer = aVectorPointer;
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCDtankRunAction::~WCDtankRunAction()
{
//	G4cout << "~WCDtankRunAction()" << G4endl;
	delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* WCDtankRunAction::GenerateRun()
{
  return new WCDtankRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WCDtankRunAction::BeginOfRunAction(const G4Run*)
{
	//G4cout << "WCDtankRunAction::BeginOfRunAction" << G4endl;
	// Get analysis manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();


	// Open an output file
	//
	G4String fileName = "WCDtank-";

	std::time_t TimeInSeconds;
	struct tm * TimeStruct;
	char buffer[80];
	std::time ( &TimeInSeconds );
	TimeStruct = std::localtime( &TimeInSeconds );
	std::strftime( buffer, 80, "%Y%m%d-%H%M%S", TimeStruct);

	G4String TimeString =  buffer;
	fileName.append(TimeString);
	analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WCDtankRunAction::EndOfRunAction(const G4Run*)
{
	// print histogram statistics
	//
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//	if ( analysisManager->GetH1(1) ) {
//		G4cout 	<< G4endl << " ----> print histograms statistic ";
//		G4cout 	<< "for the entire run " << G4endl << G4endl;
//		G4cout 	<< " Phothon count : mean = "
//				<< analysisManager->GetH1(1)->mean() << G4endl;
//	}

	// save histograms & ntuple
	//
	std::cout << "\n*****************************************" << std::endl;
	analysisManager->Write();
	analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
