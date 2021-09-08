#include <stdio.h>

//Gerar chave (N, E), usando dois primos P e Q
int chavesPublicas(){    
    int p, q, checPrimo, n, e;

    numPrimo1:
    printf("Digite o primeiro numero primo da chave publica: ");
    scanf("%d", &p);
    checPrimo = numeroPrimo(p);
    
    if(checPrimo == 0){
        printf("\nNumero digitado nao eh primo\n");
        goto numPrimo1;
    }

    numPrimo2:
    printf("\nDigite o segundo numero primo da chave publica: ");
    scanf("%d", &q);
    checPrimo = numeroPrimo(q);
    
    if(checPrimo == 0){
        printf("\nNumero digitado nao eh primo\n");
        goto numPrimo2;
    }

    n = p * q;
    
    expoente:
    printf("\nDigite um numero que seja coprimo a (p-1)*(q-1) para ser o expoente e: ");
    scanf("%d", &e);
    
    e = expoenteE(e, p, q);

    if(e == 0){
        printf("\nNumero digitado nao eh coprimo a (p-1)*(q-1)!\n");
        goto expoente;
    }

    printf("\np = %d\nq = %d\nn = %d\ne = %d\n", p, q, n, e);
    
    return 0;
}

/*
Função para verificar se o e é válido.
Caso seja retorna o próprio e.
Caso não retorna 0.
*/
int expoenteE(int e, int p, int q){ 
    int coprimo, mdc;

    coprimo = (p-1) * (q-1);
    mdc = euclides(e, coprimo);

    if (mdc != 1){
        return 0;
    }
    
    return e;
}

//Calcula o mdc entre a e b
int euclides(int a, int b){ 
    int resto;       
    resto = a % b;
    
    if(resto != 0){
        euclides(b, resto);
    }else{
        return b;
    }
    return 0;
}

//Verifica se um número é primo
int numeroPrimo(int num){
    
    if (num != 1){
        for(int i = 2; i < num; i++){
            if(num % i == 0 && num != i){
                return 0;
            }
        }
    }else{
        return 1;
    }
    return 0;
}    

int main(){

    printf("Seja bem vindo ao nosso RSA!!\n\n");
    chavesPublicas();

    return 0;
}
