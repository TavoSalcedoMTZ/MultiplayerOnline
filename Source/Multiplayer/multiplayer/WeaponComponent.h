#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class UWeaponData;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MULTIPLAYER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UWeaponData* WeaponDefinition;

	// Solo hace algo en el servidor (HasAuthority)
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void TryStartFire();
};