#ifndef ATUM_QUADRATURE_H_
#define ATUM_QUADRATURE_H_

#include <stdint.h>
#include <stddef.h>

typedef void (*QuadratureCallback)(int32_t currentPos, double velocity);

void quadrature_init();

void quadrature_register_callback(QuadratureCallback callback);

#endif

