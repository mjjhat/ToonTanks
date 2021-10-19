// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/* 	Player Controller directly recieves input notifications when something is pressed
	and also what is used to enable and disable an input
	
	Such as enabling or disabling player control over a pawn during a cutscene*/
UCLASS()
class TOONTANKS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

	public: 
		
		void SetPlayerEnabledState(bool SetPlayerEnabled);	
};
