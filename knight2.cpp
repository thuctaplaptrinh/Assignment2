#include "knight2.h"
bool checkPrime(int n){
    if(n<=1) return 0;
    else {
        for(int i = 2; i <= sqrt(n); i++){
            if(n%i==0) return 0;
        }
        return 1;
    }
}
bool checkPytago(int n){
    if(n==345||n==354||n==435||n==453||n==534||n==543){
        return 1;
    }
    return 0;
}

/* * * BEGIN implementation of class BaseItem * * */
class Antidote:public BaseItem{
    public:
    ItemType getType(){
        return ANTIDOTE;
    }
    bool canUse(BaseKnight * knight){
        if(knight->getKnightType() == DRAGON){
            return false;
        }
        else return true;
    }
    void use(BaseKnight * knight){
    }
};

class PhoenixdownI:public BaseItem{
    public:
    ItemType getType(){
        return PHOENIXI;
    }
    bool canUse(BaseKnight * knight){
        if(knight->gethp() <= 0) return true;
        else return false;
    }
    void use(BaseKnight * knight){
        knight->sethp(knight->getmaxhp());
    }
};

class PhoenixdownII:public BaseItem{
    public:
    ItemType getType(){
        return PHOENIXII;
    }
    bool canUse(BaseKnight * knight){
        if(knight->gethp() < knight->getmaxhp()/4) return true;
        else return false;
    }
    void use(BaseKnight * knight){
        knight->sethp(knight->getmaxhp());
    }
};

class PhoenixdownIII:public BaseItem{
    public:
    ItemType getType(){
        return PHOENIXIII;
    }
    bool canUse(BaseKnight * knight){
        if(knight->gethp() < knight->getmaxhp()/3) return true;
        else return false;
    }  
    void use(BaseKnight * knight){
        if(knight->gethp() <= 0) {knight->sethp(knight->getmaxhp()/3);}
        else knight->sethp(knight->gethp() + knight->getmaxhp()/4);
    }
};

class PhoenixdownIV:public BaseItem{
    public:
    ItemType getType(){
        return PHOENIXIV;
    }
    bool canUse(BaseKnight * knight){
        if(knight->gethp() < knight->getmaxhp()/2) return true;
        else return false;
    }  
    void use(BaseKnight * knight){       
        if(knight->gethp() <= 0) knight->sethp(knight->getmaxhp()/2);
        else knight->sethp(knight->gethp() + knight->getmaxhp()/5 );
    }
};
/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseBag * * */
BaseBag::BaseBag(){
    currentCapacity = 0;
    head = nullptr;   
};
BaseBag::~BaseBag(){
    ItemNode* current = head;
    while(current != nullptr){
        head = current->next; 
        delete current;
        current = head;
    }
}

class PaladinBag:public BaseBag{
    public:
    PaladinBag(BaseKnight * knight, int antidote, int phoenixdownI):BaseBag(){
        knight->setknightType(PALADIN);
        maxCapacity = 100;
        int count = 0;
        for (int i = 0; i < phoenixdownI; i++) {
            this->insertFirst(PHOENIXI);           
        }
        for (int i = 0; i < antidote; i++) {
            this->insertFirst(ANTIDOTE);
        }
    }
};

class LancelotBag:public BaseBag{
    public:
    LancelotBag(BaseKnight * knight, int antidote, int phoenixdownI):BaseBag(){
        knight->setknightType(LANCELOT);
        maxCapacity = 16;
        for (int i = 0; i < phoenixdownI; i++) {
            this->insertFirst(PHOENIXI);
        }
        for (int i = 0; i < antidote; i++) {
            this->insertFirst(ANTIDOTE);
        }
    }
};

class DragonBag:public BaseBag{
    public:
    DragonBag(BaseKnight * knight, int antidote, int phoenixdownI):BaseBag(){
        knight->setknightType(DRAGON);
        maxCapacity = 14;
        for (int i = 0; i < phoenixdownI; i++) {
            this->insertFirst(PHOENIXI);
        }
        for (int i = 0; i < antidote; i++) {
            this->insertFirst(ANTIDOTE);
        }
    }
};

class NormalBag:public BaseBag{
    public:
    NormalBag(BaseKnight * knight, int antidote, int phoenixdownI):BaseBag(){
        knight->setknightType(NORMAL);
        maxCapacity = 19;
        for (int i = 0; i < phoenixdownI; i++) {
            this->insertFirst(PHOENIXI);
        }
        for (int i = 0; i < antidote; i++) {
            this->insertFirst(ANTIDOTE);
        }
    }
};

bool BaseBag::insertFirst(ItemType type){
    if (currentCapacity + 1 <= maxCapacity) {
        ItemNode * newnode = new ItemNode();
        newnode->next = head;
        newnode->type = type;
        head = newnode;
        currentCapacity += 1; 
        return true;
    }
    return false;
}

bool BaseBag::get(ItemType itemType){
    ItemNode * ancher = head;
    ItemNode * current = head;
    ItemNode * prev = nullptr;
    ItemNode * temp = nullptr;
    while(current != nullptr){
        if (current->type == itemType) {
            if (prev == nullptr) {
                head = current->next;
                delete current;
            } 
            else if (prev == ancher){
                temp = current->next;
                ancher->next = temp;
                delete current;
            }
            else {  
                head = ancher->next;  
                temp = current->next;
                prev->next = ancher;
                ancher->next = temp;
                delete current;
            }
            currentCapacity--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

string BaseBag::toString() const {
    string listitem = "";
    string n;
    listitem += "Bag[count=";
    stringstream ss;
    ss << currentCapacity;
    ss >> n;
    listitem += n + ";";
    ItemNode * current = head;
    while(current != nullptr){
        switch(current->type){
            case ANTIDOTE:
                listitem += "Antidote";
                break;
            case PHOENIXI:
                listitem += "PhoenixI";
                break;
            case PHOENIXII:
                listitem += "PhoenixII";
                break;
            case PHOENIXIII:
                listitem += "PhoenixIII";
                break;
            default:
                listitem += "PhoenixIV";
                break;
        }
        current = current->next;
        if(current != nullptr) listitem += ",";
        else break;
    }
    listitem += "]";
    return listitem;
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) + ","
        + "hp:" + to_string(hp) + ","
        + "maxhp:" + to_string(maxhp) + ","
        + "level:" + to_string(level) + ","
        + "gil:" + to_string(gil)
        + "," + bag->toString() + ","
        + "knight_type:" + typeString[knightType]
        + "]";
    return s;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

bool ArmyKnights::hasPaladinShield() const {
    if(paladinshield == 1){return true;}
    else return false;
}

bool ArmyKnights::hasLancelotSpear() const {
    if(lancelotspear == 1) {return true;}
    else return false;
}
bool ArmyKnights::hasGuinevereHair() const {
    if(guineverhair == 1) {return true;}
    else return false;
}
bool ArmyKnights::hasExcaliburSword() const {
    if(excalibursword == 1) {return true;}
    else return false;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure(){
    delete armyKnights;
    delete events;
}

/* * * END implementation of class KnightAdventure * * */
Events::Events(const string & file_events){
    fstream f;
    string str, str1;
    f.open(file_events, ios::in);
    f >> numberOfEvents;
    eventID = new int[numberOfEvents];
    getline(f, str1);
    getline(f, str);
	int start = 0, n = 0;
	for (int i = 0; i < (str.size()); i++) {
		if (str[i] == ' ' || i == str.size() - 1) {
			if (i == str.size() - 1)
				i++;
			stringstream ss;
			ss << str.substr(start, i - start);
			ss >> eventID[n];
			start = i + 1;
			n++;
		}
	}
    f.close();
}
// Class Events
Events::~Events(){
    delete[] eventID;
}

int Events::count() const {
    return numberOfEvents;
}

int Events::get(int i) const {
    return eventID[i];
}

/* * * BEGIN implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class KnightAdventure * * */
void KnightAdventure::loadArmyKnights(const string & file_armyknights){
    armyKnights = new ArmyKnights(file_armyknights);
}

void KnightAdventure::loadEvents(const string & file_events){
    events = new Events(file_events);
}

void KnightAdventure::run(){
    bool win = armyKnights->adventure(events);
    armyKnights->printResult(win);
}

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights){ 
    ifstream input_army(file_armyknights);
    if(!input_army) {
        cout << "can not open file" << file_armyknights <<  "\n";
        exit(1);
    }
    input_army >> numberknights;
    numberofknights = numberknights;
    knightInf = new BaseKnight * [numberknights];
    for (int i = 0; i < numberknights; i++) {
        int hp, level, phoenixdownI, gil, antidote;
        input_army >> hp >> level>> phoenixdownI >> gil >> antidote ;
        knightInf[i] = BaseKnight::create(i + 1, hp, level, gil, antidote, phoenixdownI);
    }
    input_army.close();
}

ArmyKnights::~ArmyKnights(){
    for(int i = 0; i < numberofknights; i++){
        knightInf[i]->getbag()->~BaseBag();
        delete knightInf[i];
    }
}

int ArmyKnights::count() const {
    return numberknights;
}

BaseKnight *ArmyKnights::lastKnight() const{
    if(this->count() == 0) return nullptr;
    return knightInf[count()-1];
}

bool ArmyKnights::fight(OpponentType opponenttype, int i){
        switch (opponenttype){
            case MADBEAR:
                if(lastKnight() != nullptr){
                    int levelO = (1+i)%10 + 1;
                    if(lastKnight()->getKnightType() == LANCELOT || lastKnight()->getKnightType() == PALADIN || lastKnight()->getlevel() >= levelO){ 
                        lastKnight()->setgil(lastKnight()->getgil() + 100);
                        if(lastKnight()->getgil() > 999) lastKnight()->setgil(999);
                        return true;
                    }
                    else {                                          
                        int HP = lastKnight()->gethp();
                        HP = lastKnight()->gethp() - 10*(levelO - lastKnight()->getlevel());
                        lastKnight()->sethp(HP);
                        ItemNode * current = lastKnight()->getbag()->head;                    
                        while(current != nullptr){
                            if(current->type == PHOENIXI){
                                PhoenixdownI PI;
                                if(PI.canUse(lastKnight()) == true) {PI.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXI); return true;}
                            }
                            else if(current->type == PHOENIXII){
                                PhoenixdownII PII;
                                if(PII.canUse(lastKnight()) == true) {PII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXII); return true;}
                            }
                            else if(current->type == PHOENIXIII){
                                PhoenixdownIII PIII;
                                if(PIII.canUse(lastKnight()) == true) {PIII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIII); return true;}
                            }
                            else if(current->type == PHOENIXIV){
                                PhoenixdownIV PIV;
                                if(PIV.canUse(lastKnight()) == true) {PIV.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIV); return true;}
                            }
                            current = current->next;
                        }
                        if(lastKnight()->gethp() <= 0){
                            if(lastKnight()->getgil() >= 100){
                                lastKnight()->setgil(lastKnight()->getgil()-100);
                                lastKnight()->sethp(lastKnight()->getmaxhp()/2);
                                return true;
                            }
                            return false; 
                        }  
                        else return true;
                    }
                }
                else return false;
            case BANDIT:
                if(lastKnight() != nullptr){
                    int levelO = (2+i)%10 + 1;
                    if(lastKnight()->getKnightType() == LANCELOT || lastKnight()->getKnightType() == PALADIN || lastKnight()->getlevel() >= levelO){
                        lastKnight()->setgil(lastKnight()->getgil() + 150);
                        if(lastKnight()->getgil() > 999) lastKnight()->setgil(999);
                        return true;
                    }
                    else {                                         
                        int HP = lastKnight()->gethp();
                        HP = lastKnight()->gethp() - 15*(levelO - lastKnight()->getlevel());
                        lastKnight()->sethp(HP);
                        ItemNode * current = lastKnight()->getbag()->head;
                        while(current != nullptr){
                            if(current->type == PHOENIXI){
                                PhoenixdownI PI;
                                if(PI.canUse(lastKnight()) == true) {PI.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXI); return true;}
                            }
                            else if(current->type == PHOENIXII){
                                PhoenixdownII PII;
                                if(PII.canUse(lastKnight()) == true) {PII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXII); return true;}
                            }
                            else if(current->type == PHOENIXIII){
                                PhoenixdownIII PIII;
                                if(PIII.canUse(lastKnight()) == true) {PIII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIII); return true;}
                            }
                            else if(current->type == PHOENIXIV){
                                PhoenixdownIV PIV;
                                if(PIV.canUse(lastKnight()) == true) {PIV.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIV); return true;}
                            }
                            current = current->next;
                        }
                        if(lastKnight()->gethp() <= 0){
                            if(lastKnight()->getgil() >= 100){
                                lastKnight()->setgil(lastKnight()->getgil()-100);
                                lastKnight()->sethp(lastKnight()->getmaxhp()/2);
                                return true;
                            }
                            return false; 
                        }  
                        else return true;                                                                                
                    }
                }
                return false;
            case LORDLUPIN:
                if(lastKnight() != nullptr){
                    int levelO = (3+i)%10 + 1;
                    if(lastKnight()->getKnightType() == LANCELOT || lastKnight()->getKnightType() == PALADIN || lastKnight()->getlevel() >= levelO){
                        lastKnight()->setgil(lastKnight()->getgil() + 450);
                        if(lastKnight()->getgil() > 999) lastKnight()->setgil(999);
                        return true;
                    }
                    else {                                       
                        int HP = lastKnight()->gethp();
                        HP = lastKnight()->gethp() - 45*(levelO - lastKnight()->getlevel());
                        lastKnight()->sethp(HP);
                        ItemNode * current = lastKnight()->getbag()->head;
                        while(current != nullptr){
                            if(current->type == PHOENIXI){
                                PhoenixdownI PI;
                                if(PI.canUse(lastKnight()) == true) {PI.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXI); return true;}
                            }
                            else if(current->type == PHOENIXII){
                                PhoenixdownII PII;
                                if(PII.canUse(lastKnight()) == true) {PII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXII); return true;}
                            }
                            else if(current->type == PHOENIXIII){
                                PhoenixdownIII PIII;
                                if(PIII.canUse(lastKnight()) == true) {PIII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIII); return true;}
                            }
                            else if(current->type == PHOENIXIV){
                                PhoenixdownIV PIV;
                                if(PIV.canUse(lastKnight()) == true) {PIV.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIV); return true;}
                            }
                            current = current->next;
                        }
                        if(lastKnight()->gethp() <= 0){
                            if(lastKnight()->getgil() >= 100){
                                lastKnight()->setgil(lastKnight()->getgil()-100);
                                lastKnight()->sethp(lastKnight()->getmaxhp()/2);
                                return true;
                            }
                            return false; 
                        }  
                        else return true;     
                    }
                }
                return false;
            case ELF:
                if(lastKnight() != nullptr){
                    int levelO = (4+i)%10 + 1;
                    if(lastKnight()->getKnightType() == LANCELOT || lastKnight()->getKnightType() == PALADIN || lastKnight()->getlevel() >= levelO){
                        lastKnight()->setgil(lastKnight()->getgil() + 750);
                        if(lastKnight()->getgil() > 999) lastKnight()->setgil(999);
                        return true;
                    }
                    else {                                          
                        int HP = lastKnight()->gethp();
                        HP = lastKnight()->gethp() - 75*(levelO - lastKnight()->getlevel());
                        lastKnight()->sethp(HP);
                        ItemNode * current = lastKnight()->getbag()->head;
                        while(current != nullptr){
                            if(current->type == PHOENIXI){
                                PhoenixdownI PI;
                                if(PI.canUse(lastKnight()) == true) {PI.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXI); return true;}
                            }
                            else if(current->type == PHOENIXII){
                                PhoenixdownII PII;
                                if(PII.canUse(lastKnight()) == true) {PII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXII); return true;}
                            }
                            else if(current->type == PHOENIXIII){
                                PhoenixdownIII PIII;
                                if(PIII.canUse(lastKnight()) == true) {PIII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIII); return true;}
                            }
                            else if(current->type == PHOENIXIV){
                                PhoenixdownIV PIV;
                                if(PIV.canUse(lastKnight()) == true) {PIV.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIV); return true;}
                            }
                            current = current->next;
                        }
                        if(lastKnight()->gethp() <= 0){
                            if(lastKnight()->getgil() >= 100){
                                lastKnight()->setgil(lastKnight()->getgil()-100);
                                lastKnight()->sethp(lastKnight()->getmaxhp()/2);
                                return true;
                            }
                            return false; 
                        }  
                        else return true;     
                    }
                }
                return false;
            case TROLL:
                if(lastKnight() != nullptr){
                    int levelO = (5+i)%10 + 1;
                    if(lastKnight()->getKnightType() == LANCELOT || lastKnight()->getKnightType() == PALADIN || lastKnight()->getlevel() >= levelO){
                        lastKnight()->setgil(lastKnight()->getgil() + 800);
                        if(lastKnight()->getgil() > 999) lastKnight()->setgil(999);
                        return true;
                    }
                    else {                                       
                        int HP = lastKnight()->gethp();
                        HP = lastKnight()->gethp() - 95*(levelO - lastKnight()->getlevel());
                        lastKnight()->sethp(HP);
                        ItemNode * current = lastKnight()->getbag()->head;
                        while(current != nullptr){
                            if(current->type == PHOENIXI){
                                PhoenixdownI PI;
                                if(PI.canUse(lastKnight()) == true) {PI.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXI); return true;}
                            }
                            else if(current->type == PHOENIXII){
                                PhoenixdownII PII;
                                if(PII.canUse(lastKnight()) == true) {PII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXII); return true;}
                            }
                            else if(current->type == PHOENIXIII){
                                PhoenixdownIII PIII;
                                if(PIII.canUse(lastKnight()) == true) {PIII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIII); return true;}
                            }
                            else if(current->type == PHOENIXIV){
                                PhoenixdownIV PIV;
                                if(PIV.canUse(lastKnight()) == true) {PIV.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIV); return true;}
                            }
                            current = current->next;
                        }
                        if(lastKnight()->gethp() <= 0){
                            if(lastKnight()->getgil() >= 100){
                                lastKnight()->setgil(lastKnight()->getgil()-100);
                                lastKnight()->sethp(lastKnight()->getmaxhp()/2);
                                return true;
                            }
                            return false; 
                        }  
                        else return true;     
                    }
                }
                return false;
            case TORNBERY:
                if(lastKnight() != nullptr){
                    int levelO = (6+i)%10 + 1;
                    if(lastKnight()->getlevel() >= levelO){   
                        lastKnight()->setlevel(lastKnight()->getlevel() + 1);
                        if(lastKnight()->getlevel() > 10) lastKnight()->setlevel(10);
                        return true;
                    }
                    else {          
                        if(lastKnight()->getKnightType() == DRAGON){return true;}              
                        BaseBag* knightbag = lastKnight()->getbag();                    
                        ItemNode * current = knightbag->head;
                        if(knightbag->get(ANTIDOTE) == false){
                            int i = 1;
                            while(current != nullptr){
                                if(i < 4){
                                    knightbag->head = current->next;    
                                    delete current;
                                    current = knightbag->head;
                                    knightbag->setcurrentCappacity(knightbag->getcurrentCapacity()-1);
                                    i++;
                                }
                                else {current = nullptr; knightbag = nullptr; break;}
                            }
                            lastKnight()->sethp(lastKnight()->gethp()-10);                           
                            ItemNode * current1 = lastKnight()->getbag()->head;
                            while(current1 != nullptr){
                                if(current1->type == PHOENIXI){
                                    PhoenixdownI PI;
                                    if(PI.canUse(lastKnight()) == true) {PI.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXI); return true;}
                                }
                                else if(current1->type == PHOENIXII){
                                    PhoenixdownII PII;
                                    if(PII.canUse(lastKnight()) == true) {PII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXII); return true;}
                                }
                                else if(current1->type == PHOENIXIII){
                                    PhoenixdownIII PIII;
                                    if(PIII.canUse(lastKnight()) == true) {PIII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIII); return true;}
                                }
                                else if(current1->type == PHOENIXIV){
                                    PhoenixdownIV PIV;
                                    if(PIV.canUse(lastKnight()) == true) {PIV.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIV); return true;}
                                }
                                current1 = current1->next;
                            }                              
                            if(lastKnight()->gethp() <= 0){
                                if(lastKnight()->getgil() >= 100){
                                    lastKnight()->setgil(lastKnight()->getgil()-100);
                                    lastKnight()->sethp(lastKnight()->getmaxhp()/2);
                                    return true;
                                }
                                return false; 
                            }  
                            else return true; 
                        }
                        else {
                            knightbag->get(ANTIDOTE);
                            return true;
                        }                             
                    }
                }
                return false;
            case QUEENOFCARDS:
                if(lastKnight() != nullptr){
                    int levelO = (7+i)%10 + 1;
                    if(lastKnight()->getlevel() >= levelO){
                        lastKnight()->setgil(lastKnight()->getgil()*2);
                        if(lastKnight()->getgil() > 999){                                          
                            int gilresidual = lastKnight()->getgil() - 999;
                            lastKnight()->setgil(999);
                            for(int i = count() - 1; i >= 0; i--){
                                if(gilresidual + knightInf[i]->getgil() <= 999){
                                    knightInf[i]->setgil(gilresidual + knightInf[i]->getgil());
                                    break;
                                }
                                else {
                                    gilresidual = knightInf[i]->getgil() + gilresidual - 999;
                                    knightInf[i]->setgil(999); 
                                }
                            }
                        }
                        return true;
                    }
                    else {
                        if(lastKnight()->getKnightType() == PALADIN){return true;}
                        lastKnight()->setgil(lastKnight()->getgil()/2);
                        return true;
                    }
                }
                return false;
            case NINADERINGS:
                if(lastKnight() != nullptr){
                    if(lastKnight()->getKnightType() == PALADIN){
                        if(lastKnight()->gethp() < lastKnight()->getmaxhp()/3){
                            lastKnight()->sethp(lastKnight()->gethp() + lastKnight()->getmaxhp()/5);
                            return true;
                        }
                        return true;
                    }
                    else {
                        if(lastKnight()->getgil() < 50) {return true;}
                        else {
                            if(lastKnight()->gethp() < lastKnight()->getmaxhp()/3){
                                lastKnight()->setgil(lastKnight()->getgil()-50);
                                lastKnight()->sethp(lastKnight()->gethp() + lastKnight()->getmaxhp()/5);
                                return true;
                            }
                            return true;
                        }
                    }
                }
                return false;
            case DURIANGARDEN:
                if(lastKnight() != nullptr){
                    lastKnight()->sethp(lastKnight()->getmaxhp());
                    return true;
                }
                return false;
            case WEAPON:
                if(lastKnight() != nullptr){
                    if(lastKnight()->getKnightType() == DRAGON || lastKnight()->getlevel() == 10 && lastKnight()->gethp() == lastKnight()->getmaxhp()){
                        lastKnight()->setlevel(10);
                        lastKnight()->setgil(999);
                        weapon = 1;
                        return true;
                    }
                    else {
                        lastKnight()->sethp(0);
                        ItemNode * current = lastKnight()->getbag()->head;
                        while(current != nullptr){
                            if(current->type == PHOENIXI){
                                PhoenixdownI PI;
                                if(PI.canUse(lastKnight()) == true) {PI.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXI); return true;}
                            }
                            else if(current->type == PHOENIXII){
                                PhoenixdownII PII;
                                if(PII.canUse(lastKnight()) == true) {PII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXII); return true;}
                            }
                            else if(current->type == PHOENIXIII){
                                PhoenixdownIII PIII;
                                if(PIII.canUse(lastKnight()) == true) {PIII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIII); return true;}
                            }
                            else if(current->type == PHOENIXIV){
                                PhoenixdownIV PIV;
                                if(PIV.canUse(lastKnight()) == true) {PIV.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIV); return true;}
                            }
                            current = current->next;
                        }
                        if(lastKnight()->gethp() <= 0){
                            if(lastKnight()->getgil() >= 100){
                                lastKnight()->setgil(lastKnight()->getgil()-100);
                                lastKnight()->sethp(lastKnight()->getmaxhp()/2);
                                return true;
                            }
                            return false; 
                        } 
                        return false;
                    }
                }
                return false;
            case HADES:
            if(lastKnight() != nullptr){
                if(lastKnight()->getlevel() == 10 || lastKnight()->getKnightType() == PALADIN && lastKnight()->getlevel() >= 8){
                    hades = 1;
                    if(hasPaladinShield() == true){
                        return true;
                    }
                    else {this->setpaladinshield(1); return true;}
                }
                else {
                    lastKnight()->sethp(0);
                    ItemNode * current = lastKnight()->getbag()->head;
                    while(current != nullptr){
                        if(current->type == PHOENIXI){
                            PhoenixdownI PI;
                            if(PI.canUse(lastKnight()) == true) {PI.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXI); return true;}
                        }
                        else if(current->type == PHOENIXII){
                            PhoenixdownII PII;
                            if(PII.canUse(lastKnight()) == true) {PII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXII); return true;}
                        }
                        else if(current->type == PHOENIXIII){
                            PhoenixdownIII PIII;
                            if(PIII.canUse(lastKnight()) == true) {PIII.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIII); return true;}
                        }
                        else if(current->type == PHOENIXIV){
                            PhoenixdownIV PIV;
                            if(PIV.canUse(lastKnight()) == true) {PIV.use(lastKnight()); lastKnight()->getbag()->get(PHOENIXIV); return true;}
                        }
                        current = current->next;
                    }
                    if(lastKnight()->gethp() <= 0){
                        if(lastKnight()->getgil() >= 100){
                            lastKnight()->setgil(lastKnight()->getgil()-100);
                            lastKnight()->sethp(lastKnight()->getmaxhp()/2);
                            return true;
                        }
                        return false; 
                    } 
                    return false;
                }
            }
            return false;
            default: return false;
        }
}

bool ArmyKnights::adventure(Events* events){
    for(int i = 0; i < events->count(); i++){
        switch (events->get(i)){
            case 1:
                if(this->fight(MADBEAR, i) == true){
                    this->printInfo();
                }
                else {
                    numberknights--;
                    if(numberknights == 0) {this->printInfo(); return false;}
                    this->printInfo();
                }            
                continue;
            case 2:            
                if(this->fight(BANDIT, i) == true){
                    this->printInfo();
                }
                else {
                    numberknights--;
                    if(numberknights == 0) {this->printInfo(); return false;}
                    this->printInfo();
                }
                continue;
            case 3:             
                if(this->fight(LORDLUPIN, i) == true){
                    this->printInfo();
                }
                else {
                    numberknights--;
                    if(numberknights == 0) {this->printInfo(); return false;}
                    this->printInfo();
                }
                continue;
            case 4:
                if(this->fight(ELF, i) == true){
                    this->printInfo();
                }
                else {
                    numberknights--;
                    if(numberknights == 0) {this->printInfo(); return false;}
                    this->printInfo();
                }
                continue;
            case 5:       
                if(this->fight(TROLL, i) == true){
                    this->printInfo();
                }
                else {
                    numberknights--;
                    if(numberknights == 0) {this->printInfo(); return false;}
                    this->printInfo();
                }       
                continue;
            case 6:
                if(this->fight(TORNBERY, i) == true){
                    this->printInfo();
                }
                else {
                    numberknights--;
                    if(numberknights == 0) {this->printInfo(); return false;}
                    this->printInfo();
                }
                continue;
            case 7:
                if(this->fight(QUEENOFCARDS, i) == true){
                    this->printInfo();
                }
                else {
                    numberknights--;
                    if(numberknights == 0) {this->printInfo(); return false;}
                    this->printInfo();
                }
                continue;
            case 8:
                if(this->fight(NINADERINGS, i) == true){
                    this->printInfo();
                }
                continue;
            case 9:
                if(this->fight(DURIANGARDEN, i) == true){
                    this->printInfo();
                }
                continue;
            case 10:
                if(weapon == 1) {this->printInfo(); continue;}
                if(this->fight(WEAPON, i) == true){
                    this->printInfo();
                }
                else {
                    numberknights--;
                    if(numberknights == 0) {this->printInfo(); return false;}
                    this->printInfo();
                }
                continue;
            case 11:
                if(hades == 1) {this->printInfo(); continue;}
                if(this->fight(HADES, i) == true){
                    this->printInfo();
                }
                else {
                    numberknights--;
                    if(numberknights == 0) {this->printInfo(); return false;}
                    this->printInfo();
                }
                continue;
            case 112:
                lastKnight()->getbag()->insertFirst(PHOENIXII);
                this->printInfo();
                continue;
            case 113:
                lastKnight()->getbag()->insertFirst(PHOENIXIII);
                this->printInfo();
                continue;
            case 114:
                lastKnight()->getbag()->insertFirst(PHOENIXIV);
                this->printInfo();
                continue;
            case 95:
                if(this->hasPaladinShield() == false){
                    this->setpaladinshield(1); 
                }
                this->printInfo();
                continue;
            case 96:
                if(this->hasLancelotSpear() == false){
                    this->setlancelotspear(1);
                }
                this->printInfo();
                continue;
            case 97:
                if(this->hasGuinevereHair() == false){
                    this->setguineverhair(1);
                }
                this->printInfo();
                continue;
            case 98:
                if(this->hasExcaliburSword() == false && this->hasGuinevereHair() == true && this->hasLancelotSpear() == true && this->hasPaladinShield() == true){
                    this->setexcalibursword(1);
                }
                this->printInfo();
                continue;
            default:
                if(this->hasExcaliburSword() == true){
                    this->printInfo();
                    return true;
                }
                else if(this->hasPaladinShield() == true
                     && this->hasLancelotSpear() == true
                     && this->hasGuinevereHair() == true
                     && this->hasExcaliburSword() == false){
                    int hpUltimecia = 5000;
                    if(lastKnight()->getKnightType() == PALADIN){
                        hpUltimecia -= lastKnight()->gethp() * lastKnight()->getlevel()*3/50;    
                    }
                    else if(lastKnight()->getKnightType() == LANCELOT){
                        hpUltimecia -= lastKnight()->gethp() * lastKnight()->getlevel()/20;
                    }
                    else if(lastKnight()->getKnightType() == DRAGON){
                        hpUltimecia -= lastKnight()->gethp() * lastKnight()->getlevel()*3/40;
                    }
                    for(int i = this->count()-2; i >= 0; i--){
                        if(knightInf[i]->getKnightType() == PALADIN){
                            hpUltimecia -= knightInf[i]->gethp()*knightInf[i]->getlevel()*3/50; 
                            if(hpUltimecia > 0){
                                continue;
                            }
                            else {
                                this->printInfo();
                                return true;
                            }
                        }
                        else if(knightInf[i]->getKnightType() == LANCELOT){
                            hpUltimecia -= knightInf[i]->gethp()*knightInf[i]->getlevel()/20;
                            if(hpUltimecia > 0){
                                continue;
                            }
                            else {
                                this->printInfo();
                                return true;
                            }
                        }
                        else if(knightInf[i]->getKnightType() == DRAGON){
                            hpUltimecia -= knightInf[i]->gethp()*knightInf[i]->getlevel()*3/40;
                            if(hpUltimecia > 0){
                                continue;
                            }
                            else {
                                this->printInfo();
                                return true;
                            }
                        }
                    }
                    numberknights = 0;
                    this->printInfo();
                    return false;
                }
                else {
                    numberknights = 0;
                    this->printInfo();
                    return false;
                }
        }
    }
    return false;
}

// Class BaseKnights
class PaladinKnight:public BaseKnight {
    public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->gil = gil;
        this->bag = new PaladinBag(this, antidote, phoenixdownI);
        this->knightType = PALADIN;
        this->hp = maxhp;
    }
};

class LancelotKnight:public BaseKnight {
    public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->gil = gil;
        this->bag = new LancelotBag(this, antidote, phoenixdownI);
        this->knightType = LANCELOT;
        this->hp = maxhp;
    }
};

class DragonKnight:public BaseKnight {
    public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->gil = gil;
        this->bag = new DragonBag(this, antidote, phoenixdownI);
        this->knightType = DRAGON;
        this->hp = maxhp;
    }
};

class NormalKnight:public BaseKnight {
    public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->gil = gil;
        this->bag = new NormalBag(this, antidote, phoenixdownI);
        this->knightType = NORMAL;
        this->hp = maxhp;
    }
};

BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    if (checkPrime(maxhp)) {
        return new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else {
        if (maxhp == 888) {
            return new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        }
        else {
            if (checkPytago(maxhp)) {
                return new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
            }
            else {
                return new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
            }
        }
    } 
}

