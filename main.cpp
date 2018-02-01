#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;
class Player;
class Monster;
//class Item;
class Skill;

bool startGame();
Player createPlayer();

class Player
{
	int stamina; int attack_strength; int defense; int intelligence; int luck;
	int health; int mana;
	int wealth;
	
	string name; string title;
	
	//vector<Item> inventory; vector<Item> equipment;
	vector<Skill> skill_list;
	
	public:
		Player(string name, string title, int stamina, int attack_strength, int defense, int intelligence,
		int luck, int health, int mana, int wealth, vector<Skill>skill_list): name(name), title(title), stamina(stamina), attack_strength(attack_strength),
		defense(defense), intelligence(intelligence), luck(luck), health(health), mana(mana), wealth(wealth), skill_list(skill_list) {}
		
		void saveGame();
		friend pair<bool, int> dungeonCrawl(Player player);
		void playerAttacks(Monster &bad);
		void useSkill(Skill &s, Monster &bad);
		//void setTitle();
};

class Monster
{
	string name;
	int health;
	int attack;
	int gold;
	
	public:
		Monster() : name("Koop"), health(60), attack(1), gold(10){}
		Monster(string name, int health, int attack, int gold) : name(name), health(health), attack(attack), gold(gold){}
		friend void Player::playerAttacks(Monster &mon);
		friend pair<bool, int> dungeonCrawl(Player player);
		void setHealth(int val);
		friend void Player::useSkill(Skill &s, Monster &m);
		//Item drop_item();
};

 class Skill
{
	string description;
	bool self;
	int impact;
	int mana_cost;
	
	public:
		Skill(string description, int impact, int mana_cost, bool self): description(description), impact(impact), mana_cost(mana_cost), self(self){}
		friend ostream &operator<<(ostream &os, Skill &s);
		friend void Player::useSkill(Skill &s, Monster &m); 
		friend ostream &operator<<(ostream &os, vector<Skill> &v);
};
//define Player methods
void Player::playerAttacks(Monster &bad)
{
	this->health-=bad.attack;
	bad.health-=this->attack_strength;
}
void Player::useSkill(Skill &s, Monster &m)
{
	if (this->mana<s.mana_cost && s.self==true)
	{
		cout<<"You bide your time, resting up!"<<endl;
		this->mana+=1;
	}
	else if (this->mana<s.mana_cost)
	{
		cout<<"You do not have enough mana!"<<endl;
	}
	else if (s.self)
	{
		if (this->health+s.impact<100 && this->mana+s.impact<100)
		{
			this->health+=s.impact;
			this->mana+=s.impact;
			this->mana-=s.mana_cost;
		}
		else if (this->health+s.impact<100)
		{
			this->health+=s.impact;
			this->mana-=s.mana_cost;
		}
		else if (this->mana+s.impact<100)
		{
			this->mana+=s.impact;
			this->mana-=s.mana_cost;
		}
		else if (this->health!=100 && this->mana!=100)
		{
			this->health=100;
			this->mana=100;
			this->mana-=s.mana_cost;
		}
		else
		{
			cout<<"You have full health."<<endl;
		}
	}
	else
	{
		m.health-=s.impact;
		this->mana-=s.mana_cost;
	}
	this->health-=m.attack;
}	
//define Monster methods
void Monster::setHealth(int val)
{
	this->health=val;
}


//define Skill methods
ostream &operator<<(ostream &os, vector<Skill> &v)
{
	for (auto skill:v)
	{
		os<<skill.description<<" "<<skill.self<<' '<<skill.impact<<" "<<skill.mana_cost<<" ";
	}
	return os;
}
ostream &operator<<(ostream &os, Skill &s)
{
	if (s.self)
	{
		os<<s.description<<": "<< "Amount:"<<s.impact<<" "<< "Mana Cost:"<<s.mana_cost<<endl;
	}
	else
	{
		os<<s.description<<": "<< "Damage:"<<s.impact<<" "<< "Mana Cost:"<<s.mana_cost<<endl;
	}
	return os;
}

//define Main methods
bool startGame()
{
	cout<<"Hello. Welcome to the world of Dungeon Crawlers."<<endl;
	cout<<"Press enter to begin, or exit to quit."<<endl;
	string input;
	getline(cin, input);
	while (input.compare("")!=0 & input.compare("exit") !=0)
	{
		cout<<"Press enter to begin, or exit to quit."<<endl;
		cin>>input;
	}
	if (input.compare("")==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool loadGame()
{
	cout<<"1.) Load Game"<<endl;
	cout<<"2.) New Game"<<endl;
	int loadOrNew;
	string loadOrNewHandlerString;
	getline(cin, loadOrNewHandlerString);
	const char *ted = loadOrNewHandlerString.c_str();
	loadOrNew=(int)*ted-'0';
	//fstream text;
	//text.open("save.txt");
	if (loadOrNew==1)
	{
		//text.close();
		return true;
	}
	/* else if (loadOrNew==1)
	{
		cout<<"Could not load save file."<<endl;
		return false;
	} */
	else
	{
		return false;
	}
}

Player loadPlayer()
{
	ifstream text;
	text.open("save.txt");
	int stamina; int attack_strength; int defense; int intelligence; int luck;
	int health; int mana;
	int wealth;
	string name; string title;
	vector<Skill> skill_list;
	text>>name;text>>title;text>>stamina;text>>attack_strength;text>>defense;text>>intelligence;text>>luck;text>>health;text>>mana;text>>wealth;
	
	string s11; bool s1b; int s12; int s13;
	string s21; bool s2b; int s22; int s23;
	string s31; bool s3b; int s32; int s33;
	
	text>>s11;text>>s1b;text>>s12;text>>s13;
	text>>s21;text>>s2b;text>>s22;text>>s23;
	text>>s31;text>>s3b;text>>s32;text>>s33;
	
	Skill one=Skill(s11, s12, s13, s1b);
	Skill two=Skill(s21, s22, s23,s2b);
	Skill three=Skill(s31, s32, s33, s3b);
	skill_list.push_back(one);
	skill_list.push_back(two);
	skill_list.push_back(three);
	//string x;
	
	/* while(getline(text,x))
	{
		cout<<x;
	} */
	text.close();
	//cout<<name<<endl;
	//cout<<title<<endl;
	return Player(name, title,stamina,attack_strength,defense,intelligence,luck,health, mana, wealth, skill_list);
}

int choose_class()
{
	cout<<"Choose a class:"<<endl<< "1.)Warrior"<<endl<<"2.)Knight"<<endl<<"3.)BattleMage"<<endl<<"4.)Wizard"<<endl<<"5.)Hero"<<endl;
	int choice;
	string choice_handler;
	getline(cin,choice_handler);
	const char *cstr = choice_handler.c_str();
	choice=(int)*cstr-'0';
	return choice;
}

void Player::saveGame()
{
	ofstream text;
	text.open ("save.txt");
	text<< this->name<<' '<< this->title<<' '<< this->stamina<<' '<< this->attack_strength<<' '<< this->defense<<' '<< this->intelligence<<' '<< this->luck<<' '<< this->health<<' '<< this->mana<<' '<<this->wealth<<" ";
	text<<this->skill_list;
	text.close();
}
Player createPlayer()
{
	cout<<"What is your name?"<<endl;
	cout<<endl;
	string name;
	getline(cin, name);
	cout<<"Hello, "<<name<<". We have been waiting for you."<<endl;
	int choice=0;
	vector<Skill> programmedSkills;
	while (choice<1 || choice>5)
	{
		choice=choose_class();
		if (choice==1)
		{
			Skill rest_W=Skill("Rest", 20, 10, true);
			Skill cleave=Skill("Cleave", 50, 20, false);
			Skill rush_W=Skill("Sword Rush", 20, 10, false);
			programmedSkills.push_back(rest_W);
			programmedSkills.push_back(cleave);
			programmedSkills.push_back(rush_W);
			cout<<"I see. You are "<<name<<" the warrior. Good luck!"<<endl;
			return Player(name, "Warrior", 10, 10, 5, 5, 3, 100, 50, 0, programmedSkills);
		}
		else if(choice==2)
		{
			//vector<Skill> programmedSkills;
			Skill rest_K=Skill("Rest", 20, 10, true);
			Skill shield=Skill("Shield Bash", 50, 20, false);
			Skill rush=Skill("Charge", 20, 10, false);
			programmedSkills.push_back(rest_K);
			programmedSkills.push_back(shield);
			programmedSkills.push_back(rush);
			cout<<"I see. You are "<<name<<" the knight. Good luck!"<<endl;
			return Player(name, "Knight", 10, 5, 10, 5, 3, 100, 50, 0, programmedSkills);
		}
		else if(choice==3)
		{
			//vector<Skill> programmedSkills;
			Skill heal_BM=Skill("Heal", 30, 10, true);
			Skill fire=Skill("Fireball", 50, 20, false);
			Skill thunder=Skill("Thunderbolt", 20, 10, false);
			programmedSkills.push_back(heal_BM);
			programmedSkills.push_back(fire);
			programmedSkills.push_back(thunder);
			cout<<"I see. You are "<<name<<" the battlemage. Good luck!"<<endl;
			return Player(name, "BattleMage", 5, 10, 5, 10, 3, 50, 100, 0, programmedSkills);
		}
		else if(choice==4)
		{
			//vector<Skill> programmedSkills;
			Skill heal_Wiz=Skill("Heal", 50, 10, true);
			Skill freeze=Skill("Blizzard", 60, 20, false);
			Skill wind=Skill("Air Blade", 30, 10, false);
			programmedSkills.push_back(heal_Wiz);
			programmedSkills.push_back(freeze);
			programmedSkills.push_back(wind);
			cout<<"I see. You are "<<name<<" the wizard. Good luck!"<<endl;
			return Player(name, "Wizard", 5, 5, 10, 10, 3, 50, 100, 0, programmedSkills);
		}
		else if(choice==5)
		{
			//vector<Skill> programmedSkills;
			Skill heal_H=Skill("Heal", 50, 10, true);
			Skill bellow=Skill("Hero's Roar", 20, 1, false);
			Skill god=Skill("Hero's Smite", 100000, 60, false);
			programmedSkills.push_back(heal_H);
			programmedSkills.push_back(bellow);
			programmedSkills.push_back(god);
			cout<<"I see. You are "<<name<<" the Hero. Good luck!"<<endl;
			return Player(name, "Hero", 7, 7, 7, 7, 15, 50, 50, 0, programmedSkills);
		}
		else
		{
			cout<<"Try again."<<endl;
			
		}
	}
}

pair<bool, int> dungeonCrawl(Player player)
{
	while (player.health>0)
	{
		cout<<endl<<"You encountered an enemy!"<<endl;
		Monster enemy=Monster();
		while (enemy.health>0)
		{
			if (player.health<=0)
			{
				return (make_pair(true, player.wealth));
			}
			cout<<endl;
			cout<<"\t"<<player.name<<"\t\t\t\t\t"<<enemy.name<<"!"<<endl;
			cout<<"\t"<<"HP:"<<player.health<<"\t\t\t\t"<<"Monster HP:"<<enemy.health<<endl;
			cout<<"\t"<<"Mana:"<<player.mana<<endl;
			cout<<"\t"<<"Score:"<<player.wealth<<endl<<endl;
			cout<<"-------------------------------------------------------"<<endl;
			cout<<"1.)Attack \t 2.)Skills \t 3.)Save Game \t 4.)Run"<<endl;
			cout<<"-------------------------------------------------------"<<endl;
			int option;
			char option_handler;
			cin>>option_handler;
			option=(int)option_handler-'0';
			int i=1;
			if (option==1)
				player.playerAttacks(enemy);
			else if (option==2)
			{
				for (auto skill:player.skill_list)
				{	
					cout<<i<<".)"<<skill;
					i=i+1;
				}
				cout<<"4.)Back"<<endl;
				int spell;
				char spell_handler;
				cin>>spell_handler;
				spell=(int)spell_handler-'0';
				if (spell==1)
				{
					player.useSkill(player.skill_list[0],enemy);
				}
				else if (spell==2)
				{
					player.useSkill(player.skill_list[1],enemy);
				}
				else if (spell==3)
				{
					player.useSkill(player.skill_list[2],enemy);
				}
				else if (spell!=4)
				{
					cout<<"Invalid command"<<endl;
				}
				i=1;
			}
			else if (option==3)
			{
				player.saveGame();
				cout<<"Game saved"<<endl;
			}
			else if (option==4)
			{
				cout<<"You escaped!"<<endl;
				return make_pair(false,0);
			}
			else
			{
				cout<<"Sorry, that didn't make sense."<<endl;
			}
			if (enemy.health<=0)
			{
				player.wealth+=enemy.gold;
			}
		}
	}
	return make_pair(true, player.wealth);
}

int main()
{
	if (startGame())
	{
		if (loadGame())
		{
			Player savedProtag=loadPlayer();
			pair<bool, int> results;
			results= dungeonCrawl(savedProtag);
			if (results.first)
			{
				cout<<"You fell to the monster swarm! Thanks for playing!"<<endl;
				cout<<"Final Score: "<<results.second;
			}
			return 0;
		}
		else
		{
			Player protag=createPlayer();
			pair<bool, int> results;
			results= dungeonCrawl(protag);
			if (results.first)
			{
				cout<<"You fell to the monster swarm! Thanks for playing!"<<endl;
				cout<<"Final Score: "<<results.second;
			}
			return 0;
		}
	}
	else
	{
		return 0;
	}
}	