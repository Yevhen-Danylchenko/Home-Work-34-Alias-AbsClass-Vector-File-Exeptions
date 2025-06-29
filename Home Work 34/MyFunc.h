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
        std::cout << "��i���� ��'���i� ������ ��������? ";
        std::cin >> numberOfObjects;

        for (int i = 0; i < numberOfObjects; ++i) {
            std::string name;
            double value;
            std::string extraType;

            std::cout << "\n����i�� ����� ��'����: ";
            std::cin >> name;

            std::cout << "����i�� ������� ��������: ";
            std::cin >> value;

            std::cout << "������ ��� ����������� ��������� (int, string, char, double): ";
            std::cin >> extraType;

            try {
                if (extraType == "int") {
                    int extra;
                    std::cout << "����i�� int - �������: ";
                    std::cin >> extra;
                    entities.push_back(std::make_shared<MyAlias::Record<int>>(name, value, extra));
                }
                else if (extraType == "string") {
                    std::string extra;
                    std::cout << "����i�� string-��������: ";
                    std::cin >> extra;
                    entities.push_back(std::make_shared<MyAlias::Record<std::string>>(name, value, extra));
                }
                else if (extraType == "char") {
                    char extra;
                    std::cout << "����i�� char-��������: ";
                    std::cin >> extra;
                    entities.push_back(std::make_shared<MyAlias::Record<char>>(name, value, extra));
                }
                else if (extraType == "double") {
                    double extra;
                    std::cout << "����i�� double-��������: ";
                    std::cin >> extra;
                    entities.push_back(std::make_shared<MyAlias::Record<double>>(name, value, extra));
                }
                else {
                    std::cerr << "���i����� ��� ���������. �������..." << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "������� ��� ��������i ��'����: " << e.what() << std::endl;
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
                std::cerr << "������� �i� ��� ���������� ��������." << std::endl;
            }
        }

        std::cout << "========================================" << std::endl;
        std::cout << "\n���� �������: " << total << std::endl;
        std::cout << "���i��� ���������: " << successCount << std::endl;

        return 0;
    }
}