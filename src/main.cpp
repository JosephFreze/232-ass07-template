#include <stdio.h>

#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

// ============================================================
// Test Declarations — implemented in tests.cpp
// ============================================================

// PART 1: Shapes
void test_shape_areas(void);
void test_shape_names_through_base_pointer(void);
void test_shape_operator_less(void);
void test_shape_equal_area_not_less(void);

// PART 2: ShapeList
void test_list_add_and_length(void);
void test_list_add_null_guard(void);
void test_insertionSort_orders_by_area(void);
void test_insertionSort_empty_and_single(void);

// ============================================================
// Required by Unity Framework
// ============================================================
void setUp(void)    {}
void tearDown(void) {}

// ============================================================
// Main Test Runner
// ============================================================
int main(void)
{
    UNITY_BEGIN();

    // ========== PART 1 ==========
    RUN_TEST(test_shape_areas);
    RUN_TEST(test_shape_names_through_base_pointer);
    RUN_TEST(test_shape_operator_less);
    RUN_TEST(test_shape_equal_area_not_less);

    // ========== PART 2 ==========
    RUN_TEST(test_list_add_and_length);
    RUN_TEST(test_list_add_null_guard);
    RUN_TEST(test_insertionSort_orders_by_area);
    RUN_TEST(test_insertionSort_empty_and_single);

    int result = UNITY_END();
    return result;
}