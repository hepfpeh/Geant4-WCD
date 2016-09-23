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
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef KinichAhauRunAction_h
#define KinichAhauRunAction_h 1

//sd
#include "G4VSensitiveDetector.hh"
#include "KinichAhauPMTHit.hh"
//

#include "globals.hh"
#include "G4UserRunAction.hh"

//sd
#include <vector>
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Timer;
class G4Run;

// sd
class G4Step;
class G4HCofThisEvent;
//

class KinichAhauRunAction : public G4UserRunAction
{
  public:
    KinichAhauRunAction();
    virtual ~KinichAhauRunAction();
    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run* aRun);
    virtual void EndOfRunAction(const G4Run* aRun);
  private:
    G4Timer*  fTimer;
    G4double* fElapsedTime;
};

class KinichAhauSensitiveDetector : public G4VSensitiveDetector
{
  public:
    KinichAhauSensitiveDetector(const G4String& name);
    virtual ~KinichAhauSensitiveDetector();
  
    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);

    virtual void EndOfEvent(G4HCofThisEvent* );
    virtual void clear();
    void DrawAll();
    void PrintAll();

  private:
    G4Timer*  fTimer;
    G4double* fElapsedTime;
    KinichAhauPMTHit* KinichAhauSDHits;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*KinichAhauRunAction_h*/
