// Fill out your copyright notice in the Description page of Project Settings.


#include "Melee_Wooden_Club.h"

AMelee_Wooden_Club::AMelee_Wooden_Club()
{
    // ���� �⺻���� 0���� ����
    MeleeDamage = 10;
    ItemType = "Melee";
}

void AMelee_Wooden_Club::ActivateItem(AActor* Activator)
{
    // �÷��̾� �±� Ȯ��
    if (Activator && Activator->ActorHasTag("Player"))
    {
        // ���� ȹ�� ����� �޽���
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Player gained %d points!"), MeleeDamage));
        if (UWorld* World = GetWorld())
        {

            //데미지 넣는곳
            /*if (ASpartaGameStateBase* GameState = World->GetGameState<ASpartaGameStateBase>())
            {
                GameState->AddScore(PointValue);
                GameState->OnCoinCollected();
            }*/
            //데미지 넣는곳
        }
        // �θ� Ŭ���� (BaseItem)�� ���ǵ� ������ �ı� �Լ� ȣ��
       
    }
}