#ifndef UTILS_H
#define UTILS_H

typedef struct {
  float xvel;
  float yvel;
} velocity_t;

#define GRAVITY (0.15f)
#define PLAYER_SPEED (5.0f)
#define DASH_COOLDOWN (100)
#define DASH_LENGTH (20)
#define DASH_SPEED (20)
#define MAX_SPEED (1.0f)
#define JUMP_SPEED (-3.0f)
#endif
