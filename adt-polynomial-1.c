#include <stdio.h>
#define MAX_TERM 100

typedef struct {
    int degree;
    int coef[MAX_TERM];
} polynomial;


polynomial create_p(){
    polynomial new;
    new.degree = 0;
    for(int i = 0; i<MAX_TERM; i++)new.coef[i] = 0;
    return new;
}


polynomial padd(polynomial p1,polynomial p2){
    polynomial res = create_p();
    if(p1.degree >= p2.degree)res.degree = p1.degree;
    else res.degree=p2.degree;

    for(int i = 0; i < res.degree;i++){
        res.coef[i] = p1.coef[i] + p2.coef[i];
    }

    return res;
}


int main(){
    polynomial p1 = create_p(), p2 = create_p();
    p1.degree = 5;
    for(int i = 0; i < p1.degree; i++)p1.coef[i] = i;
    p2.degree = 6;
    for(int i = 0; i < p2.degree; i++)p2.coef[i] = 2;
    polynomial pr = padd(p1, p2);
    printf("degree: %d\n", pr.degree);
    printf("coef: ");
    for(int i = 0; i < pr.degree; i++)printf("%d ", pr.coef[i]);
    printf("%d", pr.coef[5]);
    getchar();
}
