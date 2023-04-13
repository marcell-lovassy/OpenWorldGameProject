// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OpenWorldCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"

AOpenWorldCharacter::AOpenWorldCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	UCharacterMovementComponent* characterMovement = GetCharacterMovement();
	characterMovement->bOrientRotationToMovement = true;
	characterMovement->RotationRate = FRotator(0.f, 400.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(FName("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(FName("Hair"));
	Hair->SetupAttachment(GetMesh());
	//Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(FName("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	//Eyebrows->AttachmentName = FString("head");
}

void AOpenWorldCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(OpenWorldInputContext, 0);
		}
	}
}


void AOpenWorldCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOpenWorldCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOpenWorldCharacter::Move);
		enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOpenWorldCharacter::Look);
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AOpenWorldCharacter::Jump);
		enhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AOpenWorldCharacter::Attack);
		enhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &AOpenWorldCharacter::Dodge);
		enhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AOpenWorldCharacter::Interact);
		enhancedInputComponent->BindAction(EquipUnequipAction, ETriggerEvent::Started, this, &AOpenWorldCharacter::ToggleArmed);
	}
}

void AOpenWorldCharacter::Move(const FInputActionValue& value)
{
	if (ActionState == EActionState::EAS_Attacking) return;

	const FVector2D movementVector = value.Get<FVector2D>();
	/*FVector forward = GetActorForwardVector();
	FVector right = GetActorRightVector();
	AddMovementInput(forward, movementVector.Y);
	AddMovementInput(right, movementVector.X);*/

	//it would be better to use the controller rotation not the actor rotation

	const FRotator controllerRotation = Controller->GetControlRotation();
	const FRotator yawRotation(0.f, controllerRotation.Yaw, 0.f);

	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(forwardDirection, movementVector.Y);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(rightDirection, movementVector.X);
}

void AOpenWorldCharacter::Look(const FInputActionValue& value)
{
	FVector2D turnValue = value.Get<FVector2D>();
	AddControllerYawInput(turnValue.X * MouseSensitivity);
	AddControllerPitchInput((InvertY ? -turnValue.Y : turnValue.Y) * MouseSensitivity);
}

void AOpenWorldCharacter::Interact()
{
	//if OverlappingItem is a nullptr then the cast just simply fails
	//no need to check if nullptr
	AWeapon* overlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if(overlappingWeapon)
	{
		overlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		EquippedWeapon = overlappingWeapon;
	}
}

void AOpenWorldCharacter::Attack()
{
	CanAttack();
	if(CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void AOpenWorldCharacter::ToggleArmed()
{
	if (CanDisarm())
	{
		PlayArmDisarmMontage("Unequip");
		CharacterState = ECharacterState::ECS_Unarmed;
	}
	else if(CanArm())
	{
		PlayArmDisarmMontage("Equip");
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	}
}

bool AOpenWorldCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unarmed;
}

bool AOpenWorldCharacter::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied
		&& CharacterState != ECharacterState::ECS_Unarmed &&
		EquippedWeapon;
}

bool AOpenWorldCharacter::CanArm()
{
	return ActionState == EActionState::EAS_Unoccupied
		&& CharacterState == ECharacterState::ECS_Unarmed &&
		EquippedWeapon;
}

void AOpenWorldCharacter::PlayAttackMontage()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (animInstance && AttackMontage)
	{
		animInstance->Montage_Play(AttackMontage);
		const int32 selection = FMath::RandRange(0, 1);
		FName sectionName = FName();
		switch (selection)
		{
		case 0:
			sectionName = FName("Attack1");
			break;
		case 1:
			sectionName = FName("Attack2");
			break;
		default:
			break;
		}

		animInstance->Montage_JumpToSection(sectionName, AttackMontage);
	}
}

void AOpenWorldCharacter::PlayArmDisarmMontage(FName sectionName)
{

	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (animInstance && ArmDisarmMontage)
	{
		animInstance->Montage_Play(ArmDisarmMontage);
		animInstance->Montage_JumpToSection(sectionName, ArmDisarmMontage);
	}
}

void AOpenWorldCharacter::EndAttack()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void AOpenWorldCharacter::Dodge()
{
}

void AOpenWorldCharacter::Jump()
{
	Super::Jump();
}