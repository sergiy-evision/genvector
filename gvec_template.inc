#include <assert.h>

#include "gvmacro.h"

#define __GV_GVEC_USE_VAL_RET *
#define __GV_GVEC_USE_REF_RET

/*
  __GVONCEFUNC is necessary to prevent multiple declarations if
  genvector.h was included more than once.
  __GVVECTYPE needed to prevent typedef redefinition with modular approach.
*/

#ifndef GVEC_MODULAR_APPROACH

  #if __STDC_VERSION__ < 199901L
    #define __GVONCEFUNC static
  #else
    #define __GVONCEFUNC static inline
  #endif

  #define __GVVECTYPE( gvTypename, gvVecName ) \
    typedef gvTypename* gvec_##gvVecName##_t

#else /* GVEC_MODULAR_APPROACH */

  #define __GVONCEFUNC
  #define __GVVECTYPE( gvTypename, gvVecName ) \
    __GV_REQUIRE_SEMICOLON_OUTDOOR

  #define GVEC_C_DEFINE GVEC_INSTANTIATE

  #define GVEC_H_DECLARE( gvTypename, gvVecName, gvPassBy, gvRetBy ) \
  \
    typedef gvTypename* gvec_##gvVecName##_t; \
  \
    extern gvec_##gvVecName##_t gvec_##gvVecName##_new( \
      size_t min_count ); \
    extern gvec_##gvVecName##_t gvec_##gvVecName##_assign( \
      gvec_##gvVecName##_t hgvec, size_t count, \
      const gvTypename gvPassBy value ); \
    extern gvec_##gvVecName##_t gvec_##gvVecName##_resize( \
      gvec_##gvVecName##_t hgvec, size_t new_count, \
      const gvTypename gvPassBy value ); \
    extern gvec_##gvVecName##_t gvec_##gvVecName##_insert( \
      gvec_##gvVecName##_t hgvec, size_t pos, size_t count, \
      const gvTypename gvPassBy value ); \
    extern gvec_##gvVecName##_t gvec_##gvVecName##_push( \
      gvec_##gvVecName##_t hgvec, const gvTypename gvPassBy value ); \
    extern gvTypename gvRetBy gvec_##gvVecName##_front( \
      gvec_##gvVecName##_t hgvec ); \
    extern gvTypename gvRetBy gvec_##gvVecName##_back( \
      gvec_##gvVecName##_t hgvec ); \
  \
  __GV_REQUIRE_SEMICOLON_OUTDOOR

#endif /* GVEC_MODULAR_APPROACH */

/******************************************************************************/

#define GVEC_INSTANTIATE( gvTypename, gvVecName, gvPassBy, gvRetBy ) \
\
  __GVVECTYPE( gvTypename, gvVecName ); \
/********************************************************************/ \
  __GVONCEFUNC gvec_##gvVecName##_t \
  gvec_##gvVecName##_new( \
    size_t min_count \
  ) { \
  { \
    return gvec_new( min_count, sizeof(gvTypename) ); \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvec_##gvVecName##_t \
  gvec_##gvVecName##_assign( \
    gvec_##gvVecName##_t hgvec, \
    size_t count, \
    const gvTypename gvPassBy value \
  ) { \
    size_t i; \
  { \
    hgvec = gvec_resize( hgvec, count ); \
    if (GVEC_NO_ERROR(hgvec)) { \
      for(i = 0; i < count; ++i) { \
        hgvec[i] = gvPassBy value; \
      } \
    } \
    return hgvec; \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvec_##gvVecName##_t \
  gvec_##gvVecName##_resize( \
    gvec_##gvVecName##_t hgvec, \
    size_t new_count, \
    const gvTypename gvPassBy value \
  ) { \
    size_t i; \
  { \
    assert( hgvec != NULL ); \
    i = gvec_count(hgvec); \
    hgvec = gvec_resize( hgvec, new_count ); \
    if (GVEC_NO_ERROR(hgvec)) { \
      for(; i < new_count; ++i) { \
        hgvec[i] = gvPassBy value; \
      } \
    } \
    return hgvec; \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvec_##gvVecName##_t \
  gvec_##gvVecName##_insert( \
    gvec_##gvVecName##_t hgvec, \
    size_t pos, \
    size_t count, \
    const gvTypename gvPassBy value \
  ) { \
    size_t i; \
  { \
    hgvec = gvec_insert( hgvec, pos, count ); \
    if (GVEC_NO_ERROR(hgvec)) { \
      for(i = 0; i < count; ++i) { \
        hgvec[i] = gvPassBy value; \
      } \
    } \
    return hgvec; \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvec_##gvVecName##_t \
  gvec_##gvVecName##_push( \
    gvec_##gvVecName##_t hgvec, \
    const gvTypename gvPassBy value \
  ) { \
  { \
    hgvec = gvec_push( hgvec ); \
    if (GVEC_NO_ERROR(hgvec)) { \
      hgvec[gvec_count(hgvec)-1] = gvPassBy value; \
    } \
    return hgvec; \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvTypename gvRetBy \
  gvec_##gvVecName##_front( \
    gvec_##gvVecName##_t hgvec \
  ) { \
  { \
    return __GV_##gvRetBy##_RET (gvTypename*) gvec_front( hgvec ); \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvTypename gvRetBy \
  gvec_##gvVecName##_back( \
    gvec_##gvVecName##_t hgvec \
  ) { \
  { \
    return __GV_##gvRetBy##_RET (gvTypename*) gvec_back( hgvec ); \
  }} \
/********************************************************************/ \
  __GV_REQUIRE_SEMICOLON_OUTDOOR