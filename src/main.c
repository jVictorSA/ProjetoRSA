#include <stdio.h>

/*Gerar chave (N, E), usando dois primos P e Q
O argumento *chaves é necessário para retornar as chaves publicas 
em um array, forma mais víavel que achei pra retornar a chave para
a criação do arquivo .txt
*/
int chavesPublicas(int *chaves){    
    int p, q, checPrimo, n, e;

    numPrimo1:
    printf("\nDigite o primeiro numero primo da chave publica: ");
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
    printf("\n");
    //e = expoenteE(e, p, q); Antiga implementação
    chaves[1] = expoenteE(e, p, q); // armazena a chave e no par chaves

    if(chaves[1] == 0){
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
    return 0;

}
 int frase (){
        char frase[25];

        printf("Digite a mensagem: \n");

        gets(frase);

        printf("%s", frase);
    }

//Salva as chaves em um arquivo txt
void SalvaEmTxt(int *chave, int a){
    FILE *pont_arq; //variavel que cria o aqrquivo txt

    switch(a) //switch para a cria��o dos nomes de cada pasta
    {
    case 1: // caso a o��o seja a chave publica
        pont_arq = fopen("arquivo_chavePublica.txt", "w");
        break;
    case 2: // caso a op��o seja a criptografia
        pont_arq = fopen("arquivo_chaveCripto.txt", "w");
        break;
    case 3: // caso a op��o seja a descriptografia
        pont_arq = fopen("arquivo_chaveDescripto.txt", "w");
        break;
    }

    if(pont_arq == NULL) // condi��o se n�o tiver valor na chave
    {
        printf("\nErro na abertura do arquivo!\n");
        return 1;
    }

    fprintf(pont_arq, "%d\t%d\n", chave[0], chave[1]); // adiciona o valor da cahave ao arquivo

    fclose(pont_arq); // fecha o arquivo

}

int main(){
    int chavesPub[2], selecao; // variável que recebe as chaves públicas

    printf("Seja bem vindo ao nosso RSA!!\n");
    inicio:
    printf("\nDigite 1 para gerar chaves publicas\n");
    printf("Digite 2 para encriptar uma mensagem\n");
    printf("Digite 3 para desencriptar uma mensagem\n");
    printf("Note que quaisquer digitos diferentes de 1, 2 e 3 nao serao aceitos!!\n\n");
    printf("Selecione a operacao desejada: ");
    scanf("%d", &selecao);

    switch(selecao){ //switch para a cria��o dos nomes de cada pasta
    case 1: 
        chavesPublicas(&chavesPub);
        SalvaEmTxt(&chavesPub, selecao);
        break;
    case 2: // caso a op��o seja a criptografia
        printf("2");
        break;
    case 3: // caso a op��o seja a descriptografia
        printf("3");
        break;
    default:
        printf("\nNumero invalido! Digite um numero entre 1 e 3!\n");
        goto inicio;
    }

    return 0;
}
