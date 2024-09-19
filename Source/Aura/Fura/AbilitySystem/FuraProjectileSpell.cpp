// Copyright Druid Mechanics


#include "FuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Aura/Fura/FuraGamePlayTags.h"
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

void UFuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
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

		//子弹的旋转角度(从插槽位置到射击目标位置的向量)
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		//将Rotator转换成四元数，并设置设计角度
		SpawnTransform.SetRotation(Rotation.Quaternion());
		//尝试生成火球
		AFuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AFuraProjectile>(
			ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//获取与某个角色或对象相关联的能力系统组件
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
			GetAvatarActorFromActorInfo());
		//这里使用MakeOutgoingSpec函数来生成一个游戏效果规格（Gameplay Effect Spec），并将其包装成一个FGameplayEffectSpecHandle对象。
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(
			DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

		const FFuraGamePlayTags GamePlayTags = FFuraGamePlayTags::Get();

		//曲线表格使用方法，根据等级显示对应数据
		const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());

		//分配标签由呼叫者幅度设置
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GamePlayTags.FDamage, ScaledDamage);

		//把伤害的spec handle传递到火球里面
		Projectile->DamageEffectSpecHandle = SpecHandle;

		//ESpawnActorCollisionHandlingMethod:生成actor的方式，忽略碰撞之类的
		Projectile->FinishSpawning(SpawnTransform);
	}
}
