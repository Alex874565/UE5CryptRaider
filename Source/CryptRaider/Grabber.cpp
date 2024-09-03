// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr){
		return;
	}

	if (PhysicsHandle -> GetGrabbedComponent()){
		FVector TargetLocation = GetOwner() -> GetActorLocation() + GetForwardVector() * HoldDist;
		PhysicsHandle -> SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Release(){
	
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr){
		return;
	}

	if (PhysicsHandle -> GetGrabbedComponent()){
		PhysicsHandle -> ReleaseComponent();
	}

}

void UGrabber::Grab(){

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr){
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);
	
	if (HasHit){
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();

		HitComponent -> WakeAllRigidBodies();

		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint, 
			GetComponentRotation()
		);
	}else{
		UE_LOG(LogTemp, Display, TEXT("No actor hit!"));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const{
	return GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
}

void UGrabber::ToggleGrab(){
	if(HasGrabbed){
		Release();
	}else{
		Grab();
	}
	HasGrabbed = !HasGrabbed;
}

bool UGrabber::GetGrabbableInReach(FHitResult& HitResult){
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDist;

	return GetWorld() -> SweepSingleByChannel(HitResult, 
													Start, End, 
													FQuat::Identity,
													ECC_GameTraceChannel2, 
													FCollisionShape::MakeSphere(GrabRadius));
}