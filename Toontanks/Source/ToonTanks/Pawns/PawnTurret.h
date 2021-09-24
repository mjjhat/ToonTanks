// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/Pawns/PawnBase.h"
#include "PawnTurret.generated.h"

/*
AI CLASS: This will become a base AI class that only needs to react to 2 things:
1. Is player in range?
2. If in Firing range, fire every so many seconds.
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

/*
SECURITY: Private, Public, and Protected sections at as 3 different levels of security.
	1. Private- Most secure (Internal)
	2. Public- Least secure, all can access it (Internal, External, Derived)
	3. Protect- Own special security- (Internal, Derived)
		* thus only child classes of this class can access these variables. 
*/
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;/*
		FIRERATE: How often the turret will fire
			* Because exposed, we can edit the firerate of each instance of this class
			  allowing for different turrents to fire at different rates.*/ 

	void CheckFireCondition();
		/*Because not using anywhere else, can be placed here.
		 *Timers: To time our fire rate we will be looking at timers, based off of long the 
				  tank will wait before it fires.*/


	FTimerHandle FireRateTimerHandle;// We start and stop timer. 

public:
// Does not need PlayerInputComponent since the AI class will not be affected by the player.
 
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
	
};
