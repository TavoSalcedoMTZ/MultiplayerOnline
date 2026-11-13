#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OnlineGameMode.generated.h"

UCLASS()
class MULTIPLAYER_API AOnlineGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOnlineGameMode();

protected:
	virtual void BeginPlay() override;
};