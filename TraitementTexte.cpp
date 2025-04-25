#include "TraitementTexte.h"

#include <string>

#include "Stack.h"

//méthode vérifié et elle ne cause aucun problème si l'input est valide. (Aucun espace toléré, seulement des chiffres et des virgules. pas de float ni de négatifs.)
Stack<int> TraitementTexte::stos(std::string data){
    Stack<int> s;
    std::string num;
    for (size_t j{0}; j < data.length(); j++){
        if(data[j] == ','){
            if (num == "")
                continue;
            s.push(std::stoi(num));
            num = "";
        }
        else{
            num.push_back(data[j]);
        }
    }
    if (num != "")
        s.push(std::stoi(num));

    return s;
}