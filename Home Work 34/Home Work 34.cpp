// Home Work 34.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Created by Yevhen Danylchenko on 29.06.2025.
// Namespace Alias, AbsClass Logger, Vector Writing in file, Class, Objects, Exptions

#include <iostream>
#include <locale>
#include "MyInterface.h"

namespace Alias = MyInterface_1;

int main()
{
    setlocale(LC_ALL, "ukr");
    Alias::MyInterface();

    return 0;
}


