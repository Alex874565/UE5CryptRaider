// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetOwner() -> GetActorRotation();
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove){
		FRotator CurrentRotation = GetOwner() -> GetActorRotation();
		FRotator TargetRotation = OriginalRotation + RotateOffset;
		GetOwner() -> SetActorRotation(FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, Speed));
	}
}

void UMover::SetShouldMove(bool NewShouldMove){
	FString string;
	string = NewShouldMove ? "true" : "false";
	UE_LOG(LogTemp, Display, TEXT("%s"), *string)
	ShouldMove = NewShouldMove;
}

