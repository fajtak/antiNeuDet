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
// $Id: ExN01PhysicsList.hh,v 1.6 2006-06-29 17:47:15 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//
//
// ExN01PhysicsList
//  Construct/define particles and physics processes
//
//  Particle defined in ExampleN01
//    geantino
//
//  Process defined in ExampleN01
//    transportation
//

#ifndef ExN01PhysicsList_h
#define ExN01PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class G4ProductionCuts;

class ExN01PhysicsList: public G4VModularPhysicsList
{
  public:
    ExN01PhysicsList();
    ~ExN01PhysicsList();

  protected:
    // Construct particle and physics process
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

    void SetCutForNeutron(G4double);

  private:

    void AddExtraBuilders(G4bool flagHP);

    G4VPhysicsConstructor*  emPhysicsList;
    G4VPhysicsConstructor*  raddecayList;
    G4VPhysicsConstructor*  particleList;
    G4VPhysicsConstructor*  hadPhysicsList;

    G4double cutForNeutron;

    std::vector<G4VPhysicsConstructor*>  hadronPhys;
    G4int nhadcomp;
};

#endif







