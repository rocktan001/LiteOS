#ifndef FEATURES_H
#define FEATURES_H

#include "../../include/features.h"

#ifndef __LITEOS__
#define weak __attribute__((__weak__))
#endif
#define hidden __attribute__((__visibility__("hidden")))
#define weak_alias(old, new) \
	extern __typeof(old) new __attribute__((__weak__, __alias__(#old)))

#ifdef __LITEOS__
#define __strong_alias(alias, sym) \
    __asm__(".global " #alias "\n" \
            #alias " = " #sym);
#endif

#endif
