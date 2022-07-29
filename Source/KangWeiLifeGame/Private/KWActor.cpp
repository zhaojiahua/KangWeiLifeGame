#include "KWActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AKWActor::AKWActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("rootSceneComp"));
	RootComponent = rootSceneComp;
}

// Called when the game starts or when spawned
void AKWActor::BeginPlay()
{
	Super::BeginPlay();
	GenerateGrid(gridXCount, gridYCount, gridSize);
	DrawGrid();
}

// Called every frame
void AKWActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AKWActor::GenerateGrid(int inXCount, int inYCount, float inGridSize)
{
	for (int x = 0; x < inXCount; x++)
	{
		for (int y = 0; y < inYCount; y++)
		{
			gridMap.Add(FVector2D(x, y), nullptr);
		}
	}
}

