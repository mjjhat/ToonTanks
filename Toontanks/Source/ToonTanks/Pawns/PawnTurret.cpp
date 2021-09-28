// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
    // To make FTimerHandle work
#include "PawnTank.h"


// BeginPlay and Tick functions are copied and pasted in from PawnTank (another child class).

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(
        FireRateTimerHandle, 
        this,//This affects the current class using the function 
        &APawnTurret::CheckFireCondition,//points to the function that make it work.
        FireRate,//InRate- how long before fires, points to a function declared in our .h
        true//bool InLoop- do we want it to loop this process over and over again?
        );/*
        GetTimerManager: We are calling up a global manager from the world itself. It allows 
                            for multiple timers to run at once in the background. 
            -Can also use GetWorldTimerManager(), this is a shorthand of the above code
            
        .SetTimer(): setting the timer we are using. It has different overlays (the different
        parameters and such found between its "()") to fill in. */

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
        //Casts own to find the player Pawn from APawnTank using the WorldContext

/*      Returns reference to player pawn if valid result is found
            -two arguements: WorldContextUOBject, PlayerIndex

        Used "WorldObject"--> Why use? Top level object (Map, Sandbox) that actors exist in a game
            -Objects are highest level class, and World is the highest type of Object
            -Actors are the highest level of objects that reside in the world.
            -Actors need to have context to the world before they will manifest some sort of 
                presence in it

        WorldContextUObject (this): provides context to this class's object/actor so can be spawned and 
                        referred to. Then can call upond using "this". Which WorldContext? This one
        PlayerIndex (0): Tracks # of players, and then use functions to call up a specific pawn, such as
                    using "this". We only have 1 player, so argument "0" will be our # */
	
//    TEST();

}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//FireFunction: Not here because both player and turret will need it, thus can go in base class
void APawnTurret::CheckFireCondition()
    //AI checks if firing range conditions are met--- thus only belongs to the AI class
{/*
We are going to make sure that the AI does not fire until the player is in range rather than
constantly firing every X amount of seconds. Looks more reactive and lifelike. 

PSUEDO CODE:

If Player ==Null || is Dead ---> Then Bail!!

If Player IS in range Then FIRE!!!*/

    if(!PlayerPawn)/* if there is not a player Pawn, Do not use this function*/
        {
            return;// need to check if player is alive!
        }

    if(ReturnDistanceToPlayer() <= FireRange)
        // Checks FirRange (in .h) against ReturnDistanceTo Player function below
        {
            // Fire!
            UE_LOG(LogTemp, Warning, TEXT("%s: Fire Condition Success"), *GetOwner()->GetName());
        }
}

float APawnTurret::ReturnDistanceToPlayer()
{
    if(!PlayerPawn)/* if there is not a player Pawn, Do not use this function*/
        {
            return 0.0f;// need to return some float value, and will stop potential hard crashes
        }
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());/*
        DIST: a function that calculates the distance between two actors (1.Player, 2.AI)
        1. Calls up the PlayerPawn Code, which we set up for casting in BeginPlay.
        2. Calls up the location of the turret (AI) */        
}

// *****TEST CODE*****//Testing Code to be discarded (Parent)
// void APawnTurret::TEST()
// {
// 	Super::TEST();// Super is calling PawnBase::TEST()
//     UE_LOG(LogTemp, Warning, TEXT("%s: Turret Call"), *GetOwner()->GetName());
// }

