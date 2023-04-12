// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;

UCLASS()
class OPENWORLDGAMEPROJECT_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine parameters")
	float Amplitude = 0.25f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine parameters")
	float Frequency = 5.f;

	UFUNCTION(BlueprintPure)
	float TransformedSin();
	UFUNCTION(BlueprintPure)
	float TransformedCos();

	template<typename T>
	T Avg(T first, T second);

	UFUNCTION()
	virtual void OnSphereTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Info")
	float runningTime;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Info")
	FVector startLocation;

	

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereTrigger;
};

template<typename T>
inline T AItem::Avg(T first, T second)
{
	return (first + second) / 2;
}
