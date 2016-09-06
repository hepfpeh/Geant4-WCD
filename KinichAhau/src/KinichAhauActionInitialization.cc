//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: KinichAhauActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file KinichAhauActionInitialization.cc
/// \brief Implementation of the KinichAhauActionInitialization class

#include "KinichAhauActionInitialization.hh"
#include "KinichAhauPrimaryGeneratorAction.hh"
#include "KinichAhauRunAction.hh"
#include "KinichAhauSteppingAction.hh"
#include "KinichAhauStackingAction.hh"
#include "KinichAhauSteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

KinichAhauActionInitialization::KinichAhauActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

KinichAhauActionInitialization::~KinichAhauActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauActionInitialization::BuildForMaster() const
{
  SetUserAction(new KinichAhauRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauActionInitialization::Build() const
{
  SetUserAction(new KinichAhauPrimaryGeneratorAction());
  SetUserAction(new KinichAhauRunAction());
  SetUserAction(new KinichAhauSteppingAction());
  SetUserAction(new KinichAhauStackingAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VSteppingVerbose*
               KinichAhauActionInitialization::InitializeSteppingVerbose() const
{
  return new KinichAhauSteppingVerbose();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
