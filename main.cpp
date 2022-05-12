/* 
 * Trabalho de IALG
 * Tema do trabalho: " Carro "
 * Identificador : placa                   
 * 
*/

#include <iostream>
#include <cstring>

using namespace std;

//Declaração do registro carro
struct carro{
	string placa;
	string nome;
	string marca;
	int ano;
	string descricao;
};

//Escopo das funções utilizadas no trabalho
void inserir(carro vetor[], int &tam, int&controle, int &verifica);
void listar(carro vetor[], int&controle);
void alterar(carro vetor[], int &controle, int &posBuscado);
void excluir(carro vetor[], int &controle, int &posBuscado);
void inicializa(carro vetor[], int &capacidade);
void buscaBinaria(carro vetor[], int inicio, int fim, string buscado, int &meio);
void arraste(carro vetor[], int &controle);
void menu();
void buscaSeq(carro vetor[], int &controle, string procurado, int &posBuscado);

carro* redimensiona(carro *vetor, int &tam);

void mergeAll(carro *arr, int p, int q, int r);
carro *merge(carro *S, int inicio, int fim);


int main () {
	int contEntrada = 0, posBuscado, continua;
	int capacidade = 5;
	carro *cadastro = new carro [capacidade];
	
	int opcao;
	menu();
	cin>>opcao;
	
	//Chamada da função para inicializar o vetor com elementos neutros antes da insersão
	inicializa(cadastro, capacidade);
	
	while(opcao!=6)
	{
		if(opcao==1)
		{
			continua=1;
			while(continua==1)
			{
				cout<<endl;
				inserir(cadastro, capacidade, contEntrada, continua);
				cout<<"\nDeseja inserir um novo cadastro, digite 1: \n";
				cout<<"Para voltar ao menu, digite zero (0): \n";
				cin>>continua;
			
				while(continua!=1 and continua!=0)
				{
					cout<<"OPCAO INVALIDA! \nDigite uma opcao valida: ";
					cin>>continua;
				}
				
				if(contEntrada==capacidade)
				{
					cadastro = redimensiona(cadastro, capacidade);
				}
			}
		}
		else if(opcao==2)
		{
			excluir(cadastro, contEntrada, posBuscado);
		}
		else if (opcao==3)
		{
			listar(cadastro, contEntrada);
		}
		else if(opcao == 4)
		{
			alterar(cadastro, contEntrada, posBuscado);
		}
		else if(opcao == 5)
		{
			//cadastro = merge(cadastro,0,contEntrada-1);
		}
		
		menu();
		cin>>opcao;
		
		while(opcao<1 and opcao>6)
		{
			cout<<"Digite uma opcao valida!\n";
			cin>>opcao;
		}
	}
	cout<<"CADASTRO FINALIZADO.\n";

	
	delete [] cadastro;
	return 0;
}

//Funcão do menu com exibição de cada opção possível
void menu()
{
  cout<<"1 - Inserir um novo cadastro \n";
  cout<<"2 - Excluir\n";
  cout<<"3 - Listar\n";
	cout<<"4 - Alterar\n";
	cout<<"5 - Ordenar\n";
	cout<<"6 - Sair\n";
	cout<<"Digite uma opcao: \n";
}

//Função para inicializar todos os elementos do vetor;
void inicializa(carro vetor[], int &tam)
{
	for(int indice=0; indice<tam; indice++)
	{
		vetor[indice].placa="-1";
		vetor[indice].nome="-1";
		vetor[indice].marca="-1";
		vetor[indice].ano=-1;
		vetor[indice].descricao="-1";
	}
}

//Função que faz a entrada de dados
void inserir(carro vetor[], int &tam, int&controle, int &verifica)
{
	while(verifica==1 and controle<tam)
	{
		cout<<"Digite a placa:\n";
		cin>>vetor[controle].placa;
		cout<<"Digite o nome:\n";
		cin>>vetor[controle].nome;
		cout<<"Digite a marca:\n";
		cin>>vetor[controle].marca;
		cout<<"Digite o ano:\n";
		cin>>vetor[controle].ano;
		cout<<"Digite a descricao:\n";
		cin.ignore();
		getline(cin, vetor[controle].descricao);
		
		controle++;
		verifica=0;
	}
}

//Função que faz a saída de dados
void listar(carro vetor[], int &controle)
{
	if(controle!=0)
	{
		cout<<"\nListagem dos elementos abaixo:\n";
		cout<<"\tPLACA\t\tNOME\t\tMARCA\t\tANO\t\tDESCRICAO\n";
		cout<<endl;
		for(int indice=0; indice<controle; indice++)
		{
			cout<<"\t"<<vetor[indice].placa<<"\t";
			cout<<"\t"<<vetor[indice].nome<<"\t";
			cout<<"\t"<<vetor[indice].marca<<"\t";
			cout<<"\t"<<vetor[indice].ano<<"\t";
			cout<<"\t"<<vetor[indice].descricao<<endl;
		}
		cout<<endl;
	}
	else
		cout<<"NENHUM cadastro registrado.\n\n";
}

//Função que faz a alteração de um cadastro inserido anteriormente
void alterar(carro vetor[], int &controle, int &posBuscado)
{
	string procurado;
	cout<<"Digite a placa que deseja modificar os dados do cadastro.\nPLACA: ";
	cin>>procurado;
	
	//Chamada da função de busca para saber a posicao do elemento digitado
	buscaSeq(vetor, controle, procurado, posBuscado);
	
	//Se o vetor estiver ordenado, utilize a primeira chamada da função busca e deixe comentado a segunda (buscaSeq)
	//Caso contrário, deve-se usar a função buscaSeq, sendo que funciona para vetor ordenado ou não.
	
	//buscaBinaria(vetor, 0, controle-1, procurado, posBuscado);
	

	
	cout<<"\nDados a serem alterados:\n";
	cout<<"Placa\tNome\tMarca\tAno\tDescricao\n";
	cout<<vetor[posBuscado].placa<<"\t";
	cout<<vetor[posBuscado].nome<<"\t";
	cout<<vetor[posBuscado].marca<<"\t";
	cout<<vetor[posBuscado].ano<<"\t";
	cout<<vetor[posBuscado].descricao<<endl;
	
	cout<<endl;
	cout<<"Digite os dados do novo Cadastro: \n\n";
	cout<<"Digite a placa:\n";
	cin>>vetor[posBuscado].placa;
	cout<<"Digite o nome:\n";
	cin>>vetor[posBuscado].nome;
	cout<<"Digite a marca:\n";
	cin>>vetor[posBuscado].marca;
	cout<<"Digite o ano:\n";
	cin>>vetor[posBuscado].ano;
	cout<<"Digite a descricao:\n";
	cin.ignore();
	getline(cin, vetor[posBuscado].descricao);
	
	cout<<"Cadastro alterado com SUCESSO.\n\n";
}

//Função que faz a exclusao lógica de um cadastro atribuindo uma flag aos campos
void excluir(carro vetor[], int &controle, int &posBuscado)
{
	string buscado;
	cout<<"Digite a placa registrada para excluir o cadastro: \nPLACA: ";
	cin>>buscado;
	
	
	//Chamada da função de buscaSeq para saber a posicao do elemento digitado
	buscaSeq(vetor, controle, buscado, posBuscado);
	
	//Se o vetor estiver ordenado, utilize a primeira chamada da função busca e deixe comentado a segunda (buscaSeq)
	//Caso contrário, deve-se usar a função buscaSeq, sendo que funciona para vetor ordenado ou não.
	
	//buscaBinaria(vetor, 0, controle-1, procurado, posBuscado);
	
	
	if(vetor[posBuscado].placa == buscado)
	{
		vetor[posBuscado].placa="-1";
		vetor[posBuscado].nome="-1";
		vetor[posBuscado].marca="-1";
		vetor[posBuscado].ano=-1;
		vetor[posBuscado].descricao="-1";
		cout<<"Exclusao executada com SUCESSO.\n\n";
		arraste(vetor, controle);	
	}
	else
		cout<<"Placa digitada NAO ENCONTRADA.\n\n";
}

//Função de busca Binaria em um vetor ordenado
void buscaBinaria(carro vetor[], int inicio, int fim, string buscado, int &meio)
{	
	while(inicio<= fim)
	{
		meio=(inicio+fim)/2;
		if(vetor[meio].placa==buscado)
		{
      fim=inicio-1;
		} 
		else if (vetor[meio].placa<buscado)
		{
			inicio=meio+1;
		} 
		else if(vetor[meio].placa>buscado)
		{
			fim=meio-1;
		}
	}
}

//Função que faz o deslocamento de um cadastro para uma posicao recente desocupada:
void arraste(carro vetor[], int &controle)
{
	int cont=0;
	bool excluido=false;
	
	for(int i=0; i<controle; i++)
	{
		if(vetor[i].placa=="-1" and i!= controle-1)
		{
			vetor[i]=vetor[i+1];
			excluido=true;
		}
		
		if(excluido and vetor[i].placa==vetor[i+1].placa)
		{
			cont=i+2;
			if(cont<controle)
				vetor[i+1]=vetor[cont];
		}
	}
	controle=controle-1;
}

//Função que faz o redimensionamento do vetor
carro* redimensiona(carro *vetor, int &tam)
{
	int novaCap = tam+tam*0.2;
	carro *novoVet = new carro [novaCap];
	
	memcpy(novoVet, vetor, sizeof(carro)*tam);
	
	tam=tam+tam*0.2;
	
	delete [] vetor;
	return novoVet;
}

//Função de busca sequencial - Para um vetor não ordenado
void buscaSeq(carro vetor[], int &controle, string buscado, int &posBuscado)
{
  int i=0;
  while(i<controle and vetor[i].placa!=buscado)
		i++;  
  
  if(vetor[i].placa==buscado or i!=controle)
		posBuscado=i;
}


//SubProgramas de ordenação:(mergeSort)

carro *merge(carro *S, int inicio, int fim) {
  int meio;
  if (inicio < fim) {

    meio = (inicio + fim) / 2;
    merge(S, inicio, meio);
    merge(S, meio + 1, fim);
    mergeAll(S, inicio, meio, fim);
  }
  return S;
}


void mergeAll(carro *arr, int inicio, int meio, int fim) {

  int t_S1 = meio - inicio + 1; //tamanho vet S1
  int t_S2 = fim - meio;        //tamanho vet S2

  carro *S1 = new carro[t_S1];
  carro *S2 = new carro[t_S2];

  for (int i = 0; i < t_S1; i++)
    S1[i].placa = arr[inicio + i].placa;
  for (int j = 0; j < t_S2; j++)
    S2[j].placa = arr[meio + 1 + j].placa;

  int i, j, k;
  i = 0;
  j = 0;
  k = inicio;

  while (i < t_S1 and j < t_S2) {
    if (S1[i].placa <= S2[j].placa) {
      arr[k].placa = S1[i].placa;
      i++;
    } else {
      arr[k].placa = S2[j].placa;
      j++;
    }
    k++;
  }
  while (i < t_S1) {
    arr[k].placa = S1[i].placa;
    i++;
    k++;
  }

  while (j < t_S2) {
    arr[k].placa = S2[j].placa;
    j++;
    k++;
  }
  delete[] S1;
  delete[] S2;
  S1 = NULL;
  S2 = NULL;
}
