/*
 * WCDtankPrimaryGeneratorMessenger.hh
 *
 *  Created on: 12/10/2016
 *      Author: hepf
 */

#ifndef WCDtankPRIMARYGENERATORMESSENGER_HH_
#define WCDtankPRIMARYGENERATORMESSENGER_HH_

#include "G4UImessenger.hh"
#include "globals.hh"

class WCDtankPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class WCDtankPrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    WCDtankPrimaryGeneratorMessenger(WCDtankPrimaryGeneratorAction* );
    virtual ~WCDtankPrimaryGeneratorMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    WCDtankPrimaryGeneratorAction* 	fWCDtankAction;
    G4UIdirectory*                  fGunDir;
    G4UIcmdWithAString*			    fDirectionCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif /* WCDtankPRIMARYGENERATORMESSENGER_HH_ */
