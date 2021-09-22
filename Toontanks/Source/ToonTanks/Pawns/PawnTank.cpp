// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/PawnTank.h"

// Below allows us to callup the camera and springarm
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"



APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
        //The above is set up according to how the PawnBase compoments were set up- go there for more detail 
}


//Cut and place in Baseclass implementation of BeginPlay, Tick, Setup:

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Rotate();
    Move();
        /*These will constantly call up our movement and rotate functions to see if being used.
            -It is good to have these called up before the movement even takes place
            
            *While we could move the AddActors to their respective Calculate Functions above them
                (see below) to reduce the number of functions, having them separate allows more 
                control in the order they are being processed or updated
                    -If reduced, it would constantly look up the 0's, which is not a bad thing, but the 
                        order is less controllable 
                        
            *Instructor prefers to have the rotation value called up first rather than the movement
                -He suggests swapping the Rotate and Move around a few times later on to see how
                    the order can change the feel of thing and see what you like best. At this point
                    it is more about personal taste. */
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward",this, &APawnTank::CalculateMoveInput);
        /* Binding keys, make sure that the name is the same as appears in the Engine Input section
            *Will constantly look up "this" function to see if pressed, and when pressed, how long it 
            is pressed. 
            * "this" is the world context of the function-- what in the world is being
            effected by the function.
            *The function will point to APawnTank using CalculateMoveInput function to move the tank
            when pressed*/
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);//see above

}

void APawnTank::CalculateMoveInput(float Value)
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
        /*We are only wanting movement on the x axis. This is being checked out by looking up the value
            times the MoveSpeed (100.0f) times Getting the DeltaSpeed from the World.
            
            *Note that FVectors require X, Y, Z values, but since we are not strafing we will set the
                Y and Z to 0*/
}

void APawnTank::CalculateRotateInput(float Value)
{
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
        /*Value is the location or rotation key the player is pressing, and this will be TIMES RotateSpeed 
        (100.0f) TIMES getting the DeltaTimeSeconds from the World
        
            * This is a temporary float to fill out a Temporary FRotator*/
    FRotator Rotation = FRotator(0, RotateAmount, 0);
        // Middle uses above float, and the rest 0 so only rotate left and right ^ 
    RotationDirection = FQuat(Rotation);
        // uses FRotator above to supply the Axis points and values ^ 
}

void APawnTank::Move()
{
    AddActorLocalOffset(MoveDirection, true);
        /* bSweep checks if collisions should be checked while the actor is moving. Without it on, can 
            phase through walls or floors.*/
}

void APawnTank::Rotate()
{
    AddActorLocalRotation(RotationDirection, true);
        // Adds Rotation Direction as Declared in CalculateRotateInput above ^
}
