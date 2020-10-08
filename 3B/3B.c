#include <stdio.h>

typedef struct fraction {
    int numerator;
    int denominator;
} fraction; 

int GCD(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    int t = a % b;
    a = b;
    b = t;
    return GCD(a, b);
}

fraction simp(fraction a) {
    int r = GCD(a.numerator, a.denominator);
    a.numerator = a.numerator / r;
    a.denominator = a.denominator / r;
    if (a.denominator < 0) {
        a.denominator = -a.denominator;
        a.numerator = -a.numerator;
    }
    return a;
}

fraction num_mul(int x, fraction a) {
    a.numerator *= x;
    return simp(a);
}

fraction plus(fraction a, fraction b) {
    a.numerator *= b.denominator;
    b.numerator *= a.denominator;
    a.denominator *= b.denominator;
    a.numerator += b.numerator;
    return simp(a);
}

fraction minus(fraction a, fraction b) {
    b.numerator = -b.numerator;
    return plus(a, b);
}

fraction mul(fraction a, fraction b) {
    a.numerator *= b.numerator;
    a.denominator *= b.denominator;
    return simp(a);
}

fraction division(fraction a, fraction b) {
    fraction c;
    c.denominator = b.numerator;
    c.numerator = b.denominator;
    return mul(a, c);
}

float tofloat(fraction a) {
    return ((float)a.numerator / (float)a.denominator);
}

int main()
{
    printf("\
    Input number to choose the operation you want:\n\
    1 for plus\n\
    2 for minus\n\
    3 for multiply\n\
    4 for division\n\
    5 for simplify\n\
    6 for translation to float\n\
    -1 to quit.\n"\
    );
    while (1) {
        int opr;
        printf("Input the operation number: ");
        scanf("%d", &opr);
        if (opr == -1) break;
        else if (opr == 1) {
            fraction a, b;
            printf("Input the numerator and denominator for the first operator a, the input the numerator and denominator for the last operator b:\n");
            scanf("%d%d%d%d", &a.numerator, &a.denominator, &b.numerator, &b.denominator);
            a = plus(a, b);
            printf("a + b = %d/%d\n", a.numerator, a.denominator);
        } else if (opr == 2) { 
            fraction a, b;
            printf("Input the numerator and denominator for the first operator a, the input the numerator and denominator for the last operator b:\n");
            scanf("%d%d%d%d", &a.numerator, &a.denominator, &b.numerator, &b.denominator);
            a = minus(a, b);
            printf("a - b = %d/%d\n", a.numerator, a.denominator);
        } else if (opr == 3) {
            fraction a, b;
            printf("Input the numerator and denominator for the first operator a, the input the numerator and denominator for the last operator b:\n");
            scanf("%d%d%d%d", &a.numerator, &a.denominator, &b.numerator, &b.denominator);
            a = mul(a, b);
            printf("a * b = %d/%d\n", a.numerator, a.denominator);
        } else if (opr == 4) {
            fraction a, b;
            printf("Input the numerator and denominator for the first operator a, the input the numerator and denominator for the last operator b:\n");
            scanf("%d%d%d%d", &a.numerator, &a.denominator, &b.numerator, &b.denominator);
            a = division(a, b);
            printf("a / b = %d/%d\n", a.numerator, a.denominator);
        } else if (opr == 5) {
            fraction a;
            printf("Input the numerator and denominator for the fraction a:\n");
            scanf("%d%d", &a.numerator, &a.denominator);
            a = simp(a);
            printf("a = %d/%d\n", a.numerator, a.denominator);
        } else if (opr == 6) {
            fraction a;
            printf("Input the numerator and denominator for the fraction a:\n");
            scanf("%d%d", &a.numerator, &a.denominator);
            printf("a = %f\n", tofloat(a));          
        } else 
            printf("Invalid operation number!\n");
    }
    return 0;
}