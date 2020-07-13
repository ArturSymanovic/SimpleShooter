// Copyright Artur Symanovic 2020.


#include "KillEmAllGameMode.h"
#include "SimpleShooter_PlayerController.h"
#include "EngineUtils.h"
#include "ShooterCharacter.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	ASimpleShooter_PlayerController* PlayerController = Cast<ASimpleShooter_PlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		Controller->GameHasEnded(Controller->GetPawn(), Controller->IsPlayerController() == bIsPlayerWinner);
	}
}
