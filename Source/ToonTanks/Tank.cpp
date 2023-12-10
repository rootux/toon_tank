// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BaseMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!TankPlayerController)
	{
		return;
	}

	
	FHitResult HitResult;
	TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	RotateTurret(HitResult.ImpactPoint);	
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::Zero();
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

void ATank::Turn(float Value)
{
	FRotator Rotation = FRotator::ZeroRotator; 
	float DeltaRotation = Value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	Rotation.Yaw = DeltaRotation;
	AddActorLocalRotation(Rotation);
}
