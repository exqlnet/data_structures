#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_ITERM 100
#define MAX_IN_STRING 100
#include <string.h>


typedef struct{
    char iterms[MAX_STACK_ITERM];
    int top;
}stack;

typedef struct{
    int iterms[MAX_STACK_ITERM];
    int top;
}num_stack;

char pop(stack s){
    char o = s.iterms[s.top];
    s.iterms[s.top] = '\0';
    s.top = s.top - 1;
    return o;
}

void append(stack *s, char i){
    (*s).iterms[++(*s).top] = i;
}

char num_pop(num_stack *s){
    char o = (*s).iterms[(*s).top];
    (*s).iterms[(*s).top] = '\0';
    (*s).top = (*s).top - 1;
    return o;
}

void num_append(num_stack *s, int i){
    (*s).iterms[++(*s).top] = i;
}

enum symbol{
    lparen=0,rparen, plus, minus, times, divide, mod, eos
};

int get_token(char symbol){
    switch (symbol){
        case '(':
            return 0;
        case ')':
            return 1;
        case '+':
            return 2;
        case '-':
            return 3;
        case '*':
            return 4;
        case '/':
            return 5;
        case '%':
            return 6;
    }
    return 8; // eof
}

void pop_all(stack *s, char *c, int *op){
    for(int i=(*s).top;i>=0;i--){
        c[++(*op)]=(*s).iterms[i];
        c[*op + 1] = '\0';
        (*s).iterms[i] = '\0';
    };
}


char * suffix(char *in, char *out){
    stack fuhao;
    fuhao.top = -1;
    int op = -1;
    char element;
    
    int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
    int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};


    for(int i=0; i<=strlen(in);i++){
        if(in[i]>='0'&&in[i]<='9'){
            out[++op] = in[i];
        }
        switch (in[i]){
            case '(':
                append(&fuhao, in[i]);
                break;
            case ')':
                for(int x=fuhao.top--; x>=0; x++){
                    if(fuhao.iterms[i] == '(')break;
                    out[++op] = fuhao.iterms[i];

                    if(i==-1)printf("synax error!");
                }
                break;
            case '+':
                if(icp[get_token('+')] > icp[get_token(fuhao.iterms[fuhao.top])])
                append(&fuhao, '+');
                else pop_all(&fuhao, out, &op);
                break;
            case '-':
                if(icp[get_token('-')] > icp[get_token(fuhao.iterms[fuhao.top])])
                append(&fuhao, '-');
                else pop_all(&fuhao, out, &op);
                break;
            case '*':
                if(icp[get_token('*')] > icp[get_token(fuhao.iterms[fuhao.top])])
                append(&fuhao, '*');
                else pop_all(&fuhao, out, &op);
                break;
            case '/':
                if(icp[get_token('/')] > icp[get_token(fuhao.iterms[fuhao.top])])
                append(&fuhao, '/');
                else pop_all(&fuhao, out, &op);
                break;
            case '%':
                if(icp[get_token('%')] > icp[get_token(fuhao.iterms[fuhao.top])])
                append(&fuhao, '%');
                else pop_all(&fuhao, out, &op);
                break;
            case '\0':
                pop_all(&fuhao, out, &op);
        }
    }
    printf("%s\n", out);
    return out;
}

int main(){

    // system("pause");
    stack fuhao;
    num_stack shuzi;
    fuhao.top = -1;shuzi.top=-1;
    char input[MAX_IN_STRING], in[MAX_IN_STRING];
    int num1, num2;
    char z[2];
    scanf("%s", &input);
    suffix(input, in);
    for (int i = 0;i<=MAX_IN_STRING;i++){
        if (in[i] == '\0'){
            break;
        }
        if (in[i]>='0' && in[i]<='9'){
            z[0] = in[i];
            num_append(&shuzi, atoi(z));
            continue;
        }
        switch (in[i]){
            case '+':
                num2 = num_pop(&shuzi);
                num1 = num_pop(&shuzi);
                num_append(&shuzi, num2+num1);
                break;
            case '-':
                num2 = num_pop(&shuzi);
                num1 = num_pop(&shuzi);
                num_append(&shuzi, num2-num1);
                break;
            case '*':
                num2 = num_pop(&shuzi);
                num1 = num_pop(&shuzi);
                num_append(&shuzi, num2*num1);
                break;
            case '/':
                num2 = num_pop(&shuzi);
                num1 = num_pop(&shuzi);
                num_append(&shuzi, num2/num1);
                break;
            case '%':
                num2 = num_pop(&shuzi);
                num1 = num_pop(&shuzi);
                num_append(&shuzi, num2%num1);
                break;
        }
    }
    printf("\n%d", shuzi.iterms[0]);
    system("pause");
    return 0;
}


