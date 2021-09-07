#include <stdio.h>

int numeroPrimo(num){
    
    if (num != 1){
        for(int i = 2; i < num; i++){
            if(num % i == 0 && num != i){
                return 0;
            }
        }
    }else{
        return 1;
    }
}    

int main(){
    int num1, num2, checPrimo;

    numPrimo1:
    printf("Digite o primeiro numero primo da chave publica: ");
    scanf("%d", &num1);
    checPrimo = numeroPrimo(num1);
    
    if(checPrimo == 0){
        printf("\nNumero digitadao nao eh primo\n");
        goto numPrimo1;
    }

    numPrimo2:
    printf("Digite o segundo numero primo da chave publica: ");
    scanf("%d", &num2);
    checPrimo = numeroPrimo(num2);
    
    if(checPrimo == 0){
        printf("\nNumero digitadao nao eh primo\n");
        goto numPrimo2;
    }

    
    }
