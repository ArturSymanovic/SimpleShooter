// Copyright Artur Symanovic 2020.


#include "BTTask_Shoot.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto AIContr = OwnerComp.GetAIOwner();
	if (AIContr == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	auto AIChar = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (AIChar == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	AIChar->Fire();
	return EBTNodeResult::Succeeded;
}
