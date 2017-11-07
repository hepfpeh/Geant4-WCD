/*
 * HunapuPrimaryGeneratorMessenger.hh
 *
 *  Created on: 12/10/2016
 *      Author: hepf
 */

#ifndef HUNAPUPRIMARYGENERATORMESSENGER_HH_
#define HUNAPUPRIMARYGENERATORMESSENGER_HH_

#include "G4UImessenger.hh"
#include "globals.hh"

class HunapuPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HunapuPrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    HunapuPrimaryGeneratorMessenger(HunapuPrimaryGeneratorAction* );
    virtual ~HunapuPrimaryGeneratorMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    HunapuPrimaryGeneratorAction* 	fHunapuAction;
    G4UIdirectory*                  fGunDir;
    G4UIcmdWithAString*			    fDirectionCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif /* HUNAPUPRIMARYGENERATORMESSENGER_HH_ */
