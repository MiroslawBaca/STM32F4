/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2001       Anil Kumar
 *  Copyright (C) 2004-2006  Anil Kumar, Jerry St.Clair
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 *  ASSERT Macro definitions and general CUnit configuration definitions.
 *
 *  09/Aug/2001   ASSERT definitions. (AK)
 *
 *  12/Mar/2003   New Assert definitions. (AK)
 *
 *  27/Jul/2003   Modified ASSERT_XXX Macro definitions. (AK)
 *
 *  15-Jul-2004   New interface, changed action on assert failure to not
 *                return, provided _FATAL versions of assertions to return
 *                from test function on failure. (JDS)
 *
 *  01-Sep-2004   Modified assertions for setjmp/longjmp mechanism of 
 *                aborting test runs, added CU_FAIL and CU_PASS macros. (JDS)
 *
 *  07-May-2005   Added CU_ prefix to remaining CUnit defines (BOOL, TRUE, 
 *                FALSE, MAX_...).  Added CU_UNREFERENCED_PARAMETER() define. (JDS)
 */

/** @file
 * Basic CUnit include file for user and system code.
 * Defines macros for assertions for use in user test cases.
 * Basic system macro definitions also appear here.
 */
/** @addtogroup Framework
 * @{
 */

#ifndef CUNIT_CUNIT_H_SEEN
#define CUNIT_CUNIT_H_SEEN

#include <string.h>
#include <math.h>

/** CUnit version number. */
#define CU_VERSION "3.5.2"

/*  Max string lengths for names (includes terminating NULL. */
/** Maximum length of a test name string. */
#define CU_MAX_TEST_NAME_LENGTH 256
/** Maximim length of a suite name string. */
#define CU_MAX_SUITE_NAME_LENGTH 256

/* Global type Definitions to be used for boolean operators. */
#ifndef CU_BOOL
  /** Boolean type for CUnit use. */
  #define CU_BOOL int
#endif

#ifndef CU_TRUE
  /** Boolean TRUE for CUnit use. */
  #define CU_TRUE 1
#endif

#ifndef CU_FALSE
  /** Boolean FALSE for CUnit use. */
  #define CU_FALSE 0
#endif

#ifndef CU_UNREFERENCED_PARAMETER
  /** Consistent approach to referencing unused parameters. */
  #define CU_UNREFERENCED_PARAMETER(x) (void)x
#endif

#ifndef CU_MAX
#  define CU_MAX(a,b) (((a) >= (b)) ? (a) : (b))
#endif

#ifndef CU_MIN
#  define CU_MIN(a,b) (((a) >= (b)) ? (b) : (a))
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__)
#  ifdef CU_DLL
#    ifdef CU_BUILD_DLL
#      define CU_EXPORT __declspec(dllexport)
#    else
#      define CU_EXPORT __declspec(dllimport)
#    endif
#  else
#    define CU_EXPORT
#  endif
#  if _MSC_VER < 1900
#    define snprintf _snprintf
#  endif
#else
#  define CU_EXPORT
#endif  /* WIN32 */

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#  define CU_FUNC __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#  define CU_FUNC __func__
#else
#  define CU_FUNC ""
#endif

#include "CUnit/CUError.h"
#include "CUnit/TestDB.h"   /* not needed here - included for user convenience */
#include "CUnit/TestRun.h"  /* not needed here - include (after BOOL define) for user convenience */
#include "CUnit/CUAssert.h"

/** Record a pass condition without performing a logical test. */
#define CU_PASS(msg) \
  { CU_assertImplementation(CU_TRUE, __LINE__, ("CU_PASS(" #msg ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Simple assertion.
 *  Reports failure with no other action.
 */
#define CU_ASSERT(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, CU_FUNC, CU_FALSE); }

/** Simple assertion.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_FATAL(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, CU_FUNC, CU_TRUE); }

/** Simple assertion.
 *  Reports failure with no other action.
 */
#define CU_TEST(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, CU_FUNC, CU_FALSE); }

/** Simple assertion.
 *  Reports failure and causes test to abort.
 */
#define CU_TEST_FATAL(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, CU_FUNC, CU_TRUE); }

/** Record a failure without performing a logical test. */
#define CU_FAIL(msg) \
  { CU_assertImplementation(CU_FALSE, __LINE__, ("CU_FAIL(" #msg ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Record a failure without performing a logical test, and abort test. */
#define CU_FAIL_FATAL(msg) \
  { CU_assertImplementation(CU_FALSE, __LINE__, ("CU_FAIL_FATAL(" #msg ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that value is CU_TRUE.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_TRUE(value) \
  { CU_assertImplementation((value), __LINE__, ("CU_ASSERT_TRUE(" #value ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that value is CU_TRUE.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_TRUE_FATAL(value) \
  { CU_assertImplementation((value), __LINE__, ("CU_ASSERT_TRUE_FATAL(" #value ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that value is CU_FALSE.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_FALSE(value) \
  { CU_assertImplementation(!(value), __LINE__, ("CU_ASSERT_FALSE(" #value ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that value is CU_FALSE.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_FALSE_FATAL(value) \
  { CU_assertImplementation(!(value), __LINE__, ("CU_ASSERT_FALSE_FATAL(" #value ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that actual == expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_EQUAL(actual, expected) \
  { CU_assertImplementation(((actual) == (expected)), __LINE__, ("CU_ASSERT_EQUAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that actual == expected.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((actual) == (expected)), __LINE__, ("CU_ASSERT_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that actual != expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_NOT_EQUAL(actual, expected) \
  { CU_assertImplementation(((actual) != (expected)), __LINE__, ("CU_ASSERT_NOT_EQUAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that actual != expected.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_NOT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((actual) != (expected)), __LINE__, ("CU_ASSERT_NOT_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that pointers actual == expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_PTR_EQUAL(actual, expected) \
  { CU_assertImplementation(((const void*)(actual) == (const void*)(expected)), __LINE__, ("CU_ASSERT_PTR_EQUAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that pointers actual == expected.
 * Reports failure and causes test to abort.
 */
#define CU_ASSERT_PTR_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((const void*)(actual) == (const void*)(expected)), __LINE__, ("CU_ASSERT_PTR_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that pointers actual != expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_PTR_NOT_EQUAL(actual, expected) \
  { CU_assertImplementation(((const void*)(actual) != (const void*)(expected)), __LINE__, ("CU_ASSERT_PTR_NOT_EQUAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that pointers actual != expected.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_PTR_NOT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((const void*)(actual) != (const void*)(expected)), __LINE__, ("CU_ASSERT_PTR_NOT_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that pointer value is NULL.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_PTR_NULL(value) \
  { CU_assertImplementation((NULL == (const void*)(value)), __LINE__, ("CU_ASSERT_PTR_NULL(" #value")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that pointer value is NULL.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_PTR_NULL_FATAL(value) \
  { CU_assertImplementation((NULL == (const void*)(value)), __LINE__, ("CU_ASSERT_PTR_NULL_FATAL(" #value")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that pointer value is not NULL.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_PTR_NOT_NULL(value) \
  { CU_assertImplementation((NULL != (const void*)(value)), __LINE__, ("CU_ASSERT_PTR_NOT_NULL(" #value")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that pointer value is not NULL.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_PTR_NOT_NULL_FATAL(value) \
  { CU_assertImplementation((NULL != (const void*)(value)), __LINE__, ("CU_ASSERT_PTR_NOT_NULL_FATAL(" #value")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that string actual == expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_STRING_EQUAL(actual, expected) \
  { CU_assertImplementation(!(strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_EQUAL(" #actual ","  #expected ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that string actual == expected.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_STRING_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(!(strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_EQUAL_FATAL(" #actual ","  #expected ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that string actual != expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_STRING_NOT_EQUAL(actual, expected) \
  { CU_assertImplementation((strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_NOT_EQUAL(" #actual ","  #expected ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that string actual != expected.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_STRING_NOT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation((strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_NOT_EQUAL_FATAL(" #actual ","  #expected ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that string actual == expected with length specified.
 *  The comparison is limited to count characters.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_NSTRING_EQUAL(actual, expected, count) \
  { CU_assertImplementation(!(strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_EQUAL(" #actual ","  #expected "," #count ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that string actual == expected with length specified.
 *  The comparison is limited to count characters.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_NSTRING_EQUAL_FATAL(actual, expected, count) \
  { CU_assertImplementation(!(strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_EQUAL_FATAL(" #actual ","  #expected "," #count ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that string actual != expected with length specified.
 *  The comparison is limited to count characters.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_NSTRING_NOT_EQUAL(actual, expected, count) \
  { CU_assertImplementation((strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_NOT_EQUAL(" #actual ","  #expected "," #count ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that string actual != expected with length specified.
 *  The comparison is limited to count characters.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_NSTRING_NOT_EQUAL_FATAL(actual, expected, count) \
  { CU_assertImplementation((strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_NOT_EQUAL_FATAL(" #actual ","  #expected "," #count ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that double actual == expected within the specified tolerance.
 *  If actual is within granularity of expected, the assertion passes.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_DOUBLE_EQUAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) <= fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_EQUAL(" #actual ","  #expected "," #granularity ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that double actual == expected within the specified tolerance.
 *  If actual is within granularity of expected, the assertion passes.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_DOUBLE_EQUAL_FATAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) <= fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_EQUAL_FATAL(" #actual ","  #expected "," #granularity ")"), __FILE__, CU_FUNC, CU_TRUE); }

/** Asserts that double actual != expected within the specified tolerance.
 *  If actual is within granularity of expected, the assertion fails.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_DOUBLE_NOT_EQUAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) > fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_NOT_EQUAL(" #actual ","  #expected "," #granularity ")"), __FILE__, CU_FUNC, CU_FALSE); }

/** Asserts that double actual != expected within the specified tolerance.
 *  If actual is within granularity of expected, the assertion fails.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_DOUBLE_NOT_EQUAL_FATAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) > fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_NOT_EQUAL_FATAL(" #actual ","  #expected "," #granularity ")"), __FILE__, CU_FUNC, CU_TRUE); }

#ifdef USE_DEPRECATED_CUNIT_NAMES

#ifndef BOOL
  /** Deprecated (version 2.0-2). @deprecated Use CU_BOOL. */
  #define BOOL int
#endif

#ifndef TRUE
  /** Deprecated (version 2.0-2). @deprecated Use CU_TRUE. */
  #define TRUE 1
#endif

#ifndef FALSE
  /** Deprecated (version 2.0-2). @deprecated Use CU_FALSE. */
  #define FALSE	0
#endif

/** Deprecated (version 2.0-2). @deprecated Use CU_MAX_TEST_NAME_LENGTH. */
#define MAX_TEST_NAME_LENGTH	256
/** Deprecated (version 2.0-2). @deprecated Use CU_MAX_SUITE_NAME_LENGTH. */
#define MAX_SUITE_NAME_LENGTH	256

/** Deprecated (version 1). @deprecated Use CU_ASSERT_FATAL. */
#define ASSERT(value) { if (FALSE == (int)(value)) { CU_assertImplementation((BOOL)value, __LINE__, #value, __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_TRUE_FATAL. */
#define ASSERT_TRUE(value) { if (FALSE == (value)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_TRUE(" #value ")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_FALSE_FATAL. */
#define ASSERT_FALSE(value) { if (FALSE != (value)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_FALSE(" #value ")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_EQUAL_FATAL. */
#define ASSERT_EQUAL(actual, expected) { if ((actual) != (expected)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_EQUAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_NOT_EQUAL_FATAL. */
#define ASSERT_NOT_EQUAL(actual, expected) { if ((void*)(actual) == (void*)(expected)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_NOT_EQUAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_PTR_EQUAL_FATAL. */
#define ASSERT_PTR_EQUAL(actual, expected) { if ((void*)(actual) != (void*)(expected)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_PTR_EQUAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_PTR_NOT_EQUAL_FATAL. */
#define ASSERT_PTR_NOT_EQUAL(actual, expected) { if ((void*)(actual) == (void*)(expected)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_PTR_NOT_EQUAL(" #actual "," #expected ")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_PTR_NULL_FATAL. */
#define ASSERT_PTR_NULL(value)  { if (NULL != (void*)(value)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_PTR_NULL(" #value")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_PTR_NOT_NULL_FATAL. */
#define ASSERT_PTR_NOT_NULL(value) { if (NULL == (void*)(value)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_PTR_NOT_NULL(" #value")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_STRING_EQUAL_FATAL. */
#define ASSERT_STRING_EQUAL(actual, expected) { if (strcmp((const char*)actual, (const char*)expected)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_STRING_EQUAL(" #actual ","  #expected ")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_STRING_NOT_EQUAL_FATAL. */
#define ASSERT_STRING_NOT_EQUAL(actual, expected) { if (!strcmp((const char*)actual, (const char*)expected)) { CU_assertImplementation(TRUE, __LINE__, ("ASSERT_STRING_NOT_EQUAL(" #actual ","  #expected ")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_NSTRING_EQUAL_FATAL. */
#define ASSERT_NSTRING_EQUAL(actual, expected, count) { if (strncmp((const char*)actual, (const char*)expected, (size_t)count)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_NSTRING_EQUAL(" #actual ","  #expected "," #count ")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_NSTRING_NOT_EQUAL_FATAL. */
#define ASSERT_NSTRING_NOT_EQUAL(actual, expected, count) { if (!strncmp((const char*)actual, (const char*)expected, (size_t)count)) { CU_assertImplementation(TRUE, __LINE__, ("ASSERT_NSTRING_NOT_EQUAL(" #actual ","  #expected "," #count ")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_DOUBLE_EQUAL_FATAL. */
#define ASSERT_DOUBLE_EQUAL(actual, expected, granularity) { if ((fabs((double)actual - expected) > fabs((double)granularity))) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_DOUBLE_EQUAL(" #actual ","  #expected "," #granularity ")"), __FILE__, CU_FUNC, FALSE); return; }}
/** Deprecated (version 1). @deprecated Use CU_ASSERT_DOUBLE_NOT_EQUAL_FATAL. */
#define ASSERT_DOUBLE_NOT_EQUAL(actual, expected, granularity) { if ((fabs((double)actual - expected) <= fabs((double)granularity))) { CU_assertImplementation(TRUE, __LINE__, ("ASSERT_DOUBLE_NOT_EQUAL(" #actual ","  #expected "," #granularity ")"), __FILE__, CU_FUNC, FALSE); return; }}
#endif  /* USE_DEPRECATED_CUNIT_NAMES */

#endif  /*  CUNIT_CUNIT_H_SEEN  */

/** @} */
