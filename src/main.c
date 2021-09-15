#include <stdio.h>
#include <string.h>
#include <math.h>
 
void SalvaEmTxt(int *chave, int a, char *message);
int chavesPublicas(int *chaves);
int expoenteE(int e, int p, int q);
int euclides(int numerador, int divisor);
int criptografar (char letra, int chaveN, int *chaveE);
char descriptografar();
char chavePrivada(int d, int n, char *mensDecifrada);
int numeroPrimo(int num);
int frase ();
int convBin(int deci, int binario[]);
int expModRap(int base, int mod, int exp[]);
int expMod( int exp,  int base,  int mod, int result);
 
//GLOBAIS
char alfabetoMasc[27]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
char alfabetoMin[27]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
 
int tamanhoString = 45;
 
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
 
   printf("\nDigite o segundo numero primo da chave publica: ");
    scanf("%d", &q);
    checPrimo = numeroPrimo(q);
     numPrimo2:
 
    if(checPrimo == 0){
        printf("\nNumero digitado nao eh primo\n");
        goto numPrimo2;
    }
 
    chaves[0] = p * q; //armazena a chave n no par chaves
    int z = (p-1)*(q-1);
 
    expoente:
    printf("\nDigite um numero que seja coprimo a %d ([p-1]*[q-1]) para ser o expoente e: ", z);
    scanf("%d", &e);
 
    chaves[1] = expoenteE(e, p, q); // armazena a chave e no par chaves
 
    if(chaves[1] == 0){
        printf("\nNumero digitado nao eh coprimo a %d!\n", z);
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
                return 0;
            }
        }
    }else{
        return 1;
    }
}    
 
int criptografar (char letra, int chaveN, int *chaveE){
    unsigned long long int num, parcial;
    int mult[16];
 
    for(int i = 0; i < 16; i++){
        mult[i] = chaveE[i];
    }
 
    for(int i = 0; i < 28; i++){
        if(letra == alfabetoMasc[i] || letra == alfabetoMin[i]){
            num = i + 2;
            num = expModRap(num, chaveN, &mult);
        }
    }
 
    return num;
}
 
char descriptografar(char *mensDecifrada)
{
    int p, q, e, checPrimo;
 
    printf("Digite dois primos p e q, e e (coprimo de (p-1)*(q-1)): \n");
 
    numPrimo1:
    scanf("%d", &p);
    checPrimo = numeroPrimo(p);
 
    if(checPrimo == 0){
        printf("\nNumero digitado nao eh primo. Digite um primo p: ");
        goto numPrimo1;
    }
 
    printf("Digite um primo q\n");
 
     numPrimo2:
 
    scanf("%d", &q);
    checPrimo = numeroPrimo(q);
 
    if(checPrimo == 0){
        printf("\nNumero digitado nao eh primo. Digite um primo q: ");
        goto numPrimo2;
    }
 
    int z = (p-1)*(q-1);
    int n = p*q;
 
    if(z < 0) z*= -1;
 
    expoente:
    printf("\nDigite um numero que seja coprimo a %d ([p-1]*[q-1]) para ser o expoente e: ", z);
    scanf("%d", &e);
    printf("\n");
 
    e = expoenteE(e, p, q);
 
    if(e == 0){
        printf("\nNumero digitado nao eh coprimo a %d!\n", z);
        goto expoente;
    }
 
    int d;
 
    //Enquanto e*d mod (p*q) for diferente de 1, continuar verificando até encontrar d
    for(int i = 0; i < 99999; i++)
    {
        d = (e*i)%z;
 
        if(d == 1)
        {
            d = i;
            break;
        }
    }
 
    char aux[tamanhoString];
 
    for (int i = 0; i < tamanhoString; i++)
    {
        aux[i] = mensDecifrada[i];
    }
    
    chavePrivada(d, n, &aux);
    for(int i = 0; i < tamanhoString; i++)
        mensDecifrada[i] = aux[i];
 
    return mensDecifrada;
}
 
//Recebe e e n para calcular a chave privada e descriptografar a mensagem
char chavePrivada(int d, int n, char *mensDecifrada)
{   
    int *dBin[16];
    *dBin = convBin(d, &dBin);
 
    unsigned long long int expModValue;
    int quant = 0;
 
    printf("Insira a quantidade de caracteres da mensagem: ");
    scanf("%d", &quant);
 
    int c_array[quant]; //ARRAY CRIPTOGRAFADO
    int o_array[quant]; //ARRAY PRONTO PARA SER CONVERTIDO PARA LETRAS
 
    printf("Agora insira a mensagem criptografada (Separada por espaco): ");
    int numCache;
 
    for(int i = 0; i < quant; i++)
    {
        scanf("%d", &c_array[i]);
 
        expModValue = expModRap(c_array[i], n, &dBin);
 
        mensDecifrada[i] = alfabetoMasc[expModValue-2];
 
    }
 
    return mensDecifrada;
}
 
//Recebe a mensagem a ser encriptada
int frase (int *fraseCifrada){
    char frase[tamanhoString], lixo;
    int tFrase, chaveN, chaveE;
    unsigned long long int *expBin[16];
    printf("");
    scanf("%c", &lixo);//Armazena o valor da tecla enter, pressionada durante a seleção da criptografia
    printf("\nDigite a mensagem:");
    gets(frase);
 
 
    tFrase = strlen(frase);
    int fraseCripto[tFrase]; //Vetor que vai receber os valores dos caracteres cifrados
 
    printf("\nAgora digite a chave publica recebebida.\nExemplo: 871 57\n\nDigite a chave publica: ");
    scanf("%d %d", &chaveN, &chaveE);
 
    *expBin = convBin(chaveE, &expBin);
 
    for (int i = 0; i < tFrase; i++){
        fraseCripto[i] = criptografar(frase[i], chaveN, &expBin);
        fraseCifrada[i] = fraseCripto[i];
    }
 
    return fraseCifrada;
}
 
//converte um numero decimal para binário, no caso, converte o expoente para sua representação binária
int convBin(int deci, int binario[]){
 
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
int expModRap(int base, int mod, int exp[]){
    unsigned long long int parcial = 1, mult[16], result, recebe[16];
 
    for(int i = 0; i < 16; i++)
        recebe[i] = exp[i];
 
    for(int i = 0; i < 16; i++){
        mult[i] = 0;
        if(exp[i] == 1){
            mult[i] = pow(2, i);
            parcial *= expMod(mult[i], base, mod, 1);
        }
    }
 
    result = parcial % mod;
 
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
void SalvaEmTxt(int *chave, int a, char *message){
    FILE *pont_arq; //variavel que cria o aqrquivo txt
 
    switch(a) //switch para a criacao dos nomes de cada pasta
    {
    case 1: // caso a o��o seja a chave publica
        pont_arq = fopen("arquivo_chavePublica.txt", "w");
 
        fprintf(pont_arq, "%d\t%d\n", chave[0], chave[1]); // adiciona o valor da chave ao arquivo das chaves
        fclose(pont_arq); // fecha o arquivo

        printf("\nArquivo gravado com sucesso!\n\n");
        break;
    case 2: // caso a op��o seja a criptografia
        pont_arq = fopen("arquivo_chaveCripto.txt", "w");
 
        for(int i = 0; i < tamanhoString; i++){
            if (chave[i] != 0){
                fprintf(pont_arq, "%d\t", chave[i]); // adiciona o valor da chave ao arquivo cripto
            }    
        }

        printf("\nArquivo gravado com sucesso!\n\n");
        break;
    case 3: // caso a op��o seja a descriptografia
        pont_arq = fopen("arquivo_chaveDescripto.txt", "w");
 
        for(int i = 0; i < tamanhoString; i++){
            fprintf(pont_arq, "%c", message[i]); // adiciona o valor da chave ao arquivo cripto 
        }

        printf("\nArquivo gravado com sucesso!\n\n");
        break;
    }
 
    if(pont_arq == NULL) // condi��o se n�o tiver valor na chave
    {
        printf("\nErro na abertura do arquivo!\n");
        return 1;
    }
 
 
}
 
int main(){
    int chavesPub[2], selecao, mensCifrada[tamanhoString];
    char mensDecifrada[tamanhoString]; // variável que recebe as chaves públicas
 
    for (int i = 0; i < tamanhoString; i++){
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
        SalvaEmTxt(&chavesPub, selecao, 0);
        break;
    case 2: // caso a opcao seja a criptografia
        frase(mensCifrada);
        SalvaEmTxt(&mensCifrada, selecao, 0);
        break;
    case 3: // caso a opcao seja a descriptografia
        descriptografar(&mensDecifrada);
        SalvaEmTxt(&mensDecifrada, selecao, &mensDecifrada);
        break;
    default:
        printf("\nNumero invalido! Digite um numero entre 1 e 3!\n");
        goto inicio;
    }
 
    return 0;
}

