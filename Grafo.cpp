/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Grafo.cpp
 * Author: joao-marcos
 * 
 * Created on 6 de Março de 2016, 13:28
 */

#include "Grafo.h"


using namespace std;

Grafo::Grafo(int V, int op)//construtor.
{
    int i, j;
    this->V = V; // número de vértices
    this->op = op;
    Ant = new int[V];//aloca espaço pro antecessor.
    nivel = new int[V];//aloca espaco pro nivel.

    if (op > 0 && op < 3) {
	switch (op) {
	case 1:
	    adj = new list<int>[V+1]; // cria as listas
	    break;
	case 2:
	    MatAdj = new int*[V];//alloca um vetor de v posições

	    for (i = 1; i <= V; i++) {
		MatAdj[i] = new int[V]; //alloca um vetor para cada cada posição do vetor	
	    }
	    break;
	}
    }
}

void Grafo::adicionarAresta(int v1, int v2)
{
    switch (op) {
    case 1:
	adj[v1].push_back(v2);//adiciona no final da lista.
	break;

    case 2:
	MatAdj[v1][v2] = 1;//adiciona nas cordenadas da matriz.
	break;
    }

}

float Grafo::ObterMediaGrau()
{
    int i, j;
    float Grau = 0.0;
    switch (op) {
    case 1:
	for (i = 1; i <= V; i++) {
	    Grau += adj[i].size();//a soma geral dos graus
	}
	break;
    case 2:
	for (i = 1; i <= V; i++) {
	    for (j = 1; j <= V; j++) {
		if (MatAdj[i][j] == 1)
		    Grau++;//graus da matriz
	    }
	}
	break;
    }
    return Grau / V;//a media dos graus .
}

int Grafo::ContaAresta(int Aresta)
{
    return Aresta;//retorne a quantidade arestas.
}

void Grafo::dfs(int v)//busca em profundidade.
{
    FILE *Saida;
    Saida = fopen("./Resultados/Resultado Busca.dat", "w");
    stack<int> pilha;
    int i = 0, aux, nivel = 0, j = 0;
    bool visitados[V]; // vetor de visitados

    switch (op) {
    case 1:
	// marca todos como não visitados
	for (i = 1; i <= V; i++)
	    visitados[i] = false;

	while (true) {
	    if (!visitados[v]) {
		fprintf(Saida, "Visitando vertice: %d Nivel: %d\n", v, nivel);
		nivel++;
		visitados[v] = true; // marca como visitado
		pilha.push(v); // insere "v" na pilha
	    }

	    bool achou = false;
	    list<int>::iterator it;//interator para a lista

	    // busca por um vizinho não visitado
	    for (it = adj[v].begin(); it != adj[v].end(); it++) {
		if (!visitados[*it]) {//verifico se ja foi visitado.
		    achou = true;
		    break;
		}
	    }

	    if (achou)
		v = *it; // atualiza o "v"
	    else {
		// se todos os vizinhos estão visitados ou não existem vizinhos
		// remove da pilha
		nivel--;//removo da pilha e decremento o nivel.
		pilha.pop();
		// se a pilha ficar vazia, então terminou a busca
		if (pilha.empty())
		    break;
		// se chegou aqui, é porque pode pegar elemento do topo
		v = pilha.top();
	    }
	}
	break;

    case 2://busca na matriz.
	// marca todos como não visitados
	for (i = 1; i <= V; i++)
	    visitados[i] = false;

	while (true) {
	    if (!visitados[v]) {
		fprintf(Saida, "Visitando vertice: %d Nivel: %d\n", v, nivel);
		nivel++;
		visitados[v] = true; // marca como visitado
		pilha.push(v); // insere "v" na pilha
	    }

	    bool achou = false;

	    // busca por um vizinho não visitado
	    for (i = 1; i <= V; i++) {
		if (MatAdj[v][i] == 1) {
		    aux = i;
		    if (!visitados[aux]) {
			achou = true;
			break;
		    }
		}
	    }

	    if (achou)
		v = aux; // atualiza o "v"
	    else {
		// se todos os vizinhos estão visitados ou não existem vizinhos
		// remove da pilha
		nivel--;
		pilha.pop();
		// se a pilha ficar vazia, então terminou a busca
		if (pilha.empty())
		    break;
		// se chegou aqui, é porque pode pegar elemento do topo
		v = pilha.top();
	    }
	}

	break;
    }
}

void Grafo::bfs(int v)
{
    FILE *Saida;
    Saida = fopen("./Resultados/Resultado Busca.dat", "w");
    queue<int> fila;
    int i, j, aux, Raiz = v;
    bool visitados[V]; // vetor de visitados

    switch (op) {
    case 1://busca na lista por largura.

	for (i = 1; i <= V; i++)//inicializa com false
	    visitados[i] = false;

	fprintf(Saida, "Visitando vertice: %d Nivel: %d\n", v, nivel[i]);
	nivel[Raiz] = 0;
	visitados[v] = true; // marca como visitado
	i = 1;
	while (true) {
	    list<int>::iterator it;//interator para a lista.

	    for (it = adj[v].begin(); it != adj[v].end(); it++) {
		if (!visitados[*it]) {//se não for visitado.
		    Ant[*it] = v;//aiciona com antecessor de it.
		    visitados[*it] = true; // marca como visitado
		    fila.push(*it); // insere na fila

		}
		nivel[i] = nivel[Ant[i]] + 1;
	    }

	    if (!fila.empty()) {

		v = fila.front(); // obtém o primeiro elemento
		fprintf(Saida, "Visitando vertice: %d Nivel: %d\n", v, nivel[i]);
		i++;
		fila.pop(); // remove da fila
	    } else {
		break;
	    }

	}
	break;
    case 2:
	int aux1 = 0, v1 = v;
	for (i = 1; i <= V; i++)
	    visitados[i] = false;

	fprintf(Saida, "Visitando vertice: %d Nivel: %d\n", v, nivel[i]);
	nivel[Raiz] = 0;
	visitados[v] = true; // marca como visitado
	j = 1;

	while (true) {
	    for (i = 1; i <= V; i++) {
		if (MatAdj[v][i] == 1) {
		    aux = i;
		    if (!visitados[aux]) {
			Ant[aux] = v;
			visitados[aux] = true; // marca como visitado
			fila.push(aux); // insere na fila
		    }
		    nivel[j] = nivel[Ant[j]] + 1;
		}//nivel[i]= nivel[Ant[i]]+1;
	    }

	    // verifica se a fila NÃO está vazia
	    if (!fila.empty()) {
		v = fila.front(); // obtém o primeiro elemento
		fprintf(Saida, "Visitando vertice: %d Nivel: %d\n", v, nivel[j]);
		j++;
		fila.pop(); // remove da fila
	    } else {
		break;
	    }
	}

	break;
    }

}

void Grafo::InitLevel()
{
    int i;
    for (i = 1; i <= V; i++) {
	nivel[i] = 0;
    }
}

void Grafo::Imprimir()
{
    int i, j;
    list<int>::iterator it;

    switch (op) {
    case 1:
	for (i = 1; i <= V; i++) {
	    printf("[%d] => ", i);
	    for (it = adj[i].begin(); it != adj[i].end(); it++) {
		printf("%d => ", *it);
	    }
	    printf("NULL\n");
	}
	break;

    case 2:
	for (i = 1; i <= V; i++) {
	    for (j = 1; j <= V; j++) {
		printf("%d", MatAdj[i][j]);
	    }
	    printf("\n");
	}
    }

}

Grafo::~Grafo()//destrutor.
{
    int i;
    switch (op) {
    case 1:
	//delete [] adj;
	adj = NULL;
	break;

    case 2:
	for (i = 0; i < V; i++) {
	    MatAdj[i] = NULL;
	}
	break;
    }
}

