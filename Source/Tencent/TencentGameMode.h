// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TencentGameMode.generated.h"

UCLASS(minimalapi)
class ATencentGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATencentGameMode();

	virtual void Tick(float DeltaSeconds) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Score, meta = (AllowPrivateAccess = "true"))
	double ImportantChance = 0.2;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Score, meta = (AllowPrivateAccess = "true"))
	int NormalScore = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Score, meta = (AllowPrivateAccess = "true"))
	int ImportantScore = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Score, meta = (AllowPrivateAccess = "true"))
	double HitScale = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Score, meta = (AllowPrivateAccess = "true"))
	double GameTime = 10;

	bool bGameOver = false;
};



