#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <cmath>
#include <iostream>
#include <numbers>

// ============================================================
// PART 1 Tests: Shapes
// ============================================================

/// Create Circle(1), Square(2), Rectangle(2, 3).
/// Verify area() is pi, 4 and 6 (compare doubles with std::fabs(a - b) < 1e-9).
void test_shape_areas(void)
{
    Circle circle(1);
    Square square(2);
    Rectangle rectangle(2, 3);

    TEST_ASSERT_TRUE(std::fabs(circle.area() - std::numbers::pi) < 1e-9);
    TEST_ASSERT_TRUE(std::fabs(square.area() - 4.0) < 1e-9);
    TEST_ASSERT_TRUE(std::fabs(rectangle.area() - 6.0) < 1e-9);
}

/// Create an array of three Shape* (a Circle, a Square, a Rectangle) with new.
/// Verify name() through the BASE pointer gives "Circle", "Square", "Rectangle".
/// Delete the shapes through the base pointers.
void test_shape_names_through_base_pointer(void)
{
    Shape* shapes[] = {new Circle(1), new Square(2), new Rectangle(2, 3)};

    TEST_ASSERT_EQUAL_STRING("Circle", shapes[0]->name().c_str());
    TEST_ASSERT_EQUAL_STRING("Square", shapes[1]->name().c_str());
    TEST_ASSERT_EQUAL_STRING("Rectangle", shapes[2]->name().c_str());

    for (Shape* shapePtr : shapes)
    {
        delete shapePtr;
    }
}

/// Create Square(1) and Square(2). Take two const Shape& to them.
/// Verify small < big is true, big < small is false, small < small is false.
void test_shape_operator_less(void)
{
    Square smallSquare(1);
    Square bigSquare(2);

    const Shape& small = smallSquare;
    const Shape& big = bigSquare;

    TEST_ASSERT_TRUE(small < big);
    TEST_ASSERT_FALSE(big < small);
    TEST_ASSERT_FALSE(small < small);
}

/// Create Square(2) and Rectangle(1, 4): both have area 4.
/// Verify that NEITHER a < b NOR b < a is true.
void test_shape_equal_area_not_less(void)
{
    Square square(2);
    Rectangle rectangle(1, 4);

    TEST_ASSERT_FALSE(square < rectangle);
    TEST_ASSERT_FALSE(rectangle < square);
}

// ============================================================
// PART 2 Tests: ShapeList
// ============================================================

/// Create a ShapeList. Add new Circle(1) and new Square(2) with addShape.
/// Verify both calls return 0 and length() is 2.
/// (Do NOT delete the shapes yourself: the list owns them.)
void test_list_add_and_length(void)
{
    ShapeList list;

    TEST_ASSERT_EQUAL_INT(0, list.addShape(new Circle(1)));
    TEST_ASSERT_EQUAL_INT(0, list.addShape(new Square(2)));
    TEST_ASSERT_EQUAL_INT(2, list.length());
}

/// Create a ShapeList. Call addShape(nullptr).
/// Verify it returns -1 and length() stays 0.
void test_list_add_null_guard(void)
{
    ShapeList list;

    TEST_ASSERT_EQUAL_INT(-1, list.addShape(nullptr));
    TEST_ASSERT_EQUAL_INT(0, list.length());
}

/// Add Rectangle(2, 5) (area 10), Circle(1) (area 3.14), Square(2) (area 4).
/// Call insertionSort(). Verify nameAt(0), nameAt(1), nameAt(2) are
/// "Circle", "Square", "Rectangle" and isSorted() is true.
void test_insertionSort_orders_by_area(void)
{
    ShapeList list;
    list.addShape(new Rectangle(2, 5));
    list.addShape(new Circle(1));
    list.addShape(new Square(2));

    list.insertionSort();

    TEST_ASSERT_TRUE(list.nameAt(0) == "Circle");
    TEST_ASSERT_TRUE(list.nameAt(1) == "Square");
    TEST_ASSERT_TRUE(list.nameAt(2) == "Rectangle");
    TEST_ASSERT_TRUE(list.isSorted());
}

/// Call insertionSort() on an EMPTY list: no crash, length() is 0.
/// Then add ONE shape and sort again: length() is 1 and nameAt(0) is unchanged.
void test_insertionSort_empty_and_single(void)
{
    ShapeList list;

    list.insertionSort();
    TEST_ASSERT_EQUAL_INT(0, list.length());

    list.addShape(new Circle(1));
    list.insertionSort();

    TEST_ASSERT_EQUAL_INT(1, list.length());
    TEST_ASSERT_TRUE(list.nameAt(0) == "Circle");
}