// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "coroutine"

Ship::Ship(Game* game)
	:Actor(game)
	,mLaserCooldown(0.0f)
	,mBulletDerayTime(0.0f)
	,mBurstCount(0)
	,mIsBursting(false)
    ,mBurstCooldown(0.0f)
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	// Create an input component and set keys/speed
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);
}

void Ship::UpdateActor(float deltaTime)
{
    if (!mIsBursting)
    {
        mLaserCooldown -= deltaTime;
    }

    // バーストモード中ならクールダウンを更新
    if (mIsBursting)
    {
        mBurstCooldown -= deltaTime;
    }
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		/*
		for (int count = 0; count < 3; count++)
		{
			// Create a laser and set its position/rotation to mine
			Laser* laser = new Laser(GetGame());
			laser->SetPosition(GetPosition());
			laser->SetRotation(GetRotation());
		}
		// Reset laser cooldown (half second)
		mLaserCooldown = 0.5f;
		*/
        if (mBurstCount < 3)
        {
            // バーストモード中でない場合、バーストモードを開始
            if (!mIsBursting)
            {
                mIsBursting = true;
                mBurstCount = 3; // バーストショットの残弾数を設定
                mBurstCooldown = 1.0f; // バースト間のクールダウン時間を設定
            }

            // レーザーを発射し、残弾数を減少
            Laser* laser = new Laser(GetGame());
            laser->SetPosition(GetPosition());
            laser->SetRotation(GetRotation());
            mBurstCount--;

            // バーストショットをすべて撃った場合、バーストモードを終了
            if (mBurstCount == 0)
            {
                mIsBursting = false;
                // レーザー発射後のクールダウンを設定
                mLaserCooldown = 0.2f; // 連射の間隔
            }
        }

        else if (!mIsBursting && mBurstCooldown <= 0.0f)
        {
            // バーストモード中でなく、クールダウンが終了したら新たなバーストを開始
            mIsBursting = true;
            mBurstCount = 3;
            mBurstCooldown = 1.0f;
        }   
	}
}
