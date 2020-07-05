#include <iostream>
#include <conio.h>
#include "item_manage.h"

int current_id = 1; //global variable

void shutdown()
{
    exit(0);
}

void user_interaction(std::string entry,
        World world,
        Player player,

        bool sensitivityWarning=false,
        bool showWorld=false,
        bool showInventory=false,
        bool showEquipment=false,
        bool showEquipable=false){
    std::cout << std::endl << "You chose a " << entry << " action." << std::endl;

    if (sensitivityWarning){
        std::cout << "Item names are case sensitive." << std::endl;
    }
    if (showWorld){
        std::cout << "These are all of the current items in the world:" << std::endl;
        std::cout << "WORLD: " << display_itemlist(world.container) << std::endl;
    }
    if (showInventory) {
        std::cout << "These are all of the current items in player's inventory:" << std::endl;
        std::cout << "INVENTORY: " << display_itemlist(player.inventory) << std::endl;
    }
    if (showEquipment) {
        std::cout << "These are all of the current items the player currently has equipped:" << std::endl;
        std::cout << "EQUIPMENT: " << display_itemlist(player.equipment) << std::endl;
    }
    if (showEquipable) {
        std::cout << "These are all of the current items in player's inventory that are equipable:" << std::endl;
        std::cout << "EQUIPABLE: " << display_itemlist(player.inventory, true) << std::endl;
    }
}

void action_item(std::string entry, int id, World &world, Player &player) {
    user_interaction(entry, world, player, true,true);
    std::string name, mode, equip;
    std::vector<std::string> invalid_name{""}, valid_mode{"ADD", "REM"}, valid_equip{"y", "n"};
    std::cout << "Enter the name of the item: " << std::endl;
    std::cin >> name;
    while (valid_string_entry(name, invalid_name)) {
        std::cout << "Please, enter at least something: " << std::endl;
        std::cin >> name;
    }
    std::cout << "ADD or REM: " << std::endl;
    std::cin >> mode;
    while (!valid_string_entry(mode, valid_mode)) {
        std::cout << " Choose a valid mode: " << std::endl;
        std::cin >> mode;
    }
    if (mode == "ADD"){
        std::cout << "Is the item equipable (y/n): " << std::endl;
        std::cin >> equip;
        while (!valid_string_entry(equip, valid_equip)) {
            std::cout << " Choose a valid answer: " << std::endl;
            std::cin >> equip;
        }
        if (equip == "y"){
            Item item(name, id, true);
            world.add_(item, world.container);
            current_id += 1;
        } else if (equip == "n") {
            Item item(name, id, false);
            world.add_(item, world.container);
            current_id += 1;
        }
    }
    if (mode == "REM"){
        player.remove_(find_itemid(name,player.inventory),player.inventory);
    }
}
void action_inventory(std::string entry, int id, World &world, Player &player) {
    user_interaction(entry, world, player, true, true, true);
    std::string name, mode, equip;
    std::vector<std::string> invalid_name{""}, valid_mode{"ADD", "REM"}, valid_equip{"y", "n"};
    std::cout << "Enter the name of the item: " << std::endl;
    std::cin >> name;
    while (valid_string_entry(name, invalid_name)) {
        std::cout << "Please, enter at least something: " << std::endl;
        std::cin >> name;
    }
    std::cout << "ADD or REM: " << std::endl;
    std::cin >> mode;
    while (!valid_string_entry(mode, valid_mode)) {
        std::cout << " Choose a valid mode: " << std::endl;
        std::cin >> mode;
    }
    if (mode == "ADD"){
        std::cout << "Is the item equipable (y/n): " << std::endl;
        std::cin >> equip;
        while (!valid_string_entry(equip, valid_equip)) {
            std::cout << " Choose a valid answer: " << std::endl;
            std::cin >> equip;
        }
        if (equip == "y"){
            Item item(name, id, true);
            player.add_(item, player.inventory);
            current_id += 1;
        } else if (equip == "n") {
            Item item(name, id, false);
            player.add_(item, player.inventory);
            current_id += 1;
        }
    }
    if (mode == "REM"){
        player.remove_(find_itemid(name,player.inventory),player.inventory);
    }
}
void action_equipment(std::string entry, World &world, Player &player) {
    user_interaction(entry, world, player, true, false, true, true, true);
    std::string name, mode;
    std::vector<std::string> valid{ "EQUIP", "UNEQUIP"};
    std::cout << "Enter the name of the item: ";
    std::cin >> name;
    std::cout << "EQUIP or UNEQUIP: ";
    std::cin >> mode;
    while (!valid_string_entry(mode, valid)){
        std::cout << " Choose a valid mode: ";
        std::cin >> mode;
    }
    if (mode == "EQUIP") {
        player.equip_(name);
    } else if (mode == "UNEQUIP") {
        player.unequip_(name);
    }
}
void action_state(std::string entry, World world, Player player) {
    user_interaction(entry, world, player);
    std::cout << "This is the current state of the world:" << std::endl;
    world.state_();
    std::cout << "This is the current state of the player:" << std::endl;
    player.state_();
    getch();
}
void action_exit(std::string entry, World world, Player player) {
    user_interaction(entry, world, player);
    std::cout << "Goodbye" << std::endl;
    shutdown();
}
void action(World &world, Player &player, int id)
{
    std::string entry;

    std::cout << std::endl;
    std::cout << "ITEM         - add/remove item to/from world" << std::endl;
    std::cout << "INVENTORY    - add/remove items to/from player inventory" << std::endl;
    std::cout << "EQUIPMENT    - equip/unequip items from/to player inventory" << std::endl;
    std::cout << "STATE        - shows the current state of the environment" << std::endl;
    std::cout << "EXIT         - exits the program" << std::endl;
    std::cout << "ITEM, INVENTORY, EQUIPMENT, STATE, EXIT";
    std::cout << " Choose an action to execute: ";
    std::cin >> entry;

    std::vector<std::string> valid{ "ITEM", "INVENTORY", "EQUIPMENT", "STATE", "EXIT"};
    while (!valid_string_entry(entry, valid))
    {
        std::cout << " Choose a valid action to execute: ";
        std::cin >> entry;
    }
    if (entry == "ITEM") {
        action_item(entry, id, world, player);
    } else if (entry == "INVENTORY") {
        action_inventory(entry, id, world, player);
    } else if (entry == "EQUIPMENT") {
        action_equipment(entry, world, player);
    } else if (entry == "STATE") {
        action_state(entry, world, player);
    } else if (entry == "EXIT") {
        action_exit(entry, world, player);
    }
}

void Clear()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}


int main()
{
    World world("World", 1);
    Player player("Player1", 1);
    /*
    Item a("a",1,true);
    Item b("a",2);
    Item c("a",3);
    Item d("a",4);
    Item e("a",5);
    Item f("a",6);*/

    bool exitstate = false;
    while (exitstate == false)
    {
        action(world, player, current_id);
    }
}
