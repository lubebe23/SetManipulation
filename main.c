/**
 * @file main.c
 *
 * <b>CE4703 Computer Software 3</b>
 * <b>Assignment 2</b><br/>
 * <b>Data Type "Ordered Set" (Group Project)</b></br>
 *
 * @brief A text menu-driven application for managing Ordered Sets.
 *
 * This application maintains an array of up to 10 Ordered Sets and allows users
 * to perform various set operations, such as adding elements, removing elements,
 * and computing set intersections, unions and differences.
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
#include "orderedSet.h"

// Maximum number of sets
#define MAX_SETS 10

OrderedIntSet* SetsArray[MAX_SETS] = { NULL };

// Helper function to validate index
/**
 * @brief Checks if the given index is valid (0-9).
 *
 * @param index The index to validate.
 * @return int Returns 1 if the index is valid, 0 otherwise.
 */
int isValidIndex(int index) {
    return index >= 0 && index < MAX_SETS;
}

// Function to clean up all sets on program exit
/**
 * @brief Cleans up all sets in the SetsArray.
 *
 * Frees memory for all allocated sets in the SetsArray and sets their pointers to NULL.
 */
void cleanup() {
    for (int i = 0; i < MAX_SETS; i++) {
        if (SetsArray[i]) {
            deleteOrderedSet(SetsArray[i]);
            SetsArray[i] = NULL;
        }
    }
}

// Function to process menu choices
/**
 * @brief Processes a single user menu choice and performs corresponding actions.
 *
 * This function handles user input to choose operations such as creating, deleting,
 * adding/removing elements, performing set operations (intersection, union, difference),
 * and exiting the program. It is recursive and will prompt the user for another choice
 * after each operation.
 */
void processMenuChoice() {
    int choice, index, elem, i1, i2, i3;

    printf("Enter your choice: ");
    scanf_s("%d", &choice);

    switch (choice) {
    case 1: // Create an Ordered Set
        /**
         * @brief Creates a new ordered set at the specified index.
         *
         * Prompts the user to specify an index. If the index is valid and the set
         * doesn't already exist, an ordered set is created at that index.
         */
        printf("Enter index (0-%d): ", MAX_SETS - 1);
        scanf_s("%d", &index);
        if (isValidIndex(index) && !SetsArray[index]) {
            SetsArray[index] = createOrderedSet();
            if (SetsArray[index]) {
                printf("Ordered set created at index %d.\n", index);
            } else {
                printf("Memory allocation failed.\n");
            }
        } else {
            printf("Invalid index or set already exists.\n");
        }
        break;

    case 2: // Delete an Ordered Set
        /**
         * @brief Deletes an ordered set at the specified index.
         *
         * Prompts the user to specify an index. If the index is valid and the set
         * exists, the set is deleted and the index is set to NULL.
         */
        printf("Enter index (0-%d): ", MAX_SETS - 1);
        scanf_s("%d", &index);
        if (isValidIndex(index) && SetsArray[index]) {
            deleteOrderedSet(SetsArray[index]);
            SetsArray[index] = NULL;
            printf("Ordered set at index %d deleted.\n", index);
        } else {
            printf("Invalid index or no set exists.\n");
        }
        break;

    case 3: // Add Elements to Ordered Set
        /**
       * @brief Adds elements to the ordered set at the specified index.
       *
       * Prompts the user to specify an index. If the index is valid and the set
       * exists, the user can enter elements to add to the set. The operation stops
       * when the user enters a negative number.
       */
        printf("Enter index (0-%d): ", MAX_SETS - 1);
        scanf_s("%d", &index);
        if (isValidIndex(index) && SetsArray[index]) {
            printf("Enter elements to add (negative to stop): ");
            while (1) {
                scanf_s("%d", &elem);
                if (elem < 0) break;
                SetStatus status = addElement(SetsArray[index], elem);
                printf(status == NUMBER_ADDED ? "Added %d.\n" : "Already in set: %d.\n", elem);
            }
            printToStdout(SetsArray[index]);
        } else {
            printf("Invalid index or no set exists.\n");
        }
        break;

    case 4: // Remove Elements from Ordered Set
        /**
       * @brief Removes elements from the ordered set at the specified index.
       *
       * Prompts the user to specify an index. If the index is valid and the set
       * exists, the user can enter elements to remove from the set. The operation stops
       * when the user enters a negative number.
       */
        printf("Enter index (0-%d): ", MAX_SETS - 1);
        scanf_s("%d", &index);
        if (isValidIndex(index) && SetsArray[index]) {
            printf("Enter elements to remove (negative to stop): ");
            while (1) {
                scanf_s("%d", &elem);
                if (elem < 0) break;
                SetStatus status = removeElement(SetsArray[index], elem);
                printf(status == NUMBER_REMOVED ? "Removed %d.\n" : "Not in set: %d.\n", elem);
            }
            printToStdout(SetsArray[index]);
        } else {
            printf("Invalid index or no set exists.\n");
        }
        break;

    case 5: // Set Intersection
    case 6: // Set Union
    case 7: // Set Difference
        /**
         * @brief Performs set operations (intersection, union or difference)
         * on the ordered sets at the specified indices and stores the result.
         *
         * Prompts the user for indices. If the indices are valid and sets are present
         * at the first two indices, the specified set operation is performed and the
         * result is stored in the third index.
         */
        printf("Enter indices i1, i2, i3: ");
        scanf_s("%d %d %d", &i1, &i2, &i3);
        if (isValidIndex(i1) && isValidIndex(i2) && isValidIndex(i3) &&
            SetsArray[i1] && SetsArray[i2] && !SetsArray[i3]) {
            OrderedIntSet* result = NULL;
            if (choice == 5) result = setIntersection(SetsArray[i1], SetsArray[i2]);
            if (choice == 6) result = setUnion(SetsArray[i1], SetsArray[i2]);
            if (choice == 7) result = setDifference(SetsArray[i1], SetsArray[i2]);

            SetsArray[i3] = result;
            if (result) {
                printf("Operation successful. Result stored at index %d.\n", i3);
                printToStdout(result);
            } else {
                printf("Memory allocation failed.\n");
            }
        } else {
            printf("Invalid indices or sets.\n");
        }
        break;

    case 8: // Exit
        /**
       * @brief Exits the program and cleans up allocated memory.
       *
       * When this choice is selected, the program will clean up any allocated memory
       * and exit.
       */
        printf("Exiting program. Cleaning up memory.\n");
        cleanup();
        return;

    default:
        printf("Invalid choice! Please enter a number between 1 and 8.\n");
    }

    // Call recursively for the next choice
    processMenuChoice();
}

/**
 * @brief Main function to start the program.
 *
 * Displays the menu once and begins recursive processing of choices.
 *
 * @return int Returns 0 to indicate successful program termination.
 */
int main() {
    printf("\nMenu Options:\n");
    printf("1. Create an empty Ordered Set\n");
    printf("2. Delete an Ordered Set\n");
    printf("3. Add Element to Ordered Set\n");
    printf("4. Remove Element from Ordered Set\n");
    printf("5. Set Intersection\n");
    printf("6. Set Union\n");
    printf("7. Set Difference\n");
    printf("8. Terminate Program\n");

    // Start processing menu choices
    processMenuChoice();

    return EXIT_SUCCESS;
}