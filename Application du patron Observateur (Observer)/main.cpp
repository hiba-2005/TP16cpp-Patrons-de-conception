#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Observateur {
public:
    virtual void mettreAJour(float temperature, float humidite, float pression) = 0;
    virtual ~Observateur() = default;
};


class StationMeteo {
    std::vector<Observateur*> observateurs;
    float temperature{};
    float humidite{};
    float pression{};

public:
    void ajouterObservateur(Observateur* obs) {
        observateurs.push_back(obs);
    }

    void supprimerObservateur(Observateur* obs) {
        auto it = std::find(observateurs.begin(), observateurs.end(), obs);
        if (it != observateurs.end()) {
            observateurs.erase(it);
        }
    }

    void notifierObservateurs() {
        for (auto obs : observateurs)
            obs->mettreAJour(temperature, humidite, pression);
    }

    void setMesures(float t, float h, float p) {
        temperature = t;
        humidite = h;
        pression = p;
        notifierObservateurs();
    }
};


class AffichageTemperature : public Observateur {
public:
    void mettreAJour(float temperature, float, float) override {
        std::cout << "Température actuelle : " << temperature << " °C" << std::endl;
    }
};

class AffichageHumidite : public Observateur {
public:
    void mettreAJour(float, float humidite, float) override {
        std::cout << "Humidité actuelle : " << humidite << " %" << std::endl;
    }
};

class AffichagePression : public Observateur {
public:
    void mettreAJour(float, float, float pression) override {
        std::cout << "Pression actuelle : " << pression << " hPa" << std::endl;
    }
};


int main() {
    StationMeteo station;

    AffichageTemperature temp;
    AffichageHumidite hum;
    AffichagePression pres;

    station.ajouterObservateur(&temp);
    station.ajouterObservateur(&hum);
    station.ajouterObservateur(&pres);

    std::cout << " Première mise à jour " << std::endl;
    station.setMesures(25.3f, 60.5f, 1012.8f);

    std::cout << "\n Deuxième mise à jour " << std::endl;
    station.setMesures(27.1f, 55.2f, 1008.6f);

    std::cout << "\nSuppression de l'affichage de la pression...\n";
    station.supprimerObservateur(&pres);

    std::cout << "\n Troisième mise à jour " << std::endl;
    station.setMesures(28.0f, 50.0f, 1005.4f);

    return 0;
}
