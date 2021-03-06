/* Pontificia Universidade Catolica de Goias
 * 
 * Trabalho feito em grupo:
 * 
 * Alunos :
 * Vitor Gabriel Silva Lima e Wudson Freitas Leandro.
 * 
 */


#include<iostream>
#include<time.h>
#include<stdlib.h>
#include <ctime>
#include<time.h>

using namespace std;

class Item
{
    private:
        int chave;
        string str;

    public:
        void setChave(int);
        int getChave()const;
        string getStr()const;
        Item();
};

void Item::setChave(int aux){
    chave = aux;
}

int Item::getChave()const{
    return chave;
}

string Item::getStr()const{
    return str;
}

Item::Item(){
    str="Esta e uma string padronizada. \n";
    chave = 0;
}

class Ordena
{
    public:
        static void selectionSort(Item**, int );
        static void bubblesort(Item**, int );
        static void shellSort(Item**, int );
        static void mergesort (Item **, int );
        static void mergesort (Item **, Item **, int , int );
        static void intercala (Item **, Item **, int , int , int );
        static void quickSort(Item ** , int );
        static void quickSort(Item **, int , int );

};

void Ordena::selectionSort(Item** vetor,int tamanho)
{
    int imin=0;
    Item *aux=0,*left=0,*right=0;


    for (int i=0;i<(tamanho-1);i++)
    {
        imin=i;

        for (int j=(i+1);j<tamanho;j++)
        {
            left=vetor[imin];
            right=vetor[j];

            if  ((right->getChave()) < (left->getChave())) imin=j;
        }

        if  (imin!=i)
        {
            aux=vetor[i];
            vetor[i]=vetor[imin];
            vetor[imin]=aux;
            aux=0;
        }
    }
}

void Ordena::bubblesort(Item**vetor,int tam ){
    if (vetor == 0) return;
    int lsup, bolha, j;
    Item *aux=0;
    lsup=tam-1;
    do{
        bolha=0;
        for (j = 0; j <lsup; j++){
            if (vetor[j]->getChave()>vetor[j+1]->getChave()){
                aux=vetor[j];
                vetor[j]=vetor[j+1];
                vetor[j+1]=aux;
                bolha=j;
            }
        }
        lsup=bolha;
    }while(lsup>0);
}

void Ordena::shellSort(Item**vetor, int tam) {
	int i, j, h;
	Item* aux;
	for(h = 1; h < tam; h = 3*h+1); /* calcula o h inicial. */
	while(h > 0) {
		h = (h-1)/3; /* atualiza o valor de h. */
		for(i = h; i < tam; i++) {
			aux = vetor[i];
			j = i;
			/* efetua compara��es entre elementos com dist�ncia h: */
			while(vetor[j - h]->getChave() > aux->getChave()) {
				vetor[j] = vetor[j - h];
				j -= h;
				if(j < h) break;
			}
			vetor[j] = aux;
		}
	}
}

void Ordena::mergesort (Item **A, int tam)
{
	if(A)
	{
		Item **B = new Item*[tam];
		int ini = 0;
		int fim = tam-1;
		mergesort (A, B, ini, fim);
		delete [] B;
	}
}
void Ordena::mergesort (Item **A, Item **B, int ini, int fim)

{
	if(fim == ini)
	{
		return;
	}
	else
	{
		int meio = (ini + fim) /2;
		mergesort (A, B, ini, meio );
		mergesort (A, B, meio+1, fim);
		intercala (A, B, ini, meio , fim);
		return;
	}
}

void Ordena::intercala (Item **A, Item **B, int ini, int meio, int fim)
{
	int i = ini, j = meio+1, k = ini;
	while( i < meio+1 && j < fim+1 )
	{
		if(A[i]->getChave() < A[j] ->getChave() )
		{
			B[k] = A[i]; i++; k++;
		}
		else
		{ 
			B[k] = A[j]; j++; k++;
		}
	}
	while( i < meio+1 ) 
	{ /*copia restante da 1a. metade.*/
		B[k] = A[i]; k++; i++;
	}
	while ( j < fim+1 ) 
	{ /*copia restante da 2a. metade.*/
		B[k] = A[j]; k++; j++;
	}
	for(k = ini; k < fim+1; k++)
	{ /* copia de volta para A */
		A[k] = B[k];
	}
}

void Ordena::quickSort(Item **vetor, int Esq, int Dir)
{
	Item *x = 0,

	*aux = 0, *t = 0; /* Piv� e auxiliares*/

	int i = 0, j = 0; /* Apontadores para o sub-vetor */
	if (Dir > Esq) 
	{ /* ????Subvetores vazios???? */
		x = vetor[Dir]; /* Define o piv� */
		i = Esq; /* Inicializa apontador da esq */
		j = Dir-1; /* Inicializa apontador da dir */
		for (;;) 
		{ /* Faz a varredura no vetor */
			aux = vetor[i];
			/* Percorre a partir da esquerda */
			while (i < Dir && aux->getChave() < x->getChave()) { i++; aux = vetor[i];}
			aux = vetor[j];
			/* Percorre a partir da direita */
			while (j >= Esq && aux->getChave() > x->getChave()) { j--; aux = vetor[j];}
			if (i >= j) break; /* ????Apontadores se cruzaram???? */
			/* Faz a troca entre os elementos */
			t = vetor[i]; vetor[i] = vetor[j]; vetor[j] = t;
			i++; j--;
		}
		/* Coloca o piv� na posi��o ordenada */
		t = vetor[i]; vetor[i] = vetor[Dir]; vetor[Dir] = t;
		quickSort(vetor, Esq, i-1); /* Ordena sub-vetor da esquerda */
		quickSort(vetor, i+1, Dir); /* Ordena sub-vetor da direita */
	}
}

void Ordena::quickSort(Item ** V, int tam)
{
	int inicio = 0, fim = tam-1;
	quickSort(V, inicio, fim);
}

class testaOrdena
{
    private:
        int tam;
        Item**vetor;

    public:
        bool setTam(int);
        void preencheVetor();
        void mostraVetor(Item**)const;
        Item**copiaVetor();
        testaOrdena();
        ~testaOrdena();
        void menu();
        void destroiVetor(Item**);
};

bool testaOrdena::setTam(int aux){
    if (aux >= 100 && aux <= 100000){
        tam=aux;
        vetor=new Item*[tam];
        for (int i =0; i < tam; i++){
            vetor[i] = 0;
        }
        return true;
    }
    return false;
}

void testaOrdena::preencheVetor(){
    int r;
    Item *aux;
    for (int i =0; i<tam; i++){
        r=(rand()%100);
        aux= new Item;
        aux->setChave(r);
        vetor[i]=aux;
    }
}

void testaOrdena::mostraVetor(Item**vetor)const{
    for (int i =0; i<tam; i++){
        cout<<vetor[i]->getChave()<<" "<<vetor[i]->getStr()<<endl;
    }
}

Item**testaOrdena::copiaVetor(){
    Item**copia=new Item*[tam];
    for(int i=0; i<tam; i++){
        copia[i]=vetor[i];
    }
    return copia;
}

testaOrdena::testaOrdena(){
    tam=0;
    vetor=0;
}

void testaOrdena::menu(){
    int tamanho;
    do {
        cout<<"Digite o tamanho do vetor: ";
        cin >>tamanho;
    }while(!setTam(tamanho));
    
    clock_t I,F;
    double T;
    
    I = clock();
    F = clock();

    preencheVetor();

    //mostraVetor(vetor);

    Item**vetorCopia = copiaVetor();

    //mostraVetor(vetorCopia);

    cout<<"\n\n\n   SelectionSort: \n\n\n";
    
    I = clock();
    Ordena::selectionSort(vetorCopia,tam);
    F = clock();
    T = double(F-I)*1000.0/CLOCKS_PER_SEC;
    std::cout << "Tempo decorrido: " << T << " ms.\n";

    mostraVetor(vetorCopia);
    
 	
    
    cout<<"\n\n\n   BubbleSort: \n\n\n";

	I = clock();

    Ordena::bubblesort(vetorCopia,tam);
    
    F = clock();
    T = double(F-I)*1000.0/CLOCKS_PER_SEC;
    std::cout << "Tempo decorrido: " << T << " ms.\n";
    
    mostraVetor(vetorCopia);

    cout<<"\n\n\n   ShellSort: \n\n\n";
   
    
    I = clock();

    Ordena::shellSort(vetorCopia,tam);

    F = clock();
    T = double(F-I)*1000.0/CLOCKS_PER_SEC;
    std::cout << "Tempo decorrido: " << T << " ms.\n";
    
    mostraVetor(vetorCopia);
    
    cout<<"\n\n\n  MergeSort: \n\n\n";
    
    I = clock();

    Ordena::mergesort(vetorCopia,tam);

    F = clock();
    T = double(F-I)*1000.0/CLOCKS_PER_SEC;
    std::cout << "Tempo decorrido: " << T << " ms.\n";
    
    mostraVetor(vetorCopia);
    
    cout<<"\n\n\n   QuickSort: \n\n\n";
    
    I = clock();

    Ordena::quickSort(vetorCopia,tam);

    F = clock();
    T = double(F-I)*1000.0/CLOCKS_PER_SEC;
    std::cout << "Tempo decorrido: " << T << " ms.\n";
    
    mostraVetor(vetorCopia);

}

void testaOrdena::destroiVetor(Item**V){
    if(V!=0){
        for(int i =0; i < tam; i++){
            if(V[i]!=0) delete V[i];
        }
        delete []V;
    }
}

testaOrdena::~testaOrdena(){
    destroiVetor(vetor);
}

int main()
{
    testaOrdena obj;

    obj.menu();
    return 0;
}


