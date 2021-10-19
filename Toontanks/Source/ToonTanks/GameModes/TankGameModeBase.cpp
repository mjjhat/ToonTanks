// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
    // need to forward these if calling up their functions
#include "Kismet/GameplayStatics.h"
    // need gameplaye statics
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
// Added this otherwise UE may not compile.


void ATankGameModeBase::BeginPlay()
    // Get references and game win/lose conditions.
    // Call HandleGameStart() to initialise the start countdown, turret activation, pawn check etc.
{
    Super::BeginPlay();
    //Static Class: not requiring an object instance, and will return the UClass of actor type.
 
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
    // Check what type of Actor died. If Turret, tally. If Player -> go to lose condition.
{
    if(DeadActor == PlayerTank)
        //If the Player is the dead actor, point PlayerTank to Handle Destruction
    {
        PlayerTank->HandleDestruction();
            //Was in "protected" in .h, but moved to public so we can have access to it
        HandleGameOver(false);
            //False: means player did not win the game!

        if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
            //Why? To stop tank from moving around even though "destroyed" and now invisible
        }
    }
    else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))//Casts to turret, referencing dead actor
        //If destoyed actor is not Player, check and store temporary pointer to APawnTurret instead
    {
        DestroyedTurret->HandleDestruction();

        if(--TargetTurrets == 0)
/*          Tells us to decrease the TargetTurret "--" until (==) 0 */
        {
            HandleGameOver(true);
        }
    }
  
  
  ///////////////Old Debug Code/////////////////////
  
  
    // if (!DeadActor) {return;}

    // UE_LOG(LogTemp, Warning, TEXT("%s Died!"), *DeadActor->GetName());
        // Call in the AActor that is being passed into this function silly!

    //UE_LOG(LogTemp, Warning, TEXT("%s Died!"), *AActor::GetDebugName(DeadActor))
        //Can use AActor::GetDebugName(DeadActor)- it is a static member function

    // UE_LOG(LogTemp, Warning, TEXT("Pawn Died!"));
}

void ATankGameModeBase::HandleGameStart()
    // Initialise the start countdown, turret activation, pawn check etc.
    // Call Blueprint version GameStart();
{
    TargetTurrets = GetTargetTurretCount();

    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
/*          Will cast out to find the player (APawnTank) using "UGameplayStatics)", to cast
            to "this" Player, set to 0 since it this is not a multiplayer game. */    
    
    // Called up in beginplay, so we can move the above variables in here. 

    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this,0));
    //Similar to Player Tank Above- casting out to get the player controller, pointing to this
    /*  This will allow us to control when player input is received or not at certain points 
        in the game*/

    GameStart();//BP implemented function in .h

      if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
            //Why here? As soon as Game starts, movement is disabled until end of countdown

            FTimerHandle PlayerEnableHandle;// sets temporary TimerHandle for TimerManager below
            FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
                PlayerControllerRef, 
                &APlayerControllerBase::SetPlayerEnabledState, true);
            /*Similar to what we did in the PawnTurret class where we confirmed that a 
                function was being called in it- pointing to the class and the function we
                wanted to called (CheckFireCondition)
                
                We set the Enabled back to true*/

            GetWorld()->GetTimerManager().SetTimer(
                PlayerEnableHandle,
                PlayerEnableDelegate,
                StartDelay,// float delay, delay player input for same amount as start widget countdown to show
                false //Don't need to keep reenabling player input after countdown
            );/* 
                Possible issue? Because we have a call to destroy the Pawn, this will set the owning 
                player controller to NULL reference- Thus we destroy a pawn and then try to call 
                a function that we cannot get to.*/

        }
}


void ATankGameModeBase::HandleGameOver(bool PlayerWon)
    // See if player has destroyed all the turrets, show win result.
    // else if turet destoyred player, show lose result.
    // Call blueprint version of GameOver(bool). 

{
    GameOver(PlayerWon);

}

int32 ATankGameModeBase::GetTargetTurretCount()
// This function was made so to move the variable below out of Beginplay, making it shorter
{
    TArray<AActor *> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(), // Will get world context object: a const UObject* [Name]-> GetWorld()
        APawnTurret::StaticClass(),//TSubclassOf<AActor> [Name]->APawnTurret::StaticClass()
        TurretActors
        );
    return TurretActors.Num();
        // # of elements in the array.
        // Because uses a int32, it must return some sort of number.
    //The above code casts out to see how many turrets there are, and then returns a #
}


