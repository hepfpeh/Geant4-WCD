#include "TstRunAction.hh"
#include "TstPrimaryGeneratorAction.hh"
#include "TstDetectorConstruction.hh"
#include "TstRun.hh"
#include "TstAnalysis.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <ctime>
#include <string>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstRunAction::TstRunAction()
: G4UserRunAction()
{
	// Create analysis manager
	// The choice of analysis technology is done via selectin of a namespace
	// in B4Analysis.hh
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	G4cout << "Using " << analysisManager->GetType() << G4endl;

	// Create directories
	//analysisManager->SetHistoDirectoryName("histograms");
	//analysisManager->SetNtupleDirectoryName("ntuple");
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetFirstHistoId(1);

	// Book histograms, ntuple
	//

	// Creating histograms
	analysisManager->CreateH1("1","Photon count at PMT", 40, 0., 400);

	// Creating ntuple
	//
	analysisManager->CreateNtuple("Tst", "Data");
	analysisManager->CreateNtupleDColumn("Primary_Energy");
	analysisManager->CreateNtupleDColumn("Deposited_Energy");
	analysisManager->CreateNtupleDColumn("Track_Length");
	analysisManager->CreateNtupleDColumn("Photon_Count");
	analysisManager->FinishNtuple();


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstRunAction::~TstRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* TstRunAction::GenerateRun()
{
  return new TstRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstRunAction::BeginOfRunAction(const G4Run*)
{
	// Get analysis manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();


	// Open an output file
	//
	G4String fileName = "Tst-";

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

void TstRunAction::EndOfRunAction(const G4Run*)
{
	// print histogram statistics
	//
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	if ( analysisManager->GetH1(1) ) {
		G4cout 	<< G4endl << " ----> print histograms statistic ";
		G4cout 	<< "for the entire run " << G4endl << G4endl;
		G4cout 	<< " Phothon count : mean = "
				<< analysisManager->GetH1(1)->mean() << G4endl;
	}

	// save histograms & ntuple
	//
	analysisManager->Write();
	analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
