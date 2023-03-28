// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "OpenWorldGameProject/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();

	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	DRAW_DEBUG_SPHERE(GetActorLocation());
	DRAW_VECTOR(location, location + forwardVector * 100.f);
}