// Copyright Artur Symanovic 2020.


#include "SimpleShooter_PlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void ASimpleShooter_PlayerController::GameHasEnded(class AActor* EndGameFocus /*= nullptr*/, bool bIsWinner /*= false*/)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	
	UUserWidget* UserWidget = CreateWidget(this, LoseScreenClass);
	if (UserWidget != nullptr)
	{
		UserWidget->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &ASimpleShooter_PlayerController::RestartLevel, RestartDelay);

}
