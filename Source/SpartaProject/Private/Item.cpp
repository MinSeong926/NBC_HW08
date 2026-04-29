// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"


// Sets default values
AItem::AItem()
{

    // Component 설정
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);

    // 리플렉션을 해줘서 필요 없음
    /*static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Star_B.SM_Star_B"));
    if (MeshAsset.Succeeded()) {
        StaticMeshComp->SetStaticMesh(MeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Gem_D.M_Gem_D"));
    if (MaterialAsset.Succeeded()) {
        StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
    }*/

    // Tick 함수 활성화
    PrimaryActorTick.bCanEverTick = true;
    // 기본 회전 속도 (1초에 90도 회전)
    RotationSpeed = 90.f;

}

void AItem::BeginPlay() {
    Super::BeginPlay();

    // 위치, 회전, 스케일 설정하기
    // (300, 200, 100) 위치로 이동
    SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
    // Yaw 방향으로 45도 회전(y축, z축, x축)
    SetActorRotation(FRotator(0.0f, 45.0f, 0.0f));
    // 모든 축을 2배로 스케일
    SetActorScale3D(FVector(2.0f));

    // 블루프린트에서 구현한 함수를 C++에서 호출함
    OnItemPickedUp();
}

void AItem::Tick(float DeltaTime)
{
    // DeltaTime: 직전 프레임부터 현재 프레임까지 걸린 시간(초)
    Super::Tick(DeltaTime);

    // RotationSpeed가 0이 아니면 회전 처리(방어 코드)
    if (!FMath::IsNearlyZero(RotationSpeed)) {
        // 초당 RotationSpeed만큼, 한 프레임당 (RotationSpeed * DeltaTime)만큼 회전
        AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
    }
}

// BlueprintCallable 함수 구현
void AItem::ResetActorPosition()
{
    // (0, 0, 0) 위치로 되돌립니다.
    SetActorLocation(FVector::ZeroVector);
}

float AItem::GetRotationSpeed() const
{
    return RotationSpeed;
}
