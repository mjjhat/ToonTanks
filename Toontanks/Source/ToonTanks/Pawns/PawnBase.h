// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/* includes look for a specific class and all its details, including any
includes that might be included. This can increase compile times since it
must search through all that information. It also reads it each time a child
class might call something that has it attached*/

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

/*Below is a Forward Declaration. It points directly to the information
you want called up and used for the specific header or .cpp file. When 
this happens, it does not have to call up all the includes that might be
included in the class being called up- it only wants what is in that file
and no other. Thus greatly speeds up compiling time. 

It also specifies what class or variable you are looking to use, and the
right one if it happens to be used in multiple points

It is like any class declaration, and is called "forward" since it declared
before used, like any other class. */
class UCapsuleComponent; 


UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:

/* this is the top component in this base pawn's hierarchy, from which the other
parts will flow out from, nestled underneath

It will also act as a general collider for the Pawns that use this class*/
	UPROPERTY()
	UCapsuleComponent* CapsuleComp;

/* Don't need to forward declare these, unlike above, since the class
has a basic "understaninding" What a Base and Turret Mesh are.

These are generic since both player and AI will have a base and turret.
The different will be whether the base will be mobile (Player) or static
(AI)*/
	UPROPERTY()
	UStaticMeshComponent* BaseMesh;
	UPROPERTY()
	UStaticMeshComponent* TurretMesh;

/* tells where the "projectile" spawns, so can be seen in the viewport
and act accordingly. 

USceneComponent is a collection of data that also includes a transform
so can have a visual representation of what is spawning in the World. */
	UPROPERTY()
	USceneComponent* ProjectileSpawnPoint;

public:
	// Sets default values for this pawn's properties
	APawnBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
