/******************************************************************************

Implementar um sistema simples de atendimento com a oferta de 3 opções através de um seletor:

0. Sair
1. Gerar senha
2. Realizar atendimento


A opção 1 deverá incrementar o controle de senhas, gerando e enfileirando a senha gerada na fila "senhasGeradas"

A opção 2 deverá consumir a senha "da vez", exibindo-a na tela e enfileirando-a na fila "senhasAtendidas".

Sempre que o seletor for exibido, informar a quantidade de senhas ainda aguardando atendimento.

O programa só poderá ser encerrado quando a fila "senhasGeradas" estiver vazia. Ao encerrar, informar a quantidade de senhas atendidas.

Obs: Desenvolver essa solução implementando as filas em forma ponteiro e de vetor.

*******************************************************************************/

#include <iostream>
using namespace std;

#define MAX 6 // add um a mais para poder funcionar corretamente

// fila em formato de vetor

struct FilaVetor
{
	int nos[MAX];
	int ini;
	int fim;
};

FilaVetor* initVetor()
{
	FilaVetor *f = new FilaVetor;
	f->ini = 0;
	f->fim = 0;
	return f;
}

int isEmptyVetor(FilaVetor *f)
{
	return (f->ini == f->fim);
}

int incrementa(int i)
{
    return (i + 1) % MAX;
}

int countVetor(FilaVetor *f)
{
	int qtde = 0;
	int i = f->ini;
	while (i != f->fim)
	{
		qtde++;
		i = incrementa(i);
	}
	return qtde;
}
int enqueueVetor(FilaVetor *f, int v)
{
	int podeEnfileirar = (incrementa(f->fim) != f->ini);
	if (podeEnfileirar)
	{
		f->nos[f->fim] = v;
		f->fim = incrementa(f->fim);
	}
	return (podeEnfileirar);
}
int dequeueVetor(FilaVetor *f)
{
	int ret;
	if (isEmptyVetor(f))
	{
		ret = -1;
	}
	else
	{
		ret = f->nos[f->ini];
		f->ini = incrementa(f->ini);
	}
	return ret;
}

void freeFilaVetor(FilaVetor *f)
{
	free(f);
}

//fila em formato de ponteiro.

struct No
{
	int dado;
	No *prox;
};

struct FilaPonteiro
{
	No *ini;
	No *fim;
};

FilaPonteiro *initPonteiro()
{
	FilaPonteiro *f = new FilaPonteiro;
	f->ini = NULL;
	f->fim = NULL;
	return f;
}

int isEmptyPonteiro(FilaPonteiro *f)
{
	return (f->ini == NULL);
}

int countPonteiro(FilaPonteiro *f)
{
	int qtde = 0;
	No *no;
	no = f->ini;
	while (no != NULL)
	{
		qtde++;
		no = no->prox;
	}
	return qtde;
}

void enqueuePonteiro(FilaPonteiro *f, int v)
{
	No *no = new No;
	no->dado = v;
	no->prox = NULL;
	if (isEmptyPonteiro(f))
	{
		f->ini = no;
	}
	else
	{
   	    f->fim->prox = no;		
	}
	f->fim = no;
}

int dequeuePonteiro(FilaPonteiro *f)
{
	int ret;
	if (isEmptyPonteiro(f))
	{
		ret = -1;
	}
	else
	{
		No *no = f->ini;
		ret = no->dado;
		f->ini = no->prox;
		if (f->ini == NULL)
		{
			f->fim = NULL;
		}
		free(no);
	}
	return ret;
}

void freeFilaPonteiro(FilaPonteiro *f)
{
    No *no;
	no = f->ini;
	while (no != NULL)
	{
		No *aux = no->prox;
		free(no);
		no = aux;
	}
	free(f);
}

int main()
{
    FilaVetor* senhasGeradas = initVetor();
	FilaPonteiro* senhasAtendidas = initPonteiro();
	
	int opcao = -1;
	int contador = 1;

	do {
        cout << "Senhas aguardando atendimento: " << countVetor(senhasGeradas) << endl;
        cout << "Menu de opções" << endl
             << "0. Sair" << endl
             << "1. Gerar senha" << endl
             << "2. Realizar atendimento" << endl
             << "Escolha a opção que deseja: ";
	    cin >> opcao;

        switch (opcao) {
            case 0:
                if (!isEmptyVetor(senhasGeradas)) {
                    cout << "Ainda tem " << countVetor(senhasGeradas) << " senhas em espera. Atenda todas antes de sair." << endl;
                    opcao = -1; // para manter o loop aberto
                } else {
                    cout << "Senhas atendidas: " << countPonteiro(senhasAtendidas) << endl;
                }       
                break;
            case 1:
                if (enqueueVetor(senhasGeradas, contador)) {
                    cout << "Senha gerada: " << contador << endl;
                    contador++;
                } else {
                    cout << "Fila de senhas geradas cheia! Aguarde atendimento." << endl;
                }
                break;
            case 2:{
                int senha = dequeueVetor(senhasGeradas);
                if (senha == -1) {
                    cout << "Nenhuma senha para atender." << endl;
                } else {
                    enqueuePonteiro(senhasAtendidas, senha);
                    cout << "Senha atendida: "<< senha << endl;
                }
                break;
            }
            default:
                cout << "Digite uma opção válida" << endl;
                break;
        }
    } while(opcao != 0);
    
    freeFilaVetor(senhasGeradas);
    freeFilaPonteiro(senhasAtendidas);

    return 0;
}
