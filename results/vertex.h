#ifndef VERTEX_H
#define VERTEX_H

#include "TString.h"
#include "TVector3.h"

#include <iostream>
#include <iomanip>

using namespace std;

class Vertex
{
    private:
        int stepID;
        int replicaNScint;
        int replicaNStack;
        int layerID;
        TString stepProcess;
        TVector3 position;
        bool activeVolume;
        double globalTime;
        double kineticEnergy;
        double stepLength;
        double totalEnergyDeposition;

    public:
        Vertex(int steID, int repNSci, int repNSta, int layID, char* stePro, TVector3 pos,bool actVol, double gloTim, double kinEne, double steLen, double totEneDep);
        ~Vertex();

        int GetStepID(void){return stepID;};
        int GetReplicaNScint(void){return replicaNScint;};
        int GetReplicaNStack(void){return replicaNStack;};
        int GetLayerID(void){return layerID;};
        TString GetStepProcess(void){return stepProcess;};
        TVector3 GetPosition(void){return position;};
        double GetPosition(int i){return position[i];};
        double GetPositionX(void){return position[0];};
        double GetPositionY(void){return position[1];};
        double GetPositionZ(void){return position[2];};
        bool GetActiveVolume(void){return activeVolume;};
        double GetGlobalTime(void){return globalTime;};
        double GetKineticEnergy(void){return kineticEnergy;};
        double GetStepLength(void){return stepLength;};
        double GetTotalEnergyDeposition(void){return totalEnergyDeposition;};

        void SetStepID(int newValue){stepID = newValue;};
        void SetReplicaNScint(int newValue){replicaNScint = newValue;};
        void SetReplicaNStack(int newValue){replicaNStack = newValue;};
        void SetLayerID(int newValue){layerID = newValue;};
        void SetStepProcess(TString newValue){stepProcess = newValue;};
        void SetPosition(TVector3 newValue){position = newValue;};
        void SetPositionX(double newValue){position[0] = newValue;};
        void SetPositionY(double newValue){position[1] = newValue;};
        void SetPositionZ(double newValue){position[2] = newValue;};
        void SetActiveVolume(bool newValue){activeVolume = newValue;};
        void SetGlobalTime(double newValue){globalTime = newValue;};
        void SetKineticEnergy(double newValue){kineticEnergy = newValue;};
        void SetStepLength(double newValue){stepLength = newValue;};
        void SetTotalEnergyDeposition(double newValue){totalEnergyDeposition = newValue;};

        void Initialize(int parID, int PDG, char* parNam, char* crePro, TVector3 verPos, double traLen, double verKinEne, bool outWor);

        void PrintVertex(void);
};

#endif
