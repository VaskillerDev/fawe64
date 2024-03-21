#pragma once

// sys
typedef struct Sprite Sprite;
typedef struct Timer Timer;
typedef struct BoundingVolume BoundingVolume;
typedef struct ImagePool ImagePool;

// in-game menu
typedef struct MenuState MenuState;
typedef enum MenuOptionType MenuOptionType;
typedef struct GameState GameState;

// in-game core
typedef struct Hp Hp;
typedef struct Player Player;
typedef struct Sword Sword;
typedef struct Level Level;
typedef enum ChunkMovingDirection ChunkMovingDirection;
typedef struct Enemy Enemy;
typedef struct EnemyUnit EnemyUnit;
typedef struct UnitMetaData UnitMetaData;
typedef enum EnemyTypeName EnemyTypeName;
typedef struct EnemyUnitNewArgs EnemyUnitNewArgs;
typedef enum EnemyAttackTypeName EnemyAttackTypeName;

typedef enum PlayerMovementDirection PlayerMovementDirection;
typedef enum PlayerActionState PlayerActionState;
typedef struct PlayerInitInstanceArgs PlayerInitInstanceArgs;

// events
typedef struct EventEmitter EventEmitter;
typedef enum EventName EventName;
typedef struct EventKeyValue EventKeyValue;

typedef struct CurrentOptionChangedEvent CurrentOptionChangedEvent;
typedef struct HpPointsChangedEvent HpPointsChangedEvent;
typedef struct HpPointsOverEvent HpPointsOverEvent;
typedef struct HpPointsFilledEvent HpPointsFilledEvent;
typedef struct EnemyActionStateChangedEvent EnemyActionStateChangedEvent;
typedef struct EnemySwordAttackHitEvent EnemySwordAttackHitEvent;
typedef struct PlayerAttackAnimationTimeoutEvent PlayerAttackAnimationTimeoutEvent;
typedef struct PlayerLevelChunkMovedEvent PlayerLevelChunkMovedEvent;
typedef struct EnemyAttackBulletEvent EnemyAttackBulletEvent;
typedef struct LevelEnemyAttackBulletEvent LevelEnemyAttackBulletEvent;
typedef struct LevelBorderContactEvent LevelBorderContactEvent;
typedef struct PlayerHasGotBulletCollisionEvent PlayerHasGotBulletCollisionEvent;
typedef struct TimerExpiredEvent TimerExpiredEvent;
typedef struct BoundingVolumeCollidedEvent BoundingVolumeCollidedEvent;
typedef struct PlayerEnterDungeonEvent PlayerEnterDungeonEvent;
typedef struct EnemyHasGotBulletCollisionEvent EnemyHasGotBulletCollisionEvent;