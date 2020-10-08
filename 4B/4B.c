#include <stdio.h>
#include <stdbool.h>

struct State {
    int a, b, c;
    int father;
}List[10000];

void output(int t, int dep) {
    if (t == -1) {
        printf("Totally %d steps: \n", dep);
        return;
    }
    output(List[t].father, dep + 1);
    printf("%d %d %d\n", List[t].a, List[t].b, List[t].c);
    return;
}

bool newstate(int a, int b, int c, int head, int tail) {
    List[tail].a = a; List[tail].b = b; List[tail].c = c; List[tail].father = head;
    bool done = false;
    if (a == 4 && b == 4) {
        done = true;
        output(tail, 0);
    }
    return done;
}

void BFS() {
    int head = 0, tail = 1;
    List[0].a = 8;
    List[0].b = 0;
    List[0].c = 0;
    List[0].father = -1;
    while (head < tail) {
        //generate new states
        //a->b,a->c
        if (List[head].a > 0) {
            if (List[head].b < 5)
                if (List[head].a >= 5 - List[head].b) {
                    bool done = newstate(List[head].a - 5 + List[head].b, 5, List[head].c, head, tail);
                    ++tail;
                    if (done) 
                        break;
                } else {
                    bool done = newstate(0, List[head].a + List[head].b, List[head].c, head, tail);
                    ++tail;
                    if (done) 
                        break;
                }
            
            if (List[head].c < 3)
                if (List[head].a >= 3 - List[head].c) {
                    bool done = newstate(List[head].a - 3 + List[head].c, List[head].b, 3, head, tail);
                    ++tail;
                    if (done) 
                        break;
                } else {
                    bool done = newstate(0, List[head].b, List[head].a + List[head].c, head, tail);
                    ++tail;
                    if (done) 
                        break;
                }
        }
        //b->a,b->c
        if (List[head].b > 0) {            
            bool done = newstate(List[head].a + List[head].b, 0, List[head].c, head, tail);
            ++tail;
            if (done) 
                break;
            
            if (List[head].c < 3)
                if (List[head].b >= 3 - List[head].c) {
                    bool done = newstate(List[head].a, List[head].b - 3 + List[head].c, 3, head, tail);
                    ++tail;
                    if (done) 
                        break;
                } else {
                    bool done = newstate(List[head].a, 0, List[head].b + List[head].c, head, tail);
                    ++tail;
                    if (done) 
                        break;
                }

        }
        //c->a,c->b
        if (List[head].c > 0) {
            bool done = newstate(List[head].a + List[head].c, List[head].b, 0, head, tail);
            ++tail;
            if (done) 
                break;
            
            if (List[head].b < 5)
                if (List[head].c >= 5 - List[head].b) {
                    bool done = newstate(List[head].a, 5, List[head].c - 5 + List[head].b, head, tail);
                    ++tail;
                    if (done) 
                        break;
                } else {
                    bool done = newstate(List[head].a, List[head].b + List[head].c, 0, head, tail);
                    ++tail;
                    if (done) 
                        break;
                }

        }
        ++head;
    }
}

int main()
{
    BFS();
    return 0;
}