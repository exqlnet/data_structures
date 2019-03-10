#include <stdio.h>
#define MAX_TERMS_NUM 100

int compare(int a, int b){
    if (a>b)return 1;
    else if (a==b) return 0;
    else return -1;
}

typedef struct {
    int e;
    int coef;
} polynomial;


polynomial create_p(){
    polynomial new;
    new.e = 0;
    new.coef = 0;
    return new;
}

polynomial padd(polynomial *terms, int start_a, int start_b, int end_a, int end_b, int *next_start){
    polynomial next;
    while (start_a<=end_a&&start_b<=end_b){
        // printf("terms_a.e:%d terms_b.e:%d next_start:%d \n start_a: %d, start_b:%d\n", terms[start_a].e, terms[start_b].e, *next_start, start_a, start_b);
        switch (compare(terms[start_a].e, terms[start_b].e)){
            case 1:
                next.e = terms[start_b].e;
                next.coef = terms[start_b].coef;
                terms[*next_start] = next;
                *next_start = *next_start + 1;
                start_b ++;
                break;
            case -1:
                next.e = terms[start_a].e;
                next.coef = terms[start_a].coef;
                terms[*next_start] = next;
                *next_start = *next_start + 1;
                start_a ++;
                break;
            case 0:
                next.e = terms[start_a].e;
                next.coef = terms[start_a].coef + terms[start_b].coef;
                terms[*next_start] = next;
                start_a ++;start_b++;*next_start = *next_start + 1;
                break;
        }
    }
    if(start_a>end_a)for(int i=start_b;i<=end_b;i++){
        terms[*next_start]=terms[i];
        *next_start = *next_start + 1;
    }
    for(int i=start_a;i<=end_a;i++){
        terms[*next_start]=terms[i];
        *next_start = *next_start + 1;
    }
}


int main(){
    polynomial terms[MAX_TERMS_NUM];
    int start_a, start_b, end_a, end_b, next_start;
    // 运算2x^2+3x^3+0x^4 + 3x^3+5x^6 = 2x^2+6x^3+0x^4+5x^6
    polynomial p;
    start_a=0; end_a=2;start_b=3; end_b=4;next_start=5;
    p.e = 2;p.coef = 2;terms[0]=p;
    p.e = 3;p.coef = 3;terms[1]=p;
    p.e = 4;p.coef = 0;terms[2]=p;
    p.e = 3;p.coef = 3;terms[3]=p;
    p.e = 6;p.coef = 5;terms[4]=p;
    
    int res_start = next_start;
    padd(terms, start_a, start_b, end_a, end_b, &next_start);
    int res_end = next_start-1;
    // printf("res_start: %d, res_end:%d\n", res_start, res_end);
    for(int i = res_start; i<=res_end;i++)
    if(i==res_end)
    printf("%dx^%d", terms[i].coef, terms[i].e);
    else printf("%dx^%d+", terms[i].coef, terms[i].e);
    getchar();
}
