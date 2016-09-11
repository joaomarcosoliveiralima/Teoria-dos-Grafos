/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.h
 * Author: joao-marcos
 *
 * Created on 6 de Março de 2016, 13:30
 */

#ifndef MENU_H
#define MENU_H
#include <iostream>
using namespace std;

int Menu1()
    {
    int opcao;
    do
        {
        system("clear");
        cout << "Informe o Algoritmo que deseja usar:\n\n";
        cout << "\tLista de Adjacencia (1):\n\n";
        cout << "\tMatriz de Adjacencia (2):\n\n";

        cin>>opcao;
        }
    while ((opcao != 1)&&(opcao != 2));

    return opcao;
    }

int MenuBusca()
    {
    int opcao;
    do
        {
        system("clear");
        cout << "Informe qual Algoritmo de busca deseja usar:\n\n";
        cout << "\tBusca em Aprofundidade (1):\n\n";
        cout << "\tBusca em Largura (2):\n\n";

        cin>>opcao;
        }
    while ((opcao != 1)&&(opcao != 2));

    return opcao;
    }

#endif /* MENU_H */

