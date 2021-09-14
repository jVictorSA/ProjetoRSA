#include <stdio.h>
#include <string.h>
#include <math.h>

void SalvaEmTxt(int *chave, int a);
int chavesPublicas(int *chaves);
int expoenteE(int e, int p, int q);
int euclides(int numerador, int divisor);
int criptografar (char letra, int chaveN, int *chaveE);
int descriptografar();
int chavePrivada(int d, int n);
int numeroPrimo(int num);
int frase ();
int convBin(int deci, int *binario);
int expModRap(int base, int mod, int *exp);
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
    printf("\n");
    
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

int descriptografar()
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

	chavePrivada(d, n);
}

//Recebe e e n para calcular a chave privada e descriptografar a mensagem
int chavePrivada(int d, int n)
{	
	int *dBin[16];
	*dBin = convBin(151, &dBin);

	int abc = abc + expModRap(151, n, &dBin);
	abc = abc%n;
	printf("%d\n", abc);
	printf("%d\n", n);

	char frase[tamanhoString], lixo;
	int quant = 0;
	//int tFrase = strlen(frase);
	printf("Insira a quantidade de caracteres da mensagem: ");
	scanf("%d", &quant);

	int c_array[quant]; //ARRAY CRIPTOGRAFADO
	int o_array[quant]; //ARRAY PRONTO PARA SER CONVERTIDO PARA LETRAS

	printf("Agora insira a mensagem criptografada (Separada por espaco): ");
	int numCache;

	for(int i = 0; i < quant; i++)
	{
		scanf("%d", &c_array[i]);

		numCache = 1000;
		printf("numcache - %i\n", numCache);
		printf("array - %i\n", c_array[i]);
		printf("d - %i\n", d);
		o_array[i] = numCache%n;

		//printf("%d", o_array[i]);
	}
}

//Recebe a mensagem a ser encriptada
int frase (int * fraseCifrada){
    char frase[tamanhoString], lixo;
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

        for(int i = 0; i < tamanhoString; i++){
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
    int chavesPub[2], selecao, mensCifrada[tamanhoString], mensDecifrada[tamanhoString]; // variável que recebe as chaves públicas

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
        SalvaEmTxt(&chavesPub, selecao);
        break;
    case 2: // caso a opcao seja a criptografia
        frase(mensCifrada);
        SalvaEmTxt(&mensCifrada, selecao);
        break;
    case 3: // caso a opcao seja a descriptografia
        descriptografar();
        break;
    default:
        printf("\nNumero invalido! Digite um numero entre 1 e 3!\n");
        goto inicio;
    }

    return 0;
}
