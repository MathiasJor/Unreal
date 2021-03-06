// Copyright Mathias Jørnsen 2017.

#include "BuildingEscape.h"
#include "Cloner.h"


// Sets default values for this component's properties
UCloner::UCloner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCloner::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0, 0, 0);
	FVector myLoc(0, 0, 100);
	//auto tst = GetWorld()->FindComponentByClass<AStaticMeshActor>();
	//GetWorld()->SpawnActor<AStaticMeshActor>(this->GetClass(), myLoc, myRot, SpawnInfo);
	FString tst = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *tst);
	FString tst2 = this->GetClass()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Class: %s"), *tst2);
	
	FTransform trans;
	FQuat quat = myRot.Quaternion();
	trans.SetLocation(myLoc);
	trans.SetRotation(quat);
	
	//auto tst3 = GetWorld()->SpawnActor<class AStaticMeshActor>(GetClass(), Parameters);

	auto world = GetWorld();

	FActorSpawnParameters Parameters;
	ESpawnActorCollisionHandlingMethod aCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Parameters.Name = GetOwner()->GetFName();
	Parameters.Template = GetOwner();
	//Parameters.Owner = GetWorld();
	Parameters.Instigator = GetOwner()->GetInstigator();
	Parameters.SpawnCollisionHandlingOverride = aCollisionHandlingOverride;
	world->SpawnActorAbsolute<AActor>(GetOwner()->GetClass(), trans, Parameters);
	
}


// Called every frame
void UCloner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

