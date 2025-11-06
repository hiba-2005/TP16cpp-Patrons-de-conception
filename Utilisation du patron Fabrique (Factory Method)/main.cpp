#include <iostream>
#include <memory>
#include <string>


class Forme {
public:
    virtual void afficher() const = 0;
    virtual ~Forme() = default;
};


class Cercle : public Forme {
public:
    void afficher() const override {
        std::cout << "c'est un Cercle" << std::endl;
    }
};

class Carre : public Forme {
public:
    void afficher() const override {
        std::cout << "c'est un Carré" << std::endl;
    }
};

class Triangle : public Forme {
public:
    void afficher() const override {
        std::cout << "c'est un Triangle" << std::endl;
    }
};


class FabriqueForme {
public:
    static std::unique_ptr<Forme> creerForme(const std::string& type) {
        if (type == "cercle")
            return std::make_unique<Cercle>();
        else if (type == "carre")
            return std::make_unique<Carre>();
        else if (type == "triangle")
            return std::make_unique<Triangle>();
        else
            return nullptr;
    }
};


int main() {
    std::unique_ptr<Forme> f1 = FabriqueForme::creerForme("cercle");
    std::unique_ptr<Forme> f2 = FabriqueForme::creerForme("carre");
    std::unique_ptr<Forme> f3 = FabriqueForme::creerForme("triangle");

    if (f1) f1->afficher();
    if (f2) f2->afficher();
    if (f3) f3->afficher();


    auto f4 = FabriqueForme::creerForme("hexagone");
    if (!f4) std::cout << "Type de forme inconnu !" << std::endl;

    return 0;
}
