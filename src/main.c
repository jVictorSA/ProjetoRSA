#include <stdio.h>
#include <string.h>
#include <math.h>

void SalvaEmTxt(int *chave, int a);
int chavesPublicas(int *chaves);
int expoenteE(int e, int p, int q);
int euclides(int numerador, int divisor);
int criptografar (char letra, int chaveN, int *chaveE);
int numeroPrimo(int num);
int frase ();
int convBin(int deci, int *binario);
int expModRap(int base, int mod, int *exp);
int expMod( int exp,  int base,  int mod, int result);


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

    chaves[0] = p * q; //armazena a chave n no par chaves
    
    expoente:
    printf("\nDigite um numero que seja coprimo a (p-1)*(q-1) para ser o expoente e: ");
    scanf("%d", &e);
    printf("\n");
    
    chaves[1] = expoenteE(e, p, q); // armazena a chave e no par chaves

    if(chaves[1] == 0){
        printf("\nNumero digitado nao eh coprimo a (p-1)*(q-1)!\n");
        goto expoente;
    }
    
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
int euclides(int numerador, int divisor){ 
    int resto;       
    resto = numerador % divisor;
    
    if(resto != 0){
       return euclides(divisor, resto);
    }
    
    return divisor;
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

int criptografar (char letra, int chaveN, int *chaveE){
    unsigned long long int num;
    char alfabetoMasc[27]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
    char alfabetoMin[27]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
    //printf("\n%d\n", chaveE[1]);
    for(int i = 0; i < 28; i++){
        if(letra == alfabetoMasc[i] || letra == alfabetoMin[i]){
            num = i + 2;
            //printf("%llu conversao e mod: %d\n", num, chaveN);
            num = expModRap(num, chaveN, &chaveE);
            //printf("%llu conversao mod", num);
        }
    }
    
    return num;
}

//Recebe a mensagem a ser encriptada
int frase (int * fraseCifrada){
    char frase[45], lixo;
    int tFrase, chaveN, chaveE, *expBin[16];
    printf("");
    scanf("%c", &lixo);//Armazena o valor da tecla enter, pressionada durante a seleção da criptografia
    printf("\nDigite a mensagem:");
    gets(frase);
    
    tFrase = strlen(frase);
    int fraseCripto[tFrase]; //Vetor que vai receber os valores dos caracteres cifrados

    printf("\nAgora digite a chave publica recebebida.\nExemplo: 871 57\n\nDigite a chave publica: ");
    scanf("%d %d", &chaveN, &chaveE);

    *expBin = convBin(chaveE, &expBin);
    printf("\n%d %d %d %d %d %d %d %d\n", expBin[0], expBin[1], expBin[2], expBin[3], expBin[4], expBin[5], expBin[6], expBin[7]);

    printf("Tamanho da string: %d\n\n", tFrase);
    for (int i = 0; i < tFrase; i++){
        fraseCripto[i] = criptografar(frase[i], chaveN, &expBin);
        fraseCifrada[i] = fraseCripto[i];
    }

    for(int i = 0; i < tFrase; i++){
        printf("%d string\n", fraseCripto[i]);
    }

    return fraseCifrada;
}

//converte um numero decimal para binário, no caso, converte o expoente para sua representação binária
int convBin(int deci, int *binario){

    for (int i = 0; i < 16; i++){
        if (deci % 2 == 0){
            binario[i] = 0;
        }else{
            binario[i] = 1;
        }
        deci /= 2;
    }
    return *binario;
}

//faz a exponenciação modular rápida
int expModRap(int base, int mod, int *exp){
    int parcial = 1, mult[16], result;

    //printf("%d mod\n", mod);
    //printf("\n%d\n", exp[1]);

    for(int i = 0; i < 16; i++){
        mult[i] = 0;
        if(exp[i] == 1){
        //printf("ola");
            mult[i] = pow(2, i);
            parcial *= expMod(mult[i], base, mod, 1);
            //printf("%llu\n", parcial);
        }
    }

    result = parcial % mod;

    //printf("%llu e %llu\n", result, parcial);

    return result;
}

//calcula a exponenciação de um numero
int expMod(int exp, int base, int mod, int result){
    
    if(exp == 1){
        return (base * exp) % mod;
    }else{
        return (expMod((exp/2), base, mod, result) % mod) * (expMod((exp/2), base, mod, result)) % mod;
    }
}

//Salva as chaves em um arquivo txt
void SalvaEmTxt(int *chave, int a){
    FILE *pont_arq; //variavel que cria o aqrquivo txt

    switch(a) //switch para a criacao dos nomes de cada pasta
    {
    case 1: // caso a o��o seja a chave publica
        pont_arq = fopen("arquivo_chavePublica.txt", "w");
        
        fprintf(pont_arq, "%d\t%d\n", chave[0], chave[1]); // adiciona o valor da chave ao arquivo das chaves
        fclose(pont_arq); // fecha o arquivo

        break;
    case 2: // caso a op��o seja a criptografia
        pont_arq = fopen("arquivo_chaveCripto.txt", "w");

        for(int i = 0; i < 45; i++){
            if (chave[i] != 0){
                fprintf(pont_arq, "%d\t", chave[i]); // adiciona o valor da chave ao arquivo cripto
            }    
        }

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


}

int main(){
    int chavesPub[2], selecao, mensCifrada[45], mensDecifrada[45]; // variável que recebe as chaves públicas

    for (int i = 0; i < 45; i++){
        mensCifrada[i] = 0;
        mensDecifrada[i] = 0;
    }
    

    printf("Seja bem vindo ao nosso RSA!!\n");
    inicio:
    printf("\nDigite 1 para gerar chaves publicas\n");
    printf("Digite 2 para encriptar uma mensagem\n");
    printf("Digite 3 para desencriptar uma mensagem\n");
    printf("Note que quaisquer digitos diferentes de 1, 2 e 3 nao serao aceitos!!\n\n");
    printf("Selecione a operacao desejada: ");
    scanf("%d", &selecao);

    switch(selecao){ //switch para a cria��o dos nomes de cada pasta
    case 1: //Caso a opcao seja gerar chaves publicas
        chavesPublicas(&chavesPub);
        SalvaEmTxt(&chavesPub, selecao);
        break;
    case 2: // caso a opcao seja a criptografia
        frase(mensCifrada);
        SalvaEmTxt(&mensCifrada, selecao);
        break;
    case 3: // caso a opcao seja a descriptografia
        printf("3");
        break;
    default:
        printf("\nNumero invalido! Digite um numero entre 1 e 3!\n");
        goto inicio;
    }

    return 0;
}