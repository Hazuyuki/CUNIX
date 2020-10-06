#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Place {
    int Day;
    int IndB, IndU;
    struct Place *Next;
};

struct Person {
    int Ind, Ifct;
    struct Place *Trace;
    struct Person *Next;
};

struct Building {
    double X, Y;
    int IndB, IndU;
    struct Building *Next; 
};

struct Building *BHead;
struct Person *PHead;

void Inflect(int Ind, int Ifct) {
    struct Person *Ptemp = PHead;
    while (Ptemp != NULL) {
        if (Ptemp->Ind == Ind) {
            Ptemp->Ifct = Ifct;
            break;
        }
        Ptemp = Ptemp->Next;
    }
    return;
}

void AddPerson(int Ind, int Ifct) {
    struct Person *Ptemp = malloc(sizeof(struct Person));
    Ptemp->Ind = Ind; Ptemp->Ifct = Ifct; 
    Ptemp->Trace = NULL; Ptemp->Next = PHead;
    PHead = Ptemp;
    return;
}

void AddBuilding(double X, double Y, int IndB, int IndU) {
    struct Building *Btemp = malloc(sizeof(struct Building));
    Btemp->X = X; Btemp->Y = Y;
    Btemp->IndB = IndB; Btemp->IndU = IndU;
    Btemp->Next = BHead;
    BHead = Btemp;
    return;
}

void PersonGo(int Ind, int Day, int IndB, int IndU) {
    struct Place *Plctemp = malloc(sizeof(struct Place));
    Plctemp->Day = Day; Plctemp->IndB = IndB; Plctemp->IndU = IndU;
    struct Person *Ptemp = PHead;
    while (Ptemp != NULL) {
        if (Ptemp->Ind == Ind) {
            Plctemp->Next = Ptemp->Trace; 
            Ptemp->Trace = Plctemp;
            break;
        }
        Ptemp = Ptemp->Next;
    }
    return;
}

void ShowTrace(int Ind, int Day) {
    struct Person *Ptemp = PHead;
    while (Ptemp != NULL) {
        if (Ptemp->Ind == Ind) {
            struct Place *Plctemp = Ptemp->Trace;
            while (Plctemp != NULL) {
                if (Day - Plctemp->Day <= 14) 
                    printf("Day: %d, BuildingID: %d, UnitID: %d;\n", Plctemp->Day, Plctemp->IndB, Plctemp->IndU);
                Plctemp = Plctemp->Next;
            }
            break;
        }
        Ptemp = Ptemp->Next;
    }
}

double distance(double x1, double y1, double x2, double y2) {
    return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

int near(int IndB, int IndU, double X, double Y) {
    struct Building *Btemp = BHead; 
    while (Btemp != NULL) {
        if (Btemp->IndB == IndB && Btemp->IndU == IndU)
            return (distance(Btemp->X, Btemp->Y, X, Y) <= 1);
        Btemp = Btemp->Next;
    }
}

void ShowInflect(double X, double Y, int Day) {
    int tot = 0;
    struct Person *Ptemp = PHead; 
    while (Ptemp != NULL) {
        if (Ptemp->Ifct == 1) {
            struct Place *Plctemp = Ptemp->Trace;
            while (Plctemp != NULL) {
                if (Day - Plctemp->Day <= 1 && near(Plctemp->IndB, Plctemp->IndU, X, Y)) {
                    ++tot;
                    break;
                }
                Plctemp = Plctemp->Next;
            }
        }
        Ptemp = Ptemp->Next;
    }

    printf("Inflected: %d\n", tot);
    return;
}

void destroyB(struct Building *B) {
    struct Building *Btemp = B;
    if (B == NULL) return;
    while (B->Next != NULL) {
        B = B->Next;
        free(Btemp);
        Btemp = B;
    }
    free(B);
    return;
}

void destroyPlc(struct Place *Plc) {
    struct Place *Plctemp = Plc;
    if (Plc == NULL) return;
    while (Plc->Next != NULL) {
        Plc = Plc->Next;
        free(Plctemp);
        Plctemp = Plc;
    }
    free(Plc);
    return;
}

void destroyP(struct Person *P) {
    struct Person *Ptemp = P;
    if (P == NULL) return;
    while (P->Next != NULL) {
        P = P->Next;
        destroyPlc(Ptemp->Trace);
        free(Ptemp);
        Ptemp = P;
    }
    free(P);
    return;
}

int main()
{
    printf("\
        Input 1 to add building message;\n\
        Input 2 to add person message;\n\
        Input 3 to change one person's status;\n\
        Input 4 to report the place a person goes;\n\
        Input 5 to ask one's trace;\n\
        Input 6 to ask the number of Inflected persons;\n\
        Input -1 to quit.\n");
    BHead = NULL;
    PHead = NULL;
    while (1) {
        printf("Input the operation number: ");
        int opr;
        scanf("%d", &opr);
        if (opr == -1) break;
        else if (opr == 1) {
            printf("Please input the geometry position X,Y of this building, and the BuildingID and UnitID:\n");
            double X, Y; int IndB, IndU;
            scanf("%lf%lf%d%d", &X, &Y, &IndB, &IndU);
            AddBuilding(X, Y, IndB, IndU);
            printf("Done.\n");
        } else if (opr == 2) {
            printf("Please input the person's ID, and a flag number for his status, 0 for not inflected and 1 for inflected:\n");
            int Ind, Ifct;
            scanf("%d%d", &Ind, &Ifct);
            AddPerson(Ind, Ifct);
            printf("Done.\n");
        } else if (opr == 3) {
            printf("Please input the person's ID, and his new status:\n");
            int Ind, Ifct;
            scanf("%d%d", &Ind, &Ifct);
            Inflect(Ind, Ifct);
            printf("Done.\n");
        } else if (opr == 4) {
            printf("Please input the person's ID, the date of today, and the BuildingID and the UnitID of the building he goes:\n");
            int Ind, Day, IndB, IndU;
            scanf("%d%d%d%d", &Ind, &Day, &IndB, &IndU);
            PersonGo(Ind, Day, IndB, IndU);
            printf("Done.\n");
        } else if (opr == 5) {
            printf("Please input the person's ID, and the date of today:\n");
            int Ind, Day;
            scanf("%d%d", &Ind, &Day);
            ShowTrace(Ind, Day);
        } else if (opr == 6) {
            printf("Please input the geometry position X,Y, and the date of today:\n");
            double X, Y;
            int Day;
            scanf("%lf%lf%d", &X, &Y, &Day);
            ShowInflect(X, Y, Day);
        } else 
            printf("Invalid operation number!\n");
    }
    destroyB(BHead); destroyP(PHead);
    return 0;
}