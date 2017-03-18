// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "Gun.h"
#include "Animation/AnimInstance.h"
#include "TestingGroundsProjectile.h"
#include "Engine/SkeletalMesh.h"

AGun::AGun()
{
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	PrimaryActorTick.bCanEverTick = true;
}

void AGun::BeginPlay()
{	
//	USceneComponent *RootComponent = GetOwner()->GetRootComponent();
//	if (ensure(RootComponent)) {
		FP_Gun->SetupAttachment(RootComponent);
//	}
}

void AGun::OnFire()
{
	class APawn* OwnerAsPawn = Cast<APawn>(GetAttachParentActor());
	if (!ensure(OwnerAsPawn)) {
		return;
	}

	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = OwnerAsPawn->GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : OwnerAsPawn->GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ATestingGroundsProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetRootComponent()->GetComponentLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		if (AnimInstance) {
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

