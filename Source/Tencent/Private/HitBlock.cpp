// Fill out your copyright notice in the Description page of Project Settings.


#include "Tencent/Public/HitBlock.h"

#include "Kismet/GameplayStatics.h"
#include "Tencent/TencentGameMode.h"

// Sets default values
AHitBlock::AHitBlock()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    RootComponent = StaticMesh;
}


// Called when the game starts or when spawned
void AHitBlock::BeginPlay()
{
	Super::BeginPlay();

	ATencentGameMode* GameMode = Cast<ATencentGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		float temp = FMath::FRand();
		if (temp < GameMode->ImportantChance)
		{
			bIsImportance = true;
		}
	}

	FLinearColor InitialColor = bIsImportance ? FLinearColor::Red : FLinearColor::White;
	UMaterialInstanceDynamic* DynamicMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynamicMaterial)
		DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), InitialColor);
	
}

// Called every frame
void AHitBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATencentGameMode* GameMode = Cast<ATencentGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(GameMode->bGameOver)
		Destroy();
}

