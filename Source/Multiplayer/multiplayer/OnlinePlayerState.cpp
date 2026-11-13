#include "OnlinePlayerState.h"
#include "AbilitySystemComponent.h"
#include "OnlineAttributeSet.h"
AOnlinePlayerState::AOnlinePlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UOnlineAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AOnlinePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AOnlinePlayerState::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PLAYERSTATE"));
}