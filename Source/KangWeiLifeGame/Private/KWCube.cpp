#include "KWCube.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AKWCube::AKWCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("rootSceneComp"));
	RootComponent = rootSceneComp;
	staticCubeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticCubeComp"));
	staticCubeComp->SetupAttachment(rootSceneComp);
}

// Called when the game starts or when spawned
void AKWCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKWCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

