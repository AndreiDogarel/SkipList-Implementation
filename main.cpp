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
    memset(this->legaturiNivel, 0, sizeof(this->legaturiNivel));
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

SkipList::SkipList(int maxLevel) : maxLevel(maxLevel){
    this->currentLevel = 0;
    this->head = new Nod(INT32_MIN, this->maxLevel);
}

int SkipList::chooseRandLevel(){
    int lvl = 0;
    int r = rand();
    while(r % 2 && lvl < this->maxLevel){
        lvl++;
        r = r >> 1;
    }
    return lvl;
}

bool SkipList::searchElement(int value){
    Nod* currNode = this->head;
    for(int level = this->maxLevel; level >= 0; --level){
        while(currNode->getLegaturiNivel()[level] != NULL && currNode->getLegaturiNivel()[level]->getKey() < value){
            currNode = currNode->getLegaturiNivel()[level];
        }
    }
    if(currNode->getLegaturiNivel()[0] != NULL && currNode->getLegaturiNivel()[0]->getKey() == value){
        return true;
    }
    return false;
}
///////////////////////////////////////////////////////////////////

int main(){

}