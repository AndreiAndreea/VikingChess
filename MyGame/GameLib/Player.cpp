#include "Player.h"

Player::Player(bool attacker)
{
    this->attacker = attacker;
}

bool Player::isAttacker()
{
    return this->attacker;
}
