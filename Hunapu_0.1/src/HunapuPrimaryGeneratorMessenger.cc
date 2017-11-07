/*
 * HunapuPrimaryGeneratorMessenger.cc
 *
 *  Created on: 12/10/2016
 *      Author: hepf
 */

#include "HunapuPrimaryGeneratorMessenger.hh"

#include "HunapuPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuPrimaryGeneratorMessenger::
  HunapuPrimaryGeneratorMessenger(HunapuPrimaryGeneratorAction* HunapuGun)
  : G4UImessenger(),
    fHunapuAction(HunapuGun)
{
  fGunDir = new G4UIdirectory("/Hunapu/gun/");
  fGunDir->SetGuidance("PrimaryGenerator particle direction control");

  fDirectionCmd =
           new G4UIcmdWithAString("/Hunapu/gun/direction",this);
  fDirectionCmd->SetGuidance("Set primary particle direction");
  fDirectionCmd->SetGuidance("Options: Vertical, NonVertical, All");
  fDirectionCmd->SetGuidance("Default: All");
  fDirectionCmd->SetParameterName("ParticleDirection",true);
  fDirectionCmd->SetDefaultValue("All");
  G4String CandidateList = "Vertical NonVertical All";
  fDirectionCmd->SetCandidates(CandidateList);
  fDirectionCmd->AvailableForStates(G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuPrimaryGeneratorMessenger::~HunapuPrimaryGeneratorMessenger()
{
  delete fDirectionCmd;
  delete fGunDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuPrimaryGeneratorMessenger::SetNewValue(
                                        G4UIcommand* command, G4String newValue)
{
  if( command == fDirectionCmd )
	  fHunapuAction->SetParticleDirection( newValue );
}

