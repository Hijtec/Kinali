//
// Created by Martin Černil
//

#include <vector>
#include <iostream>
#include <string>
#include "item_manage.h"


void Item::add_(Item item, std::vector<Item> &itemlist) {
    itemlist.push_back(item);
}

void Item::remove_(int deleteid, std::vector<Item> &itemlist){
    std::vector<Item>::iterator it, deletethis;
    for (it = itemlist.begin(); it != itemlist.end(); ++it)
    {
        if (it->id == deleteid)
        {
            deletethis = it;
        }
    }
    itemlist.erase(deletethis);
}

bool valid_id_entry(int entry,std::vector<Item> founditems)
{
    std::vector<Item>::iterator it;
    for (it = founditems.begin(); it != founditems.end(); ++it)
    {
        if (it->id == entry)
        {
            return true;
        }
    }
    return false;
}

bool valid_string_entry(std::string entry, std::vector<std::string> validentries)
{
    std::vector<std::string>::iterator it;
    for (it = validentries.begin(); it != validentries.end(); ++it)
    {
        if (*it == entry)
        {
            return true;
        }
    }
    return false;
}

int choose_item(std::vector<Item> founditems)
{
    std::vector<Item>::iterator it;
    int entry;
    for (it = founditems.begin(); it != founditems.end(); ++it)
    {
        std::cout << "INFO: Found an item named " << it->name << " with id: " << it->id << std::endl;
    }
    std::cout << "INFO: Enter an id of an item you with to interact with: " << std::endl;
    std::cin >> entry;

    while (!valid_id_entry(entry,founditems))
    {
        std::cout << "INFO: Please, enter a valid id you wish to remove: " << std::endl;
        std::cin >> entry;
    }
    return entry;
}

int find_itemid(std::string itemname, std::vector<Item> itemlist) {
    std::vector<Item> founditems;
    std::vector<Item>::iterator it, last_it_found;

    for (it = itemlist.begin(); it != itemlist.end(); ++it) {
        if (it->name == itemname)
        {
            founditems.push_back(*it);
            last_it_found = it;
        }
    }
    if (founditems.size() >= 2)
    {
        return choose_item(founditems);
    } else if (founditems.size() == 1)
    {
        return last_it_found->id;
    } else if (founditems.empty())
    {
        std::cout << "Item not found." << std::endl;
        return 0;
    }
    return 0;
}

void Player::equip_(std::string itemname)
{
    std::vector<Item>::iterator it;
    int equipid;

    if (this->inventory.empty())
    {
        std::cout << "Inventory is empty. Nothing to equip." << std::endl;
    }
    equipid = find_itemid(itemname, this->inventory);

    if (equipid == 0){
        std::cout << "Can't equip an item that was not found." << std::endl;
    }

    for (it = this->inventory.begin(); it != this->inventory.end(); ++it)
    {
        if ((it->name == itemname) && (it->id == equipid) && (it->equipable))
        {
            //equipable item found
            this->add_(*it, this->equipment);
            std::cout << it->name << " equipped." << std::endl;
            return;
        }
    }
    //equipable item not found
    std::cout << "Cannot equip item, its either unequipable or not in your inventory." << std::endl;
}

void Player::unequip_(std::string itemname)
{
    int unequipid;

    if (this->equipment.empty())
    {
        std::cout << "There's nothing to unequip." << std::endl;
    }

    unequipid = find_itemid(itemname, this->equipment);
    if (unequipid == 0){
        std::cout << "You don't have this item equipped." << std::endl;
    }
    else {
        this->remove_(unequipid, this->equipment);
    }

}

std::string display_itemlist(std::vector<Item> itemlist, bool onlyequipable) {
    std::string output;
    std::vector<Item>::iterator it;
    for (it = itemlist.begin(); it != itemlist.end(); ++it) {

        if (onlyequipable)
        {
            if (it->equipable == true){
                output += (it->name + "(");
                output += std::to_string(it->id);
                output += ") |";
            }
        } else {
            output += (it->name + "(");
            output += std::to_string(it->id);
            output += ") |";
        }
    }
    return output;
}

void Entity::state_()
{
    std::cout << "Entity: " << this->name << " ID: " << this->id << std::endl;
}

void Item::state_()
{
    std::cout << "Item: " << this->name << " ID: " << this->id << " Equipable: " << this->equipable << std::endl;
}

void Player::state_()
{
    std::cout << "Player: " << this->name << " ID: " << this->id << " Properties: " << "TODO:Add list of properties" << std::endl;
    std::cout << "Inventory: " << display_itemlist(this->inventory) << std::endl;
    std::cout << "Equipment: " << display_itemlist(this->equipment)<< std::endl;
}

void World::state_()
{
    std::cout << "World: " << this->name << " ID: " << this->id << std::endl;
    std::cout << "Contains: " << display_itemlist(this->container) << std::endl;
}