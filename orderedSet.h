/**
 * @file doubleLinkedList.c
 *
 * <b>CE4703 Computer Software 3</b>
 * <b>Assignment 2</b><br/>
 * <b>Data Type "Ordered Set" (Group Project)</b></br>
 *
 * @brief Header file for defining the Ordered Set data type and its operations.<br/>
 *
 * This header file defines the structures and function prototypes for implementing
 * and managing an Ordered Set of integers using a double linked list as the underlying
 * data structure. It includes functions for adding, removing, and performing operations
 * like union, intersection and difference on sets.
 *
 * @author
 *  - Lewis Ubebe (23327944)
 *  - Rasel Raju (23366028)
 *  - Darragh Motihar (23381388)
 *  - Karyna Enato (23329831)
 *  - Simran Rajesh Paunikar (23122668)
 *
 * @date 25.11.2024
 */

#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include "doubleLinkedList.h"

// Enumeration for return values of set operations
/**
 * @enum SetStatus
 * @brief Enum for return values of ordered set operations.
 */
typedef enum
{
    NUMBER_ADDED,            // Element was successfully added to the set
    NUMBER_ALREADY_IN_SET,   // Element is already in the set
    NUMBER_REMOVED,          // Element was successfully removed from the set
    NUMBER_NOT_IN_SET,       // Element is not in the set
    ALLOCATION_ERROR         // Memory allocation error
} SetStatus;

// Structure for an ordered integer set
/**
 * @struct OrderedIntSet
 * @brief Structure representing an ordered integer set.
 */
typedef struct
{
    struct DoubleLinkedList* list;  // Pointer to a double linked list
    int count;                      // Number of elements in the set
} OrderedIntSet;

/**
 * @brief Functions for managing and manipulating ordered integer sets.
 *
 * This set of functions provides the ability to create, delete and manipulate
 * ordered sets of integers using a double linked list as the underlying data structure.
 * The operations include adding and removing elements, performing set operations
 * (union, intersection, difference), and printing the contents of a set. The functions
 * ensure that the set remains ordered and does not contain duplicates.
 */

// Creates a new ordered integer set
OrderedIntSet* createOrderedSet();

// Deletes an ordered integer set and frees all associated memory
void deleteOrderedSet(OrderedIntSet* set);

// Adds an element to the ordered set
SetStatus addElement(OrderedIntSet* set, int elem);

// Removes an element from the ordered set
SetStatus removeElement(OrderedIntSet* set, int elem);

// Computes the intersection of two ordered sets
OrderedIntSet* setIntersection(OrderedIntSet* s1, OrderedIntSet* s2);

// Computes the union of two ordered sets
OrderedIntSet* setUnion(OrderedIntSet* s1, OrderedIntSet* s2);

// Computes the difference of two ordered sets (s1 - s2)
OrderedIntSet* setDifference(OrderedIntSet* s1, OrderedIntSet* s2);

// Prints the elements of the ordered set to the standard output
void printToStdout(OrderedIntSet* set);

#endif // ORDERED_SET_H
