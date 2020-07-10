// Copyright Artur Symanovic 2020.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (PlayerPawn == nullptr) return;
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
				
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//if (PlayerPawn == nullptr) return;
	//if (LineOfSightTo(PlayerPawn))
	//{
	//	if (Cast<AShooterCharacter>(GetPawn())->GetHealth() > 0.0f)
	//	{
	//		MoveToActor(PlayerPawn, AcceptanceRadius);
	//		SetFocus(PlayerPawn);
	//	}
	//	else 
	//	{
	//		ClearFocus(EAIFocusPriority::Gameplay);
	//		StopMovement();
	//	}
	//}
	//else
	//{
	//	ClearFocus(EAIFocusPriority::Gameplay);
	//	StopMovement();
	//}
}
