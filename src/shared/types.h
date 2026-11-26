// src/shared/types.h - shared types, frozen on Day 1. Owner: D
#pragma once
#include <string>
using std::string;

// ---------- plain data ----------
struct Item { string name; string type; int value; };                     // type: weapon, potion, key
struct Quest { int id; string title; };
struct CodexEntry { string name; string kind; string description; };     // kind: item or monster

// ---------- ids everybody agrees on ----------
enum QuestId { QUEST_MAIN = 1, QUEST_WEAPON = 2, QUEST_FORTRESS = 3 };
enum EnemyId { ENEMY_NONE = -1, ENEMY_WOLF = 0, ENEMY_TROLL = 1, ENEMY_WARDEN = 2 };
enum GameState { STORY, BATTLE, ENDING, GAME_OVER };

// ---------- one-time scene effects ----------
enum EffectType { EFF_GIVE_ITEM, EFF_HEAL, EFF_START_QUEST, EFF_COMPLETE_QUEST, EFF_DISCOVER };
struct Effect {
    EffectType type = EFF_HEAL;
    string name;     // EFF_GIVE_ITEM: item name | EFF_DISCOVER: codex entry name
    int value = 0;   // EFF_HEAL: hp | EFF_START_QUEST, EFF_COMPLETE_QUEST: quest id
};

// ---------- story tree node ----------
struct SceneNode;
struct Choice {
    string label;
    SceneNode* next = nullptr;
    bool needsMoonKey = false;
};
struct SceneNode {
    int id;                    // scene number 1..11, the SAME id for every copy of a scene
    string title, text;
    Choice choices[3];         // max 3 children
    int choiceCount;
    int enemyId;               // ENEMY_NONE if no battle in this scene
    bool isEnding;
    Effect effects[3];         // applied once per scene id
    int effectCount;

    inline static int liveNodes = 0;   // leak check: must be 0 after the tree is deleted
    SceneNode() : id(0), choiceCount(0), enemyId(ENEMY_NONE), isEnding(false), effectCount(0) { ++liveNodes; }
    ~SceneNode() { --liveNodes; }
    SceneNode(const SceneNode&) = delete;             // always create with new, never copy
    SceneNode& operator=(const SceneNode&) = delete;
};