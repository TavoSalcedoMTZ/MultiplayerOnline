#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "OnlineGameState.generated.h"

UCLASS()
class MULTIPLAYER_API AOnlineGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};