// Copyright Epic Games, Inc. All Rights Reserved.

#include "TencentGameMode.h"
#include "TencentCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"

ATencentGameMode::ATencentGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PrimaryActorTick.bCanEverTick = true;

}

void ATencentGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!bGameOver)
	{
		GameTime-=DeltaSeconds;
		if(GameTime <= 0)
		{
			GameTime = 0;
			bGameOver = true;
		}
	}
}
