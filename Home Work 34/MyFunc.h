// Created by Yevhen Danylchenko on 29.06.2025.
// Namespace Alias, AbsClass Logger, Vector Writing in file, Class, Objects, Exptions

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <exception>
#include <typeinfo>

#include "MyClass.h"

namespace MyAlias = MyAbsClass;

namespace MyFunc_1 {

    int MyFunc() {
        std::vector<std::shared_ptr<MyAlias::IEntity>> entities;
        std::ofstream logFile("log.txt", std::ios::app);

        int successCount = 0;
        double total = 0.0;

        int numberOfObjects = 0;
        std::cout << "Скiльки об'єктiв бажаєте створити? ";
        std::cin >> numberOfObjects;

        for (int i = 0; i < numberOfObjects; ++i) {
            std::string name;
            double value;
            std::string extraType;

            std::cout << "\nВведiть назву об'єкта: ";
            std::cin >> name;

            std::cout << "Введiть числове значення: ";
            std::cin >> value;

            std::cout << "Оберть тип додаткового параметра (int, string, char, double): ";
            std::cin >> extraType;

            try {
                if (extraType == "int") {
                    int extra;
                    std::cout << "Введiть int - парамет: ";
                    std::cin >> extra;
                    entities.push_back(std::make_shared<MyAlias::Record<int>>(name, value, extra));
                }
                else if (extraType == "string") {
                    std::string extra;
                    std::cout << "Введiть string-параметр: ";
                    std::cin >> extra;
                    entities.push_back(std::make_shared<MyAlias::Record<std::string>>(name, value, extra));
                }
                else if (extraType == "char") {
                    char extra;
                    std::cout << "Введiть char-параметр: ";
                    std::cin >> extra;
                    entities.push_back(std::make_shared<MyAlias::Record<char>>(name, value, extra));
                }
                else if (extraType == "double") {
                    double extra;
                    std::cout << "Введiть double-параметр: ";
                    std::cin >> extra;
                    entities.push_back(std::make_shared<MyAlias::Record<double>>(name, value, extra));
                }
                else {
                    std::cerr << "Невiдомий тип параметра. Пропуск..." << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Помилка при створеннi об'єкта: " << e.what() << std::endl;
            }
        }

        for (const auto& entity : entities) {
            entity->PrintFull();
            if (auto logger = std::dynamic_pointer_cast<MyAlias::ILogger>(entity)) {
                logger->LogShort(logFile);
            }
            try {
                total += entity->GetValue();
                successCount++;
            }
            catch (...) {
                std::cerr << "Помилка пiд час обчислення значення." << std::endl;
            }
        }

        std::cout << "========================================" << std::endl;
        std::cout << "\nСума значень: " << total << std::endl;
        std::cout << "Успiшно оброблено: " << successCount << std::endl;

        return 0;
    }
}