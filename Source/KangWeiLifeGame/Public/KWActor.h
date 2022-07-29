// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KWActor.generated.h"

UCLASS()
class KANGWEILIFEGAME_API AKWActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKWActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//公开的属性
	UPROPERTY(VisibleAnywhere, category = "zjhAddAttrs")
		class USceneComponent* rootSceneComp;
	UPROPERTY(BlueprintReadOnly, category = "zjhAddAttrs")
		TMap<FVector2D, class UStaticMeshComponent*> gridMap;

	UPROPERTY(EditAnywhere, category = "zjhAddAttrs")
		int gridXCount = 100;
	UPROPERTY(EditAnywhere, category = "zjhAddAttrs")
		int gridYCount = 100;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, category = "zjhAddAttrs")
		float gridSize = 1.0f;

public:
	//公开的函数
	UFUNCTION(BlueprintImplementableEvent, category = "zjhAddFuns")
		void DrawGrid();
private:
	void GenerateGrid(int inXCount, int inYCount, float inGridSize);
};
