#include <cstdlib>
#include <ctime>
#include "RedBlackTree.h"
#include <iostream>

using namespace std;

int main() {
    const int N = 3700000;          // Total IDs to insert initially
    const int DAILY_REMOVALS = 5;   // Number of daily removals
    const int DAILY_ADDITIONS = 5;  // Number of daily additions

    srand(time(0));

    clock_t start = clock();
    RedBlackTree rbt;
    for (int i = 0; i < N; i++) {
        rbt.Insert(i);
    }
    clock_t stop = clock();

    double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
    cout << "Collected " << rbt.Size() << " ID numbers in " << duration << " seconds." << endl;

    double totalRemoveDuration = 0.0;
    double totalInsertDuration = 0.0;

    cout << "Simulating users leaving:" << endl;
    for (int i = 0; i < DAILY_REMOVALS; i++) {
        if (rbt.Size() == 0) {
            cout << "Tree is empty. Skipping removal." << endl;
            break;
        }

        int idToRemove = rand() % N;

        clock_t startRemove = clock();
        // Use Contains to check existence before removal
        if (rbt.Contains(idToRemove)) {
            rbt.Remove(idToRemove);  // Perform removal
            clock_t stopRemove = clock();
            double removeDuration = (static_cast<double>(stopRemove - startRemove)) / CLOCKS_PER_SEC;
            totalRemoveDuration += removeDuration;
            cout << "Remove #" << (i + 1) << ": " << removeDuration << " seconds (ID " << idToRemove << ")" << endl;
        } else {
            cout << "Remove #" << (i + 1) << ": ID " << idToRemove << " not found, no removal performed." << endl;
        }
    }

    cout << "Simulating users joining:" << endl;
    for (int i = 0; i < DAILY_ADDITIONS; i++) {
        int idToAdd = N + i;

        try {
            clock_t startInsert = clock();
            rbt.Insert(idToAdd);  // Perform insertion
            clock_t stopInsert = clock();

            double insertDuration = (static_cast<double>(stopInsert - startInsert)) / CLOCKS_PER_SEC;
            totalInsertDuration += insertDuration;
            cout << "Insert #" << (i + 1) << ": " << insertDuration << " seconds (ID " << idToAdd << ")" << endl;
        } catch (const std::exception& e) {
            cout << "Error during Insert #" << (i + 1) << ": " << e.what() << endl;
        }
    }

    cout << "Final tree size: " << rbt.Size() << endl;
    cout << "Average Remove Time: " << (totalRemoveDuration / DAILY_REMOVALS) << " seconds" << endl;
    cout << "Average Insert Time: " << (totalInsertDuration / DAILY_ADDITIONS) << " seconds" << endl;

    return 0;
}