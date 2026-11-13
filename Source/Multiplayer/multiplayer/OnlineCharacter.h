#pragma once

#include "CoreMinimal.h"
#include "MultiplayerCharacter.h"
#include "AbilitySystemInterface.h"
#include "OnlineCharacter.generated.h"

class UWeaponComponent;
class UAbilitySystemComponent;

UCLASS()
class MULTIPLAYER_API AOnlineCharacter : public AMultiplayerCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AOnlineCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;  // servidor
	virtual void OnRep_PlayerState() override;                      // cliente

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UWeaponComponent* WeaponComp;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	UFUNCTION(Server, Reliable)
	void Server_Fire();

private:
	void InitASC();
};