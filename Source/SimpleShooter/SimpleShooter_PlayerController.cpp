// Copyright Artur Symanovic 2020.


#include "SimpleShooter_PlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void ASimpleShooter_PlayerController::GameHasEnded(class AActor* EndGameFocus /*= nullptr*/, bool bIsWinner /*= false*/)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	
	if (bIsWinner)
	{
		UUserWidget* UserWidget = CreateWidget(this, WinScreenClass);
		if (UserWidget != nullptr)
		{
			UserWidget->AddToViewport();
		}
	}
	else
	{
		UUserWidget* UserWidget = CreateWidget(this, LoseScreenClass);
		if (UserWidget != nullptr)
		{
			UserWidget->AddToViewport();
		}
	}
	HudWidget->RemoveFromViewport();
	GetWorldTimerManager().SetTimer(RestartTimer, this, &ASimpleShooter_PlayerController::RestartLevel, RestartDelay);

}

void ASimpleShooter_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	HudWidget = CreateWidget(this, HudClass);
	if (HudWidget != nullptr)
	{
		HudWidget->AddToViewport();
	}
}
