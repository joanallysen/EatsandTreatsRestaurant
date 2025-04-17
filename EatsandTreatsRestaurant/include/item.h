#include <string>
#include <iostream>

#pragma once
class Item {
protected:
    std::string name;
    std::string description;
    float price;

public:
    Item(const std::string& _name = "", const std::string& _description = "", float _price = 0.0f)
        : name(_name), description(_description), price(_price) {
    }

    virtual void debug() const;

    // getter
    const std::string& getName() const;
    const std::string& getDescription() const;
    float getPrice() const;

    // setter
    void setName(std::string& name);
    void setDescription(std::string& description);
    void setPrice(float price);

    virtual ~Item() = default;
};

class Special : public Item {
public:
    Special(const std::string& _name, const std::string& _description, float _price)
        : Item(_name, _description, _price) {
    }

    void debug() const override;
};

class Food : public Item {
public:
    Food(const std::string& _name, const std::string& _description, float _price)
        : Item(_name, _description, _price) {
    }

    void debug() const override;
};

class Drink : public Item {
public:
    Drink(const std::string& _name, const std::string& _description, float _price)
        : Item(_name, _description, _price) {
    }

    void debug() const override;
};
