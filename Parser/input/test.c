/*
 * 2019 Spring Compiler Course Assignment 2 
 */

float c = 1.5;
int test(int s);

bool loop(int n, int m) {
    while (n > m) {
        n--;
    }
    return true;
}

int main() {
    // Declaration
    int x;
    int i;
    int a = 5;

    // if condition
    if (a > 10) {
        int s = 1;
        x += a;
        // Undeclared variable
        print(b);
    } else {
        x = a % 10 + 10 * 7; /* Arithmetic */
    }
    print("Hello World");

    // Redeclare variable
    float a = 1.0;

    return 0; 
}

int test(int s){
    int temp = s+10;
    while(temp > 10){
        temp--;
    }
    return temp*s;
}
