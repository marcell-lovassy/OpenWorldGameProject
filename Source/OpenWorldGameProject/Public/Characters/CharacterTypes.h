#pragma once

//Unreal convention for enums:
//Start enums with E
//Use the class keyword: 
//class: needed to use the enum like this: ECharacterState::Unarmed
//Prefix with the capitals of  the enum type
//uint8: the enum now uses unsigned 8 bit ints (smaller in memory)
//UENUM: add it to the reflection system
//UMETA: use the defined display name in blueprint

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unarmed UMETA(DisplayName = "Unarmed"),
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Handed Weapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two-Handed Weapon")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
};