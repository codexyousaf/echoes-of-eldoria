// src/shared/balance.h - balance numbers only. Owner: C. Everybody else only reads.
#pragma once
namespace balance {
    const int PLAYER_MAX_HP = 60;
    const int PLAYER_MIN_DMG = 4;    // base damage per attack, before the Iron Sword bonus
    const int PLAYER_MAX_DMG = 8;
    const int POTION_HEAL = 25;
    const int STREAM_HEAL = 15;      // fixed by the story
}