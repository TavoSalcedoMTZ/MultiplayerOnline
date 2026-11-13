#include "OnlineGameState.h"

void AOnlineGameState::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("GAMESTATE"));
}