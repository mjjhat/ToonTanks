// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;// because no tick function

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	 	//Everytime the projectile mesh hits something
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
		//Don't need to attach to any component
		// Prepares variable for speed

	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
		// Sets the starting and max speed
	InitialLifeSpan = 3.0f;
		// How long the Projectile will last after deployed, then make it disappear
		// Destroys self (disappears) so to not have projectile clutter
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();	

	/*DYNAMIC DELEGATES:
		An event that can be called and responded to; anything listening for it can recieve
		it and take an action and call their own function based on the event*/

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
		//Placed here because did not work in the AProjectileBase::AProjectileBase() section
		// When the projectile mesh hits something
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
// What happens when the projectile hits something?
{
	AActor* MyOwner = GetOwner();
	if(!MyOwner){return;}// making sure it doesn't point to nothing
	
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	// We have those names because of our declariationin the .h
	//This will make sure that the projectile does not overlap with these in any way
	{
		UGameplayStatics::ApplyDamage(
			OtherActor, // Actor that will be damaged
			Damage,// Base Damage to apply
			MyOwner->GetInstigatorController(),// Controller that is responsible for the damge (player)
			this,// ACtor that actually caused the damage (gun)
			DamageType// Clas that describes the damage that was done
		);
		// Code for applying and recieving Damage

		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		// If hit, make "boom"
		Destroy();
	}
	
	
}


