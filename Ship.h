// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
class Ship : public Actor
{
public:
	Ship(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
	void CountDerayTime();

private:
	float mLaserCooldown;
	//玉の発射間隔
	float mBulletDerayTime;
	int mBurstCount;        // バーストショットの残弾数
	bool mIsBursting;       // バーストモード中かどうかのフラグ
	float mBurstCooldown;   // バースト間のクールダウン時間
};