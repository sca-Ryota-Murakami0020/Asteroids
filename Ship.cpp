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

    // �o�[�X�g���[�h���Ȃ�N�[���_�E�����X�V
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
            // �o�[�X�g���[�h���łȂ��ꍇ�A�o�[�X�g���[�h���J�n
            if (!mIsBursting)
            {
                mIsBursting = true;
                mBurstCount = 3; // �o�[�X�g�V���b�g�̎c�e����ݒ�
                mBurstCooldown = 1.0f; // �o�[�X�g�Ԃ̃N�[���_�E�����Ԃ�ݒ�
            }

            // ���[�U�[�𔭎˂��A�c�e��������
            Laser* laser = new Laser(GetGame());
            laser->SetPosition(GetPosition());
            laser->SetRotation(GetRotation());
            mBurstCount--;

            // �o�[�X�g�V���b�g�����ׂČ������ꍇ�A�o�[�X�g���[�h���I��
            if (mBurstCount == 0)
            {
                mIsBursting = false;
                // ���[�U�[���ˌ�̃N�[���_�E����ݒ�
                mLaserCooldown = 0.2f; // �A�˂̊Ԋu
            }
        }

        else if (!mIsBursting && mBurstCooldown <= 0.0f)
        {
            // �o�[�X�g���[�h���łȂ��A�N�[���_�E�����I��������V���ȃo�[�X�g���J�n
            mIsBursting = true;
            mBurstCount = 3;
            mBurstCooldown = 1.0f;
        }   
	}
}
