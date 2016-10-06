#include "event.h"

using namespace std;

Event::Event() : scintEner{0}, promptEne{0}, delayEne{0}
{
    nTracks = 0;
    pgFirstEnergies[0] = -1;
    pgFirstEnergies[1] = -1;
    pgFirstDist[0] = -1;
    pgFirstDist[1] = -1;
    timeDist = -1;
    neutronGammasSumDepEne = 0;
}

Event::~Event()
{
}

Track* Event::GetTrack(int whichTrack)
{
    return allTracks[whichTrack];
}

void Event::AddTrack(int traID, int parID, int PDG, char* parNam, char* crePro, TVector3 verPos, double traLen, double verKinEne, bool outWor)
{
    Track* newTrack = new Track(traID,parID,PDG,parNam,crePro,verPos,traLen,verKinEne,outWor);
    allTracks.push_back(newTrack);
    nTracks++;
}

void Event::PrintTracks(int verbose)
{
    cout << "***************************************************************************************************************************" << endl;
    cout << "| TraID | ParID |   PDG   | ParticleName | CreaProcess |    X    |    Y    |    Z    | TrackLength | VerKinEne | OutOfWor |" << endl;
    cout << "***************************************************************************************************************************" << endl;
    if (verbose == 0)
    {
        for (int i = 0 ; i < nTracks ; i++)
            allTracks[i]->PrintTrack();
    }

    if (verbose == 1)
    {
        Track* jedna = FindTrackTrackID(1);
        for (int i = 0 ; i < nTracks ; i++)
        {
            allTracks[i]->PrintTrack();
            if (allTracks[i] == jedna)
                allTracks[i]->PrintVertices();
        }
    }
    if (verbose == 2)
    {
        Track* jedna = FindTrackTrackID(1);
        Track* dva = FindTrackTrackID(2);
        for (int i = 0 ; i < nTracks ; i++)
        {
            allTracks[i]->PrintTrack();
            if ((allTracks[i] == jedna)||(allTracks[i] == dva))
                allTracks[i]->PrintVertices();
        }
    }
    if (verbose > 2)
        for (int i = 0 ; i < nTracks ; i++)
        {
            allTracks[i]->PrintTrack();
            allTracks[i]->PrintVertices();
        }
}

bool Event::LastInteractedLike(TString particle, bool &isCaptured, TString inter)
{
    Track* track = FindPrimaryTrackParticleName(particle);
    if (track->GetLastVertex()->GetStepProcess() == inter)
    {
        isCaptured = true;
        return true;
    }else{
        isCaptured = false;
        return false;
    }
}

bool Event::Escaped(TString particle, bool &isEscaped)
{
    Track* track = FindPrimaryTrackParticleName(particle);
    if (track->GetOutOfWorld())
    {
        isEscaped = true;
        return true;
    }else{
        isEscaped = false;
        return false;
    }
}

int Event::GammaProduced(TString particle,vector<Track*> &findTracks,TString process, int &nGammaProduced)
{
    FindOffspring(FindPrimaryTrackParticleName(particle)->GetTrackID(),findTracks);
    FilterOffspringByCreationProcess(process,findTracks);
    nGammaProduced = FilterOffspringByParticleName("gamma",findTracks);
    return nGammaProduced;
}

int Event::NeutronCapturedGammaEnergies(vector<Track*> &gammas)
{
    neutronGammasEnergies.clear();
    for (int i = 0 ; i < gammas.size() ; i++)
    {
        neutronGammasEnergies.push_back(gammas[i]->GetVertexKineticEnergy());
    }
}

int Event::PozitronAnnihilGammaEnergies(vector<Track*> &gammas)
{
    pozitronGammasEnergies.clear();
    for (int i = 0 ; i < gammas.size() ; i++)
    {
        pozitronGammasEnergies.push_back(gammas[i]->GetVertexKineticEnergy());
    }
}

int Event::NInt(TString particle, TString endProcess, int &nInt)
{
    nInt = 0;
    Track* track = FindPrimaryTrackParticleName(particle);
    int nVertices = track->GetNVertices();
    for (int i = 0 ; i < nVertices ; i++)
    {
        if (track->GetVertex(i)->GetStepProcess() == endProcess)
            break;
        if (track->GetVertex(i)->GetStepProcess() != "Transportation")
            nInt++;
    }
    return nInt;
}

void Event::Distances(TString particle, double &traLen, double &dist)
{
    Track* track = FindPrimaryTrackParticleName(particle);
    traLen = track->GetTrackLength();
    dist = (track->GetVertexPosition()- track->GetLastVertex()->GetPosition()).Mag();
}

bool Event::NeutronGdCaptured(void)
{
    vector<Track*> createdParticles;
    if (neutronCaptured)
    {
        FindOffspring(FindPrimaryTrackParticleName("neutron")->GetTrackID(),createdParticles);
        FilterOffspringByCreationProcess("nCapture",createdParticles);
        for (int i = 0 ; i < createdParticles.size() ; i++)
        {
            if(createdParticles[i]->NameContain("Gd"))
            {
                neutronGdCaptured = true;
                return true;
            }
        }
    }
    neutronGdCaptured = false;
    return false;
}

double Event::GetNeutronGammaEnergiesSum(void)
{
    double energySum = 0;
    for (int i = 0 ; i < neutronGammasEnergies.size(); i++)
        energySum += neutronGammasEnergies[i];
    return energySum;
}

double Event::InitialEnergy(TString particle, double &initEne)
{
    Track* track = FindPrimaryTrackParticleName(particle);
    initEne = track->GetVertexKineticEnergy();
    return initEne;
}

int Event::Multiplicity(TString particle, int &multi)
{
    Track* track = FindPrimaryTrackParticleName(particle);
    int nVertices = track->GetNVertices();
    int detID = 0;
    vector<int> IDs;
    Vertex* recentVertex;
    bool allreadyHitted;
    for (int i = 0 ; i < nVertices ; i++)
    {
        allreadyHitted = false;
        recentVertex = track->GetVertex(i);
        if (!recentVertex->GetActiveVolume())
            continue;
        detID = 1000000*recentVertex->GetReplicaNStack() + 10*recentVertex->GetReplicaNScint() + recentVertex->GetLayerID();
        for (int j = 0 ; j < IDs.size() ; j++)
        {
            if (IDs[j] == detID)
                allreadyHitted = true;
        }
        if (!allreadyHitted)
            IDs.push_back(detID);
    }
    multi = IDs.size();
    return multi;
}

int Event::FindOffspring(int traID, vector<Track*> &chosen)
{
    chosen.clear();
    int nChosen = 0;
    for (int i = 0 ; i < nTracks ; i++)
    {
        if (allTracks[i]->GetParentID() == traID)
        {
            chosen.push_back(allTracks[i]);
            nChosen++;
        }
    }
    return nChosen;
}

int Event::AddOffspring(int traID, vector<Track*> &chosen)
{
    int nChosen = 0;
    for (int i = 0 ; i < nTracks ; i++)
    {
        if (allTracks[i]->GetParentID() == traID)
        {
            chosen.push_back(allTracks[i]);
            nChosen++;
        }
    }
    return nChosen;
}

int Event::FilterOffspringByCreationProcess(TString crePro, vector<Track*> &chosen)
{
    vector<int> toDelete;
    for (int i = 0 ; i < chosen.size() ; i++)
    {
        if (chosen[i]->GetCreationProcess() != crePro)
        {
            toDelete.push_back(i);
        }
    }
    for (int i = toDelete.size()-1 ; i >= 0 ; i--)
        chosen.erase(chosen.begin()+toDelete[i]);
    return chosen.size();
}

int Event::FilterOffspringByParticleName(TString parNam, vector<Track*> &chosen)
{
    vector<int> toDelete;
    for (int i = 0 ; i < chosen.size() ; i++)
    {
        if (chosen[i]->GetParticleName() != parNam)
            toDelete.push_back(i);
    }
    for (int i = toDelete.size()-1 ; i >= 0 ; i--)
        chosen.erase(chosen.begin()+toDelete[i]);
    return chosen.size();
}

int Event::FilterOffspringByVertexPosition(TVector3 verPos, vector<Track*> &chosen)
{
    vector<int> toDelete;
    for (int i = 0 ; i < chosen.size() ; i++)
    {
        if (chosen[i]->GetVertexPosition() != verPos)
            toDelete.push_back(i);
    }
    for (int i = toDelete.size()-1 ; i >= 0 ; i--)
        chosen.erase(chosen.begin()+toDelete[i]);
    return chosen.size();
}

Track* Event::FindTrackTrackID(int traID)
{
    for (int i = 0 ; i < nTracks ; i++)
    {
        if (allTracks[i]->GetTrackID() == traID)
            return GetTrack(i);
    }
}

Track* Event::FindTrackParticleName(TString parNam)
{
    for (int i = 0 ; i < nTracks ; i++)
    {
        if (allTracks[i]->GetParticleName() == parNam)
            return GetTrack(i);
    }
}

Track* Event::FindPrimaryTrackParticleName(TString parNam)
{
    for (int i = 0 ; i  < nTracks ; i++)
    {
        if ((allTracks[i]->GetParticleName() == parNam)&&(allTracks[i]->GetTrackID() < 3))
            return GetTrack(i);
    }
}

void Event::ProcessNeutrons(void)
{
    TString particle = "neutron";
    TString inter = "nCapture";
    LastInteractedLike(particle,neutronCaptured,inter);
    Escaped(particle,neutronEscaped);
    GammaProduced(particle,neutronGammasCreated,inter,neutronCapturedGammaProduced);
    NeutronCapturedGammaEnergies(neutronGammasCreated);
    NInt(particle,inter,neutronNIntBeforeCapture);
    Distances(particle, neutronTrackLength, neutronDistance);
    NeutronGdCaptured();
    InitialEnergy(particle,neutronInitialEnergy);
    Multiplicity(particle,neutronMultiplicity);
}

void Event::ProcessPozitrons(void)
{
    TString particle = "e+";
    TString inter = "annihil";
    LastInteractedLike(particle,pozitronAnnihil,inter);
    Escaped(particle,pozitronEscaped);
    GammaProduced(particle,pozitronGammasCreated,inter,pozitronAnnihilGammaProduced);
    PozitronAnnihilGammaEnergies(pozitronGammasCreated);
    NInt(particle,inter,pozitronNIntBeforeAnnihil);
    Distances(particle, pozitronTrackLength, pozitronDistance);
    InitialEnergy(particle,pozitronInitialEnergy);
    Multiplicity(particle,pozitronMultiplicity);
}

void Event::ProcessRest(void)
{
    PozitronGammas();
    NeutronGammas();
    TimeDist();
    ScintEnergies();
}

void Event::ScintEnergies(void)
{
    //TH1F* example1 = new TH1F("example1","Channel 1",210,-5,100);
    //TH1F* example2 = new TH1F("example2","Channel 2",210,-5,100);
    int layer = 0;
    int scint = 0;
    for (int i = 0 ; i < nTracks ; i++)
    {
        for (int j = 0 ; j < allTracks[i]->GetNVertices() ; j++)
        {
            if (allTracks[i]->GetVertex(j)->GetActiveVolume())
            {
                layer = allTracks[i]->GetVertex(j)->GetReplicaNStack()*2 + allTracks[i]->GetVertex(j)->GetLayerID() - 1;
                scint = allTracks[i]->GetVertex(j)->GetReplicaNScint();
                scintEner[layer][scint] += allTracks[i]->GetVertex(j)->GetTotalEnergyDeposition();
                hits.push_back(Hit());
                hits.back().time = allTracks[i]->GetVertex(j)->GetGlobalTime();
                hits.back().energy = allTracks[i]->GetVertex(j)->GetTotalEnergyDeposition();
                if (hits.back().energy > 0.033 )
                {
                    if (hits.back().time < 0.5)
                        promptEne[allTracks[i]->GetVertex(j)->GetLayerID() - 1] += hits.back().energy;
                    else
                        delayEne[allTracks[i]->GetVertex(j)->GetLayerID() - 1] += hits.back().energy;
                    //cout << hits.back().time << " " << hits.back().energy << endl;
                    /*if (allTracks[i]->GetVertex(j)->GetLayerID() == 1)
                        example1->Fill(hits.back().time,hits.back().energy);
                    else
                        example2->Fill(hits.back().time,hits.back().energy);*/
                }
            }
        }
    }

    //example1->Draw();
    //example2->Draw();
    //example1->Delete();
    //example2->Delete();
    /*for (int i = 0 ; i < 40 ; i++)
    {
        for (int j = 0 ; j < 2 ; j++)
        {
            cout << scintEner[i][j] << " ";
        }
        cout << endl;
    }*/
}

int Event::PozitronGammas(void)
{
    vector<Track*> daughters;
    double energy = 0;
    bool first = true;
    for (int i = 0 ; i < pozitronAnnihilGammaProduced ; i++)
    {
        int nVertices = pozitronGammasCreated[i]->GetNVertices();
        first = true;
        for (int j = 0 ; j < nVertices ; j++)
        {
            if (pozitronGammasCreated[i]->GetVertex(j)->GetStepProcess() != "Transportation")
            {
                FindOffspring(pozitronGammasCreated[i]->GetTrackID(),daughters);
                FilterOffspringByVertexPosition(pozitronGammasCreated[i]->GetVertex(j)->GetPosition(),daughters);
                FindAllDaughters(daughters);
                energy = EnergyOfDaughters(daughters);
                if (first)
                {
                    pgFirstDist[i] = (pozitronGammasCreated[i]->GetVertex(j)->GetPosition()- pozitronGammasCreated[i]->GetVertexPosition()).Mag();
                    pgFirstEnergies[i] = energy;
                    first = false;
                }
            }
        }
    }
}

double Event::NeutronGammas(void)
{
    vector<Track*> daughters;
    double energy = 0;
    neutronGammasSumDepEne = 0;
    for (int i = 0 ; i < neutronCapturedGammaProduced ; i++)
    {
        int nVertices = neutronGammasCreated[i]->GetNVertices();
        for (int j = 0 ; j < nVertices ; j++)
        {
            if (neutronGammasCreated[i]->GetVertex(j)->GetStepProcess() != "Transportation")
            {
                FindOffspring(neutronGammasCreated[i]->GetTrackID(),daughters);
                FilterOffspringByVertexPosition(neutronGammasCreated[i]->GetVertex(j)->GetPosition(),daughters);
                FindAllDaughters(daughters);
                energy = EnergyOfDaughters(daughters);
                neutronGammasSumDepEne += energy;
            }
        }
    }
    return neutronGammasSumDepEne;
}

double Event::TimeDist()
{
    timeDist = -1;
    Track* neutron = FindPrimaryTrackParticleName("neutron");
    Track* pozitron = FindPrimaryTrackParticleName("e+");
    if (neutronCaptured&&pozitronAnnihil)
        timeDist = (neutron->FindVertexStepProcess("nCapture")->GetGlobalTime() - pozitron->FindVertexStepProcess("annihil")->GetGlobalTime());
    return timeDist;
}

int Event::FindAllDaughters(vector<Track*> &chosen)
{
    int nAdded = 0;
    int nAddedAll = 0;
    int nAddedLast = 0;
    int nInit =  chosen.size();
    for (int i = 0 ; i < nInit ; i++)
    {
        nAdded = AddOffspring(chosen[i]->GetTrackID(),chosen);
        nAddedAll += nAdded;
        nAddedLast = nAdded;
        while (nAdded != 0)
        {
            nAdded = 0;
            for (int j = 0 ; j < nAddedLast ; j++)
            {
                nAdded += AddOffspring(chosen[nInit+nAddedAll-nAddedLast+j]->GetTrackID(),chosen);
            }
            nAddedLast = nAdded;
            nAddedAll += nAdded;
        }
    }
    return chosen.size();
}

double Event::EnergyOfDaughters(vector<Track*> &chosen)
{
    int nChosen = chosen.size();
    double depEne = 0;
    double depEneDeaday = 0;
    int nVertices = 0;
    for (int i = 0 ; i < nChosen ; i++)
    {
        nVertices = chosen[i]->GetNVertices();
        for (int j = 0 ; j < nVertices ; j++)
        {
            if (chosen[i]->GetVertex(j)->GetActiveVolume())
                depEne += chosen[i]->GetVertex(j)->GetTotalEnergyDeposition();
            else
                depEneDeaday += chosen[i]->GetVertex(j)->GetTotalEnergyDeposition();
        }
    }
    return depEne;
}

