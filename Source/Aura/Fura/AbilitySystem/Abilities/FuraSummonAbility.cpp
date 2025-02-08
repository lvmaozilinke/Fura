// Copyright Druid Mechanics


#include "FuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UFuraSummonAbility::GetSpawnLocations()
{
	//获取角色朝向
	const FVector Forward=GetAvatarActorFromActorInfo()->GetActorForwardVector();
	//获取角色位置
	const FVector Location=GetAvatarActorFromActorInfo()->GetActorLocation();

	const float DeltaSpread=SpawnSpread/NumMinions;
	//绘制角色面向位置右侧偏移角度的线
	const FVector LeftOfSpread=Forward.RotateAngleAxis(-SpawnSpread/2.f,FVector::UpVector);
	//角色位置数组
	TArray<FVector>SpawnLocations;
	for (int32 i=0;i<NumMinions;i++)
	{
		const FVector Direction=LeftOfSpread.RotateAngleAxis(DeltaSpread*i,FVector::UpVector);
		//生成怪物的位置
		const FVector ChaosSpawnLocation=Location+Direction*FMath::FRandRange(MinSpawnDistance,MaxSpawnDistance);
		SpawnLocations.Add(ChaosSpawnLocation);
		DrawDebugSphere(GetWorld(),ChaosSpawnLocation,10.f,12,FColor::Red,false,3.f);

		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),Location,Location+Direction*MaxSpawnDistance,4.f,FLinearColor::Green,5.f);
		DrawDebugSphere(GetWorld(),Location+LeftOfSpread*MinSpawnDistance,5.f,12,FColor::Red,false,3.f);
		DrawDebugSphere(GetWorld(),Location+LeftOfSpread*MaxSpawnDistance,5.f,12,FColor::Red,false,3.f);

	}
	
	/*const FVector RightOfSpread=Forward.RotateAngleAxis(SpawnSpread/2.f,FVector::UpVector);
	for (int32 i=0;i<NumMinions;i++)
	{
		const FVector Direction=RightOfSpread.RotateAngleAxis(DeltaSpread*i,FVector::UpVector);
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),Location,Location+Direction*MaxSpawnDistance,4.f,FLinearColor::Green,5.f);
		DrawDebugSphere(GetWorld(),Location+RightOfSpread*MinSpawnDistance,5.f,12,FColor::Red,false,3.f);
		DrawDebugSphere(GetWorld(),Location+RightOfSpread*MaxSpawnDistance,5.f,12,FColor::Red,false,3.f);
	}*/

	/*绘制角色面向位置左侧偏移角度的线
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),Location,Location+RightOfSpread*MaxSpawnDistance,4.f,FLinearColor::Green,5.f);
	绘制角色面向位置右侧偏移角度的线
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),Location,Location+LeftOfSpread*MaxSpawnDistance,4.f,FLinearColor::Green,5.f);*/
	
	return SpawnLocations;
}
