/**
 * @file orderedSet.c
 *
 * <b>CE4703 Computer Software 3</b>
 * <b>Assignment 2</b><br/>
 * <b>Data Type "Ordered Set" (Group Project)</b><br/>
 *
 * @brief Implementation of functions to manage an Ordered Set using a Double Linked List.<br/>
 *
 * This file contains functions to create, manipulate, and manage an ordered set of integers.
 * The set is backed by a double linked list and includes operations to add, remove and perform set operations like union, intersection and difference.
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

 // Include system header files
#include <stdio.h>
#include <stdlib.h>

// Include module header files
#include "orderedSet.h"
#include "doubleLinkedList.h"

// Function to create an ordered set
/**
 * @brief Creates an empty ordered set.
 *
 * This function allocates memory for an ordered set, initializes the internal double linked list
 * to be empty and sets the count of elements to 0.
 *
 * @return A pointer to the created ordered set or NULL if memory allocation fails.
 */
OrderedIntSet* createOrderedSet() {
    OrderedIntSet* set = (OrderedIntSet*)malloc(sizeof(OrderedIntSet));
    if (!set) return NULL;
    set->list = createDoubleLinkedList();
    if (!set->list) {
        free(set);
        return NULL;
    }
    set->count = 0;
    return set;
}

// Function to add an element to the ordered set
/**
 * @brief Adds an element to the ordered set.
 *
 * This function adds an element to the ordered set while ensuring that the set remains in ascending order
 * and contains no duplicate elements.
 *
 * @param set The ordered set to add the element to.
 * @param elem The element to be added to the set.
 *
 * @return SetStatus indicating whether the element was successfully added, already in the set or an allocation error occurred.
 */
SetStatus addElement(OrderedIntSet* set, int elem) {
    if (!set) return ALLOCATION_ERROR;

    // If the list is empty, simply add the element at the head
    if (!set->list->head) {
        appendNode(set->list, elem);
        set->count++;
        return NUMBER_ADDED;
    }

    struct Node* current = set->list->head;
    while (current) {
        if (current->data == elem) {
            return NUMBER_ALREADY_IN_SET;  // Element already exists
        }
        // If we find a node with a greater value, insert before it
        if (current->data > elem) {
            insertBefore(set->list, current, elem);
            set->count++;
            return NUMBER_ADDED;
        }
        current = current->next;
    }

    // If the element is greater than all existing elements, append it at the end
    appendNode(set->list, elem);
    set->count++;
    return NUMBER_ADDED;
}

// Function to delete an ordered set
/**
 * @brief Deletes an ordered set.
 *
 * This function deallocates memory for the ordered set and its internal double linked list.
 *
 * @param set The ordered set to be deleted.
 */
void deleteOrderedSet(OrderedIntSet* set) {
    if (set) {
        deleteDoubleLinkedList(set->list);
        free(set);
    }
}

// Function to print an ordered set
/**
 * @brief Prints the elements of the ordered set to the standard output.
 *
 * This function prints the elements of the ordered set in the format {elem1, elem2, ..., elemN}.
 * If the set is empty, it prints "{}".
 *
 * @param set The ordered set to print.
 */
void printToStdout(OrderedIntSet* set) {
    if (!set || !set->list || !set->list->head) {
        printf("{}\n");
        return;
    }

    printf("{");
    struct Node* current = set->list->head;
    while (current) {
        printf("%d", current->data);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("}\n");
}

// Function to remove an element from the ordered set
/**
 * @brief Removes an element from the ordered set.
 *
 * This function removes a specified element from the ordered set. If the element is not found, no changes are made.
 *
 * @param set The ordered set to remove the element from.
 * @param elem The element to be removed from the set.
 *
 * @return SetStatus indicating whether the element was successfully removed or not found in the set.
 */
SetStatus removeElement(OrderedIntSet* set, int elem) {
    if (!set) return ALLOCATION_ERROR;

    struct Node* current = set->list->head;
    while (current) {
        if (current->data == elem) {
            removeNode(set->list, current);
            set->count--;
            return NUMBER_REMOVED;
        }
        current = current->next;
    }
    return NUMBER_NOT_IN_SET;
}

/**
 * @brief Computes the intersection of two ordered sets.
 *
 * This function returns a new ordered set containing the elements that are common to both input sets.
 * Neither of the input sets are modified.
 *
 * @param s1 The first ordered set.
 * @param s2 The second ordered set.
 *
 * @return A new ordered set containing the intersection of s1 and s2 or NULL if memory allocation fails.
 */
OrderedIntSet* setIntersection(OrderedIntSet* s1, OrderedIntSet* s2) {
    if (!s1 || !s2) return NULL;

    OrderedIntSet* result = createOrderedSet();
    if (!result) return NULL;

    struct Node* current1 = s1->list->head;
    struct Node* current2 = s2->list->head;

    while (current1 && current2) {
        if (current1->data == current2->data) {
            addElement(result, current1->data);  // Add the common element to the result
            current1 = current1->next;  // Move both pointers forward
            current2 = current2->next;
        } else if (current1->data < current2->data) {
            current1 = current1->next;  // Move current1 forward
        } else {
            current2 = current2->next;  // Move current2 forward
        }
    }
    return result;
}



// Function to find the union of two ordered sets
/**
 * @brief Computes the union of two ordered sets.
 *
 * This function returns a new ordered set containing all unique elements from both input sets.
 * Neither of the input sets are modified.
 *
 * @param s1 The first ordered set.
 * @param s2 The second ordered set.
 *
 * @return A new ordered set containing the union of s1 and s2 or NULL if memory allocation fails.
 */
OrderedIntSet* setUnion(OrderedIntSet* s1, OrderedIntSet* s2) {
    if (!s1 || !s2) return NULL;

    OrderedIntSet* result = createOrderedSet();
    if (!result) return NULL;

    struct Node* current1 = s1->list->head;
    struct Node* current2 = s2->list->head;

    while (current1 || current2) {  // Continue while either list has elements
        if (!current2 || (current1 && current1->data < current2->data)) {
            addElement(result, current1->data);
            current1 = current1->next;  // Move current1 forward
        } else if (!current1 || (current2 && current2->data < current1->data)) {
            addElement(result, current2->data);
            current2 = current2->next;  // Move current2 forward
        } else {
            addElement(result, current1->data);  // Both data are equal
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    return result;
}

// Function to find the difference of two ordered sets (s1 - s2)
/**
 * @brief Computes the difference of two ordered sets (s1 - s2).
 *
 * This function returns a new ordered set containing all elements that are in s1 but not in s2.
 * Neither of the input sets are modified.
 *
 * @param s1 The first ordered set.
 * @param s2 The second ordered set.
 *
 * @return A new ordered set containing the difference of s1 and s2 or NULL if memory allocation fails.
 */
OrderedIntSet* setDifference(OrderedIntSet* s1, OrderedIntSet* s2) {
    if (!s1 || !s2) return NULL;

    OrderedIntSet* result = createOrderedSet();
    if (!result) return NULL;

    struct Node* current1 = s1->list->head;
    struct Node* current2 = s2->list->head;

    while (current1) {
        // Compare current1 to current2, if current1's data is less add to result
        while (current2 && current1->data > current2->data) {
            current2 = current2->next;
        }
        if (!current2 || current1->data < current2->data) {
            addElement(result, current1->data);
        } else if (current1->data == current2->data) {
            current2 = current2->next;  // Skip matching elements
        }
        current1 = current1->next;  // Move current1 forward
    }
    return result;
}


