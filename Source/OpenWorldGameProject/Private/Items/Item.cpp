// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "OpenWorldGameProject/DebugMacros.h"
#include "Components/SphereComponent.h"
#include "Characters/OpenWorldCharacter.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemMeshComponent"));
	RootComponent = ItemMesh;

	SphereTrigger = CreateDefaultSubobject<USphereComponent>(FName("SphereTrigger"));
	SphereTrigger->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	startLocation = GetActorLocation();

	SphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereTriggerOverlap);
	SphereTrigger->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereTriggerEndOverlap);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	runningTime += DeltaTime;

	if(ItemState == EItemState::EIS_Hovering)
	{
		FVector hoverLocation(startLocation.X, startLocation.Y, startLocation.Z + TransformedSin());
		SetActorLocation(hoverLocation);
	}
}

float AItem::TransformedSin()
{
	//period = 2*PI/K: (K is Speed here) how much time it takes for SIN to go to the lowest and 
	// heighest point and back to the starting point
	
	return Amplitude * FMath::Sin(2 * PI * runningTime * Frequency);
}

float AItem::TransformedCos()
{
	return Amplitude * FMath::Cos(2 * PI * runningTime * Frequency);
}

void AItem::OnSphereTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOpenWorldCharacter* character = Cast<AOpenWorldCharacter>(OtherActor);
	if(character)
	{
		character->SetOverlappingItem(this);
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Cyan, FString("Press E to interact with item"));
		}
	}

}

void AItem::OnSphereTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AOpenWorldCharacter* character = Cast<AOpenWorldCharacter>(OtherActor);
	if (character)
	{
		character->SetOverlappingItem(nullptr);
	}
}
