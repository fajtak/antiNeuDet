#include "vertex.h"

Vertex::Vertex(int steID, int repNSci, int repNSta, int layID, char* stePro, TVector3 pos,bool actVol, double gloTim, double kinEne, double steLen, double totEneDep)
{
    stepID = steID;
    replicaNScint = repNSci;
    replicaNStack = repNSta;
    layerID = layID;
    stepProcess = stePro;
    position = pos;
    activeVolume = actVol;
    globalTime = gloTim;
    kineticEnergy = kinEne;
    stepLength = steLen;
    totalEnergyDeposition = totEneDep;
}

Vertex::~Vertex()
{
    ;
}

void Vertex::PrintVertex(void)
{
    cout << setw(13) << stepID << setw(8) << replicaNScint << setw(8) << replicaNStack << setw(8) << layerID;
    cout << setw(17) << stepProcess << setw(10) << position(0)<< setw(10) << position(1) << setw(10) << position(2);
    cout << setw(10) << globalTime << setw(8) << kineticEnergy  << setw(9) << stepLength;
    cout << setw(9) << totalEnergyDeposition << setw(9) << activeVolume <<endl;
}
