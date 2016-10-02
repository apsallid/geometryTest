#ifndef TrackingAction_h
#define TrackingAction_h

#include "G4UserTrackingAction.hh"
#include <map>

class G4Region;
class G4ParticleDefinition;
class DetectorConstruction;

class TrackingAction : public G4UserTrackingAction
{
public:
    TrackingAction(DetectorConstruction* detector = 0);
    ~TrackingAction();

    virtual void PreUserTrackingAction(const G4Track*);

    void SetDetector(DetectorConstruction* detector)
    {
        fDetector = detector;
    }

    std::map<const G4ParticleDefinition*, int>& GetNParticlesCreatedInTarget1()
    {
        return fNParticleInTarget1;
    }

    std::map<const G4ParticleDefinition*, int>& GetNParticlesCreatedInTarget2()
    {
        return fNParticleInTarget2;
    }

    std::map<const G4ParticleDefinition*, int>& GetNParticlesCreatedInTarget3()
    {
        return fNParticleInTarget3;
    }

    std::map<const G4ParticleDefinition*, int>& GetNParticlesCreatedInWorld()
    {
        return fNParticleInWorld;
    }

private:
    DetectorConstruction* fDetector;
    G4Region* fTarget1Region;
    G4Region* fTarget2Region;
    G4Region* fTarget3Region;
    std::map<const G4ParticleDefinition*, int> fNParticleInTarget1;
    std::map<const G4ParticleDefinition*, int> fNParticleInTarget2;
    std::map<const G4ParticleDefinition*, int> fNParticleInTarget3;
    std::map<const G4ParticleDefinition*, int> fNParticleInWorld;
};


#endif 
