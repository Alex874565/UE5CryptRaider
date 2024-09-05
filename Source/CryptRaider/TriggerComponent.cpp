// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("UwU"));
	
}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> OverlappingActors;

	GetOverlappingActors(OverlappingActors);

	TArray<AActor*> LeftDoor;
	TArray<AActor*> RightDoor;

	if (OverlappingActors.Num() > 0){
		UE_LOG(LogTemp, Display, TEXT("Should Move"));
		for (UMover* Mover : Movers){
			if(Mover){
				Mover -> SetShouldMove(true);
			}
		}
	}else{
		for (UMover* Mover : Movers){
			if(Mover){
					Mover -> SetShouldMove(false);
			}
		}
	}
}

void UTriggerComponent::SetMovers(TArray<UMover*> NewMovers){
	Movers = NewMovers;
}