#include <stdio.h>
#include <string.h>

int k, weight;

int ask(int *a, int time) {
    int i; 
    printf("weigh %d:\n", time);
    printf("left side: ");
    for (i = 0; i < 12; ++i)
        if (*(a + i) == -1) printf("%d ", i);
    printf("\nright side: ");
    for (i = 0; i < 12; ++i)
        if (*(a + i) == 1) printf("%d ", i);
    printf("\n");
    int ans = (*(a + k)) * weight;
    if (ans < 0) printf("Left side is heavier.\n");
    else if (ans > 0) printf("Left side is lighter.\n");
    else printf("Two sides are same weighted.\n");
    return ans;
}

int weigh() {
    int a[12];
    memset(a, 0, sizeof(a));
    a[0] = a[1] = a[2] = a[3] = -1; //left: -1 right: 1
    a[4] = a[5] = a[6] = a[7] = 1;
    int t1 = ask(a, 1); //left lighter, right heavier: 1
    if (t1 == 0) {
        memset(a, 0, sizeof(a));
        a[8] = -1;
        a[9] = 1;
        int t2 = ask(a, 2);
        if (t2 == 0) {
            a[9] = 0;
            a[10] = 1;
            int t3 = ask(a, 3);
            if (t3 == 0) {
                a[10] = 0;
                a[11] = 1;
                int t4 = ask(a, 4);
                if (t4 == -1) return -11;
                else return 11;
            } else if (t3 == -1) {
                return -10;
            } else return 10;
        } else if (t2 == -1) {
            a[9] = 0;
            a[10] = 1;
            int t3 = ask(a, 3);
            if (t3 == 0) return -9;
            else return 8;
        } else if (t2 == 1) {
            a[9] = 0;
            a[10] = 1;
            int t3 = ask(a, 3);
            if (t3 == 0) return 9;
            else return -8;
        }
    } else if (t1 == -1) {
        memset(a, 0, sizeof(a));
        a[0] = a[5] = a[6] = a[7] = -1;
        a[4] = a[9] = a[10] = a[11] = 1;
        int t2 = ask(a, 2);
        if (t2 == -1) {
            memset(a, 0, sizeof(a));
            a[0] = -1;
            a[1] = 1;
            int t3 = ask(a, 3);
            if (t3 == 0) return -4;
            else return 0;
        } else if (t2 == 0) {
            memset(a, 0, sizeof(a));
            a[1] = -1;
            a[2] = 1;
            int t3 = ask(a, 3);
            if (t3 == 0) return 3;
            else if (t3 == -1) return 1;
            else return 2;
        } else {
            memset(a, 0, sizeof(a));
            a[5] = -1;
            a[6] = 1;
            int t3 = ask(a, 3);
            if (t3 == 0) return -7;
            else if (t3 == -1) return -6;
            else return -5;
        }
    } else { 
        memset(a, 0, sizeof(a));
        a[0] = a[5] = a[6] = a[7] = -1;
        a[4] = a[9] = a[10] = a[11] = 1;
        int t2 = ask(a, 2);
        if (t2 == 1) {
            memset(a, 0, sizeof(a));
            a[0] = -1;
            a[1] = 1;
            int t3 = ask(a, 3);
            if (t3 == 0) return 4;
            else return -12;
        } else if (t2 == 0) {
            memset(a, 0, sizeof(a));
            a[1] = -1;
            a[2] = 1;
            int t3 = ask(a, 3);
            if (t3 == 0) return -3;
            else if (t3 == -1) return -2;
            else return -1;           
        } else {
            memset(a, 0, sizeof(a));
            a[5] = -1;
            a[6] = 1;
            int t3 = ask(a, 3);
            if (t3 == 0) return 7;
            else if (t3 == -1) return 5;
            else return 6;
        }  
    }
}

int main()
{
    while (1) {
        printf("Please input the number of the different ball(0~11), and a flag -1 for lighter or 1 for heavier. Input -1 -1 to quit.\n");
        scanf("%d%d", &k, &weight); //heavier: 1 lighter: -1
        if (k == -1) break;
        int ans = weigh(); 
        if (ans < 0) {
            if (ans == -12) printf("#%d, lighter\n\n", 0);
            else printf("#%d, lighter\n\n", -ans);
        }
        else printf("#%d, heavier\n\n", ans);
    }
    return 0;
}
