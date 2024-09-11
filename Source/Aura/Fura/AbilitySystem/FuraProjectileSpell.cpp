// Copyright Druid Mechanics


#include "FuraProjectileSpell.h"

#include "Aura/Fura/Actor/FuraProjectile.h"
#include "Aura/Fura/interaction/CombatInterface_F.h"

//#include "Kismet/KismetSystemLibrary.h"

void UFuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//UKismetSystemLibrary::PrintString(this,FString("ActivateAbility(C++)"),true,true,FLinearColor::Yellow,3);

}

void UFuraProjectileSpell::SpawnProjectile()
{
	//判断是否为服务器
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	//通过cast的方式判断GetAvatarActorFromActorInfo 当前的角色是否继承了接口
	ICombatInterface_F* CombatInterface_F = Cast<ICombatInterface_F>(GetAvatarActorFromActorInfo());

	if (CombatInterface_F)
	{
		//获取当前接口实现的玩家的子弹生成位置
		const FVector SocketLocation = CombatInterface_F->GetCombatSocketLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		//尝试生成火球
		AFuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AFuraProjectile>(
			ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		//ESpawnActorCollisionHandlingMethod:生成actor的方式，忽略碰撞之类的
		Projectile->FinishSpawning(SpawnTransform);
	}
	
}
