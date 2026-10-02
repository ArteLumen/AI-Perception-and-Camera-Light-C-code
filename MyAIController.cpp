#include "MyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/SpotLightComponent.h"

AMyAIController::AMyAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    CameraSpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("CameraSpotLight"));
    CameraSpotLight->SetupAttachment(RootComponent);

    if (CameraSpotLight)
    {
       
        CameraSpotLight->SetLightColor(FLinearColor::Green);
        CameraSpotLight->Intensity = 5000.0f;
        CameraSpotLight->OuterConeAngle = 30.0f; 
    }

    if (SightConfig)
    {
        SightConfig->SightRadius = 1500.0f;
        SightConfig->LoseSightRadius = 1800.0f;
        SightConfig->PeripheralVisionAngleDegrees = 30.0f; 
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

        AIPerceptionComponent->ConfigureSense(*SightConfig);
        AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
    }
}

void AMyAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIPerceptionComponent)
    {
        AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnTargetPerceived);
    }

    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
    }
}

void AMyAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    UBlackboardComponent* BB = GetBlackboardComponent();
    if (!BB) return;

    if (Stimulus.WasSuccessfullySensed())
    {
        BB->SetValueAsObject(FName("TargetActor"), Actor);
        BB->SetValueAsBool(FName("HasLineOfSight"), true);

     
        if (CameraSpotLight)
        {
            CameraSpotLight->SetLightColor(FLinearColor::Red);
        }
    }
    else
    {
        BB->SetValueAsBool(FName("HasLineOfSight"), false);
        BB->ClearValue(FName("TargetActor"));

       
        if (CameraSpotLight)
        {
            CameraSpotLight->SetLightColor(FLinearColor::Green);
        }
    }
}
