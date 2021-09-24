// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"// To make FTimerHandle work

// BeginPlay and Tick functions are pasted in from PawnTank.

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(
        FireRateTimerHandle, 
        this,//This this object 
        &APawnTurret::CheckFireCondition,//points to functions that make it work.
        FireRate,//InRate- how long before fires, points to our function that controls this
        true//bool InLoop- do we want it to loop this process over and over again?
        );/*
        GetTimerManager: We are getting from the world. It is a global manager that 
        allows for multiple timers to run at once in the background. 
            -Can also use GetWorldTimerManager(), this is a shorthand of the above 
            
        .SetTimer(): setting the timer we are using. It has different overlays to fill in. */
	
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//FireFunction: Not here because both player and turret will need it, thus can go in base class
//Below: This is here because only the AI needs to check if the Fire Conditions are met. 
void APawnTurret::CheckFireCondition()
{/*
We are going to make sure that the AI does not fire until the player is in range rather than
constantly firing every X amount of seconds. Looks more reactive and lifelike. 

If Player ==Null || is Dead Then Bail!!

If Player IS in range Then FIRE!!!
*/

UE_LOG(LogTemp, Warning, TEXT("Fire Condition Checked"));
}