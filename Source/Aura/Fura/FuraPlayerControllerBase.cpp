// Copyright Druid Mechanics


#include "FuraPlayerControllerBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AFuraPlayerControllerBase::AFuraPlayerControllerBase()
{
	//设置网络同步
	bReplicates=true;
	
}

void AFuraPlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AFuraPlayerControllerBase::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector=InputActionValue.Get<FVector2d>();
	const FRotator YawRotation(0.f,GetControlRotation().Yaw,0.f);

	const FVector ForwardDir=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDir=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn=GetPawn())
	{
		//获取到角色 添加输入移动
		ControllerPawn->AddMovementInput(ForwardDir,InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDir,InputAxisVector.X);
		
	}
	
	
	
}

void AFuraPlayerControllerBase::CurSorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.GetActor())
	{
		return;
	}
	LastActor=ThisActor;
	ThisActor=Cast<IEnemyInterface_F>(CursorHit.GetActor());

	if(LastActor==nullptr)
	{
		if (ThisActor!=nullptr)
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
		if (ThisActor==nullptr)
		{
			//c
			LastActor->UnHightLightActor();
		}
		else
		{
			if (LastActor==ThisActor)
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

void AFuraPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	check(FuraContext);

	//拿到输入子系统
	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	//check(Subsystem);
	if (Subsystem)
	{
		//添加输入情景--priority:优先级
		Subsystem->AddMappingContext(FuraContext,0);
	}
	

	//显示鼠标并锁定在视口
	bShowMouseCursor=true;
	DefaultMouseCursor=EMouseCursor::Default;
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
	UEnhancedInputComponent* UEnhancedInputComponentA=CastChecked<UEnhancedInputComponent>(InputComponent);
	UEnhancedInputComponentA->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AFuraPlayerControllerBase::Move);
	
}
