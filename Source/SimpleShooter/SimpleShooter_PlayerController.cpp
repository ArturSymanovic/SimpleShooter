// Copyright Artur Symanovic 2020.


#include "SimpleShooter_PlayerController.h"
#include "TimerManager.h"

void ASimpleShooter_PlayerController::GameHasEnded(class AActor* EndGameFocus /*= nullptr*/, bool bIsWinner /*= false*/)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	GetWorldTimerManager().SetTimer(RestartTimer, this, &ASimpleShooter_PlayerController::RestartLevel, RestartDelay);

}
