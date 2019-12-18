#include <iostream>
#include <vector>
#include <stdlib.h>
#include "topXquick.cpp"

extern void initArray( vector<int> &array, int rand_max );
extern void printArray( vector<int> &array, char name[] );

int main( int argc, char* argv[] ) {
  // verify arguments
  if ( argc != 3 ) {
    cerr << "usage: quicksort size topX" << endl;
    return -1;
  }

  // verify an array size
  int size = atoi( argv[1] );
  if ( size <= 0 ) {
    cerr << "array size must be positive" << endl;
    return -1;
  }

  // verify top X
  int topX = atoi( argv[2] );
  if ( topX <= 0 ) {
    cerr << "topX must be positive" << endl;
    return -1;
  }

  // array generation
  srand( 1 );
  vector<int> items( size );
  initArray( items, size );
  cout << "initial:" << endl;
  printArray( items, "items" );

  // quicksort
  quicksort( items, topX );
  cout << "sorted:" << endl;
  printArray( items, "items" );

  return 0;
}
