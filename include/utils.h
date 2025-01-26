#ifndef UTILS_H
#define UTILS_H

typedef struct {
  float xvel;
  float yvel;
} velocity_t;

#define GRAVITY (-0.25f)
#define PLAYER_SPEED (0.25f)
#define DASH_COOLDOWN (100)
#define DASH_LENGTH (20)
#define DASH_SPEED (20)

#endif
