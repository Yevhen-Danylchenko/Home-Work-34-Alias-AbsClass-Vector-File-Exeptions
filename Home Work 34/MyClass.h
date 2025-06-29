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

namespace MyAbsClass {

    // Абстрактний базовий тип
    class IEntity {
    public:
        virtual void PrintFull() const = 0;
        virtual double GetValue() const = 0;
        virtual ~IEntity() = default;
    };

    // Абстрактний логер
    class ILogger {
    public:
        virtual void LogShort(std::ostream& os) const = 0;
        virtual ~ILogger() = default;
    };

    // Реалізація обох базових інтерфейсів
    template<typename T>
    class Record : public IEntity, public ILogger {
    private:
        std::string name;
        double value;
        T extra;

    public:
        Record(const std::string& name, double value, const T& extra)
            : name(name), value(value), extra(extra) {
            if (value < 0)
                throw std::invalid_argument("Змiнна не може бути негативна.");
        }

        void PrintFull() const override {
            std::cout << "Name: " << name
                << ", Value: " << value
                << ", Extra: " << extra << std::endl;
        }

        double GetValue() const override {
            return value;
        }

        void LogShort(std::ostream& os) const override {
            os << "[MYLOG] " << name << ": " << value << ": " << extra << std::endl;
        }
    };

}
