#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 100
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
        case 'e':
            return 7;
    }
    return 8; // eof
}

int cal(int num1, int num2, char f){
    switch (f){
        case '+':
            printf("%d+%d=%d\n", num1, num2, num1+num2);
            return num1+num2;
        case '-':
            printf("%d-%d=%d\n", num1, num2, num1-num2);
            return num1-num2;
        case '*':
            printf("%d*%d=%d\n", num1, num2, num1*num2);
            return num1*num2;
        case '/':
            printf("%d/%d=%d\n", num1, num2, num1/num2);
            return num1/num2;
        case '%':
            printf("%d %d=%d\n", num1, num2, num1%num2);
            return num1%num2;
    }
    return -1;
}

void proceed(char *c, int *nums, char *fuhao, int *n_top, int *f_top, int *flag){
    // 设定符号优先级，符号在栈里和栈外时的优先级不一样
    // 若当前符号优先级比栈顶符号优先级高，则入栈
    // 若优先级较低，则逐个弹出所有符号栈里的符号，用数字栈顶的两个数字来运算，并把运算结果放入数字栈
    // ( ) + - * / % e
    int isp[] = {1, -1, 12, 12, 13, 13, 13, -1};
    int icp[] = {20, -1, 12, 12, 13, 13, 13, -1};
    if((*c)>='0' && (*c)<='9'){
        if((*flag)!=1){
            nums[++(*n_top)] = atoi(c);
            *flag=1; // 锁住
        }
    }
    else{
        if((*f_top)!=-1){        
        int p1 = icp[get_token(*c)];
        int p2 = isp[get_token(fuhao[(*f_top)])];
        // printf("\n%d, %d\n", p1, p2);
        }
        if((*f_top)==-1)
        fuhao[++(*f_top)] = *c;
        else if(icp[get_token(*c)] > isp[get_token(fuhao[(*f_top)])]){

            fuhao[++(*f_top)] = *c;
        }
        else{
            // 把之前的符号全部弹出计算
            for(int i = (*f_top); i>=0; i--){
                if (fuhao[i] == '('){
                        *f_top = *f_top - 1;
                        break;
                    }
                int num2 = nums[(*n_top)--], num1 = nums[(*n_top)--];
                int res = cal(num1, num2, fuhao[(*f_top)--]);
                // 把计算结果放入数字栈
                nums[++(*n_top)] = res;
            }
            // 继续把当前符号压入栈
            if(*c != ')')fuhao[++(*f_top)] = *c;
        }
        *flag=0; // 解锁
    }
    

}

int main(){
    int nums[MAX_LENGTH];
    int n_top=-1, f_top=-1;
    int flag = 0; // 跳过连续的数字，用于转换多位数
    char fuhao[MAX_LENGTH], in[MAX_LENGTH];
    char eof = 'e'; // 结束标识符
    scanf("%s", &in);

    for(int i = 0;i<MAX_LENGTH; i++){
        if(in[i] == '\0'){
            proceed(&eof, nums, fuhao, &n_top, &f_top, &flag); // 发出结束信号，计算已入栈元素
            break;
        }
        proceed(&in[i], nums, fuhao, &n_top, &f_top, &flag);
    }
    printf("%d", nums[n_top]);
    system("pause");
    return 0;
}