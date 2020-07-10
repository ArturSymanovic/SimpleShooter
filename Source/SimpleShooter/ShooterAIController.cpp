// Copyright Artur Symanovic 2020.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr) return;
	
	
	SetFocus(PlayerPawn);
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr) return;

	if (Cast<AShooterCharacter>(GetPawn())->GetHealth() > 0.0f)
	{
		MoveToActor(PlayerPawn, 100);
	}
	
}
