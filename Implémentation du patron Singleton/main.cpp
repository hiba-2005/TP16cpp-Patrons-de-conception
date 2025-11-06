#include <iostream>
#include <string>

class Configuration {
private:
    std::string cheminFichier;
    std::string utilisateur;
    std::string motDePasse;


    Configuration(const std::string& chemin, const std::string& user, const std::string& mdp)
        : cheminFichier(chemin), utilisateur(user), motDePasse(mdp) {}


    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

public:

    static Configuration& getInstance() {
        static Configuration instance("test.txt", "admin", "2005");
        return instance;
    }

    void afficherParametres() const {
        std::cout << "Chemin fichier : " << cheminFichier << std::endl;
        std::cout << "Utilisateur     : " << utilisateur << std::endl;
        std::cout << "Mot de passe    : " << motDePasse << std::endl;
    }


    void setUtilisateur(const std::string& user) { utilisateur = user; }
};

int main() {

    Configuration& conf1 = Configuration::getInstance();
    conf1.afficherParametres();


    Configuration& conf2 = Configuration::getInstance();
    conf2.setUtilisateur("root");

    std::cout << "\nAprès modification via conf2 :" << std::endl;
    conf1.afficherParametres();
    return 0;
}
