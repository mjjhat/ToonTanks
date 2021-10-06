// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
	//Refers to the GameMode we created
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;// not using tick

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	/*	Health is equal to what we had declared and exposed (DefaultHealth) value in the .h
		-	Every time we start the game, the health will be updated to set default health.*/	

	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	/* Gets context of the current world and finding current active GameMode in that world,
		then casting it back to our ATankGameModeBase.*/

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	/* Will return reference to the owning actor, and will bind the TakeDamage function to 
		the OnTakeAnyDamage Function in the same we we did for the OnHit fucntion in the 
		Projectile Class. 
		
		Another Dynamic class, as is used in the ProjectileBase.cpp, binding it to our 
		UHealthComponent, and the TakeDamage (as is found in the .h)
		
		When OnTakeAnyDamag is called on owning actor, the function in our health compoment
		will also be called, which will be the take damage (found below). */
}

void UHealthComponent::TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

	if (Damage == 0 || Health <= 0) // To insure death sequence if below 0 or equal to it
	{return;}
	// if(Damage == 0 ) {return;}// old code- change above for instruction sake
/*		Making it not do anything if 0, because if returns 0, something is probably wrong 
		-	Only 0, because we can extend the function to do other things, like add health!
		-	Can heal and do damage.*/
	
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
	/*	If a none-0 health value is not pass through, we will clamp the health to a specific
		value
		-	Insures that health cannot drop below 0, or above max health cap. 
		-	0.0f tells us that this is a float number that the Fmath requires- otherwise
			we would get an error-- we need an integer type.*/

	if (Health <= 0)
		// health lower or equal to zereo? If so- ActorDied function
		/*Although we define our health in the FMath, this code separates the 0 scenario
			and makes sure that it causes death no matter what
			-	useful if we end up changing some of our code above!
			- 	accounts for other devlopers joining the team and needing to make changes*/
	{
		if(GameModeRef)
			//Make sure it is a valid reference to the GameMode
		{
			GameModeRef->ActorDied(GetOwner());
				//If valid reference, proceed to the ActorDied function, refering to the Owner
			/*	We hav not passed anything in the GetOwner because our game's simplicity:
				We only have 2 pawn classis at this time
				-	Rather than passing in multiple things, one to the GameMode and another to
					the classes, let GameMode know something has happened to one of the classes
					and let the GameMode process the results accordingly
				-	If want to have damage to other props, can use similar implementation to 
					some sort of destroy function on the PropToPlayAt- effects relating to 
					the destruction.*/

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health Component does not have a reference to the GameMode"));
				//If no valid GameModeRef, notify us!
		}
	}
}