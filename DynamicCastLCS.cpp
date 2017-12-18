#include <bits/stdc++.h>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <deque>
#include <vector>
#include <map>
#include <exception>
#include <stdexcept>
using namespace std;



#define LINE_LEN (200)
#define INVALID_NODE (-1)

typedef unsigned long u32_t;
typedef long s32_t;

class Spell {
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell {
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell {
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell {
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
};
string SpellJournal::journal = "";

std::ifstream fin("input");
void counterspell(Spell *spell) {
/*
    if (Fireball *pSpell = dynamic_cast<Fireball *>(spell))
    {
        cout << "base is casted to be derived" << endl;
    }
	else
	{
		cout << "base cannot be casted to be derived" << endl;
		assert(0);
	}
*/
    /* Enter your code here */
	unsigned int uMax = 0;
    if (Fireball *pSpell = dynamic_cast<Fireball *>(spell))
    {
    	pSpell -> revealFirepower();
    }
    else if (Frostbite *pSpell = dynamic_cast<Frostbite *>(spell))
    {
    	pSpell -> revealFrostpower();
    }
    else if (Thunderstorm *pSpell = dynamic_cast<Thunderstorm *>(spell))
    {
    	pSpell -> revealThunderpower();
    }
    else if (Waterbolt *pSpell = dynamic_cast<Waterbolt *>(spell))
    {
    	pSpell -> revealWaterpower();
    }
    else if (Spell *pSpell = dynamic_cast<Spell *>(spell))
    {
    	string genericScrollName = pSpell -> revealScrollName();
    	unsigned int uMatch = 0;
    	size_t uSearch = genericScrollName.find_first_of(SpellJournal::read());
    	while (uSearch != string::npos)
    	{
    		uMatch++;
    		uSearch = genericScrollName.find_first_of(SpellJournal::read(), uSearch+1);
    	}

    	if (uMax < uMatch)
    	{
    		uMax = uMatch;
    	}
    	cout << uMax << endl;
    }
    else
    {
        cout << "not spell" << endl;
    }
}

class Wizard {
    public:

        Spell *cast() {
            Spell *spell;
            string s; fin >> s;
            int power; fin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            }
            else {
                spell = new Spell(s);
                fin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    fin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}
