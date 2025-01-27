#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

class UNiagaraComponent;
class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

protected:

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<URadialForceComponent> ForceComp;


	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent,
					AActor* OtherActor,
					UPrimitiveComponent* OtherComp,
					FVector NormalImpulse,
					const FHitResult& Hit);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
};
