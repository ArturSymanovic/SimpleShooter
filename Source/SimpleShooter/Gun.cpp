// Copyright Artur Symanovic 2020.

#include "Components/SkeletalMeshComponent.h"
#include "Gun.h"
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

	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (OwningPawn == nullptr) { return; }
	AController* Controller = OwningPawn->GetController();
	if (Controller == nullptr) { return; }
	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint(Location, Rotation);
	//DrawDebugCamera(GetWorld(), Location, Rotation, 90.0f, 1.0f, FColor::Blue, true);

	auto End = Location + Rotation.Vector() * MaxRange;
	FHitResult HitResult;
	bool bIsHitFound = GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECC_GameTraceChannel1);
	if (bIsHitFound)
	{
		//DrawDebugPoint(GetWorld(), HitResult.Location, 5.f, FColor::Red, true);

		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, ShotDirection.Rotation());
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

