// Copyright Mathias Jørnsen 2017.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (!PressurePlate) { return; }
}


void UOpenDoor::OpenDoor()
{
	OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	OnCloseRequest.Broadcast();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float CurrentMass = GetTotalMassOfActorsOnPlate();
	if (CurrentMass != LastFrameMass) {
		if (CurrentMass > LastFrameMass) {
			OpenDoor();
		}
		else if (CurrentMass < LastFrameMass) {
			CloseDoor();
		}
	}
	LastFrameMass = CurrentMass;
	float weightedAngle = GetTotalMassOfActorsOnPlate();
	//OpenDoor(weightedAngle);
	//Poll trigger volume
	/*if (weightedAngle > 30.0f) { // TODO make into parameter
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}*/

	//CloseDoor after delay
	/*if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	} */
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.0f;

	TArray<AActor*> OverLappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverLappingActors);

	for (const auto* Actor : OverLappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	//UE_LOG(LogTemp, Warning, TEXT("Mass: %f"), TotalMass);
	return OpenDoorAngle(TotalMass);
}

float UOpenDoor::GetMassForBP()
{
	UE_LOG(LogTemp, Warning, TEXT("BP Update %f"), GetTotalMassOfActorsOnPlate());
	return GetTotalMassOfActorsOnPlate();
}

float UOpenDoor::OpenDoorAngle(float angle)
{
	//UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), angle);
	if (angle >= 0 && angle <= 90) {
		return angle;
	}
	else if (angle > 90) {
		return 90.0f;
	}
	else /*if (angle < 0)*/ {
		return 0.0f;
	}

}