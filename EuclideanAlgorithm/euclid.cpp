/*-----------About this program ------------/
 * Written by Alex van Zuiden-Rylander      /
 * Algorithm Analysis of Euclidean Alg.     /
 * Date: January 28th, 2019                 /
 * Input: User defined integer that has to  /
 * be greater than 8.                       /
 * Output: The GCD along with the modulus   /
 * operation count for the given two        /
 * integers.                                /
-------------------------------------------*/

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sys/time.h>

using namespace std;

/*----------------- Method -----------------/
 *This method find the greatest common      /
 * denominator and keeps track of the       /
 * modulus operations ran. Also assumes     /
 * that b will always be your smaller int.  /
-------------------------------------------*/
int gcd(int a, int b, int &cost) {
    if (b == 0) {
        return a;
    }
    cost++;
    return gcd(b, a % b, cost);
}

int main() {

// creates a file that will be used to track algorithms performance.
    ofstream file("euclid.dat");

//definition of all variables used in the program.
    struct timeval startTime, endTime;
    int itr, maxA, maxB, maxModulus, currentModulus, maxAns, tempAns;

    while (itr < 8) {
        cout << "Enter n " << endl;
        cin >> itr;
    }

//Starting the timer.
    gettimeofday(&startTime, NULL);

    for (int i = 8; i <= itr; i++) {
        for (int j = 1; j <= i; j++) {
            currentModulus = 0;
            tempAns = gcd(i, j, currentModulus);

//Assignment of variables that will be used.
            if (currentModulus > maxModulus) {
                maxA = j;
                maxB = i;
                maxModulus = currentModulus;
                maxAns = tempAns;
            }
        }

//Ending the timer.
        gettimeofday(&endTime, NULL);

        cout << "At i = " << i << " gcd( " << maxA << ", " << maxB << " ) = "
             << maxAns << " took " << maxModulus << " modulus operations"
             << " ...time required = "
             << (endTime.tv_sec - startTime.tv_sec) * 1000000 +
                (endTime.tv_usec - startTime.tv_usec) << endl;

//Writing to the file and writing to an error file in g++.
        file << i << " " << maxModulus << endl;
//        cerr << i << " " << maxModulus << endl;
    }

    file.close();

    return 0;
}