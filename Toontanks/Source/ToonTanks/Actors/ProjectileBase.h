// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
// used below and given names

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
private: 
//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))	
	UProjectileMovementComponent* ProjectileMovement;
		//Points to our forwarded class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))	
	UStaticMeshComponent* ProjectileMesh;
		//Will call up visual representation of Projectile Component	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))	
	UParticleSystemComponent* ParticleTrail;/*
 		This will set a scenecomponent, similar tot he explosion in the HitParticle effect
		 except that it will trial behind the projectile until the projectile is destroyed
		Because a component, will be attachable to Projectile, or any other class*/

//VARIABLES
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;/*
		A Class template that UE has built in that calculates damage for us
		so we call up the SubclassOf, the DamageType Class, and then name it.
		   -This will provide us access in UE to anything that is a subclass of
			UDamageType.
		   -This limits the options we will see, which will make it easier to find
		   	what types of damage we want.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 1300;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage = 50;
		//These will set our projectile speed and damage
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitParticle;
		//Provide projectile effects when hit something. 
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* LaunchSound;
		/*Sound is very important, but often saved until last once logic is working and "feel"
			of the game is now being developed. If it does not"feel" right at the start it is 
			likely because there is no sound, or minimal sound. */

//FUNCTION
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//Deleted Tick function, won't be using.
};
