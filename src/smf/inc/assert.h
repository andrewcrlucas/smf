/*
 * assert.h
 *
 *  Description:  Provides assert functionality
 *
 */

#ifndef ASSERT_H
#define ASSERT_H

#ifdef NO_ASSERT             /* NO_ASSERT defined-assertion checking disabled */

    #define DEFINE_THIS_FILE
    #define ASSERT(test_)
    #define ERROR()
#else                    /* NO_ASSERT not defined-assertion checking enabled */

/* callback invoked in case the condition passed to assertion fails */
void on_assert(char const * const file, int line);
void assert_init(void);

// The macro DEFINE_THIS_FILE defines a static and constant string
// g_this_file[] as the name of the source file provided in the standard
// macro __FILE__. You need to place the DEFINE_THIS_FILE macro at the
// top of every .C file.
    #define DEFINE_THIS_FILE \
    static char const g_this_file[] = __FILE__;

// general purpose assertion
    #define ASSERT(test_) \
    if (test_)            \
    {                     \
        ;                 \
    }                     \
    else (on_assert(g_this_file, __LINE__))

// assertion that always fails
    #define ERROR() \
    (on_assert(g_this_file, __LINE__))

#endif /* NO_ASSERT */

// see http://www.drdobbs.com/184401873 for a description of this ASSERT_STATIC
// macro if an assertion fails it will generate a compiler warning about a
// divide by 0 error

#if 1
// compile-time assertion
    #define ASSERT_STATIC(e)                \
    do                                      \
    {                                       \
        enum { ASSERT_STATIC__ = 1 / (e) }; \
    } while (0)
#else
// if an assertion fails it will generate a compiler warning about a an
// invalid array size
    #define ASSERT_STATIC(e) \
    { char assert_static__[(e) ? 1 : -1] }

// From state machine book
    #define ASSERT_STATIC(test_) \
    extern char assert_compile [(test_)]
#endif

#endif
