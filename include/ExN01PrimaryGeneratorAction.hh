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
// $Id: ExN01PrimaryGeneratorAction.hh,v 1.5 2006-06-29 17:47:17 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#ifndef ExN01PrimaryGeneratorAction_h
#define ExN01PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

#include "AnalysisManager.hh"
#include "TF1.h"
#include "TRandom.h"
#include "TRandom3.h"

class G4ParticleGun;
class G4Event;
class ExN01DetectorConstruction;
class ExN01PrimaryGeneratorMessenger;

class ExN01PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    ExN01PrimaryGeneratorAction(ExN01DetectorConstruction*);
    ~ExN01PrimaryGeneratorAction();

    void SetPosition(int newPos){pos = newPos;Update();};
    int GetPosition(void){return pos;};
    void SetDirection(int newDir){dir = newDir;Update();};
    int GetDirection(void){return dir;};
    void SetEnergy(int newEne){energy = newEne;Update();};
    int GetEnergy(void){return energy;};
    void SetParticle(int newPar){particle = newPar;Update();};
    int GetParticle(void){return particle;};

    G4ThreeVector GetNewPos(void);
    G4ThreeVector GetNewPosDir(void);
    G4ThreeVector GetNewNeuDir(void);
    double GetNewPosEne(void);
    double GetNewNeuEne(void);

  public:
    void GeneratePrimaries(G4Event* anEvent);
    void Update();

  private:
    G4ParticleGun* particleGun;
    ExN01DetectorConstruction* myDetector;
    ExN01PrimaryGeneratorMessenger* gunMessenger;
    G4int pos;
    G4int dir;
    G4int energy;
    G4int particle;
    TF1 *fU235, *fPu239, *fPu241, *fcross, *getU235;
    TH1F* neutronEnergies;
    //double alphaU235[6];
    //double alphaPu239[6];
    //double alphaPu241[6];
};

#endif


