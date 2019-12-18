/*
 * Edited by Alex van Zuiden-Rylander
 * This program was written to calculate the time complexity of a sieve function.
 * It goes through an array 1 - n times and each time iterates through
 * marking all non prime numbers in the array as false, each time a spot
 * is marked false the cost goes up by one and the time taken for the function is calculated.
 */


#include <iostream>
#include <vector>
#include <math.h>
#include <sys/time.h>
using namespace std;

// A method to find if the number is prime
bool isPrime(const int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;

    if (n%2 == 0 || n%3 == 0)
        return false;

    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
            return false;

    return true;
}

// sieve method that marks each multiple of a prime number within the boolean array as false
int sieve(const int n, vector<int> &primes ) {

    int cost = 0;
    bool array[n + 1];
// array initialization
    for (int i = 0; i < n; i++) {
        array[i] = true;
    }
// implement sieve here
// every time you perform: array[j] = false;
    for (int j = 2; j <= sqrt(n); j++) {
        if (isPrime(j)) {
            for (int k = j * j; k <= n;  k += j) {
                if(array[k]) {
                    cost++;
                    array[k] = false;
                }
            }
        }
    }


// collect all prime numbers
    for ( int i = 0; i < n; i++ )
        if ( array[i] == true )
            primes.push_back( i );
    return cost;
}
int main( ) {

    int n = 0;
    struct timeval startTime, endTime;
    while ( n < 2 ) {
        cout << "Enter n " << endl;
        cin >> n;
    }
    char printOption = 'n';
    cout << "print all primes (y|n)? " << endl;
    cin >> printOption;
    for ( int i = 2; i <= n; i++ ) {
        gettimeofday( &startTime, NULL );
        vector<int> primes;
        int cost = sieve( i, primes );
        gettimeofday( &endTime, NULL );
//        cout << (double) cost / (( endTime.tv_sec - startTime.tv_sec ) * 1000000 + ( endTime.tv_usec - startTime.tv_usec ) ) << endl;
        cout << "primes[1.." << i << "] took " << cost
             << " sweeping operations...time required = "
             << ( endTime.tv_sec - startTime.tv_sec ) * 1000000 +
                ( endTime.tv_usec - startTime.tv_usec ) << endl;
        if ( printOption == 'y' ) {
            cout << "all primes = ";
            for ( int j = 0; j < primes.size( ); j++ )
                cout << primes[j] << " ";
            cout << endl;
        }
        cerr << i << " " << cost << endl;
    }
    return 0;
}
