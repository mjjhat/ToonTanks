// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/Pawns/PawnBase.h"
	/*If you cannot create a C++ class properly(child or parent), and you get errors
		don't press "yes" on the error message,but no. This message may come up if
		you have created a custom folder (like if you start your Project in BP but 
		add a C++ folder later, or some other folder)
		
		*Then Navigate to the VS code and the new class's .h file.
		*Once there, go to the inlcudes and (if child) change the include to only
		include the parent - 
		*****NOT WORK*****PawnBase.h rather then Pawns/Pawnbase.h****NOT WORK***** 
		
		* likewise you can change the include to include the entire path instead:
		
		*****WORKD******ToonkTanks/Pawns/PawnBase.h******
		
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

	float MoveSpeed = 100.0f;
	float RotateSpeed = 100.0f;
		//These will control the speed values of Rotation and movement


    void CalculateMoveInput(float Value);
        /*will be bound to movement input funtion, so that when we press a button to move the tank,
            a value (axis value) will be returned to the game so can calculate the location
            of the tank--- move forward or back---*/
    void CalculateRotateInput(float Value);// Like above, but for rotation.

    void Move();
    void Rotate();

public:

	APawnTank();
		//Our Constructor

// We are cutting out Tick, Setup, BeginPlay from PawnBase and placing it here instead:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
	
};

