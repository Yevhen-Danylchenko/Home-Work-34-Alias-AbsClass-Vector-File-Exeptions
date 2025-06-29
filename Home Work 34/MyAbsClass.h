#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <typeinfo>

namespace MyAbsClassName {

    class MyComClass {
    public:
        virtual void PrintFull() const = 0;
        virtual double GetValue() const = 0;
        virtual ~MyComClass() {}
    };

    class MyLogger {
    public:
        virtual void LogShort() const = 0;
        virtual ~MyLogger() {}
    };

    template<typename T>
    class Item : public MyComClass, public MyLogger {
    private:
        std::string Name;
        double Value;
        T Extra;

    public:
        Item(const std::string& name, double value, const T& extra)
            : Name(name), Value(value), Extra(extra) {
            if (value < 0) {
                throw std::invalid_argument("Значення не може бути вiд’ємним");
            }
        }

        void PrintFull() const override {
            std::cout << "Назва: " << Name
                << ", Значення: " << Value
                << ", Додаткове: " << Extra << "\n";
        }

        double GetValue() const override {
            return Value;
        }

        void LogShort() const override {
            std::cout << Name << " [" << Value << "]\n";
        }
    };

    template<>
    void Item<std::nullptr_t>::PrintFull() const {
        std::cout << "Назва: " << "невiдомо"
            << ", Значення: " << Value
            << ", Додаткове: nullptr\n";
    }

    int MyInterface() {
        using BasePtr = std::shared_ptr<MyComClass>;
        std::vector<std::shared_ptr<MyComClass>> objects;

        int successful = 0;
        double total = 0;

        try {
            objects.push_back(std::make_shared<Item<int>>("SensorA", 10.5, 42));
            objects.push_back(std::make_shared<Item<std::string>>("ModuleB", 20.3, "extraData"));
            objects.push_back(std::make_shared<Item<double>>("DeviceC", 5.5, 3.14));

            objects.push_back(std::make_shared<Item<int>>("Faulty", -1.0, 666));
        }
        catch (const std::invalid_argument& ex) {
            std::cerr << "Помилка створення об'єкта: " << ex.what() << "\n";
        }

        for (const auto& obj : objects) {
            if (!obj) continue;

            auto logger = std::dynamic_pointer_cast<MyLogger>(obj);
            if (logger) logger->LogShort();

            obj->PrintFull();
            total += obj->GetValue();
            ++successful;
        }

        std::cout << "Оброблено об'єктiв: " << successful << "\n";
        std::cout << "Сума значень: " << total << "\n";

        return 0;
    }
}
