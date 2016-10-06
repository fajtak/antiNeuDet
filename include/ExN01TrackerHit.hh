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
// $Id: ExN02TrackerHit.hh,v 1.8 2006-06-29 17:47:53 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef ExN01TrackerHit_h
#define ExN01TrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "TString.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN01TrackerHit : public G4VHit
{
    public:

        ExN01TrackerHit();
        ~ExN01TrackerHit();
        ExN01TrackerHit(const ExN01TrackerHit&);
        const ExN01TrackerHit& operator=(const ExN01TrackerHit&);
        G4int operator==(const ExN01TrackerHit&) const;

        void Draw();
        void Print(int);

    public:

        void SetRunID(G4int newValue){runID = newValue;};
        void SetEveID(G4int newValue){eveID = newValue;};
        void SetTraID(G4int newValue){traID = newValue;};
        void SetParID(G4int newValue){parID = newValue;};
        void SetSteID(G4int newValue){steID = newValue;};
        void SetPDGenc(G4int newValue){PDGenc = newValue;};
        void SetRepNSci(G4int newValue){repNSci = newValue;};
        void SetRepNSta(G4int newValue){repNSta = newValue;};
        void SetLayID(G4int newValue){layID = newValue;};

        void SetParNam(TString newValue){parNam = newValue;};
        void SetCrePro(TString newValue){crePro = newValue;};
        void SetStePro(TString newValue){stePro = newValue;};
        void SetDeaLayNam(TString newValue){deaLayNam = newValue;};

        void SetPos(G4ThreeVector newValue){pos = newValue;};
        void SetVerPos(G4ThreeVector newValue){verPos = newValue;};

        void SetGloTim(G4double newValue){gloTim = newValue;};
        void SetTraLen(G4double newValue){traLen = newValue;};
        void SetKinEne(G4double newValue){kinEne = newValue;};
        void SetVerKinEne(G4double newValue){verKinEne = newValue;};
        void SetSteLen(G4double newValue){steLen = newValue;};
        void SetTotEneDep(G4double newValue){totEneDep = newValue;};

        void SetActVol(G4bool newValue){actVol = newValue;};
        void SetOutOfWorld(G4bool newValue){outOfWorld = newValue;};

        G4int GetRunID(){return runID;};
        G4int GetEveID(){return eveID;};
        G4int GetTraID(){return traID;};
        G4int GetParID(){return parID;};
        G4int GetSteID(){return steID;};
        G4int GetPDGenc(){return PDGenc;};
        G4int GetRepNSci(){return repNSci;};
        G4int GetRepNSta(){return repNSta;};
        G4int GetLayID(){return layID;};

        TString GetParNam(){return parNam;};
        TString GetCrePro(){return crePro;};
        TString GetStePro(){return stePro;};
        TString GetDeaLayNam(){return deaLayNam;};

        G4ThreeVector GetPos(){return pos;};
        G4ThreeVector GetVerPos(){return verPos;};

        G4double GetPosX(){return pos.x();};
        G4double GetPosY(){return pos.y();};
        G4double GetPosZ(){return pos.z();};

        G4double GetVerPosX(){return verPos.x();};
        G4double GetVerPosY(){return verPos.y();};
        G4double GetVerPosZ(){return verPos.z();};

        G4double GetGloTim(){return gloTim;};
        G4double GetTraLen(){return traLen;};
        G4double GetKinEne(){return kinEne;};
        G4double GetVerKinEne(){return verKinEne;};
        G4double GetSteLen(){return steLen;};
        G4double GetTotEneDep(){return totEneDep;};

        G4bool GetActVol(){return actVol;};
        G4bool GetOutOfWorld(){return outOfWorld;};

        G4double GetDis(){return (verPos-pos).getR();};

    private:

        G4int         runID;
        G4int         eveID;
        G4int         traID;
        G4int         parID;
        G4int         steID;
        G4int         PDGenc;
        G4int         repNSci;
        G4int         repNSta;
        G4int         layID;

        TString      parNam;
        TString      crePro;
        TString      stePro;
        TString      deaLayNam;

        G4ThreeVector pos;
        G4ThreeVector verPos;

        G4double      gloTim;
        G4double      traLen;
        G4double      kinEne;
        G4double      verKinEne;
        G4double      steLen;
        G4double      totEneDep;

        G4bool        actVol;
        G4bool        outOfWorld;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
