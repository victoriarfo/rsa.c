#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//Função para descobrir o MDC
long long int mdc( long long int a, long long int b)
{
	long long int resto;
     //MDC feito como algoritmo de Euclides
	while(a % b != 0)
	{
		resto = a;
		a = b;
		b = resto % a;
	}
	return b;
}
//Aplica o Teorema do Resto
long long int teoremadoresto(long long int m, long long int n, long long int e)
{
	long long int contador, resto = 1;
	for(contador = 1; contador <= e; contador++)
	{
		resto = (resto * m % n) % n;
	}
	return resto;
}
//Função para verificar se é primo
long long primo(long long int p,long long int *pont)
{
	int i, e_primo = 1;
	long long int raiz; 
	raiz = sqrt(p);
	if(p == 1)
	{
	    e_primo = 0;
	}
    if(p == 0)
     {
        e_primo = 0;
     }
	for(i = 2 ;i <= raiz; i++)
	{
		if(p % i == 0)
		{
		    e_primo = 0;
		}
	}
	if(e_primo == 0)
	{
		printf("O número: %lld, não é primo redigite-o:", p);
		scanf("%lld", pont);
		p = *pont;
		primo(p, pont);
	}
}
//Função para calcular o inverso modular
long long int inversoMod(long long int a, long long int b)
{
    long long int quociente[100000], valor[100000], contador = 0, auxiliar1 = 0, auxiliar2 = 0, resto = 0, d = 0, phi = 0;
    phi = a;
	//While para salvar os quocientes 
    while(b != 0)
    {
        quociente[contador] = a/b;
        contador++;
        resto = a % b;
        a = b;
        b = resto;
    }
    valor[0] = 1;
	//Ciclo de repetição para salvar os valores do MDC
    for (auxiliar2 = contador - 2; auxiliar2 >= 0; auxiliar2--)
    {
        if(auxiliar1 == 0)
        {
            valor[auxiliar1 + 1] = quociente[auxiliar2] * valor[auxiliar1];
        }
        else
        {
            valor[auxiliar1 + 1] = (quociente[auxiliar2] * valor[auxiliar1]) + valor[auxiliar1 -1];
        }
		auxiliar1++;
    }
	//Após isso, encontramos d
    if (auxiliar1 % 2 == 0)
    {
        d = valor[auxiliar1];
        return d;
    }
    else
    {
        d = -valor[auxiliar1];
        while(1)
        {
            d = d + phi;
            if (d >= 0)
            {
                break;
            }
        }
        return d;
    }
}
//Função para verificar se os números digitados eram iguais
long long igual(long long int*a, long long int*b)
{
	printf("Os números não podem ser iguais redigite-os:");
	scanf("%lld %lld", a, b);
    //Após obter os novos números, verifica se são primos
	primo(*a, a);
	primo(*b, b);
	if(*a == *b)
	{
		igual(a,b);
	}
}
long long verificarmenor(long long int *p, long long int *q)
{
	printf("O produto de p e q tem que ser maior que o alfabeto redigite-os:\nDigite p e q:");
	scanf("%lld%lld",p,q);
	primo(*p, p);
	primo(*q, q);
	if((*p)*(*q)<28)
	{
		verificarmenor(p,q);
	}
	if(p == q)
	{
		igual(p, q);
	}
}
//Função para verificar se "e" é relativamente primo a "p" * "q"(p multiplicando q)
long long verificar(long long int e, long long int p, long long int q,long long int *pont)
{
	long long int auxiliar;
	p = p - 1;
	q = q - 1;
	auxiliar = p * q;
	if(mdc(e, auxiliar) != 1)
	{
		printf("O  número %lld, nao é relativamente primo a (p - 1)(q -1), redigite-o:", e);
		scanf("%lld", pont);
		e = *pont;
		verificar(e, p, q, pont);
	}
}
//Função para converter o texto em números
void converte(char frase[],long long int *ponteiro)
{
	//Foi utilizado ponteiros para a mudança ocorrer no array original
	int contador, auxiliar;
	contador = strlen(frase);
	for(auxiliar = 0; auxiliar < contador - 1; auxiliar++)
	{
		if(frase[auxiliar] ==' ')
		{
			*(ponteiro + auxiliar) = frase[auxiliar] - 4;
			
		}
		else
		{
			*(ponteiro + auxiliar) = frase[auxiliar] - 63;
		}
	}
}
//Função para encriptar a mensagem
long long criptografar(long long int *pont, long long int n, long long int e, int contador1)
{
	int contador;
	for(contador = 0; contador < contador1 - 1; contador++)
	{
		*(pont + contador) = teoremadoresto(*(pont + contador),n,e);
	}
}
//Função para desencriptar a mensagem
long long descriptografar(long long int p,long long int q, long long int e, long long int frasenumerada[], char *frase, int contador)
{
	long long int auxiliar1, d, contador1, n;
	auxiliar1 = (p - 1) * (q - 1);
	n = p * q;
	d = inversoMod(auxiliar1,e);
	for(contador1 = 0; contador1 < contador; contador1++)
	{
		if(teoremadoresto(frasenumerada[contador1], n, d)==28)
		{
			*(frase + contador1)=28+4;
		}
		else
		{
			*(frase + contador1)=teoremadoresto(frasenumerada[contador1], n, d)+63;
		}
		
	}
}
//Função para criar o arquivo .txt contendo a chave pública gerada
long long criararquivo(long long int chave, long long int e)
{
	FILE *chav;
	chav= fopen("chave.txt", "w");
	fprintf(chav,"A chave publica é :%lld %lld",chave, e );
	fclose(chav);
}
//Função para criar o arquivo .txt contendo o texto encriptado
long long criararquivocr(long long int chave[], long long int n,long long int e,int cont1)
{
	int cont;
	FILE *chav;
	chav= fopen("encriptado.txt", "w");
	for(cont=0; cont<cont1-1; cont++)
	{
		fprintf(chav,"%lld ",chave[cont]);
	}
	fclose(chav);
}
//Função para criar o arquivo .txt contendo o texto desencriptado
long long criararquivodecr(char chave[])
{
	int cont;
	FILE *chav;
	chav= fopen("desencriptado.txt", "w");
	fprintf(chav,"O texto desencriptado é: %s", chave);
	fclose(chav);
}
int main()
{
	int contador, contador1, funcao, sair = 0;
	long long int p, q, e, n, frasen[10000]; char frase [10000];	
	while(1)
	{
		system("clear");
		system("tput reset");
		//printf("\e[H\e[2J");
		printf("**********                                           CRIPTOGRAFIA RSA                                      **********\n\n");
		printf("                                          Leila Maria  Victória Regina  Steven Davis                                 \n\n");
		printf("-> Selecione uma opção:   \n\n");
		printf("-> 1 = Gerar a chave pública  					 \n");
		printf("-> 2 = Encriptar a mensagem  			     	 \n");
		printf("-> 3 = Desencriptar a mensagem  				 \n\n");
		printf("-> Digite o número da opção que deseja ultilizar: ");
		scanf("%d", &funcao);
		system("clear");
		system("tput reset");
		getchar();

		// Executa os comandos atribuidos a função 1 - Gerar Chave Pública
		if(funcao == 1)
		{
			printf("*** Opção 1 ***\n\n");
			printf("Digite os números primos p e q:");
			scanf("%lld%lld", &p, &q);

			//verificar se P e Q são iguais
			if(p == q)
			{
				igual(&p, &q);
			}
			if(p*q<28)
			{
				verificarmenor(&p,&q);
			}
			//verificar se os valores de P e Q são primos através da função
			//onde caso nao seja primo, será solicitado novamente ate que o valor seja primo
			primo(p, &p);
			primo(q, &q);
			printf("Agora digite o expoente ¨E¨ que é relativamente primo a (p - 1)(q -1):");
			scanf("%lld", &e);

			//verificar se o E é relativamente primo ao produto (p-1)*(q-1)
			verificar(e, p, q, &e);
			printf("\nAguarde...\nChave pública gerada!\n");

			//após verificação um arquivo é criado com a chave pública gerada
			criararquivo(p*q,e);
			printf("\n\nCaso deseje voltar ao menu, digite 1 e caso contrário, digite 0 para encerrar: ");

			//Após a conclusão da Opção 1, verificar se o usuário quer continuar ou encerrar o programa.
			scanf("%d", &sair);
			if (sair == 1)
			{
				continue;
			}
			else
			{
				printf("Obrigado!\n");
				break;
			}			
		}

		// Executa os comandos atribuidos a função 2 - Encriptar
		if (funcao == 2)
		{
			printf("*** Opção 2 ***\n\n");

			printf("Digite o texto a ser encriptado: ");

			//Inicialmente será solicitado o texto a ser encriptado
			fgets(frase, 4000, stdin);

			//Logo após, será solicitado a chave pública, para encriptar o texto
			//O texto será criptografado com base nos valores de (p * q) e E
			printf("\nDigite a chave pública para encriptar:");
			scanf("%lld%lld", &n, &e);
			printf("Aguarde, estamos encriptando sua mensagem...\n");

			//Nessa etapa os valores de cada letra basearam-se na Tabela ASCII.
			//Considerando apenas as letras maiúsculas, e enquadrando o alfabeto no intervalo de 2 à 28, incluindo o espaço.
			converte(frase, frasen);

			//verificar tamanho da frase.
			contador1 = strlen(frase);

			//Após a alteração dos valores de cada letra, a Criptografia é feita
			criptografar(frasen, n, e, contador1);
			printf("Pronto! Sua mensagem foi encriptada.\n");

			//Após é criado um txt contendo a frase encriptada
			criararquivocr(frasen,n,e,contador1);
			printf("\n\nCaso deseje voltar ao menu, digite 1 e caso contrário, digite 0 para encerrar o programa: ");
			scanf("%d", &sair);

			//Após a conclusão da Opção 2, verificar se o usuário quer continuar ou encerrar o programa.
			if (sair == 1)
			{
				continue;
			}
			else
			{
				printf("Obrigado!\n");
				break;
			}
			printf("\n");
		}

		// Executa os comandos atribuidos a função 3 - Desencriptar
		if(funcao == 3)
		{
			printf("*** Opção 3 ***\n\n");
			printf("Digite os números primos p e q:");

			//Inicialmente será inserido os valores de P e Q.
			//PS: É de extrema importancia que P e Q seja o mesmo utilizado para gerar a chave pública.
			scanf("%lld%lld", &p, &q);

			//verificar se P e Q são iguais
			if(p == q)
			{
				igual(&p, &q);
			}

			//verificar se os valores de P e Q são primos através da função.
			primo(p, &p);
			primo(q, &q);
			printf("Agora digite o expoente ¨E¨ que é relativamente primo a (p - 1)(q -1):");

			//Inserir o mesmo valor de E, utilizado na chave pública.
			scanf("%lld", &e);

			//verificar se o E é relativamente primo ao produto (p-1)*(q-1).
			verificar(e, p, q, &e);

			//A leitura do arquivo txt da mensagem encriptada é feita
			FILE *chav;
			chav= fopen("encriptado.txt", "r");
			contador = 0;
			printf("Aguarde, estamos desencriptando a sua mensagem...\n");
			while (!feof(chav))
			{
				fscanf(chav,"%lld", &frasen[contador]);
				contador++;
			}
			fclose(chav);

			//Após a leitura da mensagem e dos valores de P e Q e E
			//A descriptografia é feita
			descriptografar(p, q, e, frasen, frase, (contador - 1));

			//Um arquivo txt é criado com frase desencriptada
			criararquivodecr(frase);
			printf("Pronto! Sua mensagem foi desencriptada.\n");
			printf("\n\nCaso deseje voltar ao menu, digite 1 e caso contrário, digite 0 para encerrar o programa: ");
			scanf("%d", &sair);

			//Após a conclusão da Opção 3, verificar se o usuário quer continuar ou encerrar o programa.
			if (sair == 1)
			{
				continue;
			}
			else
			{
				printf("Obrigado!\n");

				break;
			}
		}
	}
	return 0;
}
