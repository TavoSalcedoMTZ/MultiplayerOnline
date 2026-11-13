#include "WeaponComponent.h"
#include "WeaponData.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::TryStartFire()
{
	// ---------- PUNTO 1: Validaciones y autoridad ----------
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor || !OwnerActor->HasAuthority() || !WeaponDefinition)
	{
		return;
	}

	// ---------- PUNTO 2: Origen, dirección y Line Trace ----------
	FVector Origin;
	FRotator ViewRotation;
	OwnerActor->GetActorEyesViewPoint(Origin, ViewRotation);
	if (Origin.IsZero())
	{
		Origin = OwnerActor->GetActorLocation();
		ViewRotation = OwnerActor->GetActorRotation();
	}

	const FVector Direction = ViewRotation.Vector();
	const FVector EndLocation = Origin + (Direction * WeaponDefinition->Range);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerActor);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, Origin, EndLocation, ECC_Visibility, QueryParams);

	DrawDebugLine(GetWorld(), Origin, bHit ? HitResult.ImpactPoint : EndLocation,
		bHit ? FColor::Green : FColor::Red, false, 2.0f, 0, 1.0f);
	if (bHit)
	{
		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5.f), FColor::Yellow, false, 2.0f);
	}

	// ---------- PUNTO 3: Aplicar el Gameplay Effect ----------
	AActor* TargetActor = bHit ? HitResult.GetActor() : nullptr;
	if (!TargetActor)
	{
		return;
	}

	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerActor);
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (!SourceASC || !TargetASC || !WeaponDefinition->DamageEffectClass)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
				TEXT("Falta SourceASC, TargetASC o DamageEffectClass"));
		}
		return;
	}

	FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	EffectContext.AddHitResult(HitResult);

	FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(
		WeaponDefinition->DamageEffectClass, 1.0f, EffectContext);

	if (SpecHandle.IsValid())
	{
		// Con Scalable Float en el GE (-50) NO hace falta nada más.
		// Si usas Set By Caller, descomenta:
		// SpecHandle.Data->SetSetByCallerMagnitude(
		//     FGameplayTag::RequestGameplayTag(FName("Data.Damage")),
		//     -WeaponDefinition->BaseDamage);

		SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
	}
}