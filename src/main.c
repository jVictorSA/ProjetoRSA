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
    int p, q, checPrimo, n, e;

    numPrimo1:
    printf("Digite o primeiro numero primo da chave publica: ");
    scanf("%d", &p);
    checPrimo = numeroPrimo(p);
    
    if(checPrimo == 0){
        printf("\nNumero digitadao nao eh primo\n");
        goto numPrimo1;
    }

    numPrimo2:
    printf("Digite o segundo numero primo da chave publica: ");
    scanf("%d", &q);
    checPrimo = numeroPrimo(q);
    
    if(checPrimo == 0){
        printf("\nNumero digitadao nao eh primo\n");
        goto numPrimo2;
    }

    n = p * q;
    e = (p - 1) * (q - 1); //Não tenho certeza se esse e equivale a (p-1)*(q-1). Temos de revisar
    
    }
