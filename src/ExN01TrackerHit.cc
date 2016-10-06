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
// $Id: ExN02TrackerHit.cc,v 1.10 2006-06-29 17:48:24 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN01TrackerHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN01TrackerHit::ExN01TrackerHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN01TrackerHit::~ExN01TrackerHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN01TrackerHit::ExN01TrackerHit(const ExN01TrackerHit& right)
  : G4VHit()
{
    runID = right.runID;
    eveID = right.eveID;
    traID = right.traID;
    parID = right.parID;
    steID = right.steID;
    PDGenc = right.PDGenc;
    repNSci = right.repNSci;
    repNSta = right.repNSta;
    layID = right.layID;

    parNam = right.parNam;
    crePro = right.crePro;
    stePro = right.stePro;
    deaLayNam = right.deaLayNam;

    pos = right.pos;
    verPos = right.verPos;

    gloTim = right.gloTim;
    traLen = right.traLen;
    kinEne = right.kinEne;
    verKinEne = right.verKinEne;
    steLen = right.steLen;
    totEneDep = right.totEneDep;

    actVol = right.actVol;
    outOfWorld = right.outOfWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ExN01TrackerHit& ExN01TrackerHit::operator=(const ExN01TrackerHit& right)
{
    runID = right.runID;
    eveID = right.eveID;
    traID = right.traID;
    parID = right.parID;
    steID = right.steID;
    PDGenc = right.PDGenc;
    repNSci = right.repNSci;
    repNSta = right.repNSta;
    layID = right.layID;

    parNam = right.parNam;
    crePro = right.crePro;
    stePro = right.stePro;
    deaLayNam = right.deaLayNam;

    pos = right.pos;
    verPos = right.verPos;

    gloTim = right.gloTim;
    traLen = right.traLen;
    kinEne = right.kinEne;
    verKinEne = right.verKinEne;
    steLen = right.steLen;
    totEneDep = right.totEneDep;

    actVol = right.actVol;
    outOfWorld = right.outOfWorld;
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int ExN01TrackerHit::operator==(const ExN01TrackerHit& right) const
{
    return (this==&right) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN01TrackerHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if(pVVisManager)
    {
        G4Circle circle(pos);
        circle.SetScreenSize(2.);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1.,0.,0.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN01TrackerHit::Print(int i)
{
    G4int prec = G4cout.precision(3);

    if (i > 0) G4cout << " RunID : " << runID << " EventID : " << eveID << " TrackID : " << traID << "  ParentID : " << parID << " StepID : " << steID << " ActiveVol : " << actVol <<  G4endl;
    if (i > 1) G4cout << " Replica number of scintillator : " << repNSci << " Replica number of stack : " << repNSta << " Layer ID : " << layID <<  G4endl;
    if (i > 2) G4cout << " ParticleName : " << parNam << " PDG enco : " << PDGenc << " CreProcess : " << crePro << " SteProcess : " << stePro << G4endl;
    if (i > 3) G4cout << " Vertex kinetic energy : " << verKinEne << " Kinetic Energy : " << kinEne << " Total deposited energy : " << totEneDep << G4endl;
    if (i > 4) G4cout << " Global time : " << gloTim << " Step length : " << steLen << " Track length : " << traLen << G4endl;
    if (i > 5) G4cout << " Position x : " << this->GetPosX() << " y : " << this->GetPosY() << " z : " << this->GetPosZ() << " outOfWorld : " << this->GetOutOfWorld() << " Dead layer name : " << this->GetDeaLayNam() << G4endl;
    if (i > 6) G4cout << " Vertex position x : " << this->GetVerPosX() << " y : " << this->GetVerPosY() << " z : " << this->GetVerPosZ() << G4endl;

    G4cout.precision(prec);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

