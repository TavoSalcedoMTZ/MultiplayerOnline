#include "OnlineGameMode.h"
#include "OnlinePlayerState.h"

AOnlineGameMode::AOnlineGameMode()
{
	PlayerStateClass = AOnlinePlayerState::StaticClass();
}

void AOnlineGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("GAMEMODE"));
}