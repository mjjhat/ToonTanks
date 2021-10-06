// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	private:

		APawnTank* PlayerTank;
		int32 TargetTurrets = 0;
			// these will be for destructable tanks
			//	the second will keep track how many turrets need to be destroyed.

		int32 GetTargetTurretCount();//To shorten some code
		void HandleGameStart();
		void HandleGameOver(bool PlayerWon);
	/*	The logic will be in C++, including tracking turrets
		- actual gamestart and over will be handled by BPs*/

		

	public:

		void ActorDied(AActor* DeadActor);
			//Will discern between player or AI death


	protected:

		virtual void BeginPlay() override;
		// will track more complicated functions here, such as how many tank targets begin
		// can also include round timer, lives for each player. 
	
		UFUNCTION(BlueprintImplementableEvent)
		void GameStart();
		UFUNCTION(BlueprintImplementableEvent)	
		void GameOver(bool PlayerWon);
		/* UFUNCTION(BPImpl...)Allow us to handle function implementation in the derived blueprintclass as setting
			timers and widgets, making the process more time efficient
			- Not to be inlcuded as a C++ when a BP implementable Event*/
	
};
