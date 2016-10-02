#include "TrackingAction.hh"
#include "G4Track.hh"
#include "G4VSolid.hh"
#include "G4Region.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "DetectorConstruction.hh"

using namespace std;

TrackingAction::TrackingAction(DetectorConstruction* detector)
{
    fDetector = detector;
    fTarget1Region = 0;
    fTarget2Region = 0;
    fTarget3Region = 0;
}

TrackingAction::~TrackingAction()
{
    fDetector = 0;
    fTarget1Region = 0;
    fTarget2Region = 0;
    fTarget3Region = 0;
}

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    const G4ParticleDefinition* particleDefinition = track->GetParticleDefinition();

    if(particleDefinition == G4Electron::Definition() || particleDefinition == G4Gamma::Definition())
    {
        if(fTarget1Region == 0) // target 1 region is initialized after detector construction instantiation
        {
            fTarget1Region = fDetector->GetTarget1Region();
        }

        if(fTarget2Region == 0) // target 2 region is initialized after detector construction instantiation
        {
            fTarget2Region = fDetector->GetTarget2Region();
        }

        if(fTarget3Region == 0) // target 3 region is initialized after detector construction instantiation
        {
            fTarget3Region = fDetector->GetTarget3Region();
        }

        const G4ThreeVector& position = track->GetPosition();

        int N1 =  fTarget1Region->GetNumberOfRootVolumes();
        std::vector<G4LogicalVolume*>::iterator it_logicalVolumeInRegion1 =
                fTarget1Region->GetRootLogicalVolumeIterator();

        bool inside_target1 = false;

        for(int i = 0; i < N1 ; i++, it_logicalVolumeInRegion1++)
        {
            EInside test_status = (*it_logicalVolumeInRegion1)->GetSolid()->Inside(position) ;
            if(test_status == kInside)
            {
                inside_target1 = true;
                break;
            }
            /*
            else if (test_status == kSurface)
            {
            }
            */
        }

        int N2 =  fTarget2Region->GetNumberOfRootVolumes();
        std::vector<G4LogicalVolume*>::iterator it_logicalVolumeInRegion2 =
                fTarget2Region->GetRootLogicalVolumeIterator();

        bool inside_target2 = false;

        for(int i = 0; i < N2 ; i++, it_logicalVolumeInRegion2++)
        {
            EInside test_status = (*it_logicalVolumeInRegion2)->GetSolid()->Inside(position) ;
            if(test_status == kInside)
            {
                inside_target2 = true;
                break;
            }
            /*
            else if (test_status == kSurface)
            {
            }
            */
        }

        int N3 =  fTarget3Region->GetNumberOfRootVolumes();
        std::vector<G4LogicalVolume*>::iterator it_logicalVolumeInRegion3 =
                fTarget3Region->GetRootLogicalVolumeIterator();

        bool inside_target3 = false;

        for(int i = 0; i < N3 ; i++, it_logicalVolumeInRegion3++)
        {
            EInside test_status = (*it_logicalVolumeInRegion3)->GetSolid()->Inside(position) ;
            if(test_status == kInside)
            {
                inside_target3 = true;
                break;
            }
            /*
            else if (test_status == kSurface)
            {
            }
            */
        }

        if(inside_target1 == true)
        {
            fNParticleInTarget1[particleDefinition]++;
        }
        else if (inside_target2 == true)
        {
            fNParticleInTarget2[particleDefinition]++;
        }
        else if (inside_target3 == true)
        {
            fNParticleInTarget3[particleDefinition]++;
        }
        else
        {
            fNParticleInWorld[particleDefinition]++;
        }
    }
}

