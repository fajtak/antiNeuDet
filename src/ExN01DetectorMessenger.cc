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
#include "ExN01DetectorMessenger.hh"
#include "ExN01DetectorConstruction.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4Scintillation.hh"

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
ExN01DetectorMessenger::ExN01DetectorMessenger(ExN01DetectorConstruction* ExN01Detect)
:ExN01Detector(ExN01Detect)
{
    //Setup a command directory for detector controls with guidance
    detectorDir = new G4UIdirectory("/antiNeu/geometry/");
    detectorDir->SetGuidance("Detector geometry control");

    //Various commands for modifying detector geometry

    polyXCmd = new G4UIcmdWithADoubleAndUnit("/antiNeu/geometry/polyX",this);
    polyXCmd->SetGuidance("Set the dimension of the polyethylene detector in x axis.");
    polyXCmd->SetDefaultUnit("cm");

    polyYCmd = new G4UIcmdWithADoubleAndUnit("/antiNeu/geometry/polyY",this);
    polyYCmd->SetGuidance("Set the dimension of the polyethylene detector in y axis.");
    polyYCmd->SetDefaultUnit("cm");

    polyZCmd = new G4UIcmdWithADoubleAndUnit("/antiNeu/geometry/polyZ",this);
    polyZCmd->SetGuidance("Set the dimension of the polyethylene detector in z axis.");
    polyZCmd->SetDefaultUnit("cm");

    tiO2thickCmd = new G4UIcmdWithADoubleAndUnit("/antiNeu/geometry/tiO2thick",this);
    tiO2thickCmd->SetGuidance("Set the thickness of the tiO2 coaching of polyethylene detector.");
    tiO2thickCmd->SetDefaultUnit("um");

    nLayersCmd = new G4UIcmdWithAnInteger("/antiNeu/geometry/nLayers",this);
    nLayersCmd->SetGuidance("Choose the number of layers in the detector.");
    nLayersCmd->SetParameterName("nLayers",false);
    nLayersCmd->SetRange("nLayers>1");

    nLayInOneStackCmd = new G4UIcmdWithAnInteger("/antiNeu/geometry/nLayInOneStack",this);
    nLayInOneStackCmd->SetGuidance("Choose the number of layers in one stack.");
    nLayInOneStackCmd->SetParameterName("nLayInOneStack",false);
    nLayInOneStackCmd->SetRange("nLayInOneStack>0");

    nScintInOneLayerCmd = new G4UIcmdWithAnInteger("/antiNeu/geometry/nScintInOneLayer",this);
    nScintInOneLayerCmd->SetGuidance("Choose the number of scintilators in one layer.");
    nScintInOneLayerCmd->SetParameterName("nScintInOneLayer",false);
    nScintInOneLayerCmd->SetRange("nScintInOneLayer>0");

    updateCmd = new G4UIcommand("/antiNeu/geometry/update",this);
    updateCmd->SetGuidance("Update the detector geometry with changed values.");
    updateCmd->SetGuidance("Must be run before beamOn if detector has been changed.");
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
ExN01DetectorMessenger::~ExN01DetectorMessenger()
{
    delete updateCmd;
    delete detectorDir;

    delete nLayersCmd;
    delete nLayInOneStackCmd;
    delete nScintInOneLayerCmd;
    delete polyXCmd;
    delete polyYCmd;
    delete polyZCmd;
    delete tiO2thickCmd;
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void ExN01DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if( command == polyXCmd ){
        ExN01Detector->SetPoly_x(polyXCmd->GetNewDoubleValue(newValue));
    }
    else if (command == polyYCmd){
        ExN01Detector->SetPoly_y(polyYCmd->GetNewDoubleValue(newValue));
    }
    else if (command == polyZCmd){
        ExN01Detector->SetPoly_z(polyZCmd->GetNewDoubleValue(newValue));
    }
    else if (command == tiO2thickCmd){
        ExN01Detector->SetTiO2_thick(tiO2thickCmd->GetNewDoubleValue(newValue));
    }
    else if (command == nLayersCmd){
        ExN01Detector->SetNLayers(nLayersCmd->GetNewIntValue(newValue));
    }
    else if (command == nLayInOneStackCmd){
        ExN01Detector->SetNLayInOneStack(nLayInOneStackCmd->GetNewIntValue(newValue));
    }
    else if (command == nScintInOneLayerCmd){
        ExN01Detector->SetNScintInOneLayer(nScintInOneLayerCmd->GetNewIntValue(newValue));
    }
    else if (command == updateCmd){
        ExN01Detector->CountDimensions();
        ExN01Detector->UpdateGeometry();
    }
}
