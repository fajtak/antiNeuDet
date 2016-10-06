#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "ExN01DetectorConstruction.hh"
#include "ExN01PhysicsList.hh"
#include "ExN01PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

#include <ctime>

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

int main(int argc,char** argv)
{
    long seed;
    time_t systime = time(NULL);
    seed = (long) systime;
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    CLHEP::HepRandom::setTheSeed(seed);

    // Construct the default run manager
    //
    G4RunManager* runManager = new G4RunManager;

    // set mandatory initialization classes
    //
    ExN01DetectorConstruction* detector = new ExN01DetectorConstruction;
    runManager->SetUserInitialization(detector);
    //
    G4VUserPhysicsList* physics = new ExN01PhysicsList;
    runManager->SetUserInitialization(physics);

    // set mandatory user action class
    //
    G4VUserPrimaryGeneratorAction* gen_action = new ExN01PrimaryGeneratorAction(detector);
    runManager->SetUserAction(gen_action);

    //  Run action
    G4cout << ""  << G4endl;
    G4cout << "Setting Run Action... " << G4endl;
    RunAction * runAction = new RunAction(detector);
    runManager -> SetUserAction(runAction);

    //  Event action
    G4cout << ""  << G4endl;
    G4cout << "Setting Event Action... " << G4endl;
    EventAction * eventAction = new EventAction(runAction,detector);
    runManager -> SetUserAction(eventAction);

    #ifdef G4VIS_USE
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
    #endif

    // Initialize G4 kernel
    //
    runManager->Initialize();

    // Get the pointer to the UI manager and set verbosities
    //
    G4UImanager* UI = G4UImanager::GetUIpointer();


    if (argc == 2)   // batch mode
    {
        //UI->ApplyCommand("/physics_engine/neutron/energyCut -100");
        UI->ApplyCommand("/process/inactivate nKiller");
        //UI->ApplyCommand("/process/inactivate msc");
        UI->ApplyCommand("/process/list");
        //UI->ApplyCommand("/physics_engine/neutron/timeLimit 1.0");
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UI->ApplyCommand(command+fileName);
    }else{
        if(argc > 2){
            #ifdef G4VIS_USE
                UI->ApplyCommand("/control/execute visO.mac");
            #endif
        }
            //UI->ApplyCommand("/run/verbose 1");
            //UI->ApplyCommand("/event/verbose 1");
            UI->ApplyCommand("/process/inactivate nKiller");
            UI->ApplyCommand("/tracking/verbose 1");
            G4int numberOfEvent = 1;

            runManager->BeamOn(numberOfEvent);
    }


    #ifdef G4VIS_USE
    delete visManager;
    #endif

    delete runManager;

    return 0;
}


