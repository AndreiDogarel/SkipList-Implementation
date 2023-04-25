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
    void printList();
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

void SkipList::printList(){
    // system("cls");
    cout << "-------SKIP LIST-------\n";
    for(int i = 0; i <= this->currentLevel; ++i){
        cout << "Level " << i << ": ";
        Nod* node = this->head->getLegaturiNivel()[i];
        while(node){
            cout << node->getKey() << " ";
            node = node->getLegaturiNivel()[i];
        }
        cout << "\n";
    }
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
///////////////////////////////////////////////////////////////////

int main(){
    srand((unsigned)time(0));
    SkipList lst(3);
    
    return 0;
}