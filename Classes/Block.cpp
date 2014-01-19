#include "Block.h"

Block::Block()
{
    this->life = 0;
}

Block::~Block()
{
}

void Block::setLife(int life)
{
    this->life = life;
}

int Block::getLife()
{
    return this->life;
}

void Block::hit()
{
    if (this->isDead()) {
        return;
    }
    this->life--;

    // Spriteの画像をlife残量に応じて変更する
}

bool Block::isDead()
{
    if (this->life == 0) {
        return true;
    }
    return false;
}

void Block::explode()
{
    // 爆発エフェクトを表示する
    // 効果音を出す
}
