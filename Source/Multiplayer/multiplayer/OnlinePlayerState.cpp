// Fill out your copyright notice in the Description page of Project Settings.


#include "multiplayer/OnlinePlayerState.h"

// Sets default values
AOnlinePlayerState::AOnlinePlayerState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOnlinePlayerState::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("GAMEMODE"));
}

// Called every frame
void AOnlinePlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

