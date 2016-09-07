/*
File: Debug.h
Description:
   Debug Macros are defined here
Date: Sep 4 2016
Author: Lixing Zhang
*/

#ifndef __DEBUG_H__
#define __DEBUG_H__
#define VOID_RETURN
#ifndef DEBUG
#define assert_or_return(expr, ret) do { \
     if (!(expr)) { \
            printf("Assertion %s in %s(%d) failed\n", #expr, __FILE__, __LINE__); \
            return ret; \
          } \
} while(0)
#else
#define assert_or_return(expr) do { \
     if (!(expr)) { \
            fprintf(stderr, "Assertion %s in %s(%d) failed\n", #expr, __FILE__, __LINE__); \
            abort(); \
          } \
} while(0)
#endif

#endif /*__DEBUG_H__*/
