// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/Pawns/PawnBase.h"/*
	If you cannot create a C++ class properly(child or parent), and you get errors:

		1. 	Don't press "yes" but no on the error log. This message may come up if you have 
			created a custom folder (like if you start your Project in BP but then add a C++ 
			folder later, or some other folder)
		
		2.	Navigate to the VS code and the new class's .h file.

		3. 	Once there, go to the inlcudes and (if child) change the include to only
		include the parent - 
							*****NOT WORK*****
		PawnBase.h rather then Pawns/Pawnbase.h 
		
		4. If (3) does not work you can change the include to include the entire path instead:
							*****WORKED******
			ToonkTanks/Pawns/PawnBase.h
		
		*/
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	FVector MoveDirection;// deltalocation for actor local rotation Offset
    FQuat RotationDirection;// delalocation for actor local rotation

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))	
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.0f;/*
		These will control the speed values of Rotation and movement
		 	EditAnywhere:
				PRO:in the middle of testing can jump out and make adjustments
				CON: If in a team it may be too available for everyone to play with, so if 
					they are not aware of what you trying to accomplish, they may end up 
					messing up your settings and balance. 

			BlueprintReadWrite: 
				The instructor chose to use that so that he would be able to implement
				code or changes to the code later on if he wanted to add more features. It is
				Better to do some of this at the start when you might not need it, than later on
				when you realize that you do need it. 
				Example: if the prgrammer wants to implement speed boosts to the tank. */
		
    void CalculateMoveInput(float Value); /*
      	MOVEMENT: Will be bound to a movement input funtion, so that when we press a button 
		  			to move the tank,a value (axis value) will be returned to the game so 
					that the game may be able to calculate the location of the tank, such as 
					moveing forward or back*/

    void CalculateRotateInput(float Value);// Like above, but for rotation.

    void Move();
    void Rotate();

public:

	APawnTank();//Our Constructor
	

/* We had cut out Tick, Setup, BeginPlay from PawnBase (Parent Class)and placed it here:
		It is better if our constant checks and play functions happen in their respective
		class, only calling up whatever other functions they need from the parent class*/

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
	
};

