//
// Created by Martin Černil on 04.07.2020.
//
/*dont forget to change name*/
#ifndef KINALI_TESTING_H
#define KINALI_TESTING_H
#include <vector>

class Entity
{
public:
    Entity(std::string entityname, int givenid)
    {
        std::cout << "INFO: Entity created, with a name: " << entityname << " and id: " << givenid << std::endl;
        this->name = entityname;
        this->id = givenid;
    };
    std::string name;
    int id;

    void state_();
};

class Item : public Entity
{
public:
    Item(std::string itemname, int itemid, bool equipable = false) : Entity(itemname, itemid) {this->equipable = equipable;};
    std::vector<Item> container;
    bool equipable;

    void add_(Item item, std::vector<Item> &itemlist);
    void remove_(int deleteid, std::vector<Item> &itemlist);
    void state_();
};

class Player : public Item
{
public:
    Player(std::string playername, int playerid) : Item(playername, playerid) {};
    std::vector<Item> equipment, inventory;
    std::vector<std::string> properties;

    void equip_(std::string itemname);
    void unequip_(std::string itemname);
    void state_();
};

class World : public Item
{
public:
    World(std::string worldname, int worldid) : Item(worldname, worldid) {};

    void state_();
};

bool valid_id_entry(int entry,std::vector<Item> founditems);
bool valid_string_entry(std::string entry, std::vector<std::string> validentries);
std::string display_itemlist(std::vector<Item> itemlist, bool onlyequipable=false);
int find_itemid(std::string itemname, std::vector<Item> itemlist);
int choose_item(std::vector<Item> founditems);
#endif //KINALI_TESTING_H
