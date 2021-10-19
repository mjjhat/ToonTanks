// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnabledState(bool SetPlayerEnabled)
{
    if(SetPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
/*          Allow Pawn to process input responses and is taking in a reference to the Owning 
            Player controll

            Nice to place things in Controllers, can add "this" without having to use 
            pointer and such*/
    }
    else
    {
        GetPawn()->DisableInput(this);
    }

    //Mouse visible?, make mouse not visible until after countdown- will help aim in game
    bShowMouseCursor = SetPlayerEnabled;

}
