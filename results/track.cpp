#include "track.h"

using namespace std;

Track::Track(int traID, int parID, int PDG, char* parNam, char* crePro, TVector3 verPos, double traLen, double verKinEne, bool outWor)
{
    trackID = traID;
    parentID = parID;
    PDGencoding = PDG;
    particleName = parNam;
    creationProcess = crePro;
    vertexPosition = verPos;
    trackLength = traLen;
    vertexKineticEnergy = verKinEne;
    outOfWorld = outWor;

    nVertices = 0;
}

Track::~Track()
{
}


Vertex* Track::GetVertex(int whichVertex)
{
    return allVertices[whichVertex];
}

void Track::AddVertex(int steID, int repNSci, int repNSta, int layID, char* stePro, TVector3 pos,bool actVol, double gloTim, double kinEne, double steLen, double totEneDep)
{
    Vertex* newVertex = new Vertex(steID,repNSci,repNSta,layID,stePro,pos,actVol,gloTim,kinEne,steLen,totEneDep);
    allVertices.push_back(newVertex);
    nVertices++;
}

void Track::PrintVertices(void)
{
    cout << "      *****************************************************************************************************************************" << endl;
    cout << "      | SteID | SciID | StaID | LayID |  Step Process  |    X    |    Y    |    Z    | GloTim | KinEne | SteLen | EneDep | ActVol |" << endl;
    cout << "      *****************************************************************************************************************************" << endl;
    for (int i = 0 ; i < nVertices ; i++)
        allVertices[i]->PrintVertex();
    cout << "      *****************************************************************************************************************************" << endl;
}

void Track::PrintTrack(void)
{
    cout << setw(7) << trackID << setw(8) << parentID << setw(10) << PDGencoding << setw(15) << particleName;
    cout << setw(14) << creationProcess << setprecision(3) << setw(10) << vertexPosition(0) << setw(10) << vertexPosition(1);
    cout  << setw(10) << vertexPosition(2) << setw(14) << trackLength << setw(12) << vertexKineticEnergy << setw(11) << outOfWorld << endl;
    //setprecision(3) << setw(8)
}

Vertex* Track::GetLastVertex(void)
{
    return allVertices[nVertices-1];
}

bool Track::NameContain(TString partName)
{
    if (particleName.Contains(partName))
        return true;
    else
        return false;
}

Vertex* Track::FindVertexStepProcess(TString stePro)
{
    for (int i = 0 ; i < nVertices ; i++)
    {
        if (allVertices[i]->GetStepProcess() == stePro)
            return GetVertex(i);
    }
}
