// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"
#include "Characters/OpenWorldCharacter.h"

void AWeapon::OnSphereTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereTriggerOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	AOpenWorldCharacter* character = Cast<AOpenWorldCharacter>(OtherActor);
	if(character)
	{
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		ItemMesh->AttachToComponent(character->GetMesh(), TransformRules, FName("RightHandSocket"));
	}
}

void AWeapon::OnSphereTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereTriggerEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
