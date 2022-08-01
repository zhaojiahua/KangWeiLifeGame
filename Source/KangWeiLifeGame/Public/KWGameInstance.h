#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KWGameInstance.generated.h"


UCLASS()
class KANGWEILIFEGAME_API UKWGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddAttrs")
		int gridXCount = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddAttrs")
		int gridYCount = 100;
};
