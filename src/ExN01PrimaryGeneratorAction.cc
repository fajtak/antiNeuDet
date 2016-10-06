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
// $Id: ExN01PrimaryGeneratorAction.cc,v 1.6 2006-06-29 17:47:23 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#include "ExN01PrimaryGeneratorAction.hh"
#include "ExN01DetectorConstruction.hh"
#include "ExN01PrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"
#include <ctime>
#include <cstdlib>

ExN01PrimaryGeneratorAction::ExN01PrimaryGeneratorAction(ExN01DetectorConstruction* myDC):myDetector(myDC)
{
    G4int n_particle = 1;
    particleGun = new G4ParticleGun(n_particle);

    gunMessenger = new ExN01PrimaryGeneratorMessenger(this);

    pos = 1;
    dir = 1;
    energy = 1;
    particle = 1;
    Update();
    fU235=new TF1("fU235","exp(4.367-4.577*x+2.100*x^2-0.5294*x^3+0.06186*x^4-0.002777*x^5)*0.0952*(x-1.293)*((x-1.293)^2-0.511^2)^0.5",1.806,10);
    fPu239=new TF1("fPu239","exp(4.757-5.392*x+2.563*x^2-0.6596*x^3+0.07820*x^4-0.003536*x^5)*0.0952*(x-1.293)*((x-1.293)^2-0.511^2)^0.5",1.806,10);
    fPu241=new TF1("fPu241","exp(2.990-2.882*x+1.278*x^2-0.3343*x^3+0.03905*x^4-0.001754*x^5)*0.0952*(x-1.293)*((x-1.293)^2-0.511^2)^0.5",1.806,10);
    fcross=new TF1("fcross","0.0952*(x-1.293)*((x-1.293)^2-0.511^2)^0.5",0,10);
    //alphaU235 = {4.367,-4.577,2.100,-0.5294,0.06186,-0.002777};
    //alphaPu239 = {4.757,-5.392,2.563,-0.6596,0.07820,-0.003536};
    //alpahPu241 = {2.990,-2.882,1.278,-0.3343,0.03905,-0.001754};
    neutronEnergies = new TH1F("neutronEnergies","neuEne",45,0,90);
    double neuEne[45] = {0,760,700,600,500,430,370,320,270,240,200,170,150,130,112,100,86,74,64,56,50,44,39,35,32,30,28,26,24,22,20,18,16,14,12,10,9,8,7,6,5,4,3,2,0};
    for (int i = 0 ; i < 45 ; i++)
        neutronEnergies->Fill(i*2,neuEne[i]);
    gRandom->SetSeed(time(NULL));
}


ExN01PrimaryGeneratorAction::~ExN01PrimaryGeneratorAction()
{
    delete particleGun;
    delete gunMessenger;
}

void ExN01PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    particleGun->SetParticlePosition(GetNewPos());

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;

    switch (particle){
        case 1 :
            particleGun->SetParticleMomentumDirection(GetNewPosDir());
            particleGun->SetParticleEnergy(GetNewPosEne());
            particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e+"));
            particleGun->GeneratePrimaryVertex(anEvent);
            break;
        case 2 :
            particleGun->SetParticleMomentumDirection(GetNewNeuDir());
            particleGun->SetParticleEnergy(GetNewNeuEne());
            particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="neutron"));
            particleGun->GeneratePrimaryVertex(anEvent);
            break;
        case 3 :
            particleGun->SetParticleMomentumDirection(GetNewPosDir());
            particleGun->SetParticleEnergy(GetNewPosEne());
            particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e+"));
            particleGun->GeneratePrimaryVertex(anEvent);
            particleGun->SetParticleMomentumDirection(GetNewNeuDir());
            particleGun->SetParticleEnergy(GetNewNeuEne());
            particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="neutron"));
            particleGun->GeneratePrimaryVertex(anEvent);
            break;
    }
}

void ExN01PrimaryGeneratorAction::Update()
{
    AnalysisManager * analysis = AnalysisManager::GetInstance();
    analysis->UpdateGunInfo(pos,dir,energy,particle);
}

G4ThreeVector ExN01PrimaryGeneratorAction::GetNewPos(void)
{
    G4double detX = 0;
    G4double detY = 0;
    G4double detZ = 0;

    switch (pos){
        case 1 :
            detX = 0;
            detY = 0;
            detZ = 0;
            break;
        case 2 :
            detX = 0;
            detY = 0;
            detZ = -myDetector->GetDet_z()/2 - 10.0*cm;
            break;
        case 3 :
            detX = (myDetector->GetDet_x())*(G4UniformRand()-0.5);
            detY = (myDetector->GetDet_y())*(G4UniformRand()-0.5);
            detZ = (myDetector->GetDet_z())*(G4UniformRand()-0.5);
            break;
        case 4 :
            detX = (myDetector->GetDet_x())*(G4UniformRand()-0.5)*0.1;
            detY = (myDetector->GetDet_y())*(G4UniformRand()-0.5)*0.1;
            detZ = (myDetector->GetDet_z())*(G4UniformRand()-0.5)*0.1;
            break;
        case 5 :
            detX = -15.0*cm;
            detY = -15.0*cm;
            detZ = 0.0*cm;
    }
    return G4ThreeVector(detX,detY,detZ);
}

G4ThreeVector ExN01PrimaryGeneratorAction::GetNewPosDir(void)
{
    G4double dirX = 0.0;
    G4double dirY = 0.0;
    G4double dirZ = 0.0;

    switch (dir){
        case 1 :
            dirX = 0.0;
            dirY = 0.0;
            dirZ = 1.0;
            break;
        case 2 :
            G4double cosTheta = -1.0+2.0*G4UniformRand();
            G4double phi = twopi * G4UniformRand();
            G4double sinTheta = sqrt(1-cosTheta*cosTheta);
            dirX = sinTheta * cos(phi);
            dirY = sinTheta * sin(phi);
            dirZ = cosTheta;
            break;
    }

    return G4ThreeVector(dirX,dirY,dirZ);
}

G4ThreeVector ExN01PrimaryGeneratorAction::GetNewNeuDir(void)
{
    G4double dirX = 0.0;
    G4double dirY = 0.0;
    G4double dirZ = -1.0;

    return G4ThreeVector(dirX,dirY,dirZ);
}

double ExN01PrimaryGeneratorAction::GetNewPosEne(void)
{
    double newEnergy;

    switch (energy){
        case 1 :
            newEnergy = 2.2*MeV;
            //particleGun->SetParticleEnergy(2.2*MeV);
            break;
        case 2 :
            newEnergy = (fU235->GetRandom(1.806,10) - (1.293 + 0.511))*MeV;
            //particleGun->SetParticleEnergy(randEne);
            break;
    }
    return newEnergy;
}

double ExN01PrimaryGeneratorAction::GetNewNeuEne(void)
{
    double newEnergy;

    switch (energy){
        case 1 :
            newEnergy = 15*keV;
            //particleGun->SetParticleEnergy(2.2*MeV);
            break;
        case 2 :
            newEnergy = neutronEnergies->GetRandom()*keV;
            //particleGun->SetParticleEnergy(randEne);
            break;
    }
    return newEnergy;
}
