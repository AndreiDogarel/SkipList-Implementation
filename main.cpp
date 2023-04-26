#include <bits/stdc++.h>

using namespace std;

///////////////////////////////////////////////////////////////////
class Nod{
private:
    int key;
    Nod** legaturiNivel;

public:
    int getKey() const {return this->key;}
    Nod** getLegaturiNivel() const {return this->legaturiNivel;}
    void setKey(int key){this->key = key;}
    Nod(int key, int level);
};

Nod::Nod(int key, int level){
    this->key = key;
    this->legaturiNivel = new Nod*[level + 1];
    memset(this->legaturiNivel, 0, sizeof(Nod*)*(level + 1));
}
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
class SkipList{
private:
    Nod* head;
    int maxLevel;
    int currentLevel;

public:
    SkipList(int maxLevel);
    int chooseRandLevel();
    void insertElement(int value);
    void deleteElement(int value);
    bool searchElement(int value);
    int searchBiggestElement(int value);
    int searchLowestElement(int value);
    ostream& printList(ostream& out);
    ostream& printListBetween(ostream& out, int x, int y);
};

SkipList::SkipList(int maxLevel){
    this->maxLevel = maxLevel;
    this->currentLevel = 0;
    this->head = new Nod(INT32_MIN, this->maxLevel);
}

int SkipList::chooseRandLevel(){
    int lvl = 0;
    while(rand() % 2 == 0 && lvl < this->maxLevel){
        ++lvl;
    }
    return lvl;
    // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // uniform_int_distribution<int> randNr(0, this->maxLevel);
    // int lvl = 0;
    // while(randNr(rng) % 2 == 0 && lvl < this->maxLevel){
    //     ++lvl;
    // }
    // return lvl;
}

bool SkipList::searchElement(int value){
    Nod* currNode = this->head;
    for(int level = this->currentLevel; level >= 0; --level){
        while(currNode->getLegaturiNivel()[level] != NULL && currNode->getLegaturiNivel()[level]->getKey() < value){
            currNode = currNode->getLegaturiNivel()[level];
        }
    }
    if(currNode->getLegaturiNivel()[0] != NULL && currNode->getLegaturiNivel()[0]->getKey() == value){
        return true;
    }
    return false;
}

int SkipList::searchBiggestElement(int value){
    Nod* currNode = this->head;
    for(int level = this->currentLevel; level >= 0; --level){
        while(currNode->getLegaturiNivel()[level] != NULL && currNode->getLegaturiNivel()[level]->getKey() <= value){
            currNode = currNode->getLegaturiNivel()[level];
        }
    }
    return currNode->getKey();
}

int SkipList::searchLowestElement(int value){
    Nod* currNode = this->head;
    for(int level = this->currentLevel; level >= 0; --level){
        while(currNode->getLegaturiNivel()[level] != NULL && currNode->getLegaturiNivel()[level]->getKey() < value){
            currNode = currNode->getLegaturiNivel()[level];
        }
    }
    currNode = currNode->getLegaturiNivel()[0];
    return currNode->getKey();
}

void SkipList::insertElement(int value){
    Nod* currNode = this->head;
    Nod* update[this->maxLevel + 1];
    memset(update, 0, sizeof(Nod*)*(this->maxLevel + 1));
    for(int level = this->currentLevel; level >= 0; --level){
        while(currNode->getLegaturiNivel()[level] != NULL && currNode->getLegaturiNivel()[level]->getKey() < value){
            currNode = currNode->getLegaturiNivel()[level];
        }
        update[level] = currNode;
    }
    if(currNode->getLegaturiNivel()[0] == NULL || currNode->getLegaturiNivel()[0]->getKey() != value){
        int lvl = chooseRandLevel();
        if(lvl > this->currentLevel){
            for(int i = this->currentLevel + 1; i <= lvl; ++i){
                update[i] = this->head;
            }
            this->currentLevel = lvl;
        }
        Nod* node = new Nod(value, lvl);
        for(int i = 0; i <= lvl; ++i){
            node->getLegaturiNivel()[i] = update[i]->getLegaturiNivel()[i];
            update[i]->getLegaturiNivel()[i] = node;
        }
    }
}

ostream& SkipList::printList(ostream& out){
    // system("cls");
    out << "-------SKIP LIST-------\n";
    for(int i = 0; i <= this->currentLevel; ++i){
        cout << "Level " << i << ": ";
        Nod* node = this->head->getLegaturiNivel()[i];
        while(node){
            out << node->getKey() << " ";
            node = node->getLegaturiNivel()[i];
        }
        out << "\n";
    }
    return out;
}

ostream& SkipList::printListBetween(ostream& out, int x, int y){
    Nod* currNode = this->head;
    for(int level = this->currentLevel; level >= 0; --level){
        while(currNode->getLegaturiNivel()[level] != NULL && currNode->getLegaturiNivel()[level]->getKey() < x){
            currNode = currNode->getLegaturiNivel()[level];
        }
    }
    currNode = currNode->getLegaturiNivel()[0];
    while(currNode != NULL && currNode->getKey() <= y){
        out << currNode->getKey() << " ";
        currNode = currNode->getLegaturiNivel()[0];
    }
    out << "\n";
    return out;
}

void SkipList::deleteElement(int value){
    Nod* currNode = this->head;
    Nod* update[this->maxLevel + 1];
    memset(update, 0, sizeof(Nod*)*(this->maxLevel + 1));
    for(int level = this->currentLevel; level >= 0; --level){
        while(currNode->getLegaturiNivel()[level] != NULL && currNode->getLegaturiNivel()[level]->getKey() < value){
            currNode = currNode->getLegaturiNivel()[level];
        }
        update[level] = currNode;
    }
    currNode = currNode->getLegaturiNivel()[0];
    if(currNode != NULL && currNode->getKey() == value){
        for(int i = 0; i <= this->currentLevel; ++i){
            if(update[i]->getLegaturiNivel()[i] != currNode){
                break;
            }
            update[i]->getLegaturiNivel()[i] = currNode->getLegaturiNivel()[i];
        }
        while(this->currentLevel > 0 && this->head->getLegaturiNivel()[this->currentLevel] == 0){
            this->currentLevel--;
        }
    }
    delete currNode;
}

class Meniu{
private:
    int numberOfQueries;
    int queryType;

public:
    ostream& solve(istream& in, ostream& out){
        SkipList lista(20);
        in >> this->numberOfQueries;
        for(int i = 1; i <= this->numberOfQueries; ++i){
            in >> this->queryType;
            switch(this->queryType){
                case 1:{
                    int value;
                    in >> value;
                    lista.insertElement(value);
                    break;
                }
                case 2:{
                    int value;
                    in >> value;
                    lista.deleteElement(value);
                    break;
                }
                case 3:{
                    int value;
                    in >> value;
                    if(lista.searchElement(value)){
                        out << 1 << "\n";
                    }
                    else{
                        out << 0 << "\n";
                    }
                    break;
                }
                case 4:{
                    int value;
                    in >> value;
                    out << lista.searchBiggestElement(value) << "\n";
                    break;
                }
                case 5:{
                    int value;
                    in >> value;
                    out << lista.searchLowestElement(value) << "\n";
                    break;
                }
                case 6:{
                    int x, y;
                    in >> x >> y;
                    lista.printListBetween(out, x, y);
                    break;
                }
            }
        }
        return out;
    }
};
///////////////////////////////////////////////////////////////////

int main(){
    ifstream f("abce.in");
    ofstream g("abce.out");
    srand((unsigned)time(0));
    Meniu M;
    M.solve(f, g);
    return 0;
}