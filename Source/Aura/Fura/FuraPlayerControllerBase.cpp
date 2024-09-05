// Copyright Druid Mechanics


#include "FuraPlayerControllerBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "FuraAbilitySystemComponent.h"
#include "FuraAbilitySystemLibrary.h"
#include "FuraGamePlayTags.h"
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
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.GetActor())
	{
		return;
	}
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface_F>(CursorHit.GetActor());

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//B
			ThisActor->HightLightActor();
		}
		else
		{
			//A
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			//c
			LastActor->UnHightLightActor();
		}
		else
		{
			if (LastActor == ThisActor)
			{
				//E
			}
			else
			{
				LastActor->UnHightLightActor();
				ThisActor->HightLightActor();
			}
		}
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

	if (GetASC() == nullptr)
	{
		return;
	}
	GetASC()->AbilityInputTagReleased(InputTag);
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
		FollowTime+=GetWorld()->GetDeltaSeconds();
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility,false,Hit))
		{
			//命中坐标点
			CachedDestination=Hit.ImpactPoint;
			
		}
		if (APawn* ControllerPawn=GetPawn())
		{
			//创建坐标变量，值为命中坐标点减去玩家当前位置
			const FVector WorldDirection=(CachedDestination-ControllerPawn->GetActorLocation()).GetSafeNormal();
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
