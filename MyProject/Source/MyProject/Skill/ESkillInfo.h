#pragma once
UENUM(BlueprintType)
enum class ESkillName : uint8
{

	ESN_Skill1 UMETA(DisplayName = "Skill1"),
	ESN_Skill2 UMETA(DisplayName = "Skill2"),
	ESN_Skill3 UMETA(DisplayName = "Skill3"),
	ESN_Skill4 UMETA(DisplayName = "Skill4"),

};


UENUM(BlueprintType)
enum class ESkillInput : uint8
{

	ESI_InputQ UMETA(DisplayName = "InputQ"),
	ESI_InputW UMETA(DisplayName = "InputW"),
	ESI_InputE UMETA(DisplayName = "InputE"),
	ESI_InputR UMETA(DisplayName = "InputR"),

};