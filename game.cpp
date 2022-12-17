// ================== Pre-processor commands =================
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;
// ==================== Structures ==========================

struct Weapon 
{   string type; //Multiple weapons in game that are used to fight monsters 
    int strike;
};

struct Character //The player's stats as you play
{   float health;
    int stamina;
    int energy;
};

struct Enemy //Multiple enemies in the game, show's their stats
{   string name;
    float healthPoints;
    int damage;
};

// =================== Prototypes ======================

int genericMenu (string, string [], int, int &, string);

int startGame (int &);
int mapLocationSelection (int &); 
int adventureOceanStart (int &);
int adventureMountainStart (int &);
int adventureCaveStart (int &); 
int oceanRouteContd (int &);
int bossFight (Enemy &, Character &, Weapon &, int &);

void showEnemyHealthPoints (Enemy &, Weapon &);
void showPlayerHealthPoints (Enemy &, Character &); 
void displayerUserStatus (Character &);
void displayEnemyStatus (Enemy &);
void displayWeaponStats (Weapon &);
void initializeCharacter (Character &, float, int, int);
void initializeEnemy (Enemy &, string, float, int);
void initializeWeapon (Weapon &, string, int);
void outsideCave (Weapon &, Character &);
void insideCave (Weapon &, Character &);
void caveFinalBattle (Enemy &, Character &, Weapon &, int &);
void climbMountain (Weapon &, Character &);
void slugMoutainBattle (Weapon &, Character &);
void mountainFinalBattle (Enemy &, Character &, Weapon &, int &);
void oceanSandPath (Character &);
void oceanGravelPath (Character &);
void oceanAxeOption (Weapon &);
void oceanSpearOption (Weapon &);
void oceanFinalBattle (Enemy &, Character &, Weapon &, int &);
void adventureEnd (Character &);

// =================== Definitions ======================

//Generic Menu for the function (selecting from the choices)
int genericMenu (string prompt, string options[], int numberOfOptions, int &userChoice, string errorMessage)
{   do
    {
        cout << prompt << endl;
        for (int i = 0; i < numberOfOptions; i++)
        {
            cout << i + 1 << ") " << options[i] << endl; //user options 

        }
        cin >> userChoice;
        if (userChoice > numberOfOptions || userChoice < 1)
        {
            cout << errorMessage << endl; //error message
        }
    }while (userChoice > numberOfOptions || userChoice < 1);

    return userChoice;
}

//Display structures 
void displayUserStatus (Character &_player) //function to display end-user's status
{
    cout << "===== Player Status =====" << endl;
    cout << "Health: " << _player.health << endl;
    cout << "Energy: " << _player.energy << endl;
    cout << "Stamina: " << _player.stamina << endl;
    cout << endl;

    return;
}

void displayEnemyStatus (Enemy &_enemy)
{   cout << "===== Enemy Status =====" << endl; //function to an enemy's status
    cout << "Enemy: " << _enemy.name << endl;
    cout << "Health: " << _enemy.healthPoints << endl;
    cout << "Damage: " << _enemy.damage << endl; 
    cout << endl;

    return;
}

void displayWeaponStats (Weapon &_weapon)
{   cout << "===== Weapon Stats =====" << endl; //function to weapon stats. 
    cout << "Type: " << _weapon.type << endl;
    cout << "Damage: " << _weapon.strike << endl;

    return;
}

//Initializing Character Structure
void initializeCharacter (Character &_player, float _health, int _stamina, int _energy)
{
    _player.health = _health;
    _player.energy = _energy;
    _player.stamina = _stamina;

    return;
}
//Initializing Enemy Structure
void initializeEnemy (Enemy &_enemy, string _name, float _healthPoints, int _damage)
{
    _enemy.name = _name;
    _enemy.healthPoints = _healthPoints;
    _enemy.damage = _damage;

    return;
}
//Initializing Weapon Structure
void initializeWeapon (Weapon &_weapon, string _type, int _strike)
{
    _weapon.type = _type;
    _weapon.strike = _strike;

    return;
}

//Enemy Encounters attacks inflicted
void showEnemyHealthPoints(Enemy &_enemy, Weapon &_weapon)
{   _enemy.healthPoints = _enemy.healthPoints - _weapon.strike; //During combat - enemy health after taking damage 

    return;
}

void showPlayerHealthPoints (Enemy &_enemy, Character &_player)
{   _player.health = _player.health - _enemy.damage; //During combat - player health after taking damage

    return;
}

//Boss Fight Function - common funciton used in each world. 
int bossFight (Enemy &_enemy, Character &_player, Weapon &_weapon,  int &userChoice)
{   
    if (userChoice == 1)
    {
        displayEnemyStatus (_enemy); //displays stats for both enemy and player 
        displayUserStatus (_player);
            
        cout << "\nYou attacked the Boss.\n";
        showEnemyHealthPoints (_enemy, _weapon); //Calls to show enemy hp after being hit by weapon

        cout << "The enemy " << _enemy.healthPoints << " HP left.\n\n";

        cout << "The Boss hit you back.\n";
        showPlayerHealthPoints (_enemy, _player); //Calls to show player hp after being hit by enemy
        cout << "You now have " << _player.health << " HP left.\n\n";

    }
    else if (userChoice == 2)
    {
        displayEnemyStatus (_enemy); //displays stats for both enemy and player 
        displayUserStatus (_player);

        cout << "You chose not to attack so the Boss striked you instead\n";
        showPlayerHealthPoints (_enemy, _player); //Calls to show player hp after being hit by enemy
        cout << "You now have " << _player.health << " HP left.\n\n";
    }
    
    //Possible outcomes from battle (once you die. The entire program ends.)
    
    if (_player.health == 0 && _enemy.healthPoints == 0) //both you and the enemy are dead
    {   cout << "You both perished...\n\n" << endl; 
        adventureEnd (_player);
    }
    else if (_player.health <= 0) //if you're dead then game ends 
    {   cout << "You died...lol\n\n" << endl;
        adventureEnd (_player);
    }
    else if (_enemy.healthPoints <= 0) //if enemy is dead you can continue 
    {   cout << "You won!\n\n=====================WORLD COMPLETE!===================\n\nLet's go back to the map!" << endl;
    }
    return userChoice; 
}


// Game Title Screen - provides option to start their adventure or quit depending on userChoice
int startGame (int &userChoice)
{   string options[2] = {"Yes", "No"}; //Generic menu prompts for options 

    cout << "========================================= Title Screen =========================================\n" << endl;
    cout << "Welcome to this adventure game of Block.o's secrets. Now that you have unraveled the untold secret of who I truly am. Today you will be discovering the world inside Block.o's" << endl;
    cout << "world! As you are the only human ever to enter this world, will you be able to go back to humanity? You took all this effort to discover this world are you going to sit still?" << endl;
    cout << "Would you like to get started to unfold this cautionary tale? Remember it's me Cube ruler of the Block realm... But you never know what may this world hold for a simple traveller like you...\n" << endl;

    genericMenu ("Would you like to get started?", options , 2, userChoice, "Invalid"); //calling generic menu

    return userChoice;
}

//Map Location - user chooses to the realm they want to go to
int mapLocationSelection (int &userChoice)
{   string options [4] = {"Go down to the Great Blue Ocean!", "Go to the rocky mountains", "Discover the caves", "Exit Game"}; //Generic menu prompts for options 

    cout << "This world is quite large and dangerous. Here, have a map for your troubles. This map will help you navigate through the world. Whenever you want to move or change locations!" << endl;
    cout << "Hey! Traveller select the location, where you want to go to!\n" << endl;

    genericMenu ("Where do you want to go?", options , 4 , userChoice, "Invalid"); //calling generic menu 

    return userChoice;
}

//Map Choice Location 1 - Ocean Realm

//Start of Location 1 
int adventureOceanStart (int &userChoice)
{   string options[2] = {"Search for materials in the sand", "Search for materials in gravel "}; //The maximum number you can guess from

    cout << "========================================= Ocean Realm =========================================\n" << endl;
    cout << "Oh the under water route I see... Interesting choice... You can't breathe under water smart one - remember you're human silly. Well I mean I am the ruler of the overworld."<< endl;
    cout << "I can't really help you in this situation, but you know what we can do? Collect some materials along the way to brew some effects, so you know, so you can live underwater." << endl;
    cout << "No worries, we're just chilling on the shore for now, so you can find your materials here, but MAKE SURE to be careful here, I hear that there is spooky things that lurk around these parts" << endl;
    cout << "Anyways heads up! Just to let you know once you start to collect all the materials, you sorta can't go back, your map's powers are sort of like a compass. Once you enter the realm, you cant access" << endl;
    cout << "the same frequencies like you do on earth. Anyways, just keep that in mind alright? Now... onto collecting materials. important important...\n" << endl;

    genericMenu ("Where shall we search?", options, 2, userChoice, "Invalid, please select a journey path!"); //prompts the user and checks if end-user choice is valid

    return userChoice;
}

//Path one location 1 
void oceanSandPath (Character &_player)
{
    cout << "Well smart going searching for the materials IN ALL THIS SAND. We're on the outskirts of the ocean. Smart... smart, how long do you think this is going to take us?" << endl;
    cout << "You dig and dig for materials, although you really have no idea whwat you're really looking for. But you feel a look in a promising looking sand clump. Amazing..." << endl;
    cout << "You uncover the clump and realize it is a crab that pinches you. You lie there on the sand bank tired and feel incredibly foolish for choosing this route\n**Energy -5, Health -5, Stamina -2**" << endl;
    
    //Status Change
    _player.energy -= 5;
    _player.health -= 5;
    _player.stamina -= 2;

    cout << endl;
    displayUserStatus (_player); //display the users status after status change

    cout << "At least you found the materials? Okay, took you long enough....\n" << endl;


    return;
}

//Path Two location 1 
void oceanGravelPath  (Character &_player)
{
    cout << "Well this gravel looks... rocky? I mean to be fair it is less things to look through than you know sand, cause we're basically on a beach. You know how many years that would take" << endl;
    cout << "As the wise old cube I am, rocks are pretty neat and sharp, so just watch out but since the particle size is way larger than sand, you'll probably be able to find everything you need" << endl;
    cout << "***cRacKL***\nWell that sounded like it hurt... don't worry just take a break!\n**Energy -2, Health -10, Stamina -2**" << endl;
    
    //Status Change
    _player.energy -= 2; 
    _player.health -= 10;
    _player.stamina -= 2;

    cout << endl;
    displayUserStatus (_player); //display the users status after status change

    cout << "You collect the materials and are ready for the rest of the journey..." << endl;

    return;
}

//Route Two location 1 
int oceanRouteContd (int &userChoice)
{   string options [2] = {"Pick up spear" , "Pick up axe"}; //Options for end-user to choose from generic menu

    cout << "You collect the materials and are ready to make an elixir to be able to breathe under the dark blue sea, to finally discover the underwater world! You set up camp on the shore and get ready for" << endl;
    cout << "sleep, then in the sand you see a glimering sight. Oh some weapons... not like that will help. But this world is dangerous\nYou: Cube why are you narrating?\nCube:Hushhh it's all about the ~lure~ k." << endl;
    cout << "You're curious about if you actually take a weapon, because as Cube said DANGER = BAD\nYou: I never thought that\nCube: Well... are you going to take one?\nYou ponder and think better be safe than sorry" << endl;

    cout << endl;
    genericMenu ("Well which weapon should you grab?", options, 2, userChoice, "Stop being stuborn, go on choose");

    return userChoice;
}

//Path one - Route Two location 1 
void oceanAxeOption (Weapon &_weapon) 
{   initializeWeapon (_weapon,"Axe", 25); //Intializes weapon going to be used 

    cout << "You pick up an axe! How exciting....Cube mumbles... what are you a lumber jack?. Well nice choice, I mean you can only carry so many things on your journey am I right?\nYou: You know I'm holding an axe" << endl;
    cout << "Jeez no need to get so agro. So here it is in all its glory... Real talk human to cube. You really chose this as your weapon it's so... OVER POWERED HELLO? Yeah, you'll do just fine with this, enjoys" << endl;
    
    displayWeaponStats (_weapon); //displays weapon type
    cout << endl;
    
    return;
}

//Path two - Route Two location 1 
void oceanSpearOption (Weapon &_weapon)
{   initializeWeapon (_weapon,"Spear", 25); //Intializes weapon going to be used 

    cout << "You pick up the spear. Wow, I'm wondering how no one noticed this long stick siting in the middle of the sand. I mean it's a two handed object and beings only have so much carrying space." << endl;
    cout << "Even in this realm, a spear is pretty prehistoric. I can't judge. You're literally the one standing with a sharp pointy stick, I'm not taking any risks of getting impaled... again...sigh*" << endl;
    
    displayWeaponStats (_weapon); //displays weapon type
    cout << endl;

    return;
}

//Final Battle - Location 1 
void oceanFinalBattle(Enemy &_enemy, Character &_player, Weapon &_weapon,  int &userChoice)
{
    string options [2] = {"Swing", "Stab"}; //Options for end-user to choose from generic menu
    
    initializeEnemy (_enemy, "Hydro Boss", 125 , 15); //Intializes enemy
    initializeCharacter (_player, 150, 75, 60); //Intitializes player's status to set back to full health

    cout << "You stumble across a under water cave and realize jump on something squishy... The squishy creature arises...\n???: *GROWL*\nWell goodjob, you woke up somthing scary didn't you.";
    cout << "Hurry you need to decide quick what are you going to do!\nThis is going to be incredibly dangerous... so beware and choose wisely for gods sake. It's a Hydro Boss congrats, they're sorta real" << endl;
    cout << "Hydro Boss: *GROWLS* Who goes there!?!\n Welp... traveller good luck! I'll heal you first, so it's a fair fight :)\n =====MAX REVIVE=====" << endl;

    cout << "========================================= OCEAN REALM BOSS =========================================\n" << endl;
    
    displayWeaponStats (_weapon);  //displays weapon type
    cout << endl;
    
    do
    {   genericMenu ("Hit Hydro Boss:", options, 2, userChoice, "Invalid Response"); //Generic Menu. Provides choices for end-user to battle with. 
        
        bossFight (_enemy, _player, _weapon, userChoice);
        
        //Stats change after every loop
        _player.energy -= 2;
        _player.stamina -= 2;

    }while(_player.health > 0 && _enemy.healthPoints > 0);
    
    return;
}

//Map Choice Location 2 - Mountain Realm

int adventureMountainStart (int &userChoice)
{   string options [2] = {"Climb up the mountain", "Safely Dig a Route Up"}; //Options for generic menu

    cout << "========================================= MOUNTAIN REALM =========================================\n" << endl;
    cout << "Welcome. I mean technically I own the flat part of this realm, but the mountain's are a place I never really understood why anyone liked. Like being honest," << endl;
    cout << "climbing these things are incredibly tiring...since I don't have legs my sides just get dirty and rocks HURT, anyways let's just venture off and see what this" << endl;
    cout << "world has in store for you...Choose a route, even though I hate this place, I have to flaunt it off somehow." << endl;

    genericMenu ("Where are we off to?", options, 2, userChoice, "Hey WAKE UP. Invalid response."); //Calls Generic menu.

    return userChoice;
}

//Route 1 - Location 2 (Mini Battle)
void slugMoutainBattle (Weapon &_weapon, Enemy &_enemy, Character &_player, int &userChoice)
{   string options [3] = {"Clean up!", "Deep Rinse", "AH it's a BUG"};//Options for generic menu

    initializeEnemy (_enemy, "Mountain Slugs", 20, 0); //Intializes Enemy For Specific Battle 
    initializeWeapon (_weapon, "The MOP", 10); //Intializes Weapon Type 

    cout << "Well isn't that great, MOUNTAIN SLUGS. The worst kind of slugs. Great, just great. You know hard it is to get SLUG JUICE out of my faces. You can take care of them right?"<< endl;
    cout << "The thing with slugs is that they're slippery and slimy, so I provide you my god tier weapon of choice... the mop..." << endl;

    displayWeaponStats (_weapon);
    
    //Introduction to Battle Prompt 
    cout << "\nLet's destroy some SLUGS! They have no limbs just goop, so it's just nature's house keeping I guess..." << endl;
    cout << "=========== SLUG BATTLE? (CLEAN UP TIME?) ============\n" << endl;
    displayUserStatus (_player);
    displayEnemyStatus (_enemy);
    
    //This Battle is one sided to ensure 100% win rate 
    do
    {   genericMenu ("Time to attack! Choose a move", options, 3, userChoice, "They're going to make me slimy. INVALID CHOICE. C'MON!"); //Generic menu.

        if (userChoice == 1 || userChoice == 2 || userChoice == 3) //User possible choices
        {   displayUserStatus (_player);
            displayEnemyStatus (_enemy);

            cout << "You attacked the slugs" << endl;
            showEnemyHealthPoints (_enemy, _weapon);
            
            _player.energy -= 2; //Player status change
            _player.stamina -= 2;

            cout << "Mountain Slugs now have " << _enemy.healthPoints << " HP left.\n\n";
        }

        if (_enemy.healthPoints <= 0) //When Enemy dies, final prompt of this route
        {   
            cout << "You won!\n" << endl;
        }

    }while( _enemy.healthPoints > 0); //Loops until the enemy has died. 

    cout << endl;

    return;
}

//Route 2 - Location 2 (Chance Game)
void climbMountain (Weapon &_weapon, Character &_player, int &userChoice)
{   
    float luckyBlock = 1 + (rand() % 3); //Randomizes the selction you can get 
    string options [2] = {"Roll Lucky Block", "Move on"}; //options for generic menu 

    cout << "The long and boring way up the mountain. I mean to be fair it is the safer route... it just takes a little long to climb, quite tiring I must say" << endl;
    cout << "Oh look here a lucky block! Let's see if you can get lucky from this... Don't worry about it try it you want to...?\n" << endl;

    genericMenu ("Do you want to take the chance?", options, 2,  userChoice, "Invalid."); //calls generic menu

    if (userChoice == 1)
    {   
        cout << "You rolled a " << luckyBlock << endl; 
        
        if (luckyBlock == 1)
        {   cout << "New Weapon! You recieved a Fork!\n" << endl; //Initializes selected weapon 
            initializeWeapon (_weapon, "The Fork", 10);
            displayWeaponStats (_weapon); //Display Weapon Stats 
        }
        else if (luckyBlock == 2)
        {   cout << "New Weapon! You recieved a Shovel\n" << endl;
            initializeWeapon (_weapon, "Shovel", 10); //Initializes selected weapon
            displayWeaponStats (_weapon);  //Display Weapon Stats 
        }
        else if (luckyBlock == 3)
        {   cout << "New Weapon! You recieved a brick...\n" << endl;
            initializeWeapon (_weapon, "BRICK", 10); //Initializes selected weapon
            displayWeaponStats (_weapon);  //Display Weapon Stats 
        }
    }
    else if (userChoice == 2)
    {   cout << "Alright Moving on..." << endl;
        cout << "You pick up a Spork on your way" << endl; 
        initializeWeapon (_weapon, "Spork", 10);//Initializes selected weapon
        displayWeaponStats (_weapon);  //Display Weapon Stats 
    }
 
    cout << endl;

    return;
}

void mountainFinalBattle(Enemy &_enemy, Character &_player, Weapon &_weapon,  int &userChoice)
{
    string options [2] = {"Wack", "Stab"}; //Options for generic menu 
    
    initializeEnemy (_enemy, "Monkey", 120, 5); //Initializes Enemy within the function 
    initializeCharacter (_player, 150, 75, 60); //Initializes Player back to full health

    cout << "You reach the top of the mountain and are ready for what is going to come at you. Get ready! **THUNK**. Well that doesn't sound promising. I give you the bestest of luck." << endl;
    cout << "That's so much fun, you bumped into the a monster... Isn't your luck amazing! Ha. ha. I am really just joking... Don't worry! You have a weapon now." << endl; 
    cout << "Geo Boss: *cLunK* Who goes there!?!\n Welp... traveller good luck! I'll heal you first, so it's a fair fight :)\n =====MAX REVIVE REST STATS=====" << endl;

    cout << "========================================= MOUNTAIN REALM BOSS =========================================\n" << endl;
    
    displayWeaponStats (_weapon);  //displays weapon type
    cout << endl;
    
    do
    {   genericMenu ("Choose a your choice: ", options, 2, userChoice, "Invalid Response"); //Generic Menu. Provides choices for end-user to battle with.
        
        bossFight (_enemy, _player, _weapon, userChoice); 
        
        //Change in player status 
        _player.energy -= 1;
        _player.stamina -= 2;

    }while(_player.health > 0 && _enemy.healthPoints > 0); //Only contiue looping the functions until it meets these requirements 
    
    return; 
}

//Map Choice Location 3 - Cave Route

//Beginning of Location 3 
int adventureCaveStart (int &userChoice)
{   string options [2] = {"I'll find something in the caves!", "I'll stay back to find one"}; //Options for end-user to choose from generic meu
    
    cout << "========================================= CAVE REALM ========================================\n" << endl; 
    cout << "Welcome to the caves! They're incredibly dark and spooky, so you better be prepared! I am not really joking, so ha, do you have everything... oh yeah you don't know what to do" << endl;
    cout << "Well the caves are quite daunting when you look at them for too long, so it's better to be safe. Do you want to dive right into the cave realm? If you have a weapon that's great!" << endl;
    cout << "If so, we can keep moving along, if not you better look! Here check your weapon stats if you have any. Either option you can go through the caves, but it's a little risky" << endl;

    genericMenu ("Want to continue into the caves?", options, 2, userChoice, "Invalid"); //Generic Menu. Provides choices for end-user with.

    return userChoice;
}

//Route 1 - Location 3
void outsideCave (Weapon &_weapon, Character &_player)
{   initializeWeapon (_weapon, "Lucky Hoe!", 20); //Initializes selected weapon
    
    cout << "You slowly walk out the cave entrence and lead yourself to the outskirts of the cave. You stumble across some materials to put them together to create a weapon of your choice!" << endl; 
    cout << "You have a stick, broken head of a hoe, and as shiny nickle!\nCube: Those materials are special OKAY!\nTake your time to build it!\n**Energy -5, Stamina -5**" << endl; 
    
    //Player Status Change
    _player.energy -= 5;
    _player.stamina -= 5;
    
    displayUserStatus (_player);
    
    cout << "Nice work! You created a lucky hoe!" << endl; 
    
    displayWeaponStats (_weapon); 
    
    cout << endl; 
    
    return; 
}

//Route 2 - Location 3
void insideCave (Weapon &_weapon, Character &_player)
{   initializeWeapon (_weapon, "Knife", 20); //Initializes selected weapon
    
    cout << "You enter the cave and stumble upon a knife! Wow lucky chance, it's attached to a skeleton - not so lucky - .You yank it off to reveal you huer your self in the process." << endl; 
    cout << "Sick Knife! It looks like you can do a lot of... ya know damage with hat. Try not to mess with it :)\n**Energy -5, Stamina -5**\n" << endl; 
    
    //Player Status Change
    _player.health -= 5;
    _player.energy -= 5;
    
    displayUserStatus (_player);
    
    displayWeaponStats (_weapon); 
    
    cout << endl; 
    
    return; 
}

//Location 3 - Final Battle 
void caveFinalBattle(Enemy &_enemy, Character &_player, Weapon &_weapon,  int &userChoice)
{
    string options [2] = {"Slash", "Chop"};//Options to select using generic menu
    
    initializeEnemy (_enemy, "Zoobat", 120, 15); //Intializes Enemy Into Function 
    initializeCharacter (_player, 150, 75, 60); //Initalizes Player Back to Original Health 
    
    //Introduction to Battle Prompt 
    cout << "You enter the cave and are ready for what is going to come at you. Get ready! **cLuNKKKK**. Well that doesn't sound pleasent. I give you the bestest of luck." << endl;
    cout << "Well isn't that fun, you bumped into the a monster... Isn't your luck amazing! Ha. ha. I am really just joking... Don't sweat it, you're in the dark...spoooopy." << endl; 
    cout << "Geo Boss: *cLunK* Who goes there!?!\n Welp... traveller good luck! I'll heal you first, so it's a fair fight :)\n =====MAX REVIVE=====" << endl;

    cout << "========================================= CAVE REALM BOSS =========================================\n" << endl;
    
    displayWeaponStats (_weapon);  //displays weapon type
    cout << endl;
    
    do
    {   genericMenu ("Choose a move: ", options, 2, userChoice, "Invalid Response"); //Generic Menu. Provides choices for end-user to battle with. 
        
        bossFight (_enemy, _player, _weapon, userChoice); //Calling Boss Fight Function 
        
        //Change in player status 
        _player.energy -= 2;
        _player.stamina -= 2;

    }while(_player.health > 0 && _enemy.healthPoints > 0); //Only contiue looping the functions until it meets these requirements 

    return; 
}

//Automatic Ending
void adventureEnd (Character &_player)
{
    cout << "Here are your final stats" << endl;
    displayUserStatus (_player); //Final game status  
    cout << "=====================GAME OVER===================" << endl;

    return;
}

int main ()
{   //Declaring Variables 
    srand(time(NULL)); //used for the Randomize variable
    
    int userChoice = 0;
    int adventureStart = 0;
    
    Character player; //Structures (structures are intialized within functions, depending on with location you take, there is a intialized enemy, weapon, or player stats avalible)
    Enemy targetEnemy;
    Weapon weapon;

    initializeCharacter (player, 150, 75, 60); //Beginning Stats for Player (Others are intialized depending on path)

    adventureStart = startGame (userChoice); //Option to Start Game

    //Using Nested if structure to represent decisions being made + do while loop so end-user can go back to map and select a new world
    
    if (userChoice == 1) //Starts the game, allows user to begin adventure
    {
        do
        {   mapLocationSelection (userChoice); //Selection Map Once you start and finish a location (All user stats carry over to following worlds if you loop)

            if (userChoice == 1) // OCEAN LOCATION START
            {   adventureOceanStart (userChoice); 

                if (userChoice = 1)
                {   
                    oceanSandPath (player); //Route original
                    oceanRouteContd (userChoice);
                    
                    if (userChoice == 1)
                    {   
                        oceanSpearOption (weapon); //Route one
                        oceanFinalBattle (targetEnemy, player, weapon, userChoice); //Route One Boss Fight
                    }
                    else if (userChoice == 2)
                    {   
                        oceanAxeOption (weapon); //Route two
                        oceanFinalBattle (targetEnemy, player, weapon, userChoice); //Route two Boss Fight
                    }
                }
                else if (userChoice == 2)
                {   
                    oceanGravelPath (player); //Route alternate
                    oceanRouteContd (userChoice); 
                    
                    if (userChoice == 1)
                    {   
                        oceanSpearOption (weapon);//Route one alternate
                        oceanFinalBattle (targetEnemy, player, weapon, userChoice);//Route One Boss Fight
                    }
                    else if (userChoice == 2)
                    {   
                        oceanAxeOption (weapon);//Route two alternate
                        oceanFinalBattle (targetEnemy, player, weapon, userChoice);//Route two Boss Fight
                    }
                }
            }
            else if (userChoice == 2) // MOUNTAIN LOCATION START
            {   adventureMountainStart (userChoice); 
                if (userChoice == 1)
                {
                    slugMoutainBattle (weapon, targetEnemy, player, userChoice); //Route one
                    mountainFinalBattle (targetEnemy, player, weapon, userChoice); //Route One Boss Fight
                }
                else if (userChoice == 2)
                {   climbMountain (weapon, player, userChoice);
                    mountainFinalBattle (targetEnemy, player, weapon, userChoice); //Route two Boss Fight
                }
            }
            else if (userChoice == 3) // CAVE LOCATION START
            {   adventureCaveStart (userChoice); 
                if (userChoice = 1)
                {   insideCave (weapon, player);//Route one
                    caveFinalBattle (targetEnemy, player, weapon, userChoice); //Route One Boss Fight
                }
                else if (userChoice == 2)
                {   outsideCave (weapon, player);//Route two
                    caveFinalBattle (targetEnemy, player, weapon, userChoice); //Route two Boss Fight
                }
            }
            else if (userChoice == 4) //Only source of completing the game, either than dying is leaving the world!
            {   adventureEnd (player);
            }

        }while (player.health > 0 && userChoice != 4);
        
    }
    else if (userChoice == 2) // When the user wants to leave the title screen and not go on a journey
    {
        cout << "Well see you later traveller!" << endl; //Good Bye Prompt
    }
    
    return 0;
}

