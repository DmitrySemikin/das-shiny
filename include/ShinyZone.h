#ifndef SHINY_ZONE_H
#define SHINY_ZONE_H

#include "ShinyData.h"
#include <memory.h>

#if SHINY_IS_COMPILED == TRUE


/*---------------------------------------------------------------------------*/

#define SHINY_ZONE_STATE_HIDDEN			0
#define SHINY_ZONE_STATE_INITIALIZED	1
#define SHINY_ZONE_STATE_UPDATING		2


/*---------------------------------------------------------------------------*/

typedef struct _ShinyZone {
    struct _ShinyZone* next;
    int _state;
    const char* name;
    ShinyData data;
} ShinyZone;


/*---------------------------------------------------------------------------*/

SHINY_INLINE void ShinyZone_init(ShinyZone *self, ShinyZone* a_prev) {
    self->_state = SHINY_ZONE_STATE_INITIALIZED;
    a_prev->next = self;
}

SHINY_INLINE void ShinyZone_uninit(ShinyZone *self) {
    self->_state = SHINY_ZONE_STATE_HIDDEN;
    self->next = NULL;
}

SHINY_API void ShinyZone_preUpdateChain(ShinyZone *first);
SHINY_API void ShinyZone_updateChain(ShinyZone *first, float a_damping);
SHINY_API void ShinyZone_updateChainClean(ShinyZone *first);

SHINY_API void ShinyZone_resetChain(ShinyZone *first);

SHINY_API ShinyZone* ShinyZone_sortChain(ShinyZone **first);

SHINY_INLINE float ShinyZone_compare(ShinyZone *a, ShinyZone *b) {
    return a->data.selfTicks.avg - b->data.selfTicks.avg;
}

SHINY_API void ShinyZone_clear(ShinyZone* self);

SHINY_API void ShinyZone_enumerateZones(const ShinyZone* a_zone, void (*a_func)(const ShinyZone*));

#if __cplusplus
} /* end of extern "C" */

template <class T>
void ShinyZone_enumerateZones(const ShinyZone* a_zone, T* a_this, void (T::*a_func)(const ShinyZone*)) {
    (a_this->*a_func)(a_zone);

    if (a_zone->next) ShinyZone_enumerateZones(a_zone->next, a_this, a_func);
}

extern "C" { /* end of c++ */
#endif

#endif /* if SHINY_IS_COMPILED == TRUE */

#endif /* SHINY_ZONE_H */