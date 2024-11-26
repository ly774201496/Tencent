// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitBlock.generated.h"

UCLASS()
class TENCENT_API AHitBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

public:
	bool bIsImportance = false;
	bool bIsScale = false;
};
