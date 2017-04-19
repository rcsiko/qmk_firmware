#define ONESHOT_TIMEOUT 3000
#define TAPPING_TERM 200
#define PREVENT_STUCK_MODIFIERS
#define LEADER_TIMEOUT 1000

#include "../../config.h"

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef DIODE_DIRECTION

#define MATRIX_ROW_PINS { F0,  F1,  F4,  F5,  F6 }
#define MATRIX_COL_PINS { F7,  B6,  B5,  B4,  D3,  D2,  D1,  D0,  B7,  B3,  B2,  B1,  B0 }

#define DIODE_DIRECTION COL2ROW
