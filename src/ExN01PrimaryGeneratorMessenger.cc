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
// $Id: PrimaryGeneratorMessenger.cc,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN01PrimaryGeneratorMessenger.hh"

#include "ExN01PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN01PrimaryGeneratorMessenger::ExN01PrimaryGeneratorMessenger(
                                          ExN01PrimaryGeneratorAction* Gun)
:Action(Gun)
{
    gunDir = new G4UIdirectory("/antiNeu/gun/");
    gunDir->SetGuidance("PrimaryGenerator control");

    posCmd = new G4UIcmdWithAnInteger("/antiNeu/gun/position",this);
    posCmd->SetGuidance("Choose required position of particles.");
    posCmd->SetParameterName("Position",false);
    posCmd->SetRange("Position>0 && Position<6");

    dirCmd = new G4UIcmdWithAnInteger("/antiNeu/gun/direction",this);
    dirCmd->SetGuidance("Choose required direction of particles.");
    dirCmd->SetParameterName("Direction",false);
    dirCmd->SetRange("Direction>0 && Direction<5");

    energyCmd = new G4UIcmdWithAnInteger("/antiNeu/gun/energy",this);
    energyCmd->SetGuidance("Choose required energy distribution of particles.");
    energyCmd->SetParameterName("Energy",false);
    energyCmd->SetRange("Energy>0 && Energy<5");

    particleCmd = new G4UIcmdWithAnInteger("/antiNeu/gun/particle",this);
    particleCmd->SetGuidance("Choose required primary particles.");
    particleCmd->SetParameterName("Particle",false);
    particleCmd->SetRange("Particle>0 && Particle<5");
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN01PrimaryGeneratorMessenger::~ExN01PrimaryGeneratorMessenger()
{
    delete posCmd;
    delete dirCmd;
    delete energyCmd;
    delete particleCmd;
    delete gunDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN01PrimaryGeneratorMessenger::SetNewValue(
                                        G4UIcommand* command, G4String newValue)
{

    if( command == posCmd ){
        Action->SetPosition(posCmd->GetNewIntValue(newValue));
    }
    else if (command == dirCmd){
        Action->SetDirection(dirCmd->GetNewIntValue(newValue));
    }
    else if (command == energyCmd){
        Action->SetEnergy(energyCmd->GetNewIntValue(newValue));
    }
    else if (command == particleCmd){
        Action->SetParticle(particleCmd->GetNewIntValue(newValue));
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

