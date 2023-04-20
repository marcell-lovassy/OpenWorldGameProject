// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "OpenWorldGameProject/DebugMacros.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	//our sword is ignoring pawns, but overlapping WorldDynamic so the enemy should be WorldDynamic
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	//we need to set this (this is not the default on a skeletal mesh)
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void AEnemy::PlayHitReactionMontage(const FName& sectionName)
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	
	if (animInstance && HitReactionMontage)
	{
		animInstance->Montage_Play(HitReactionMontage);
		animInstance->Montage_JumpToSection(sectionName, HitReactionMontage);
	}
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit(const FVector& impactPoint)
{
	DRAW_DEBUG_SPHERE_TIME(impactPoint, FColor::Yellow, 2.f);
	DirectionalHitReaction(impactPoint);
}

void AEnemy::DirectionalHitReaction(const FVector& impactPoint)
{
	FVector forward = GetActorForwardVector();
	const FVector impactLowered(impactPoint.X, impactPoint.Y, GetActorLocation().Z);
	FVector toHit = (impactLowered - GetActorLocation()).GetSafeNormal();

	//forward * toHit = |forward||toHit| * cos(theta)
	//here					=1		=1
	const double cosTheta = FVector::DotProduct(forward, toHit);

	//this is in radians, need to convert it to degree
	double theta = FMath::Acos(cosTheta);
	theta = FMath::RadiansToDegrees(theta);
	UE_LOG(LogTemp, Warning, TEXT("Dot: %f"), theta);

	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + forward * 60.f, 5.f, FColor::Red, 5.f);
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + toHit * 60.f, 5.f, FColor::Green, 5.f);

	//if cross product points down, theta should be negative
	const FVector crossProduct = FVector::CrossProduct(forward, toHit);

	if (crossProduct.Z < 0)
	{
		theta *= -1.f;
	}
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + crossProduct * 100.f, 5.f, FColor::Blue, 5.f);

	FString montageSection = "FromBack";
	GetMontageSectionForHitReaction(theta, montageSection);

	PlayHitReactionMontage(FName(montageSection));
}

void AEnemy::GetMontageSectionForHitReaction(double theta, FString& montageSection)
{
	if (theta >= -45.f && theta < 45.f)
	{
		montageSection = "FromFront";
	}
	else if (theta >= 45.f && theta < 135.f)
	{
		montageSection = "FromRight";
	}
	else if (theta >= -135.f && theta < -45.f)
	{
		montageSection = "FromLeft";
	}
}

