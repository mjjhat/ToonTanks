// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/PawnBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


/***********Below will allow these components to show up in a BP file****************/


/* QUICKLY COMPILE: The CreateDefaultSubobject<> is a Function will be create and
add the component (whatever component we want to set) to the inside of our 
existing class.

CLASSTYPE EXPECTED: <> are added because the function is expecting a class type, which we declared
in the .h file, <UCapsuleComponents>

HIERARCHY: This is at top because it is the root component, the parent on top from which
the rest of the components will stem out from. So stick it at top*/

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
// CLARITY: Below is added to clarify what we just did and remove any ambiguity
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
// We want BaseMesh to inherit  movement and capsule properly, so:
	BaseMesh->SetupAttachment(RootComponent);
/* INHEREIT so we setup the attachment, Root Component
which is the CaspuleComp, so the BaseMesh can inherit from it.*/

/*NO ROOT: RootComponent is removed because we want it to follow the basemesh of the Tank*/
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
 	TurretMesh->SetupAttachment(BaseMesh);//follows base mesh, not capsule

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
 	ProjectileSpawnPoint->SetupAttachment(TurretMesh);// follows turret mesh
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

