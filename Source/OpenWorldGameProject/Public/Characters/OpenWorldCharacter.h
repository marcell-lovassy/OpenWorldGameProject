// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <InputActionValue.h>
#include "CharacterTypes.h"
#include "OpenWorldCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;
class AWeapon;

UCLASS()
class OPENWORLDGAMEPROJECT_API AOpenWorldCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AOpenWorldCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* OpenWorldInputContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* DodgeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* EquipUnequipAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float MouseSensitivity = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool InvertY = false;

	/*
	Callbacks for input
	*/
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Interact();
	void Attack();
	void ToggleArmed();
	void Dodge();

	/*
	Play montage functions
	*/
	void PlayAttackMontage();
	void PlayArmDisarmMontage(FName sectionName);
	UFUNCTION(BlueprintCallable)
	void EndAttack();
	UFUNCTION(BlueprintCallable)
	void Disarm();
	UFUNCTION(BlueprintCallable)
	void Arm();
	UFUNCTION(BlueprintCallable)
	void EndArmDisarm();
	bool CanAttack();
	bool CanDisarm();
	bool CanArm();

private:

	ECharacterState CharacterState = ECharacterState::ECS_Unarmed;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	/*
	Animation Montages
	*/

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* ArmDisarmMontage;

public:
	FORCEINLINE void SetOverlappingItem(AItem* item) { OverlappingItem = item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
