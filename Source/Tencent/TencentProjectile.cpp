// Copyright Epic Games, Inc. All Rights Reserved.

#include "TencentProjectile.h"

#include "TencentCharacter.h"
#include "TencentGameMode.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Public/HitBlock.h"

ATencentProjectile::ATencentProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ATencentProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ATencentProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if(OtherComp->IsSimulatingPhysics())
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		if(AHitBlock* HitBlock = Cast<AHitBlock>(OtherActor))
		{
			ATencentGameMode* GameMode = Cast<ATencentGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			if(!HitBlock->bIsScale)
			{
				HitBlock->SetActorScale3D(HitBlock->GetActorScale3D()*GameMode->HitScale);
				HitBlock->bIsScale = true;
			}
			else
			{
				ATencentCharacter* Character = Cast<ATencentCharacter>(Shooter);
				if(HitBlock->bIsImportance)
					Character->Score += GameMode->ImportantScore;
				else
					Character->Score += GameMode->NormalScore;

				HitBlock->Destroy();
			}
			
				
		}
		
		Destroy();
	}
}