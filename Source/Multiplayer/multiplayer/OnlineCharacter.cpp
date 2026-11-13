#include "OnlineCharacter.h"
#include "OnlinePlayerState.h"
#include "WeaponComponent.h"
#include "AbilitySystemComponent.h"

AOnlineCharacter::AOnlineCharacter()
{
	WeaponComp = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComp"));
}

UAbilitySystemComponent* AOnlineCharacter::GetAbilitySystemComponent() const
{
	AOnlinePlayerState* PS = GetPlayerState<AOnlinePlayerState>();
	if (PS)
	{
		return PS->GetAbilitySystemComponent();
	}
	return nullptr;
}

void AOnlineCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitASC();
}

void AOnlineCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitASC();
}

void AOnlineCharacter::InitASC()
{
	if (AOnlinePlayerState* PS = GetPlayerState<AOnlinePlayerState>())
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	}
}

void AOnlineCharacter::Fire()
{
	if (HasAuthority())
	{
		WeaponComp->TryStartFire();
	}
	else
	{
		Server_Fire();   // el cliente pide al servidor
	}
}

void AOnlineCharacter::Server_Fire_Implementation()
{
	WeaponComp->TryStartFire();
}