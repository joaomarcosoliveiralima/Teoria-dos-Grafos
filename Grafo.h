/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Grafo.h
 * Author: joao-marcos
 *
 * Created on 6 de Março de 2016, 13:28
 */

#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <list> //estrutura Lista
#include <stack> // pilha para usar na DFS
#include <queue> // fila para usar na BFS
#include <stdio.h>

using namespace std;

class Grafo {
    /*
     * Atributos da classe grafo
     */
    
    int V; // número de vértices
    int **MatAdj; // Matriz de adjacencia
    int *Ant;//armazena os vertices anteriores
    int *nivel;//armazena os niveis.
    int op;//escolha do usuario
    list<int>*adj; // ponteiro para um array contendo as listas de adjacências

public:
    /*
     * Metodos usados na classe grafo.
     */
    
    Grafo(int V, int op); // construtor

    void adicionarAresta(int v1, int v2); // adiciona uma aresta no grafo
    
    float ObterMediaGrau();//produz o grado do numero de vertice.

    int ContaAresta(int Aresta);

    void dfs(int v);//Busca em profundidade.

    void bfs(int v);//busca em largura
    
    void InitLevel();//inicializa o vetor nivel
    
    void Imprimir();//mostra o grafo representado.

    ~Grafo(); // Destrutor..
};


#endif /* GRAFO_H */

