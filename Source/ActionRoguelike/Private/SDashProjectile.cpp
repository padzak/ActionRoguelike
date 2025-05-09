// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"

ASDashProjectile::ASDashProjectile()
{
    TeleportDelay = 0.7f;
    DetonationDelay = 0.2f;

    MovementComp->InitialSpeed = 6000.f;
}

void ASDashProjectile::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ASDashProjectile::Explode, TeleportDelay, false);
}

void ASDashProjectile::Explode_Implementation()
{
    GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

    UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
    
    EffectComp->DeactivateSystem();

    MovementComp->StopMovementImmediately();
    SetActorEnableCollision(false);

    FTimerHandle TimerHandle_DelayedTeleport;
    GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ASDashProjectile::TeleportInstigation, TeleportDelay);

}

void ASDashProjectile::TeleportInstigation()
{
    AActor* ActorToTeleport = GetInstigator();

    check(ActorToTeleport);
    ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
    const APawn* InstigatorPawn = CastChecked<APawn>(ActorToTeleport);

    Destroy();
}
