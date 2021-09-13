#include <stdio.h>

/*Gerar chave (N, E), usando dois primos P e Q
O argumento *chaves é necessário para retornar as chaves publicas 
em um array, forma mais víavel que achei pra retornar a chave para
a criação do arquivo .txt
*/
int chavesPublicas(int *chaves[2]){    
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

    //n = p * q; Antiga implementação
    chaves[0] = p * q; //armazena a chave n no par chaves
    
    expoente:
    printf("\nDigite um numero que seja coprimo a (p-1)*(q-1) para ser o expoente e: ");
    scanf("%d", &e);
    
    //e = expoenteE(e, p, q); Antiga implementação
    chaves[1] = expoenteE(e, p, q); // armazena a chave e no par chaves

    if(e == 0){
        printf("\nNumero digitado nao eh coprimo a (p-1)*(q-1)!\n");
        goto expoente;
    }

    //printf("\np = %d\nq = %d\nn = %d\ne = %d\n", p, q, n, e); printf apenas pra saber se os numeros estão sendo processados corretamente
    
    return chaves; //retorna o vetor chaves
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
       return euclides(b, resto);
    }
    
    return b;
}

//Verifica se um número é primo
int numeroPrimo(int num){
    
    if (num != 1){
        for(int i = 2; i < num; i++){
            if(num % i == 0 && num != i){
                printf("%d\n", i);
                return 0;
            }
        }
    }else{
        return 1;
    }
}    
int criptografar (){

    char letra;
    int num;
    char alfabeto[27]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
    char alfabetomin[27]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
    scanf("%c", &letra);
    for(int i = 0;i < 28; i++){

        if(letra == alfabeto[i]||letra == alfabetomin[i]){

            num = i+2;

        }

    }

    printf("%d", num);

    return 0;

}
 int frase (){

        char frase[25];

        printf("Digite a mensagem: \n");

        gets(frase);

        printf("%s", frase);

    }
int main(){
    int print[2]; // variável que recebe as chaves públicas

    printf("Seja bem vindo ao nosso RSA!!\n\n");
    chavesPublicas(&print);

    return 0;
}
