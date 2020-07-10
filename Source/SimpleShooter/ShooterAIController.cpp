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
		//GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr) return;
	if (LineOfSightTo(PlayerPawn))
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
}
