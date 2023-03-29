// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "OpenWorldGameProject/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemMeshComponent"));
	RootComponent = ItemMesh;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	startLocation = GetActorLocation();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	runningTime += DeltaTime;
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