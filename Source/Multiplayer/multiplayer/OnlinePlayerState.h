#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "OnlinePlayerState.generated.h"

class UAbilitySystemComponent;
class UOnlineAttributeSet;

UCLASS()
class MULTIPLAYER_API AOnlinePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AOnlinePlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UOnlineAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UOnlineAttributeSet* AttributeSet;
};