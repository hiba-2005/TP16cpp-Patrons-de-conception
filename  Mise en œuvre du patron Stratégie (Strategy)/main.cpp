// main.cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Observateur {
public:
    virtual void mettreAJour(float temperature, float humidite, float pression) = 0;
    virtual ~Observateur() = default;
};


class StationMeteo {
    vector<Observateur*> observateurs;
    float temperature{};
    float humidite{};
    float pression{};

public:
    void ajouterObservateur(Observateur* obs) {
        observateurs.push_back(obs);
    }

    void supprimerObservateur(Observateur* obs) {
        observateurs.erase(
            std::remove(observateurs.begin(), observateurs.end(), obs),
            observateurs.end()
        );
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
        cout << "[Température] = " << temperature << " °C" << endl;
    }
};

class AffichageHumidite : public Observateur {
public:
    void mettreAJour(float, float humidite, float) override {
        cout << "[Humidité] = " << humidite << " %" << endl;
    }
};

class AffichagePression : public Observateur {
public:
    void mettreAJour(float, float, float pression) override {
        cout << "[Pression] = " << pression << " hPa" << endl;
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

    cout << "=== Mise à jour 1 ===" << endl;
    station.setMesures(24.3, 60.2, 1513.5);

    cout << "\n=== Suppression de l'observateur Humidité ===" << endl;
    station.supprimerObservateur(&hum);

    cout << "\n=== Mise à jour 2 ===" << endl;
    station.setMesures(27.7, 65.1, 1210.2);

    return 0;
}
