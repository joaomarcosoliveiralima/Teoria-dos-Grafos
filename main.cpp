/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: joao-marcos
 *
 * Created on 6 de Março de 2016, 15:20
 */
/*
 inclusão das blibiotecas que serão ultilizadas no projeto.
 */
/**
*Para compilar pelo terminal do linux substitua o Grafo.h por Grafo.cpp.
**/
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <list> //usar a estrutura lista encadeada.
#include <sys/time.h>
#include <unistd.h> //usanda para medir o tempo de execulção
#include "Grafo.h"//incluir a classe grafo
#include "Menu.h"//menu do projeto
#include <string.h>

using namespace std;

bool TestArq(FILE *Arquivo);//testa se foi possivel abrir o arquivo ou não.

int main(int argc, char** argv)
{    
    FILE *Data, *Saida;
    //char Nome_Arq[] = "./Entrada/Grafo.dat";
    int a, b, n, opcao, Aresta = 0, Busca, i = 0,seach = 0,Raiz;
    struct timeval inicio, final;//variaveis para serem usadas no tempo de execulção.
    double tmili;
    char Nome[50];
    


    Saida = fopen("./Resultados/Saida.dat", "w");//arquivo onde ficara armazenado a saida do grafo.

    if (TestArq(Saida)) {
	cout << "Não foi possivel criar o arquivo" << endl;
	return 1;
    }
    opcao = Menu1();
    Busca = MenuBusca();
    system("clear");
    cout << "Informe o nome do arquivo com extenção e não use espaço: " << endl;
    cout << "Exemplo: Meu_Arquivo.txt" << endl;
    cin >>Nome;    
    Data = fopen(Nome, "r");

    if (TestArq(Data)) {
	cout << "Não foi possivel abrir o arquivo" << endl;
	return 1;
    }
    system("clear");
    cout<<"Informe o seu vertice raiz para a busca: "<<endl;
    cin>>Raiz;
    
    fscanf(Data, "%d\n", &n);
    //inicia o tempo no começo da execulção...
    gettimeofday(&inicio, NULL);
    Grafo grafo(n, opcao);//cria um grafo do tipo selecionado e com n vertice.
    while (!feof(Data)) {
	//srand((unsigned)time(NULL));
	fscanf(Data, "%d %d\n", &a, &b);
	Aresta++;
	grafo.adicionarAresta(a, b);//lendo as aresta do arquivo de entrada
	grafo.adicionarAresta(b, a);//como o grafo não e direcionado ler as aresta invertidas também
    }

    system("clear");
    cout << "Vértice: " << n << endl;
    fprintf(Saida, "Vértice : %d\n", n);
    cout << "Arestas: " << grafo.ContaAresta(Aresta) << endl;
    fprintf(Saida, "Aresta : %d\n", grafo.ContaAresta(Aresta));
    cout << "Média de Grau: " << fixed << setprecision(2) << grafo.ObterMediaGrau() << endl;
    fprintf(Saida, "Média de Grau: %.2f\n", grafo.ObterMediaGrau());
    cout << "A Raiz da busca é : " << Raiz << endl;
    fprintf(Saida, "A Raiz da busca é : %d\n", Raiz);
    srand((unsigned)time(NULL));
    
   // grafo.Imprimir();
    
    grafo.InitLevel();//inicia o vetor de nivel com 0.
    if (Busca == 1)
	grafo.dfs(Raiz);//função busca em profundidade.
    else
	grafo.bfs(Raiz);//função busca em largura.
    
    //captura o tempo que levou na execulção..
    gettimeofday(&final, NULL);
    tmili = (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);

    cout << "tempo decorrido: " << fixed << setprecision(2) << tmili / 1000 << endl;//tempo decorrido em segundos
    fprintf(Saida, "tempo decorrido: %.2f\n", tmili / 1000);

    return 0;
}

bool TestArq(FILE *Arquivo)
{
    if (Arquivo == NULL)
	return true;
    else
	return false;
}


