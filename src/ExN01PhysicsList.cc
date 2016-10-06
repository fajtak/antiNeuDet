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
// $Id: ExN01PhysicsList.cc,v 1.6 2006-06-29 17:47:21 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//

#include "ExN01PhysicsList.hh"
#include "G4ParticleTypes.hh"

#include "HadronPhysicsQGSP_BIC_HP.hh"
#include "HadronPhysicsQGSP_BERT_HP.hh"
#include "HadronPhysicsFTFP_BERT.hh"
#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"


ExN01PhysicsList::ExN01PhysicsList() : G4VModularPhysicsList()
{

  SetVerboseLevel(1);

  //default physics
  particleList = new G4DecayPhysics();

  //default physics
  raddecayList = new G4RadioactiveDecayPhysics();

  // EM physics
  emPhysicsList = new G4EmStandardPhysics();

  AddExtraBuilders(true);
  hadPhysicsList = new HadronPhysicsQGSP_BIC_HP("std-hadron");
  //hadPhysicsList = new HadronPhysicsQGSP_BERT_HP("std-hadron");
  //hadPhysicsList = new HadronPhysicsFTFP_BERT("std-hadron");

  defaultCutValue = 0.01*mm;
  cutForNeutron = defaultCutValue;

  SetCuts();
  //SetCutForNeutron(defaultCutValue);
}

ExN01PhysicsList::~ExN01PhysicsList()
{
  delete raddecayList;
  delete emPhysicsList;
  if (hadPhysicsList) delete hadPhysicsList;
  if (nhadcomp > 0) {
    for(G4int i=0; i<nhadcomp; i++) {
      delete hadronPhys[i];
    }
  }
}

void ExN01PhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program.

  particleList->ConstructParticle();
}

void ExN01PhysicsList::ConstructProcess()
{
  // Define transportation process

  AddTransportation();

  // em
  emPhysicsList->ConstructProcess();
  // decays
  particleList->ConstructProcess();
  raddecayList->ConstructProcess();

  if (nhadcomp > 0) {
    for(G4int i=0; i<nhadcomp; i++) {
      (hadronPhys[i])->ConstructProcess();
    }
  }
  if (hadPhysicsList) hadPhysicsList->ConstructProcess();

}

#include "G4EmExtraPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4QStoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4NeutronTrackingCut.hh"

void ExN01PhysicsList::AddExtraBuilders(G4bool flagHP)
{
  nhadcomp = 5;
  hadronPhys.push_back( new G4EmExtraPhysics("extra EM"));
  hadronPhys.push_back( new G4HadronElasticPhysics("elastic",verboseLevel,
						   flagHP));
  hadronPhys.push_back( new G4QStoppingPhysics("stopping",verboseLevel));
  hadronPhys.push_back( new G4IonBinaryCascadePhysics("ionBIC"));
  hadronPhys.push_back( new G4NeutronTrackingCut("Neutron tracking cut"));
}

void ExN01PhysicsList::SetCuts()
{
  // uppress error messages even in case e/gamma/proton do not exist
  G4int temp = GetVerboseLevel();                                                SetVerboseLevel(0);
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets
  //   the default cut value for all particle types
  SetCutsWithDefault();

  //SetCutValue(cutForNeutron, "neutron");

  // Retrieve verbose level
  SetVerboseLevel(temp);
}

#include "G4Neutron.hh"

void ExN01PhysicsList::SetCutForNeutron(G4double cut)
{
  cutForNeutron = cut;
  SetParticleCuts(cutForNeutron, G4Neutron::Neutron());
}

