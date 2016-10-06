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
// $Id: ExN01DetectorConstruction.cc,v 1.9 2006-06-29 17:47:19 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#include "ExN01DetectorConstruction.hh"
#include "SensitiveDetector.hh"
#include "NonSensitiveDetector.hh"
#include "ExN01DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4Isotope.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "globals.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"

#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4GeometryManager.hh"
#include "G4RunManager.hh"
#include "G4RotationMatrix.hh"

#include "AnalysisManager.hh"


ExN01DetectorConstruction::ExN01DetectorConstruction()
{
    detectorMessenger = new ExN01DetectorMessenger(this);
    SetDefaults();
    MadeMaterials();
    geometryChanged = false;
}

ExN01DetectorConstruction::~ExN01DetectorConstruction()
{
}

void ExN01DetectorConstruction::MadeMaterials(){

    //------------------------------------------------------ materials

    G4double a;
    G4double z;
    G4double density;
    G4String name;
    G4String symbol;
    G4int    ncomponents;
    G4double fractionmass;

    G4NistManager* man = G4NistManager::Instance();

    tiO2 = man->FindOrBuildMaterial("G4_TITANIUM_DIOXIDE");
    GdMat = man->FindOrBuildMaterial("G4_Gd");
    OMat = man->FindOrBuildMaterial("G4_O");

    G4Element* Gd = man->FindOrBuildElement("Gd");
    G4Element* O = man->FindOrBuildElement("O");
    G4Element* Cl = man->FindOrBuildElement("Cl");

    GdtiO2 = new G4Material("Gd+TiO2", density = 4.26*g/cm3, ncomponents = 2);
    GdtiO2->AddMaterial(tiO2, fractionmass=95.0*perCent);
    GdtiO2->AddMaterial(GdMat, fractionmass=5.0*perCent);

    Gd2O3 = new G4Material("Gd2O3", density = 7.407*g/cm3, ncomponents = 2);
    Gd2O3->AddElement(Gd, ncomponents=2);
    Gd2O3->AddElement(O, ncomponents=3);

    GdCl3 = new G4Material("GdCl3", density = 4.52*g/cm3, ncomponents = 2);
    GdCl3->AddElement(Gd, ncomponents=1);
    GdCl3->AddElement(Cl, ncomponents=3);

    G4Element* H = man->FindOrBuildElement("H");
    G4Element* C = man->FindOrBuildElement("C");

    Vacuum = new G4Material(name="Vacuum", z=1.0 , a=1.01*g/mole , density= universe_mean_density ,
                                        kStateGas, 2.73*kelvin, 3.e-18*pascal);

    C8H8 = new G4Material(name="polystyrene", density=1.03*g/cm3, ncomponents=2);
    C8H8 -> AddElement(C, ncomponents=8);
    C8H8 -> AddElement(H, ncomponents=8);

}

G4VPhysicalVolume* ExN01DetectorConstruction::Construct()
{
    //------------------------------ experimental hall (world volume)

    G4Box* experimentalHall_box
        = new G4Box("expHall_box",expHall_x/2,expHall_y/2,expHall_z/2);
    G4LogicalVolume* experimentalHall_log = new G4LogicalVolume(experimentalHall_box,
                                                Vacuum,"expHall_log",0,0,0);
    G4PVPlacement* experimentalHall_phys = new G4PVPlacement(0,G4ThreeVector(),
                                        experimentalHall_log,"expHall",0,false,0);

    G4Box* det_box = new G4Box("det_box", det_x/2, det_y/2, det_z/2);
    G4LogicalVolume* det_log = new G4LogicalVolume(det_box, Vacuum, "det_log", 0,0,0);
    G4PVPlacement* det_phys = new G4PVPlacement(0, G4ThreeVector(0,0,0), det_log, "Detector", experimentalHall_log, false, 0);

    G4Box* stack_box = new G4Box("stack_box", stack_x/2, stack_y/2, stack_z/2);
    G4LogicalVolume* stack_log = new G4LogicalVolume(stack_box, Vacuum, "stack_log", 0,0,0);
    if (nStacks > 1) {
        G4PVReplica* stack_phys  = new G4PVReplica("Stack", stack_log, det_log, kZAxis, nStacks, stack_z);
    }else{
        G4PVPlacement* stack_phys = new G4PVPlacement(0, G4ThreeVector(0,0,0), stack_log, "Stack", det_log, false, 0);
    }


    G4Box* layer_box = new G4Box("layer_box", layer_x/2, layer_y/2, layer_z/2);
    G4LogicalVolume* layer_log = new G4LogicalVolume(layer_box, Vacuum, "layer_log", 0,0,0);
    G4double phi = 90.*deg;
    G4RotationMatrix* rm = new G4RotationMatrix();
    rm->rotateZ(phi);
    G4PVPlacement* layer_phys1 = new G4PVPlacement(0, G4ThreeVector(0,0,-layer_z/2), layer_log, "Layer1", stack_log, false, 0);
    //G4PVPlacement* layer_phys2 = new G4PVPlacement(rm, G4ThreeVector(0,0,layer_z/2), layer_log, "Layer2", stack_log, false, 0);
    G4PVPlacement* layer_phys2 = new G4PVPlacement(0, G4ThreeVector(0,0,layer_z/2), layer_log, "Layer2", stack_log, false, 0);

    G4Box* scint_box = new G4Box("scint_box", scint_x/2, scint_y/2, scint_z/2);
    G4LogicalVolume* scint_log = new G4LogicalVolume(scint_box, GdCl3, "scint_log", 0,0,0);
    if (nScintInOneLayer > 1) {
        G4PVReplica* scint_phys  = new G4PVReplica("Scintilator", scint_log, layer_log, kYAxis, nScintInOneLayer, scint_y);
    }else{
        G4PVPlacement* scint_phys = new G4PVPlacement(0, G4ThreeVector(0,0,0), scint_log, "Scintilator", layer_log, false, 0);
    }

    G4Box* poly_box = new G4Box("poly_box", poly_x/2, poly_y/2, poly_z/2);
    G4LogicalVolume* poly_log = new G4LogicalVolume(poly_box, C8H8, "poly_log", 0,0,0);
    G4PVPlacement* poly_phys = new G4PVPlacement(0, G4ThreeVector(0,0,0), poly_log, "Polyethylene", scint_log, false, 0);

    //------------------------------ sensitive volumes ---------->>

    G4SDManager * pointSDMan = G4SDManager::GetSDMpointer();

    if (!geometryChanged){
        G4VSensitiveDetector *polySens = new SensitiveDetector("ScintDet");
        poly_log -> SetSensitiveDetector(polySens);
        pointSDMan -> AddNewDetector(polySens);
        G4VSensitiveDetector *tio2Sens = new NonSensitiveDetector("DeadLayer");
        scint_log -> SetSensitiveDetector(tio2Sens);
        pointSDMan -> AddNewDetector(tio2Sens);
        G4VSensitiveDetector *worldSens = new NonSensitiveDetector("World");
        experimentalHall_log -> SetSensitiveDetector(worldSens);
        pointSDMan -> AddNewDetector(worldSens);
    }else{
        G4VSensitiveDetector *polySens = pointSDMan->FindSensitiveDetector("ScintDet");
        poly_log -> SetSensitiveDetector(polySens);
        G4VSensitiveDetector *tio2Sens = pointSDMan->FindSensitiveDetector("DeadLayer");
        scint_log -> SetSensitiveDetector(tio2Sens);
        G4VSensitiveDetector *worldSens = pointSDMan->FindSensitiveDetector("World");
        experimentalHall_log -> SetSensitiveDetector(worldSens);
    }



    return experimentalHall_phys;
}

void ExN01DetectorConstruction::UpdateGeometry(){

  // clean-up previous geometry
    geometryChanged = true;

    G4GeometryManager::GetInstance()->OpenGeometry();

    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();
    //G4VSensitiveDetector

    //define new one
    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void ExN01DetectorConstruction::PrintDimensions(){

    G4cout << "nLayers = " << nLayers << G4endl;
}

void ExN01DetectorConstruction::SetDefaults(){

    nLayers   = 40;
    nScintInOneLayer = 2;
    nLayInOneStack = 2;

    tiO2_thick = 64.0*um;

    poly_x = 40.0*cm;
    poly_y = 20.0*cm;
    poly_z = 1.0*cm;

    CountDimensions();
}

void ExN01DetectorConstruction::CountDimensions(){

    nStacks   = nLayers/nLayInOneStack;

    scint_x = poly_x+2*tiO2_thick;
    scint_y = poly_y+2*tiO2_thick;
    scint_z = poly_z+2*tiO2_thick;

    layer_x = scint_x;
    layer_y = scint_y*nScintInOneLayer;
    layer_z = scint_z;

    stack_x = layer_y; //layer_y je malinko širší než layer_x a nevešlo by se rozměrově.
    stack_y = layer_y;
    stack_z = layer_z*nLayInOneStack;

    det_x = stack_x;
    det_y = stack_y;
    det_z = stack_z*nStacks;

    expHall_x = 1.5*det_x;
    expHall_y = 1.5*det_y;
    expHall_z = 1.5*det_z;

    AnalysisManager * analysis = AnalysisManager::GetInstance();
    analysis->UpdateScintDim(poly_x,poly_y,poly_z);
    analysis->UpdateNumScint(nLayers,nLayInOneStack, nScintInOneLayer);
    analysis->UpdateDeadLayThic(tiO2_thick);
}

/*SensitiveDetector* ExN01DetectorConstruction::GetSensDet(void){

    G4SDManager * pointSDMan = G4SDManager::GetSDMpointer();
    SensitiveDetector* polySens = pointSDMan->FindSensitiveDetector("ScintDet");
    return polySens;

}

NonSensitiveDetector* ExN01DetectorConstruction::GetNonSensDet1(void){

    G4SDManager * pointSDMan = G4SDManager::GetSDMpointer();
    NonSensitiveDetector* tio2Sens = pointSDMan->FindSensitiveDetector("DeadLayer");
    return tio2Sens;

}

NonSensitiveDetector* ExN01DetectorConstruction::GetNonSensDet2(void){

    G4SDManager * pointSDMan = G4SDManager::GetSDMpointer();
    NonSensitiveDetector* worldSens = pointSDMan->FindSensitiveDetector("World");
    return worldSens;

}*/

