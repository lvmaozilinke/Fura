// Copyright Druid Mechanics


#include "FuraProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AFuraProjectile::AFuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	//设置同步
	bReplicates=true;
	
	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//碰撞查询
	//设置所有效果关闭
	Sphere->SetCollisionResponseToChannels(ECR_Ignore);// 不会与任何物体产生碰撞。它会忽略所有类型的碰撞检测，既不会引发物理反应，也不会触发事件。
	//单独开启对WorldDynamic的,属性:Overlap
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
	//单独开启对WorldDynamic的,属性:Overlap
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	//单独开启对pawn的,属性:Overlap
	Sphere->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);

	ProjectileMovement=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed=550.f;
	ProjectileMovement->MaxSpeed=550.f;
	///**此Projectile的自定义重力.设置为0，无重力。 */
	ProjectileMovement->ProjectileGravityScale=0.f;
	
}

void AFuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AFuraProjectile::OnSphereOverlap);
	
}



/*	UPrimitiveComponent*, OverlappedComponent,
 *	AActor*, OtherActor,
 *	UPrimitiveComponent*, OtherComp,
 *	int32, OtherBodyIndex,
 *	bool, bFromSweep,
 *	const FHitResult &, SweepResult
*/
void AFuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}


