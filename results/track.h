#ifndef TRACK_H
#define TRACK_H

#include "TString.h"
#include "TVector3.h"
#include "vertex.h"
#include <vector>

#include <iostream>
#include <iomanip>

using namespace std;

class Track
{
    private:
        int trackID;
        int parentID;
        int PDGencoding;
        TString particleName;
        TString creationProcess;
        TVector3 vertexPosition;
        double trackLength;
        double vertexKineticEnergy;
        bool outOfWorld;

        int nVertices;
        vector<Vertex*> allVertices;

    public:
        Track(int traID, int parID, int PDG, char* parNam, char* crePro, TVector3 verPos, double traLen, double verKinEne, bool outWor);
        ~Track();

        void AddVertex(int steID, int repNSci, int repNSta, int layID, char* stePro, TVector3 pos,bool actVol, double gloTim, double kinEne, double steLen, double totEneDep);
        Vertex* GetVertex(int whichVertex);
        void Update(double traLen, bool outWor){trackLength = traLen;outOfWorld = outWor;};

        int GetNVertices(){return nVertices;};
        void SetNVertices(int newValue){nVertices = newValue;};

        int GetTrackID(void){return trackID;};
        int GetParentID(void){return parentID;};
        int GetPDGencoding(void){return PDGencoding;};
        TString GetParticleName(void){return particleName;};
        TString GetCreationProcess(void){return creationProcess;};
        TVector3 GetVertexPosition(void){return vertexPosition;};
        double GetVertexPosition(int i){return vertexPosition[i];};
        double GetVertexPositionX(void){return vertexPosition[0];};
        double GetVertexPositionY(void){return vertexPosition[1];};
        double GetVertexPositionZ(void){return vertexPosition[2];};
        double GetTrackLength(void){return trackLength;};
        double GetVertexKineticEnergy(void){return vertexKineticEnergy;};
        bool GetOutOfWorld(void){return outOfWorld;};

        void SetTrackID(int newValue){trackID = newValue;};
        void SetParentID(int newValue){parentID = newValue;};
        void SetPDGencoding(int newValue){PDGencoding = newValue;};
        void SetParticleName(TString newValue){particleName = newValue;};
        void SetCreationProcess(TString newValue){creationProcess = newValue;};
        void SetVertexPosition(TVector3 newValue){vertexPosition = newValue;};
        void SetVertexPositionX(double newValue){vertexPosition[0] = newValue;};
        void SetVertexPositionY(double newValue){vertexPosition[1] = newValue;};
        void SetVertexPositionZ(double newValue){vertexPosition[2] = newValue;};
        void SetTrackLength(double newValue){trackLength = newValue;};
        void SetVertexKineticEnergy(double newValue){vertexKineticEnergy = newValue;};
        void SetOutOfWorld(bool newValue){outOfWorld = newValue;};

        Vertex* FindVertexStepProcess(TString stePro);

        void PrintVertices(void);
        void PrintTrack(void);
        Vertex* GetLastVertex(void);
        bool NameContain(TString partName);
};

#endif
