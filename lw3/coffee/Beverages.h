#pragma once

#include <utility>

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
    explicit CBeverage(std::string description)
            : m_description(std::move(description))
    {}

    std::string GetDescription() const
    {
        return m_description;
    }

private:
    std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
    explicit CCoffee(const std::string &description = "Coffee")
            : CBeverage(description)
    {}

    double GetCost() const override
    {
        return 60;
    }
};

enum class CustomCoffeePortion
{
    Standard,
    Double,
};

// Авторский кофе
class CCustomCoffee : public CCoffee
{
public:
    CCustomCoffee(CustomCoffeePortion portion, const std::string &description)
            : CCoffee(std::string(portion == CustomCoffeePortion::Double ? "Double " : "") + description),
              m_portion(portion)
    {}

    double GetCost() const override
    {
        return m_portion == CustomCoffeePortion::Double ? GetDoublePortionCost() : GetStandardPortionCost();
    }

private:
    virtual double GetStandardPortionCost() const = 0;

    virtual double GetDoublePortionCost() const = 0;

    CustomCoffeePortion m_portion;
};

// Капуччино
class CCappuccino : public CCustomCoffee
{
public:
    explicit CCappuccino(CustomCoffeePortion portion)
            : CCustomCoffee(portion, "Cappuccino")
    {}

private:
    double GetStandardPortionCost() const override
    {
        return 80;
    }

    double GetDoublePortionCost() const override
    {
        return 120;
    }
};

// Латте
class CLatte : public CCustomCoffee
{
public:
    explicit CLatte(CustomCoffeePortion type)
            : CCustomCoffee(type, "Latte")
    {}

private:
    double GetStandardPortionCost() const override
    {
        return 90;
    }

    double GetDoublePortionCost() const override
    {
        return 130;
    }
};

enum TeaType {
    Green,
    Red,
    Black,
    Blue
};

// Чай
class CTea : public CBeverage
{
public:
    explicit CTea(TeaType type)
            : CBeverage(GenerateDescription(type))
    {}

    double GetCost() const override
    {
        return 30;
    }

private:
    static std::string GenerateDescription(TeaType type)
    {
        std::string description = "Tea";
        switch (type)
        {
            case Green:
                return "Green " + description;
            case Black:
                return "Black " + description;
            case Red:
                return "Red " + description;
            case Blue:
                return "Blue " + description;
        }
        return description;
    }
};

enum MilkshakePortion
{
    Small,
    Standard,
    Big
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:

    explicit CMilkshake(MilkshakePortion portion)
            : CBeverage(GenerateDescription(portion)),
              m_portion(portion)
    {}

    double GetCost() const override
    {
        switch (m_portion)
        {
            case Small:
                return 50;
            case Standard:
                return 60;
            case Big:
                return 80;
        }
        return 60;
    }

private:
    static std::string GenerateDescription(MilkshakePortion portion)
    {
        std::string description = "Milkshake";
        switch (portion)
        {
            case Small:
                return "Small " + description;
            case Standard:
                return "Standard " + description;
            case Big:
                return "Big " + description;
        }
        return description;
    }

    MilkshakePortion m_portion;
};
