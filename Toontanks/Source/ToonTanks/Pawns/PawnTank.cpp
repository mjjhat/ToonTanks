// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/PawnTank.h"

/////////////////////
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"/*
    The two includes above allows us to callup the camera and springarm*/



APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);/*
        INHERITANCE: The above is set up in a manner like in PawnBase.cpp.
            Go to PawnBase.cpp for more details.*/
}


// BeginPlay, Tick, Setup were taken from the Parent Class (PawnBase.cpp):

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();	
    PlayerControllerRef = Cast<APlayerController>(GetController());
/*      We have casted out before, but this time to cast out to get the active player controller
        that the world created in order to handle the playerpawn
            -this is then being stored as our PlayerControllerRef */
}

void APawnTank::HandleDestruction() 
{
    Super::HandleDestruction();
/*      Hide player. TODO - Create new function to handle this.
    //Destroy();// call to destroy the pawn-> but will shoot us to default camera
        Removed Destroy because we need to call a few things which may crash UE 
            if we destroyed the pawn we are trying to call*/
    
    bIsPlayerAlive = false;// if tank is destroyed, Alive now = false

    SetActorHiddenInGame(true);// hides the player if no longer alive
    SetActorTickEnabled(false);
/*      Stops the tick function if no longer alive- and saves a little performance too!
        Stops move/rotate because Tick has these functions there. 
        CAMERA: Does not jump back to default camera because still focused on the (hidden)
                Player*/

}

bool APawnTank::GetIsPlayerAlive()
/*  This class is here to safegaurd the bIsPlayerAlive variable while making it available to
other functions to call it up and use it, or any other class that may want to use it.

    Other classes may need to know the state of the player, so they can access this to see if
    true or false
    
    Thus can be called upon, but not so easily changed from the outside this way*/
{
    return bIsPlayerAlive;
}



// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Rotate();
    Move();/*
        These will constantly call up our movement and rotate functions to see if they are
        being used.
            -It is good to have this information called up before the movement functions
             even begin to take place. It will be ready for processing at any frame.
            
            *While we could move the AddActors code (as seen below)to their respective 
                Calculate Functions above them to reduce the number of functions in our code,
                having them separate grants better control over our code's order of processing:
                That is, we can change a variable or it's placement in the hierarchy without 
                crashing our code. 
                    -If reduced, it would constantly look up the 0's, which is not a bad thing, 
                        but the order is less controllable (some may want to move the rotate or 
                        move AddActors around because they find one order more preferable than
                        another)
                        
            *Instructor prefers to have the rotation value called up first rather than the movement
                -He suggests swapping the Rotate and Move around a few times later on to see how
                    the order can change the feel of thing and see what you like best. At this point
                    it is more about personal taste. */
        if(PlayerControllerRef)
        // Casts out into world from player tank into world
        {
            FHitResult TraceHitResult;
            PlayerControllerRef->GetHitResultUnderCursor(
                ECC_Visibility, 
                false, //don't need complex tracing-like specific limbs or parts
                TraceHitResult
            );
    /*          Will trace the cursors screen location into the world space and find
                the resulting location casted out */
            FVector HitLocation = TraceHitResult.ImpactPoint;// end location for our tank turret to look at
           
            RotateTurret(HitLocation);// alrady have a class in the parent, only prove FVector
        }
}


void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)/*
    Called to bind functionality to input, that is, our tank will respond to the keys we
    press on our keyboard in the manner we code it to act: if "w" = move forward, it will
    move the tank forward.*/
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward",this, &APawnTank::CalculateMoveInput);/*
        BINDING KEYS: make sure that the name is the same as appears in the Engine Input 
                        section
        THIS: Will constantly look up "this" function to see if a key is pressed, when pressed, 
                how long it is pressed. "this" is the world context of the function-- what in 
                the world is being effected by specified function (&APawnTank::...).
        FUNCTION: The function will point to the APawnTank class using CalculateMoveInput function to move the tank
            when pressed*/
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);/*
        As Above, but with the "Turn" key binding- has value of 0-1 for incremental changes
        like as those found for movement.*/
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
    /*  Single press events do not need an increment value count, such as firing a gun, 
        jumping, interaction pressed. 
        IE_Pressed: Tells us to do a function upon pressing a bound key (such as space
                    bar = fire gun or interact: thus will go to FireGun function)
            -we can also have logic for "When released"-> IE_Pressed*/
}

void APawnTank::CalculateMoveInput(float Value)
    //Calculate Tank movement (backward/forward) direction. 
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);/*
        We are only wanting movement on the x axis. This is being checked  by looking up 
        the Value * MoveSpeed (100.0f) * DeltaSpeed (which we will pull up out from the world).
            
            *Note that FVectors require X, Y, Z values. Since we are not strafing we will set 
                the Y and Z to 0*/
}

void APawnTank::CalculateRotateInput(float Value)
    // Calculate Tank rotation direction
{
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;/*
        ROTATION VALUE: This is based off of the value set to bound key, and this will calculate
                        the complete rotation thus: KeyValue * RotateSpeed (100.0f) * DeltaTime 
                        (Which we will pull up from out of the world) 
        
            * This is a temporary float to fill out a Temporary FRotator*/
    FRotator Rotation = FRotator(0, RotateAmount, 0);
        // Middle uses the float declared above, and the rest 0 so only rotate left and right ^ 
    RotationDirection = FQuat(Rotation);
        // uses FRotator above to supply the Axis points and values ^ 
}

void APawnTank::Move()
{
    AddActorLocalOffset(MoveDirection, true);/* 
        bSweep(true): looks to see if collisions should be checked while the actor is moving. 
                        Without it on, can phase through walls or floors.*/
}

void APawnTank::Rotate()
{
    AddActorLocalRotation(RotationDirection, true);
        // Adds Rotation Direction as Declared in CalculateRotateInput above ^
}
