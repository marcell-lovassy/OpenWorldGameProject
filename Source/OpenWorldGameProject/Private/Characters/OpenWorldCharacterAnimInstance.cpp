// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OpenWorldCharacterAnimInstance.h"
#include "Characters/OpenWorldCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UOpenWorldCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OpenWorldCharacter = Cast<AOpenWorldCharacter>(TryGetPawnOwner());

	if (OpenWorldCharacter) 
	{
		OpenWorldCharacterMovement = OpenWorldCharacter->GetCharacterMovement();
	}
}

void UOpenWorldCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (OpenWorldCharacterMovement) 
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(OpenWorldCharacterMovement->Velocity);
		IsFalling = OpenWorldCharacterMovement->IsFalling();
	}
}
