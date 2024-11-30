/**
 * @file doubleLinkedList.c
 *
 * <b>CE4703 Computer Software 3</b>
 * <b>Assignment 2</b><br/>
 * <b>Data Type "Ordered Set" (Group Project)</b></br>
 *
 * @brief File to demonstrate Double Linked List functions.<br/>
 * 
 * This file contains a set of functions to manage and manipulate a Double Linked List,
 * including creating, deleting and printing the list.
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

 // include system header files
#include <stdio.h>
#include <stdlib.h>

// include module header file
#include "doubleLinkedList.h"

// Function to create an empty double linked list
/**
 * @brief Creates a new empty Double Linked List, consisting only of head and tail
 *
 * @return struct DoubleLinkedList* Pointer to the newly created Double Linked List.
 * 
 */
struct DoubleLinkedList* createDoubleLinkedList() {
    struct DoubleLinkedList* list = (struct DoubleLinkedList*)malloc(sizeof(struct DoubleLinkedList));
    if (!list) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    printf("Empty double linked list created.\n");
    return list;
}

// Function to delete the entire double linked list
/**
 * @brief Deletes an entire Double Linked List and frees its memory.
 *
 * @param list Pointer to the Double Linked List to delete.
 * 
 */
void deleteDoubleLinkedList(struct DoubleLinkedList* list) {
    if (!list) return;

    struct Node* currentNode = list->head;
    struct Node* nextNode;

    while (currentNode != NULL) {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }

    list->head = NULL;
    list->tail = NULL;
    free(list);
    printf("The entire list is deleted.\n");
}

// Function to print the double linked list
/**
 * @brief Prints the contents of a Double Linked List.
 * 
 * @param list Pointer to the Double Linked List to print.
 * @details The function prints the data of each node in the list in the format.
 *          If the list is empty, it prints '{}'.
 */
void printDoubleLinkedList(struct DoubleLinkedList* list) {
    if (list == NULL || list->head == NULL) {
        printf("{}\n");
        return;
    }

    struct Node* current = list->head;
    printf("{");
    while (current) {
        printf("%d", current->data);
        if (current->next) {
            printf(", ");
        }
        current = current->next;
    }
    printf("}\n");
}

// Function to remove a node from the double linked list
/**
 * @brief Removes a specific node from the Double Linked List.
 *
 * @param list Pointer to the Double Linked List.
 * @param current Pointer to the node to be removed.
 * @details Updates head or tail pointers if the first or last node is removed.
 */
void removeNode(struct DoubleLinkedList* list, struct Node* current) {
    if (!list || !current) {
        printf("Invalid node or list.\n");
        return;
    }

    if (current->prev) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;  // Update head if removing the first node
    }

    if (current->next) {
        current->next->prev = current->prev;
    } else {
        list->tail = current->prev;  // Update tail if removing the last node
    }

    free(current);
    printf("Node removed successfully.\n");
}

// Function to append a node to the end of the list
/**
 * @brief Appends a new node to the end of the Double Linked List.
 *
 * @param list Pointer to the Double Linked List.
 * @param newdata The data to store in the new node.
 * @details If the list is empty, the new node becomes both the head and tail.
 */
void appendNode(struct DoubleLinkedList* list, int newdata) {
    if (!list) {
        printf("Invalid list.\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = newdata;
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (list->tail) {
        list->tail->next = newNode;
    } else {
        list->head = newNode;
    }
    list->tail = newNode;
}

// Function to insert a node before a given node
/**
 * @brief Inserts a new node before a specific node in the Double Linked List.
 *
 * @param list Pointer to the Double Linked List.
 * @param current Pointer to the node before which the new node will be inserted.
 * @param newdata The data to store in the new node.
 * @details Updates the head pointer if the insertion is at the start of the list.
 */
void insertBefore(struct DoubleLinkedList* list, struct Node* current, int newdata) {
    if (!current || !list) {
        printf("Cannot insert before a NULL node or in an invalid list.\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = newdata;
    newNode->next = current;
    newNode->prev = current->prev;

    if (current->prev) {
        current->prev->next = newNode;
    } else {
        list->head = newNode;  // Update head if inserting at the start
    }
    current->prev = newNode;
}
