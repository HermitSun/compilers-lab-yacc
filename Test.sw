// Test.sw
// OS.sw contains a function print
import OS;
// Exception.sw contains exception mechanisms
import Exception;
import MathOverflowException;

// properties
number array[10];
Test next;
number i;
i = 0;

while(array[i]){
    if(next){
        continue;
    }else{
        break;
    }
    i = i + 1;
}
array[i] = (2 + 1.0 * 3 / 4.0);
print(1 + 1.0 * 3 == 4);

return 0;