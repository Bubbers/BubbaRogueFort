//
// Created by simon on 2016-06-22.
//

#include "KidBandit.h"

using namespace std;

KidBandit::KidBandit(string name) : Bandit(name){
    stats = new Stats(1);
    health = 15;
    attacks = new unordered_map<string,Attack>();
    attacks->insert(pair<string,Attack>("punch",punch()));
}