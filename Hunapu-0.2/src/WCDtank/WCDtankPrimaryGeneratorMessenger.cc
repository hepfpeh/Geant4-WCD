/*
 * WCDtankPrimaryGeneratorMessenger.cc
 *
 *  Created on: 12/10/2016
 *      Author: hepf
 */

#include "WCDtankPrimaryGeneratorMessenger.hh"

#include "WCDtankPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCDtankPrimaryGeneratorMessenger::
  WCDtankPrimaryGeneratorMessenger(WCDtankPrimaryGeneratorAction* WCDtankGun)
  : G4UImessenger(),
    fWCDtankAction(WCDtankGun)
{
  fGunDir = new G4UIdirectory("/WCDtank/gun/");
  fGunDir->SetGuidance("PrimaryGenerator particle direction control");

  fDirectionCmd =
           new G4UIcmdWithAString("/WCDtank/gun/direction",this);
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

WCDtankPrimaryGeneratorMessenger::~WCDtankPrimaryGeneratorMessenger()
{
  delete fDirectionCmd;
  delete fGunDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WCDtankPrimaryGeneratorMessenger::SetNewValue(
                                        G4UIcommand* command, G4String newValue)
{
  if( command == fDirectionCmd )
	  fWCDtankAction->SetParticleDirection( newValue );
}

