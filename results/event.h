#ifndef EVENT_H
#define EVENT_H

#include "track.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include "TH1F.h"
#include "TCanvas.h"

using namespace std;

struct Hit
{
    double time;
    double energy;
};

class Event
{
    private:
        int nTracks;
        vector<Track*> allTracks;

        bool neutronCaptured;
        bool neutronEscaped;
        int neutronCapturedGammaProduced;
        vector<Track*> neutronGammasCreated;
        vector<double> neutronGammasEnergies;
        int neutronNIntBeforeCapture;
        double neutronTrackLength;
        double neutronDistance;
        bool neutronGdCaptured;
        double neutronInitialEnergy;
        int neutronMultiplicity;

        bool pozitronAnnihil;
        bool pozitronEscaped;
        int pozitronAnnihilGammaProduced;
        vector<Track*> pozitronGammasCreated;
        vector<double> pozitronGammasEnergies;
        int pozitronNIntBeforeAnnihil;
        double pozitronTrackLength;
        double pozitronDistance;
        double pozitronInitialEnergy;
        int pozitronMultiplicity;

        double pgFirstEnergies[2];
        double pgFirstDist[2];
        double scintEner[100][25];
        double promptEne[2];
        double delayEne[2];

        double neutronGammasSumDepEne;

        double timeDist;

        vector<Hit> hits;

    public:
        Event();
        ~Event();

        bool GetNeutronCaptured(void){return neutronCaptured;};
        bool GetNeutronEscaped(void){return neutronEscaped;};
        int GetNeutronCapturedGammaProduced(void){return neutronCapturedGammaProduced;};
        vector<double>& GetNeutronGammaEnergies(void){return neutronGammasEnergies;};
        double GetNeutronGammaEnergiesSum(void);
        int GetNeutronNIntBeforeCapture(void){return neutronNIntBeforeCapture;};
        double GetNeutronTrackLength(void){return neutronTrackLength;};
        double GetNeutronDistance(void){return neutronDistance;};
        bool GetNeutronGdCaptured(void){return neutronGdCaptured;};
        double GetNeutronInitialEnergy(void){return neutronInitialEnergy;};
        int GetNeutronMultiplicity(void){return neutronMultiplicity;};

        bool GetPozitronAnnihil(void){return pozitronAnnihil;};
        bool GetPozitronEscaped(void){return pozitronEscaped;};
        int GetPozitronAnnihilGammaProduced(void){return pozitronAnnihilGammaProduced;};
        vector<double>& GetPozitronGammaEnergies(void){return pozitronGammasEnergies;};
        int GetPozitronNIntBeforeAnnihil(void){return pozitronNIntBeforeAnnihil;};
        double GetPozitronTrackLength(void){return pozitronTrackLength;};
        double GetPozitronDistance(void){return pozitronDistance;};
        double GetPozitronInitialEnergy(void){return pozitronInitialEnergy;};
        int GetPozitronMultiplicity(void){return pozitronMultiplicity;};

        double GetTimeDist(void){return timeDist;};
        double GetPGFirstEnergies(int which){return pgFirstEnergies[which];};
        double GetPGFirstDist(int which){return pgFirstDist[which];};

        double GetPromptEne(int which){return promptEne[which];};
        double GetDelayEne(int which){return delayEne[which];};

        double GetNeutronGammasSumDepEne(void){return neutronGammasSumDepEne;};

        void AddTrack(int trackID, int parentID, int PDGenconding, char* particleName, char* crePro, TVector3 verPos, double traLen, double verKinEne, bool outWor);
        Track* GetTrack(int whichTrack);

        int GetNTracks(){return nTracks;};
        void SetNTracks(int newValue){nTracks = newValue;};

        void PrintTracks(int verbose = 0);

        bool Escaped(TString particle, bool &isEscaped);
        bool LastInteractedLike(TString particle, bool &isCaptured, TString inter);
        int GammaProduced(TString particle, vector<Track*> &findTracks, TString process, int &nGammaProduced);
        int NeutronCapturedGammaEnergies(vector<Track*> &gammas);
        int PozitronAnnihilGammaEnergies(vector<Track*> &gammas);
        int NInt(TString Particle, TString endProcess, int &nInt);
        void Distances(TString particle, double &tralen, double &dist);
        bool NeutronGdCaptured(void);
        double InitialEnergy(TString particle, double &initEne);
        int Multiplicity(TString particle, int &multi);

        int PozitronGammas(void);
        double NeutronGammas(void);
        double TimeDist();
        void ScintEnergies();

        void ProcessNeutrons(void);
        void ProcessPozitrons(void);
        void ProcessRest(void);

        Track* FindTrackTrackID(int traID);
        Track* FindTrackParticleName(TString parNam);
        Track* FindPrimaryTrackParticleName(TString parNam);
        int FindOffspring(int traID, vector<Track*> &chosen);
        int AddOffspring(int traID, vector<Track*> &chosen);
        int FilterOffspringByCreationProcess(TString crePro, vector<Track*> &chosen);
        int FilterOffspringByParticleName(TString parNam, vector<Track*> &chosen);
        int FilterOffspringByVertexPosition(TVector3 verPos, vector<Track*> &chosen);
        int FindAllDaughters(vector<Track*> &chosen);
        double EnergyOfDaughters(vector<Track*> &chosen);
};

#endif
