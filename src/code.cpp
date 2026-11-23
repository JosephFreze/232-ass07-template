// ============================================================
// CSCI 232 Assignment 07 – Shapes, Polymorphism and Insertion Sort
// Student Implementation
// ============================================================

#include "code.hpp"
#include <iostream>
#include <iterator>
#include <numbers>

// Uncomment the author block below and fill in your name:

std::string AUTHOR_NAME       = "Joseph Freze";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this "
"assignment independently, except where explicitly noted and referenced. "
"Any collaboration or use of external resources has been properly cited. "
"I am fully aware of the consequences of academic dishonesty and agree "
"to abide by the university's academic integrity policy.";

// ============================================================
// PART 1: Shape, Circle, Square, Rectangle
// ============================================================

/// True if THIS shape has a strictly smaller area() than other.
bool Shape::operator<(const Shape &other) const
{
    return area() < other.area();
}

/// Constructor with a member initializer list.
Circle::Circle(double newRadius)
    : radius{newRadius}
{
    // TODO: move the initialization of 'radius' into an initializer list
}

/// pi * radius * radius, use std::numbers::pi
double Circle::area() const
{
    return std::numbers::pi * radius * radius;
}

/// Return exactly "Circle".
std::string Circle::name() const
{
    // TODO: implement
    return "Circle";
}

Square::Square(double newSide)
    : side{newSide}
{
    // TODO: initializer list
}

/// side * side
double Square::area() const
{
    return side * side;
}

/// Return exactly "Square".
std::string Square::name() const
{
    // TODO: implement
    return "Square";
}

Rectangle::Rectangle(double newWidth, double newHeight)
    : width{newWidth}, height{newHeight}
{
    // TODO: initializer list
}

/// width * height
double Rectangle::area() const
{
    // TODO: implement
    return width * height;
}

/// Return exactly "Rectangle".
std::string Rectangle::name() const
{
    // TODO: implement
    return "Rectangle";
}

// ============================================================
// PART 2: ShapeList
// ============================================================

/// RAII: delete EVERY shape, then clear the list.
ShapeList::~ShapeList()
{
    for (Shape *shapePtr : data)
    {
        delete shapePtr;
    }

    data.clear();
}

/// Append at the end. Return -1 if newShapePtr is nullptr, 0 on success.
int ShapeList::addShape(Shape *newShapePtr)
{
    if (newShapePtr == nullptr)
    {
        return -1;
    }

    data.push_back(newShapePtr);
    
    return 0;
}

/// Delete the first shape and remove it from the list.
/// Return false if the list is empty, true otherwise.
bool ShapeList::removeFirst()
{
    if (data.empty())
    {
        return false;
    }

    delete data.front();

    data.pop_front();

    return true;
}

/// Number of shapes in the list.
int ShapeList::length() const
{
    return data.size();
}

/// Sum of area() of all shapes (0.0 if empty).
double ShapeList::totalArea() const
{
    if (data.size() == 0)
    {
        return 0.0;
    }

    double total = 0.0;

    for (Shape* shapePtr : data)
    {
        total = total + shapePtr->area();
    }

    return total;
}

/// One line per shape: name, one space, area. Return the number of shapes.
int ShapeList::printList() const
{
    int count = 0;
    for (Shape* shapePtr : data)
    {
        std::cout << shapePtr->name() << ' ' << shapePtr->area() << '\n';
        count++;
    }

    return count;
}

/// area() of the shape at index, or std::nullopt if index is out of range.
/// Hint: std::next(data.begin(), index)
std::optional<double> ShapeList::areaAt(int index) const
{
    if (index < 0 || index > length() - 1)
    {
        return std::nullopt;
    }

    auto position = std::next(data.begin(), index);

    return (*position)->area();
}

/// name() of the shape at index, or std::nullopt if index is out of range.
std::optional<std::string> ShapeList::nameAt(int index) const
{
    if (index < 0 || index > length() - 1)
    {
        return std::nullopt;
    }

    auto position = std::next(data.begin(), index);
    return (*position)->name();
}

/// Your own STABLE insertion sort, smallest area first.
/// Compare shapes with operator< (dereference the pointers!).
/// Hint: for every element, walk left while the previous shape is bigger,
/// then move the element there with data.splice(...).


// Note: I was struggling to get the insertionSort to work properly, so I did use AI to help with debugging after attempting to fix it on my own.
// The main things I implemented with help from AI was how to use .splice(), .begin(), and .end().
// .begin() - gives iterator pointing to the first item in the list
// .splice() - moves things to before a position of my choosing
// .end() - gives iterator pointing to the last item in the list


void ShapeList::insertionSort()
{
    auto nextNotSorted = data.begin();

    while (nextNotSorted != data.end())
    {
        auto current = nextNotSorted;
        ++nextNotSorted;

        auto position = current;

        while (position != data.begin())
        {
            auto previous = std::prev(position);

            if (**current < **previous)
            {
                position = previous;
            }
            else
            {
                break;
            }
        }

        if (position != current)
        {
            data.splice(position, data, current);
        }
    }
}

/// True if no shape is smaller than the one before it.
bool ShapeList::isSorted() const
{
    const Shape* previous = nullptr;

    for (const Shape* current : data)
    {
        if (previous != nullptr && *current < *previous)
        {
            return false;
        }

        previous = current;
    }

    return true;
}