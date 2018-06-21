//
//  main.cpp
//  cppPlayground
//
//  Created by Hilton Pintor Bezerra Leite on 20/06/2018.
//  Copyright © 2018 Hilton Pintor Bezerra Leite. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    
    return 0;
}

// MARK: - Pointer of a type can hold value or array
void pointerValueArray() {
    int* pointer;
    int value = 8;
    
    pointer = &value;
    cout << *pointer << endl;
    
    int array[2] = {9, 10};
    
    pointer = array;
    cout << *pointer << endl;
}
