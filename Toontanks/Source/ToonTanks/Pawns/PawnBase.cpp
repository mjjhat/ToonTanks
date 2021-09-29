// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/PawnBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


/***********Below will allow these components to show up in a BP file****************/

/* 
QUICKLY COMPILE: The CreateDefaultSubobject<> is a Function will be create and
 	add the component (whatever component we want to set) to the inside of our 
	existing class.

CLASSTYPE EXPECTED: <> are added because the function is expecting a class type, which we declared
 	in the .h file- <UCapsuleComponents>

HIERARCHY: This is at top because it is the root component, the parent on top from which
	the rest of the components will stem out from. So stick it at top*/

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;/*
		ROOTCOMPONENT: this clarifies that the CapsuleComp is the RootComponent in the BP*/

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);/*
		INHERIT: The above attaches the CapsuleComp to the BaseMesh, which allows the BaseMesh
		to inherit the properties of CapsuleCom (RootComponent). This will also inherit 
		the movement functionality that comes with the RootComponent.*/


	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
 	TurretMesh->SetupAttachment(BaseMesh);/*
	 	Follows BaseMesh
	 	NO ROOT: RootComponent is removed because we want it to follow the basemesh of the 
		 			tank rather than the Capsule.*/


	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
 	ProjectileSpawnPoint->SetupAttachment(TurretMesh);/*
		Follows TurretMesh*/
}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	FVector LookAtTargetCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();
		//The above code could be placed below, but it would be too long and cluttered
	FRotator TurretRotation = FVector(LookAtTargetCleaned - StartLocation).Rotation();
	/*	Will allow TurretMesh rotation and make sure rotation is not up or down
		We are minusing the Look at Target (X,Y, and TurretMesh Location) by the start 
		Location to clean up our rotation and make it precise, converting our equation into
		a rotation (.Rotation)*/
	TurretMesh->SetWorldRotation(TurretRotation);// pass in above
	
	
	//Update TurretMesh rotation to face towards the LookAtTarget passed in from the Child Classes.
	//TurretMesh->SetWorldRotation()...	
}

void APawnBase::Fire()
{
	// Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile Class at Location firing towards Rotation. 
	UE_LOG(LogTemp, Warning, TEXT("%s: Fire Condition Success"), *GetOwner()->GetName());
}

void APawnBase::HandleDestruction()
{
	//--- Universal Functionality --
	// Play death effects particle, sound and camera shake.

	// --- Then do Child overrides ---
	//--- PawnTurret- Inform GameMode Turret Died -> Then Destroy() self.

	// -- PawnTank- Inform GameMode Player died -> Then Hide() all component && stop movement input
}


// *****TEST CODE***** //Testing Code to be discarded (Parent)
// void APawnBase::TEST()
// {
// 	UE_LOG(LogTemp, Warning, TEXT("%s: Base Call"), *GetOwner()->GetName());
// }
//Removed Setup, BeginPlay, Tick and placed in PawnTank.cpp. (child class)

