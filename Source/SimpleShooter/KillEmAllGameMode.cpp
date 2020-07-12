// Copyright Artur Symanovic 2020.


#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	UE_LOG(LogTemp, Warning, TEXT("%s killed"), *PawnKilled->GetName());
}
