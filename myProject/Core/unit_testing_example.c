/*
 * unit_testing_example.c
 *
 *  Created on: Mar 18, 2025
 *      Author: admin
 */

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "word_utilities.h"

void TEST_CASE_1(void) {
    // test using standard CUnit assert macro
    CU_ASSERT(7 == GetLongestWordLen("What is the longest word?"));

    CU_ASSERT(0 == GetLongestWordLen(""));

    CU_ASSERT(6 == GetLongestWordLen("Co sie dzieje hmm?!!!"));

    CU_ASSERT(6 == GetLongestWordLen("test	owane slowka"));

    CU_ASSERT(6 == GetLongestWordLen("test\rowane slowka"));

    CU_ASSERT(6 == GetLongestWordLen("test(owane slowka"));

    CU_ASSERT(6 == GetLongestWordLen("test+owane slowka"));

    CU_ASSERT(6 == GetLongestWordLen("jakie,to slowka"));
    char* testNull = NULL;
    CU_ASSERT(0 == GetLongestWordLen(testNull));


}




void unit_testing_example(void) {
    CU_pSuite myTestSuite;
    // initialize CUnit
    CU_initialize_registry();
    // create new test suite
    myTestSuite = CU_add_suite("my test suite", NULL, NULL);
    // add test to test suite
    CU_add_test(myTestSuite, "simple test case", TEST_CASE_1);

    // set verbose mode
    CU_basic_set_mode(CU_BRM_VERBOSE);
    // run all tests
    CU_basic_run_tests();
    // print results
    CU_basic_show_failures(CU_get_failure_list());
    // deinitialize CUnit
    CU_cleanup_registry();
}
