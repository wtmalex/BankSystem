/*
    Autor:  Alex Attila Wittmann
    MatrNr: 1326430
*/
#include <vector>
#define filename "datenbank.txt"

class Konto
{
public:
    enum Bonus {NORMAL, SILBER, GOLD, PLATIN};
    Konto();
    Konto(int, const char *, int);
    ~Konto();
    void zeige();                       // cout << Object
    void aendern_name();
    void aendern_stand_pos(int paramEUR = 0, int paramCent = 0);        //default arguments
    void aendern_stand_neg(int paramEUR = 0, int paramCent = 0);
    void geldwechsel();
    void aendern_bonus();
    int get_kontonummer();              // brauche getters/setters fuer read/write
    char* get_kontoname();
    int get_kontostand();
    Bonus get_kontobonus();
    void set_kontonummer(int);
    void set_kontoname(char*);
    void set_kontostand(int);
    void set_kontobonus(Bonus);

    static int kontoanzahle;



private:

    int kontonummer;
    char kontoname[50];
    int kontostand; //1 euro = 100, 1 cent = 1
    Bonus kontobonus;

    const char *bonusstrings[4] =
    {
        "NORMAL", "SILBER", "GOLD", "PLATIN"
    };
};

void my_write(std::vector<Konto*>&);
void my_read(std::vector<Konto*>&, std::vector<int>&);
