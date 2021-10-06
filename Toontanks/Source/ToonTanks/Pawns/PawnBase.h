// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
	/* includes look for a specific class and all its details, including any
	includes that might be included. This can increase compile times since it
	must search through all information from that called class. It also reads the class each time a child
	class might call something that has it attached*/

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"
/*Below is a Forward Declaration. It points directly to the information
	you want called up and use for the specific header or .cpp file. When 
	this happens, it does not have to call up all the includes that might be
	included in the class being called up- it only wants what is in that file
	and no other. Thus greatly speeds up compiling time. 

	It also specifies what class or variable you are looking to use, and the
	right one if it happens to be used in multiple points

	It is like any class declaration, and is called "forward" since it is declared
	before it is used, like any other class. */
class UCapsuleComponent; //frwrd declare
class AProjectileBase;


UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
/* It is good to put most of our properites in the private section so that they do not 
	cross over into other classes. However, we may have reason to access them in the 
	editor. We can do this by adding the "meta..." code as seen below.*/

/*  BELOW:  We are planning on having a few components appear in our Bluepring Class of the Paw Base
			So the classes below are a means to do this: */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp;//Top- pointer
/*  	CAPSULE: this is the top component in this base pawn's hierarchy (and BP), from which the other
		parts will flow out from, nestled underneath

		It will also act as a general collider for the Pawns that use this class*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
		/* Don't need to forward declare these, unlike the Capsule Component, since the class
		already has a programmed "understaninding" what a "Base" and "Turret" Mesh are.

WHY IN PAWNBASE?
		The Capsule, base, turret, and projectile spawn point are generic components that both 
		player and AI will utilize. This is why we are placing it in the PawnBase class. 

		The difference will be whether the base will be mobile (Player) or static (AI)*/
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
	/* PROJECTILE SPAWN POINT: tells where the "projectile" spawns (missile and smoke), so 
		that it can be seen in the viewport and act accordingly. 

		USceneComponent is a collection of data that also includes a transform
		so can have a visual representation of what is spawning in the World. */

		/*COMPONENTS: Standard visible classes = VisibleAnywhere
			* since going to be a visual component, we do not need to have any reference of it in 
				the editor. 
			* meta =... etc. is added because this component is in the private section. Thus it needs
				code to access it, otherwise the compiler will say that it cannot compile it due to
				it being in the private properites section.*/


//VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;
	//Making options available

public:
		// Sets default values for this pawn's properties
	APawnBase();
	virtual void HandleDestruction();// How pawn reacts when destroyed

protected: 

	void RotateTurret(FVector LookAtTarget);// Turret rotation for player and AI

	void Fire();// Will create projectile when we have a projectile class implemented

	




//	virtual void TEST();/* TEST CODE
//		"viritual" allows us to use "override" in a child class, and tells us that this is 
//		an intended effect.


//************* Below are examples of BP editing code******//


/*/VISIBLE: greyed out so that others cannot accidently edit them in the editor- good for debugging
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Demo")
	int VisibleAnywhere;
	UPROPERTY(VisibleDefaultsOnly, Category = "Demo")
	int VisibleDefaultsOnly;
	UPROPERTY(VisibleInstanceOnly, Category = "Demo")
	int VisibleInstanceOnly;

//EDIT: All can be edited in the editor. Good for debugging as well. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
	int EditAnywhere;
	UPROPERTY(EditDefaultsOnly, Category = "Demo")
	int EditDefaultsOnly;
	UPROPERTY(EditInstanceOnly, Category = "Demo")
	int EditInstanceOnly;

		DEFAULTS ONLY: will only show up in Parent or Child of class, not in editor. 
						Only regards the class itself
		INSTANCE ONLY: will replace the Defaults only when an instance of the class 		
						or parent is created, that is, anything placed in the actual map/level.
		BLUEPRINT READWRITE/READONLY: These will edit the BP functionality, without which 
						is mainly editor functionality. */
};

// Removed Setup, BeginPlay, Tick and moved into PawnTank (child class)
