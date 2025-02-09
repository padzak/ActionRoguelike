// Fill out your copyright notice in the Description page of Project Settings.


#include "SPrimaryAttackProjectile.h"

#include <SAttributeComponent.h>

void ASPrimaryAttackProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComp,
											   AActor* OtherActor,
											   UPrimitiveComponent* OtherComp,
											   int32 OtherBodyIndex,
											   bool bFromSweep,
											   const FHitResult& SweepResult) 
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f);

			Destroy();
		}
		;
	}
}
