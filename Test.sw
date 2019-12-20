// Test.sw
// OS.sw contains a function print
import OS;
// Exception.sw contains exception mechanisms
import Exception;
import MathOverflowException;

// properties
number array[10];
Test next = void;

// methods
export void say_hello(function get_msg){
    number i = 0;
    while(i < 3){
        if(i == 1){
            OS.print(get_msg());
            array[i] = i;
            continue;
        } else {
            OS.print(add(2, 1.0));
            break;
        }
    }
    try{
        Test t;
    	next = t;
    }catch(Exception){
        OS.print(Exception.what());
    }
}

number add(number a, number b) throw MathOverflowException{
    if(a + b < MIN_NUMBER){
        throw MathOverflowException;
    }
    return a + b;
}

string get_msg(){
    return "Hello World!";
}