#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include <chrono>

using namespace std;

void SlowPrint(string text){
    for(char c : text){
        cout<<c<<flush;
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    cout<<endl;
}


struct Player {

string name;
string characterClass;
    int gold=10;
    int honor=50;
    int health=100;
    int level=1;
    int experience=0;
    int aleTolerance=10;
    int dragonCourage=10;
    int royalFavour=10;
    int luck=10;
    vector<string>inventory;
};

struct Scene{
    string description;
    vector<pair<string, string>> choices;
    int goldChange=0;
    int honorChange=0;
};

class Game{
    
    private: 
    Player player;
    map<string , Scene> world;
    string CurrentSceneID;
    
    public:
    
    void ChooseCharacter(){
        int choice;
        cout<<"\n======================================================"<<endl;
        cout<<"                CHOOSE  YOUR  CHARACTER                 "<<endl;
        cout<<"  ======================================================"<<endl;
        cout<<"1. Ser Cedric  (Honorable Knight)"<<endl;
        cout<<"  +20 Honor"<<endl;
        cout<<"   +10 Health\n"<<endl;
        
        cout<<"2. Lady Elara  (Rich NobleWoman)"<<endl;
        cout<<"  +20 Gold"<<endl;
        cout<<"   +10 Luck\n"<<endl;
        
        cout<<"3.  Prince Daemon(Dragon Rider)"<<endl;
        cout<<"  +20 Dragon Courage"<<endl;
        cout<<"   +10 Royal Favour\n"<<endl;
        
         cout<<"4.  The Drunk Knight"<<endl;
        cout<<"  +30 Ale Tolerance"<<endl;
        cout<<"   +10 Health\n"<<endl;
        
        cout<<"Enter Choice : ";
        cin>>choice;
        
        switch(choice){
            case 1 : 
            player.name = "Ser Cedric";
            player.characterClass = "Knight";
            player.honor += 20;
            player.health += 10;
            break;
            
            case 2 : 
            player.name = "Lay Elara";
            player.characterClass = "Noble";
            player.gold += 20;
            player.luck += 10;
            break;
            
            case 3 : 
            player.name = "Prince Daemon";
            player.characterClass = "Dragon Rider";
            player.dragonCourage += 20;
            player.royalFavour += 10;
            break;
            
            case 4 : 
            player.name = "The Drunk Knight";
            player.characterClass = "Warrior";
            player.aleTolerance += 30;
            player.health += 10;
            break;
            
            default:;
            
            cout<<"\nInvalid choice!"<<endl;
            cout<<"Ser Cedric has been selected.\n";
            player.name = "Ser Cedric";
            player.characterClass = "Knight";
            player.honor += 20;
            player.health += 10;
            
        }
        cout<<"\nCharacter Selected Successfully!\n";
    }
    
    
    void gainExperience(int xp){
        player.experience += xp;
        cout<<"\nYou gained  "<<xp<<"XP!"<<endl;
        while(player.experience>=player.level*100){
           player.experience -= player.level*100;
           player.level++;
           player.health += 20;
           player.honor += 5;
           cout<<"\n==============================================="<<endl;
           cout<<"                    LEVEL  UP!                   "<<endl;
           cout<<"You reached level"<<player.level<<"!"<<endl;
           cout<<"Health +20"<<endl;
           cout<<"Honor +5"<<endl;
           cout<<"================================================"<<endl;
        }
    };
    
    
    void takeDamage(int damage){
        player.health -= damage;
        if(player.health<0){
            player.health = 0;
            cout<<"\nYou lost"<<damage<<"Health!"<<endl; }
            if(player.health==0){
                cout<<"\n=============================================="<<endl;
                cout<<"                   YOU DIED!                   "<<endl;
                cout<<"The Seven Kingdoms will never know your name."<<endl;
                cout<<"============================================="<<endl;
                CurrentSceneID = "quit";
        
    }};
    
    
    void HealPlayer(int heal){
        player.health += heal;
        if(player.health>100){
            player.health=100;
            cout<<"\nYou recovered "<<heal<<"Health!"<<endl;        }
    };
    
    
    void AddItems(string item){
        player.inventory.push_back(item);
        cout<<"\nYou obtained: "<<item<<"!"<<endl;
    };
    
    
    void ShowInventory(){
      cout<<"\n================================================="<<endl;
      if(player.inventory.empty()){
          cout<<"Your inventory is empty."<<endl;
      } else{
          for(int i=0;i<player.inventory.size();i++){
              cout<<i+1<<". "<<player.inventory[i]<<endl;
          }
      }
      cout<<"==================================================="<<endl;
    };
    
    bool HasItem(string item){
        for(string x : player.inventory){
            if(x == item){
                return true;
            
        }}
        
            
         return false;
    };
    
    
    void InitGame(){
    world["start"] = {
   "You are at the tournament. The King's prized goose has escaped! The court will honor the person with a castle whosoever brings the goose back.",
            {{"Take the King's road","road"}, {"Chase the goose into the forest","bandits"}, {"Blame a rival knight","trial"}, {"Disguise as the goose","fail_state"}}
        };
        
     world["road"] = {
            "You ride through the King's road, your horse trips over a rock and you fall!",{{"Get back on the horse","forest"}}
        };
        
     world["trial"] = {
          "You blame the knight , but he has a better lawyer. The king isn't amused. You lose 5 gold for the trouble.",{{"Head to the forest to find the goose anyway","forest"}}  
        };
        
     world["bandits"] = {
            "As you chase the goose deepe into the forest, a group of bandits jumps out from the bushes with swords drawn!",{{"Fight the bandits","forest"},{"Run away","road"}}
        };
        
     world["forest"] = {
            "You enter the ancient forest.The King's goose is sitting behind a sleeping dragon.",
            {{"Approach the dragon","dragon_check"},{"Sneak towards the goose","steal_goose"}, {"Run away","start"}}
        };
        
        world["dragon_check"] = {
            "The dragon slowly opens one eye and stares directly at you..",{{"Continue","dragon_result"}}
        };
        
     world["dragon_talk"] = {
            "The dragon eyes your purse.'A measly 5 gold for my time?'",{{"Give the gold","success"},{"Try to wrestle the goose","fail_state"}}
        };
        
     world["dragon_friend"] = {
         "The dragon allows you to ride upon its back.Together you recover the King's goose.",{{"Fly to King's Landing","royal_reward"}}
     } ;  
       
     world["royal_reward"] = {
        "The King is amazed that you arrived riding a dragon.",{{"Accept the King's reward","quit"}} 
     } ;
     
     world["steal_goose"] = {
     "You quietly sneak toward the goose.",
      {{"Grab the goose","goose_escape"},{"Take treasure instead","dragon_angry"}}
      };
      
      world["goose_escape"] = {
      "The goose starts honking loudly!",
        {{"Run!","road"},{"Hide behind treasure","dragon_angry"}}
                  };
                  
     world["dragon_angry"] = {
      "The dragon wakes up furious!",{{"Fight","fight_dragon"},{"Beg for mercy","dragon_talk"}}
            }; 
            
     world["fight_dragon"] = {
     "The dragon towers above you.",{{"Attack with Valyrian Sword","dragon_win"},{"Attack bare-handed","fail_state"}}
         };
         
     world["dragon_win"]={
      "You slay the dragon using Valyrian Steel!",{{"Claim treasure","royal_reward"}}
       };
       
     world["secret_room"] = {
       "You discover an ancient Valyrian chamber beneath the dragon's cave.",{{"Open the chest","legend"},{"Leave","royal_reward"}}
    };
    
     world["legend"] = {
        "You become the greatest legend in Westeros.",{{"Finish","quit"}}
          };
     
     world["success"] = {
            "The dragon is impressed by your audacity! He returns the goose. You return to the capital a hero.",{{"Finish game","quit"}}
        };
        
     world["fail_state"] = {
            "You tried to disguise yourself or tried to wrestle a dragon. You are now lunch. Game over.",{{"Restart","start"}}
        };
        
     world["broke"] = {
            "The dragon spits fire when he sees your empty pockets. You have no gold and now , you have no eyebrows. Game over.",{{"Restart","start"}}
        };
        
        CurrentSceneID = "start";
    };
    
    
     void processChoice(int choiceIndex){
         Scene& s = world[CurrentSceneID];
         string nextID = s.choices[choiceIndex-1].second;
         
         if (CurrentSceneID == "start" && choiceIndex == 1){
        cout<<"\nYou sprinted! You feel more athletic. (+5 honour)"<<endl;
        player.honor+=5;
        gainExperience(20);
        AddItems("Wooden Sword");
        CurrentSceneID=nextID; }
        
        else if (CurrentSceneID == "trial"){
         player.gold-=5;
         gainExperience(10);
         CurrentSceneID = nextID; }
         
         else if(CurrentSceneID == "road"){
            takeDamage(15);
            gainExperience(10);
            
            CurrentSceneID = nextID;
        }
        
         else if (CurrentSceneID == "bandits"){
            if(choiceIndex == 1){
                cout<<"\nYou defeat the bandits after a fierce battle!"<<endl;
                takeDamage(20);
                player.gold += 15;
                AddItems("Valyrian Steel Sword");
                gainExperience(30);
                CurrentSceneID = nextID;}
                else{
            cout<<"\nYou escape safely but lose some honor."<<endl;
            player.honor -= 5;
            CurrentSceneID = nextID;
        }}
        
        else if(CurrentSceneID == "fight_dragon"){
            if (HasItem("Valyrian Steel Sword")){
                gainExperience(100);
                AddItems("Dragon_Crown");
                CurrentSceneID = "dragon_win";}
                else{
                    cout<<"You don't have a weapon capable of hurting a dragon."<<endl;
                    takeDamage(100);
                    CurrentSceneID = "fail_state";
                }
        }
         
        else if(CurrentSceneID == "forest" && choiceIndex == 1){
            if (player.gold>=5){
            player.gold-=5;
            AddItems("Dragon Glass");
            gainExperience(40);
            cout<<"\nYou pay the dragon 5 gold. He lets you pass!"<<endl;
            CurrentSceneID = "dragon_talk";}
         else{
            cout<<"\nYou reach into your pockets...empty! The dragon breathes fire."<<endl;
            if(HasItem("Dragon Shield")){
                cout<<"\nYour Dragon Shield protects you!"<<endl;
            } else{
            takeDamage(30);}
    CurrentSceneID = "broke";
             }}
             
        else if (nextID == "fail_state"){
            takeDamage(100);
            cout<<"\nFATAL MISTAKE! You are now lunch!"<<endl;
            CurrentSceneID = "fail_mistake";
        
            
            takeDamage(20);
            player.gold += 15;
            gainExperience(30);
            CurrentSceneID = nextID;
        }
        
        else if(CurrentSceneID=="dragon_check"){
            if(player.characterClass=="Dragon Rider"){
                cout<<"\nThe dragon smells ancient targareyen blood."<<endl;
                cout<<"A child of Old Valyria .. You may approach."<<endl;
                AddItems("Dragon Egg");
                gainExperience(80);
                CurrentSceneID="dragon_friend";
            } else{
                cout<<"\nThe dragon roars."<<endl;
                takeDamage(25);
                CurrentSceneID="dragon_talk";
            }}
            
        else if(CurrentSceneID=="road" && player.characterClass=="Noble"){
            cout<<"A merchant rewards your noble status."<<endl;
            player.gold += 20;
            AddItems("Golden Necklace");
            gainExperience(40);
            CurrentSceneID = nextID;
        }
        
       else if(CurrentSceneID=="bandits" && player.characterClass=="Warrior")
         {
            cout<<"You drink ale before battle!"<<endl;
       if(player.aleTolerance>=40)
      {
        cout<<"You become fearless and defeat every bandit!"<<endl;
         AddItems("Bandit Axe");
          gainExperience(60);
         player.gold+=30;
         CurrentSceneID="forest";
                 } }
                 
                 
        else if(CurrentSceneID=="trial" && player.characterClass=="Knight")
            {
          cout<<"The King respects your honor."<<endl;
           player.honor+=20;
         gainExperience(40);
         CurrentSceneID="forest";
}
        
        
        else{
            gainExperience(100);
            CurrentSceneID = nextID;
        }};


     void play(){
        while(CurrentSceneID != "quit"){
                Scene& s = world[CurrentSceneID];
                cout<< "\n----------------------------------------------\n";
                cout<<"=================================================="<<endl;
                cout<<"Character: "<<player.name<<endl;
                cout<<"Class: "<<player.characterClass<<endl;
                cout<<"Health: "<<player.health<<endl;
                cout<<"Gold: "<<player.gold<<endl; 
                cout<<"Honor: "<<player.honor<<endl;
                cout<<"Level: "<<player.level<<endl;
                cout<<"XP: "<<player.experience<<endl; 
                cout<<"Dragon Courage: "<<player.dragonCourage<<endl;
                cout<<"Ale Tolerance: "<<player.aleTolerance<<endl;
                cout<<"Royal Favour: "<<player.royalFavour<<endl;
                cout<<"Luck: "<<player.luck<<endl;
                cout<<"=================================================="<<endl;
               SlowPrint(s.description);
                
                for(int i=0;i<s.choices.size();i++){
                    cout<<i+1<<". "<<s.choices[i].first<<endl;
                    }
                    cout<<"0. Check Journal"<<endl;
      int input;
      cout<<"\n10. View Inventory"<<endl;
      cout<<"\nChoice: ";
      cin>>input;
      if(input==10){
          ShowInventory();
          continue;
      }
      if(input>0 && input<=s.choices.size()){
          processChoice(input);
      } else{
          cout<<"Invalid choice! You trip over your own feet"<<endl;
      }}};               };

    int main() {
        Game game;
        game.ChooseCharacter();
        game.InitGame();
        game.play();
        
   
    return 0;
}
