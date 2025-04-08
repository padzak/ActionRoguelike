#pragma once

#include "CoreMinimal.h"
#include "SMagicProjectile.h"
#include "SBlackHoleProjectile.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ASBlackHoleProjectile : public ASMagicProjectile
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComp;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UCurveFloat* AnimRadiusCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float MaxRadius;

	UFUNCTION()
	void OnOverlappedPhysicsActor(UPrimitiveComponent* OverlappedComponent,
								  AActor* OtherActor,
								  UPrimitiveComponent* OtherComp,
								  int32 OtherBodyIndex,
								  bool bFromSweep,
								  const FHitResult& SweepResult);

public:
	ASBlackHoleProjectile();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
};
