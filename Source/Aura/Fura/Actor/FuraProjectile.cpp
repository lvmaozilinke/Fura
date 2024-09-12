// Copyright Druid Mechanics


#include "FuraProjectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFuraProjectile::AFuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	//设置同步
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);

	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly); //碰撞查询
	//设置所有效果关闭
	Sphere->SetCollisionResponseToChannels(ECR_Ignore); // 不会与任何物体产生碰撞。它会忽略所有类型的碰撞检测，既不会引发物理反应，也不会触发事件。
	//单独开启对WorldDynamic的,属性:Overlap
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	//单独开启对WorldDynamic的,属性:Overlap
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	//单独开启对pawn的,属性:Overlap
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	///**此Projectile的自定义重力.设置为0，无重力。 */
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AFuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AFuraProjectile::OnSphereOverlap);
}

void AFuraProjectile::Destroyed()
{
	//检查是否在客户端且投射物没有命中
	if (!bHit && !HasAuthority())
	{
		//播放命中音效
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		//播放命中特效
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	}
	
	Super::Destroyed();
}


/*	UPrimitiveComponent*, OverlappedComponent,
 *	AActor*, OtherActor,
 *	UPrimitiveComponent*, OtherComp,
 *	int32, OtherBodyIndex,
 *	bool, bFromSweep,
 *	const FHitResult &, SweepResult
*/
void AFuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	//用于检查当前实例是否拥有网络权限（Authority）的一个常用条件，特别在多玩家（多人游戏）和服务器/客户端架构中使用。
	//它可以用来区分当前的代码是否在服务器上运行（即拥有权限），还是在客户端上运行（没有权限）。
	if (HasAuthority())
	{
		Destroy(); //服务器上销毁，会同步（同步到客户端后调用到Destroyed）
	}
	else
	{
		bHit = true; // 在客户端标记为命中
	}
}
