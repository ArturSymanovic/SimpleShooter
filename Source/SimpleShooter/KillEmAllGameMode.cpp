// Copyright Artur Symanovic 2020.


#include "KillEmAllGameMode.h"
#include "SimpleShooter_PlayerController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	ASimpleShooter_PlayerController* PlayerController = Cast<ASimpleShooter_PlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->GameHasEnded(nullptr, false);
	}
}
