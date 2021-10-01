// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

/* HealthComponent as a base class can be used to apply damage in ALL things in our world before it
	reacts to complete damage loss.

We are using an Actor Component rather than a scene component
	Similarities: 
		1. Both can be placed on Actors
		2. Scene component inherits from Actor Component
	Difference between components?
	1. ACTOR: Cannot be moved about and attached to other components
		-No Transform or representation in the world.
		-
	2. SCENE: Can be moved about in the world and attached to other scene components
		-It also has a transform or representation in the world, and can be moved about in BP
	
Why use Actor Component?
In our case, we only need an actor to loose health, not a specific player in the world,
like the tanks wheels, turret, gun, etc. If this were the case we would want to use a
Scene Component*/

class ATankGameModeBase;
/*Forward declaring, or directly pulling into this class, the TankGameModeBase class, so we
don't have to go mucking about other classes and their code to get to it*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)// only in C++ can be updated, not BP because not specified as such
	float DefaultHealth = 100.0f;// start health
	float Health = 0.0f;// default is zero (for end game?)

	ATankGameModeBase* GameModeRef;
/*	we are pointing back to the ATankGameModeBase so we can call it up here for use and reference
	for our code*/

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(
		AActor* DamagedActor, // who is being hurt
		float Damage, //how much it hurts
		const UDamageType* DamageType, //bullet-piercing
		AController* InstigateBy, //Pulled the trigger
		AActor* DamageCauser// The gun whose trigger was pulled
		);
	// Will be binding to an existing function: Any damage event on the owning pawn.
	// will need overrides like in the OnHits Function(the one with the long list of arugument/overlays?)
	
	//*******NOTE: Keep in mind OnHit and TakeDamage functions for future considerations*********


		
};
// IDEA: Can have the UGrab function with the tank (technology of some sort as the excuse)