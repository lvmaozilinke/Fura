// Copyright Druid Mechanics


#include "FuraPlayerControllerBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "FuraAbilitySystemComponent.h"
#include "FuraGamePlayTags.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Components/SplineComponent.h"
#include "Input/FuraInputComponent.h"

AFuraPlayerControllerBase::AFuraPlayerControllerBase()
{
	//设置网络同步
	bReplicates = true;
	//
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AFuraPlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//调用检测鼠标是否在继承IEnemyInterface_F 接口的actor上
	CurSorTrace();

	//自动移动
	AutoRun();
}

void AFuraPlayerControllerBase::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);

	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn())
	{
		//获取到角色 添加输入移动
		ControllerPawn->AddMovementInput(ForwardDir, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDir, InputAxisVector.X);
	}
}

void AFuraPlayerControllerBase::CurSorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.GetActor())
	{
		return;
	}
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface_F>(CursorHit.GetActor());

	//判断 ThisActor 是否与 LastActor 不同，然后进行高亮或取消高亮的处理。
	if (ThisActor != LastActor)
	{
		if (LastActor) LastActor->UnHightLightActor();
		if (ThisActor) ThisActor->HightLightActor();
	}
}

void AFuraPlayerControllerBase::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());

	//当按键按下时，判断是否是LMB按下了
	if (InputTag.MatchesTagExact(FFuraGamePlayTags::Get().FInputTag_LMB))
	{
		//如果鼠标左键按下的时候this actor
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

//释放按键
void AFuraPlayerControllerBase::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, *InputTag.ToString());

	//松开的是左键的时候的逻辑
	if (!InputTag.MatchesTagExact(FFuraGamePlayTags::Get().FInputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold)
		{
			//判断
			//导航移动，从一个地方移动到另一个地方，类似AImove

			//查询是否有从玩家当前位置到鼠标点击终点的路径
			if (UNavigationPath* Navpath = UNavigationSystemV1::FindPathToLocationSynchronously(
				this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				//根据路径移动
				//绘制移动路线 Nav path->PathPoints 是一个TArray数组，路线坐标点数组集合。
				//清空绘制线的坐标点
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : Navpath->PathPoints)
				{
					//绘制数组里面的每一个点,在spline 为样条线添加一个点。入参为点坐标和坐标系（本地和世界）
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
				}
				//移动判断自身离移动坐标数组的最后一个点是否等于点击终点
				CachedDestination = Navpath->PathPoints[Navpath->PathPoints.Num() - 1];

				//开始移动
				bAutoRunning = true;
			}
		}
		//松开后恢复数值
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AFuraPlayerControllerBase::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Green, *InputTag.ToString());
	if (!InputTag.MatchesTagExact(FFuraGamePlayTags::Get().FInputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		//判断鼠标是否命中的函数[.bBlockingHit]
		if (CursorHit.bBlockingHit)
		{
			//命中坐标点
			CachedDestination = CursorHit.ImpactPoint;
		}
		if (APawn* ControllerPawn = GetPawn())
		{
			//创建坐标变量，值为命中坐标点减去玩家当前位置
			const FVector WorldDirection = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
			ControllerPawn->AddMovementInput(WorldDirection);
		}
	}
}

/*获取AbilitySystemComponent*/
UFuraAbilitySystemComponent* AFuraPlayerControllerBase::GetASC()
{
	if (FuraAbilitySystemComponent == nullptr)
	{
		//通过AbilitySystemBlueprintLibrary::GetAbilitySystemComponent,并设置到FuraAbilitySystemComponent
		FuraAbilitySystemComponent = Cast<UFuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return FuraAbilitySystemComponent;
}

void AFuraPlayerControllerBase::AutoRun()
{
	//如果不是自动运行就返回
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		//实现沿着样条线移动
		//给定一个位置，在世界空间中，返回最接近该位置的曲线上的点的位置。 
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(
			ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		//获取方向Direction
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(
			LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);
		//创建float长度，值为玩家距离曲线最近点的位置-点击命中的点的长度（length）
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		//判断这个长度是为小于等于设定的值
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			//移动完成
			bAutoRunning = false;
		}
	}
}

void AFuraPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	check(FuraContext);

	//拿到输入子系统
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());

	//check(Subsystem);
	if (Subsystem)
	{
		//添加输入情景--priority:优先级
		Subsystem->AddMappingContext(FuraContext, 0);
	}


	//显示鼠标并锁定在视口
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	//创建输入模式配置InputModeData
	FInputModeGameAndUI InputModeData;
	//不锁定视口
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//在鼠标按下导致的临时鼠标捕获过程中是否隐藏光标
	InputModeData.SetHideCursorDuringCapture(false);
	//正确设置
	SetInputMode(InputModeData);
}

void AFuraPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	UFuraInputComponent* FuraInputComponentA = CastChecked<UFuraInputComponent>(InputComponent);
	//绑定wasd
	FuraInputComponentA->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFuraPlayerControllerBase::Move);
	//绑定按键的按下、松开、按住
	FuraInputComponentA->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed,
	                                        &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}
