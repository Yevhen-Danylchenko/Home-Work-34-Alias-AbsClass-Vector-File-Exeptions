// Created by Yevhen Danylchenko on 29.06.2025.
// Namespace Alias, AbsClass Logger, Vector Writing in file, Class, Objects, Exptions

#pragma once

#include <iostream>

#include "MyFunc.h"

namespace Alias_1 = MyFunc_1;

namespace MyInterface_1 {
	void MyInterface() {
		char choice = 'y';
		do {
			Alias_1::MyFunc();
			std::cout << "Бажаєте продовжити виконання програми? (Y/N)" << std::endl;
			std::cin >> choice;
		} while (tolower(choice) == 'y');
	}
}
