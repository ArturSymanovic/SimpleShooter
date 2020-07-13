// Copyright Artur Symanovic 2020.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	FHitResult HitResult;
	FVector ShotDirection;
	bool bIsHitFound = GunTrace(HitResult, ShotDirection);
	if (bIsHitFound)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, ShotDirection.Rotation());
		FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
		auto ReceivingActor = HitResult.GetActor();
		if (ReceivingActor == nullptr) { return; }
		ReceivingActor->TakeDamage(Damage, DamageEvent, GetOwningController(), this);
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (OwningPawn == nullptr) { return false; }
	AController* Controller = OwningPawn->GetController();
	if (Controller == nullptr) { return false; }

	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	auto End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwningPawn);
	Params.AddIgnoredActor(this);
	return GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwningController()
{
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (OwningPawn == nullptr) { return nullptr; }
	return OwningPawn->GetController();
}

