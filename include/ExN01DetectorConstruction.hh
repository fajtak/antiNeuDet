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
// $Id: ExN01DetectorConstruction.hh,v 1.6 2006-06-29 17:47:13 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#ifndef ExN01DetectorConstruction_H
#define ExN01DetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

#include "G4VUserDetectorConstruction.hh"
#include "ExN01DetectorMessenger.hh"
#include "SensitiveDetector.hh"
#include "NonSensitiveDetector.hh"

class ExN01DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    ExN01DetectorConstruction();
    ~ExN01DetectorConstruction();

    G4VPhysicalVolume* Construct();

    G4int GetNLayers(void){return nLayers;};
    G4int GetNStacks(void){return nStacks;};
    G4int GetNLayInOneStack(void){return nLayInOneStack;};
    G4int GetNScintInOneLayer(void){return nScintInOneLayer;};

    G4double GetDet_x(void){return det_x;};
    G4double GetDet_y(void){return det_y;};
    G4double GetDet_z(void){return det_z;};

    G4double GetPoly_x(void){return poly_x;};
    G4double GetPoly_y(void){return poly_y;};
    G4double GetPoly_z(void){return poly_z;};

    G4double GetTiO2_thick(void){return tiO2_thick;};

    /*SensitiveDetector* GetSensDet(void);
    NonSensitiveDetector* GetNonSensDet1(void);
    NonSensitiveDetector* GetNonSensDet2(void);*/

    void SetNLayers(int newValue){nLayers = newValue;};
    void SetNStacks(int newValue){nStacks = newValue;};
    void SetNLayInOneStack(int newValue){nLayInOneStack = newValue;};
    void SetNScintInOneLayer(int newValue){nScintInOneLayer = newValue;};

    void SetDet_x(G4double newValue){det_x = newValue;};
    void SetDet_y(G4double newValue){det_y = newValue;};
    void SetDet_z(G4double newValue){det_z = newValue;};

    void SetPoly_x(G4double newValue){poly_x = newValue;};
    void SetPoly_y(G4double newValue){poly_y = newValue;};
    void SetPoly_z(G4double newValue){poly_z = newValue;};

    void SetTiO2_thick(G4double newValue){tiO2_thick = newValue;};

    void UpdateGeometry();
    void SetDefaults();
    void CountDimensions();
    void MadeMaterials();
    void PrintDimensions();

  private:

    ExN01DetectorMessenger* detectorMessenger;

    G4double tiO2_thick;

    G4double poly_x;
    G4double poly_y;
    G4double poly_z;

    G4double scint_x;
    G4double scint_y;
    G4double scint_z;

    G4double layer_x;
    G4double layer_y;
    G4double layer_z;

    G4double stack_x;
    G4double stack_y;
    G4double stack_z;

    G4double det_x;
    G4double det_y;
    G4double det_z;

    G4double expHall_x;
    G4double expHall_y;
    G4double expHall_z;

    G4int nLayers;
    G4int nStacks;
    G4int nLayInOneStack;
    G4int nScintInOneLayer;

    G4bool geometryChanged;

    G4Material* Air;
    G4Material* Vacuum;
    G4Material* tiO2;
    G4Material* C8H8;
    G4Material* GdMat;
    G4Material* GdtiO2;
    G4Material* OMat;
    G4Material* Gd2O3;
    G4Material* GdCl3;

};

#endif

