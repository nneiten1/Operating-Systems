//
// nicholas neitenbach
// 11/30/2023
// banker's algorithm
//

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main() {

    int n = 5;              // # of processes
    int m = 3;              // # of resources types
    int safe[n], vari = 0;  // for checked processes

    int avail[m]; // array for storing available resources
    {
    ifstream fileAvailable("available.txt");
    if (!fileAvailable) { 
        cout << "Cannot open or find file: 'available.txt'"; // checking if file can be opened, if not this it outputted
        exit(EXIT_FAILURE);
    }

    char input;
    fileAvailable >> input;
    for (int i = 0; i < m; i++) {
        avail[i] = input - '0';                       // reading available resources from available.txt
        fileAvailable >> input;
    }
    fileAvailable.close();
    }

    int max[n][m];
    {
    ifstream fileMax("max.txt");
    if (!fileMax) {
        cout << "Cannot open or find file: 'max.txt'";  // stores maximum resource needed by each process
        exit(EXIT_FAILURE);
    }

    char input;
    fileMax >> input;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            max[i][j] = input - '0';
            fileMax >> input;
        }
    }

    fileMax.close();
    }
    
    int allo[n][m];
    {
    ifstream fileAllocation("alloc.txt");
    if (!fileAllocation) {
        cout << "Cannot open or find file: 'allocation.txt'";   // array storing allocated resource to each process
        exit(EXIT_FAILURE);
    }

    char input;
    fileAllocation >> input;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {   // reading allocated resources to each process from file
            allo[i][j] = input - '0';
            fileAllocation >> input;
        }
    }

    fileAllocation.close();
    }

    int need[n][m];
    {
    for (int i = 0; i < n; i++) {   // storing needed resources by each proccess
        for (int j = 0; j < m; j++)     
            need[i][j] = max[i][j] - allo[i][j];    // calculating needed resource by each proccess
    }
    }

    bool finish[n];
    for (int s = 0; s < n; s++) finish[s] = false;      // tracking finished proccesses

    int t = 0;
    do {
        for (int i = 0; i < n; i++) {
            if (finish[i] == false) { // if process not finished
            bool flag = false;
                for (int j = 0; j < m; j++) { 
                    if (need[i][j] > avail[j]) { 
                        flag = true;
                        break;
                    }
                }

                if (!flag) {
                    safe[vari++] = i;   // marking proccess as safe
                    for (int x = 0; x < m; x++)
                        avail[x] += allo[i][x]; // updating available resources after process completion
                    finish[i] = 1;  // marking as finished
                }
            }
        }
    t++;
    } while (t < n);

    int flag = 1;
    for (int i = 0; i < n; i++) {
        if (finish[i] == false) { // need > available
            cout << "THIS IS NOT A SAFE SYSTEM."; // indicates system is not in safe mode
            flag = 0;
            break;
        }
    }

    if (flag == 1) {
        cout << "Safest process order: ";
        for (int i = 0; i < n; i++) {
            cout << safe[i];        // safest proccess order
            cout << " ";
        }
        cout << endl;
    }

    return(0);

}