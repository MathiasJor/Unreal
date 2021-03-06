// Copyright Mathias Jørnsen 2017.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//How far the grabber can reach from player
	float Reach = 100.0f;

	//PhysicsComponent handle
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	//Input component handle
	UInputComponent* InputHandle = nullptr;

	// Ray-cast and grab whats in reach
	void Grab();

	// Release from grab()
	void Release();

	//Find attached PhysicsComponent
	void FindPhysicsHandleComponent();

	//Setup (assumed) attached input component
	void SetupInputComponent();

	//Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach();

	// Return current start of reach line
	FVector GetReachLineStart();
	
	// Return current end of reach line
	FVector GetReachLineEnd();
};