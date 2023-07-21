#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
class BaseKnight;   
enum ItemType {ANTIDOTE, PHOENIXI, PHOENIXII, PHOENIXIII, PHOENIXIV/* TODO: */};
class BaseItem {
public:
    virtual ItemType getType() = 0;
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};
struct ItemNode{
    ItemType type; // data
    ItemNode * next;    // next node
};
class BaseBag {
protected:
    BaseKnight * knight;
    int maxCapacity;
    int currentCapacity;
public:
    BaseItem* item;
    ItemNode * head;
    BaseBag();
    ~BaseBag();
    void setcurrentCappacity(int currentCapacity){this->currentCapacity = currentCapacity;}
    int getcurrentCapacity(){return currentCapacity;}
    bool insertFirst(ItemType type);
    bool get(ItemType itemType);
    string toString() const;
};
enum OpponentType {MADBEAR = 1, BANDIT, LORDLUPIN, ELF, TROLL, TORNBERY, QUEENOFCARDS, NINADERINGS, DURIANGARDEN, WEAPON, HADES};
class BaseOpponent{
    protected:
    int n;
    int eventID;
    int basedamage;
    int plusgil;
    OpponentType opponenttype;
    public:
    void setplusgil(int plusgil){this->plusgil = plusgil;};
    void setn(int n){this->n = n;};
    void seteventID(int eventID){this->eventID = eventID;};
    void setbasedamage(int basedamage){this->basedamage = basedamage;};
    void setopponenttype(OpponentType opponenttype){this->opponenttype = opponenttype;};
    int getplusgil(){return plusgil;};
    int geteventID(){return eventID;};
    int getlevelO(){return (n+eventID)%10+1;};
    int getbasedamage(){return basedamage;};
    OpponentType getopponenttype(){return opponenttype;};
};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

public:
    void sethp(int hp){this->hp = hp;};
    void setmaxhp(int maxhp){this->maxhp = maxhp;};
    void setlevel(int level){this->level = level;};
    void setgil(int gil){this->gil = gil;};
    void setantidote(int antidote){this->antidote = antidote;};
    void setknightType(KnightType knightType){this->knightType = knightType;}
    int gethp(){return hp;};
    int getmaxhp(){return maxhp;};
    int getlevel(){return level;};
    int getgil(){return gil;};
    int getantidote(){return antidote;};
    BaseBag * getbag(){return bag;}
    KnightType getKnightType() {return knightType;}
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};

class Events {
private:
    int numberOfEvents;
    int *eventID;
public:
    Events(const string & file_events);
    ~Events();
    int count() const;
    int get(int i) const;
};

class ArmyKnights {
    protected:
        int paladinshield;
        int lancelotspear;
        int guineverhair;
        int excalibursword;
        int numberofknights;
        int numberknights;
        int weapon;
        int hades;
    public:
        BaseKnight** knightInf;
        ArmyKnights (const string & file_armyknights);
        ~ArmyKnights();
        bool fight(OpponentType opponenttype, int i);
        bool adventure (Events * events);
        int count() const;
        BaseKnight * lastKnight() const;
        void setpaladinshield(int paladinshield){this->paladinshield = paladinshield;};
        void setlancelotspear(int lancelotspear){this->lancelotspear = lancelotspear;};
        void setguineverhair(int guineverhair){this->guineverhair = guineverhair;};
        void setexcalibursword(int excalibursword){this->excalibursword = excalibursword;};
        int getpaladinshield(){return paladinshield;};
        int getlancelotspear(){return lancelotspear;};
        int getguineverhair(){return guineverhair;};
        int getexcalibursword(){return excalibursword;};
        bool hasPaladinShield() const;
        bool hasLancelotSpear() const;
        bool hasGuinevereHair() const;
        bool hasExcaliburSword() const;

        void printInfo() const;
        void printResult(bool win) const;
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string & file_armyknights);
    void loadEvents(const string & file_events);
    void run();
};

#endif // __KNIGHT2_H__