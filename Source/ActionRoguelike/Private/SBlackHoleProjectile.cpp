#include "SBlackHoleProjectile.h"

#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

void ASBlackHoleProjectile::OnOverlappedPhysicsActor(UPrimitiveComponent* OverlappedComponent,
													 AActor* OtherActor,
													 UPrimitiveComponent* OtherComp,
													 int32 OtherBodyIndex,
													 bool bFromSweep,
													 const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

ASBlackHoleProjectile::ASBlackHoleProjectile()
{
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(RootComponent);
	// Roundabout way of removing the object type...
	RadialForceComp->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	//RadialForceComp->Radius = 1000.f;
	RadialForceComp->ForceStrength = -2000000.f;

	MaxRadius = 1000.f;

	// Match with VFX
	InitialLifeSpan = 4.8f;

	// Skip any collision for this projectile
	// Only look for "PhysicsBody" (we are looking to "Absorb" only physics simulating actors) 
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
}

void ASBlackHoleProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASBlackHoleProjectile::OnOverlappedPhysicsActor);
}

void ASBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Fun little bonus, grow and shrink the influence radius of the radial force over time.
	if (AnimRadiusCurve)
	{
		//URogueCurveAnimSubsystem* AnimSubsystem = GetWorld()->GetSubsystem<URogueCurveAnimSubsystem>();

		// Figure out the playrate to match the lifespan
		float MinTime;
		float MaxTime;
		AnimRadiusCurve->FloatCurve.GetTimeRange(MinTime, MaxTime);

		float Duration = MaxTime - MinTime;

		// Match the animation length with the lifespan of the actor
		float PlayRate = Duration / GetLifeSpan();

		//AnimSubsystem->PlayCurveAnim(AnimRadiusCurve, PlayRate, [&](float CurrentValue)
		//{
		//	RadialForceComp->Radius = MaxRadius * CurrentValue;

		//	DrawDebugSphere(GetWorld(), GetActorLocation(), RadialForceComp->Radius, 32, FColor::Blue, false, 0.f);
		//});
	}
}
