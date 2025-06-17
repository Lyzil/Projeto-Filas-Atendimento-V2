/******************************************************************************

Implementar (através de ponteiros) a versão 2.0 do sistema de atendimento já realizado, agora com a oferta de 5 opções através de um seletor:

0. Sair
1. Gerar senha
2. Abrir guichê
3. Realizar atendimento
4. Listar senhas atendidas
A opção 1 deverá incrementar o controle de senhas, gerando e enfileirando a senha gerada na fila "senhasGeradas"

A opção 2 deverá adicionar, em uma estrutura do tipo Lista, um objeto (struct) contendo o id do guichê e uma fila (senhasAtendidas) para o armazenamento das 
senhas atendidas por ele

A opção 3 deverá solicitar a digitação do id do guichê que está chamando a senha "da vez", enfileirando-a na fila "senhasAtendidas" do respectivo guichê

A opção 4 deverá solicitar a digitação do id do guichê e, na sequência, listar todas as senhas que foram atendidas por ele

Sempre que o seletor for exibido, informar a quantidade de senhas ainda aguardando atendimento e o número de guichês abertos para atendimento.

O programa só poderá ser encerrado quando a fila "senhasGeradas" estiver vazia. Ao encerrar, informar a quantidade de senhas atendidas.

*******************************************************************************/

#include <iostream>
using namespace std;

struct No
{
	int dado;
	No *prox;
};

struct NoGuiche {
    guiches dado;
    NoGuiche* prox;
};

struct guiches
{
    int IDguiche;
    FilaPonteiro* SenhasAtendidasGuiche;
};

void listarSenhasDeGuiche(NoGuiche* listaGuiches, int IDbuscado) {
    NoGuiche* auxListar = listaGuiches;
	
	while (auxListar != NULL) {
	    if (auxListar->dado.IDguiche == IDbuscado) {
	        cout << "--- Senhas atendidas pelo guiche " << IDbuscado << " ---" << endl;
            No* no auxListar->dado.SenhasAtendidasGuiche->ini;
            while (no != NULL) {
                cout << "Senha: " << no->dado << endl;
                no = no->prox;
            }
            cout << "------------------------------------------" << endl;
            return;
        }
		auxListar = auxListar->prox;
	}
	cout << "Guichê " << IDbuscado << " não encontrado." << endl;
}

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
    	FilaPonteiro* senhasGeradas = initPonteiro();
	    NoGuiche* listaGuiches = NULL;
	
	int opcao = -1, contador = 1, IDescolhido = -1, i = 0, IDexibir = -1;

	do {
        cout << "Senhas aguardando atendimento: " << countPonteiro(senhasGeradas) << endl;
        cout << "Menu de opções" << endl
             << "0. Sair" << endl
             << "1. Gerar senha" << endl
             << "2. Abrir guichê" << endl
             << "3. Realizar atendimento" << endl
             << "4. Listar senhas atendidas" << endl
             << "Escolha a opção que deseja: ";
	    cin >> opcao;

    switch (opcao) {
        case 0:
            if (!isEmptyPonteiro(senhasGeradas)) {
                cout << "Ainda tem " << countPonteiro(senhasGeradas) << " senhas em espera. Atenda todas antes de sair." << endl;
                opcao = -1; // para manter o loop aberto
            } else {
                cout << "Senhas atendidas: " << countPonteiro(senhasAtendidas) << endl;
            }       
            break;
        case 1:
            enqueuePonteiro(senhasGeradas, contador);
            cout << "Senha gerada: " << contador << endl;
            contador++;
            break;
        case 2:{
            guiches novoGuiche;
            novoGuiche.IDguiche = (i+1);
            novoGuiche.SenhasAtendidasGuiche = initPonteiro();
            i++;
            
            NoGuiche* novoNO = new NoGuiche;
            novoNO->dado = novoGuiche;
            novoNO->prox = listaGuiches;
            listaGuiches = novoNO;
            break;
        }
        case 3:
        {
            NoGuiche* aux = listaGuiches;
            bool IDencontrado = false;
            cout <<"Digite o ID do guichê: ";
            cin >> IDescolhido;
            while (aux != NULL)
            {
        		if(IDescolhido == aux->dado.IDguiche)
        		{
        		    int senha = dequeuePonteiro(senhasGeradas);
                    if (senha == -1) {
                        cout << "Nenhuma senha para atender." << endl;
                    } else {
                        enqueuePonteiro(aux->dado.SenhasAtendidasGuiche, senha);
                        cout << "Senha atendida: "<< senha << endl;
                    }
                    IDencontrado = true;
        		    break;
        		}
        		aux = aux->prox;
            }
            if (!encontrado) 
            {
                cout << "Nenhum guichê encontrado." << endl;
            }
            break;
        }
        case 4:
            cout <<"Digite o ID do guichê: ";
            cin >> IDexibir;
            listarSenhasDeGuiche(listaGuiches, IDexibir);
            break;
        
        default:
            cout << "Digite uma opção válida" << endl;
            break;
        }
    } while(opcao != 0);
    
    freeFilaPonteiro(senhasGeradas);
    freeFilaPonteiro(senhasAtendidas);

    return 0;
}
