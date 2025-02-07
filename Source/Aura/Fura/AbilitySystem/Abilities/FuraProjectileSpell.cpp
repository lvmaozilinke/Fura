// Copyright Druid Mechanics


#include "FuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Aura/Fura/FuraAbilitySystemLibrary.h"
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
		//const FVector SocketLocation = CombatInterface_F->GetCombatSocketLocation_Implementation();
		
		/*`ICombatInterface_F::Execute_GetCombatSocketLocation();
		 ***调用目标**：这种方式是通过 Unreal Engine 自动生成的 `Execute_` 方法来调用接口函数。
		 *它的作用是在不知道实际类实现的情况下，安全地调用实现了该接口的任何对象的方法。
		*/
		const FVector SocketLocation = ICombatInterface_F::Execute_GetCombatSocketLocation(
			GetAvatarActorFromActorInfo(),FFuraGamePlayTags::Get().FCombatSocket_Weapon);


		//子弹的旋转角度(从插槽位置到射击目标位置的向量)
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

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

		//GameplayEffectContextHandle:游戏效果上下文句柄，通过makeEffectContext获取得到。
		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();

		//设置上下文实例参数 
		EffectContextHandle.SetAbility(this);
		//设置创建此效果的对象 
		EffectContextHandle.AddSourceObject(Projectile);

		/*	TWeakObjectPtr 是一种弱引用指针，通常用于避免循环引用问题。
		 *	它不会增加对象的引用计数，因此即使 TWeakObjectPtr 指向的对象被销毁，TWeakObjectPtr 本身不会阻止该对象被垃圾回收。
		 *	这是一个指向 AActor 对象的弱引用。
		 */
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(Projectile);
		//将Actors放到列表
		EffectContextHandle.AddActors(Actors);

		//命中结果
		FHitResult HitResult;
		//命中的敌人的位置进行传递
		HitResult.Location = ProjectileTargetLocation;
		EffectContextHandle.AddHitResult(HitResult);

		//这里使用MakeOutgoingSpec函数来生成一个游戏效果规格（Gameplay Effect Spec），并将其包装成一个FGameplayEffectSpecHandle对象。
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(
			DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

		const FFuraGamePlayTags GamePlayTags = FFuraGamePlayTags::Get();

		//遍历Map
		for (auto& Pair : DamageTypes)
		{
			//计算伤害值
			const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
			//AssignTagSetByCallerMagnitude:将计算后的伤害值（ScaledDamage）与指定的 Tag（Pair.Key）绑定到一个 SpecHandle 上。
			if (!SpecHandle.IsValid() || !SpecHandle.Data.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("SpecHandle is invalid before assigning damage values!"));
			}
			UE_LOG(LogTemp, Warning, TEXT("Assigning Damage: Tag = %s, ScaledDamage = %f"), *Pair.Key.ToString(), ScaledDamage);
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
		}

		/*
		//曲线表格使用方法，根据等级显示对应数据
		const float ScaledDamage = Damage.GetValueAtLevel(10);

		//分配标签由呼叫者幅度设置
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GamePlayTags.FDamage, ScaledDamage);
		*/

		//把伤害的spec handle传递到火球里面
		Projectile->DamageEffectSpecHandle = SpecHandle;

		//ESpawnActorCollisionHandlingMethod:生成actor的方式，忽略碰撞之类的
		Projectile->FinishSpawning(SpawnTransform);
	}
}
