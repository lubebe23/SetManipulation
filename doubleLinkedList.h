/**
 * @file doubleLinkedList.c
 *
 * <b>CE4703 Computer Software 3</b>
 * <b>Assignment 2</b><br/>
 * <b>Data Type "Ordered Set" (Group Project)</b></br>
 *
 * @brief Header file for the Double Linked List data structure.<br/>
 *
 * This header file defines the structures and function prototypes for implementing
 * and managing a Double Linked List. It includes operations for creating, deleting
 * and manipulating the list and its nodes.
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

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

// Node structure
/**
 * @brief Structure representing a node in the double linked list.
 *
 * This structure holds an integer value ('data') and two pointers:
 * - 'next': points to the next node in the list.
 * - 'prev': points to the previous node in the list.
 */
struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
};

// Double Linked List structure
/**
 * @brief Structure representing a double linked list.
 *
 * This structure holds two pointers:
 * - 'head': points to the first node of the list.
 * - 'tail': points to the last node of the list.
 *
 */
struct DoubleLinkedList
{
    struct Node* head;
    struct Node* tail;
};

// Function declarations
/**
 * @brief Function declarations for Double Linked List operations.
 *
 * These functions enable the creation, deletion, and manipulation of a Double Linked List.
 *
 * - 'createDoubleLinkedList': Creates a new empty Double Linked List.
 * - 'deleteDoubleLinkedList': Deletes an entire Double Linked List and frees its memory.
 * - 'printDoubleLinkedList': Prints the contents of the Double Linked List.
 * - 'removeNode': Removes a specific node from the Double Linked List.
 * - 'insertBefore': Inserts a new node before a specific node in the Double Linked List.
 * - 'appendNode': Appends a new node to the end of the Double Linked List.
 */
struct DoubleLinkedList* createDoubleLinkedList();
void deleteDoubleLinkedList(struct DoubleLinkedList* list);
void printDoubleLinkedList(struct DoubleLinkedList* list);
void removeNode(struct DoubleLinkedList* list, struct Node* current);  // Declaration for removeNode
void insertBefore(struct DoubleLinkedList* list, struct Node* current, int newdata);
void appendNode(struct DoubleLinkedList* list, int newdata);

#endif // DOUBLE_LINKED_LIST_H
