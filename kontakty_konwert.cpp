#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


using namespace std;

class Kontakt
{
    public:
    string beg_;
    string ver;
    string n;
    string fn;
    string telc;
    string org;
    string end_;
    string other;


    void t_choose(string tt)
    {
        string tag[8]; int fin=0;

        tag[0]="BEGIN:";
        tag[1]="VERSION:";
        tag[2]="N:";
        tag[3]="FN:";
        tag[4]="TEL;CELL:";
        tag[5]="ORG:";
        tag[6]="END:";
        tag[7]="other info";

        if (t_analiz(tt, tag[0]) != "")     {beg_  = t_analiz(tt, tag[0]); fin=1;}
        if (t_analiz(tt, tag[1]) != "")     {ver   = t_analiz(tt, tag[1]); fin=1;}
        if (t_analiz(tt, tag[2]) != "")     {n     = t_analiz(tt, tag[2]); fin=1;}
        if (t_analiz(tt, tag[3]) != "")     {fn    = t_analiz(tt, tag[3]); fin=1;}
        if (t_analiz(tt, tag[4]) != "")     {telc  = t_analiz(tt, tag[4]); fin=1;}
        if (t_analiz(tt, tag[5]) != "")     {org   = t_analiz(tt, tag[5]); fin=1;}
        if (t_analiz(tt, tag[6]) != "")     {end_  = t_analiz(tt, tag[6]); fin=1;}
        if (fin==0) other = tt;
    }

    string t_analiz(string lt, string intr_t)
    {
        int intr_le = intr_t.length();

        if (lt.substr(0,intr_le) == intr_t)
        {
            lt.erase(0,intr_le);
            return lt;
        }
        else return "";

    }

    string write_line() //merge contact data to one line (skleja dane kontaktu w jeden wiersz)
    {
        string line_out;
        line_out =
        beg_
        + "|" +
        "'" + ver
        + "| " +
        n
        + "|" +
        fn
        + "|" +
        "'" + telc
        + "|" +
        org
        + "|" +
        end_
        + "|" +
        other;

        return line_out;
    }

    void del_kont() //usuwa stare dane
    {
        this-> beg_ = '\0';
        this-> ver = '\0';
        this-> n = '\0';
        this-> fn = '\0';
        this-> telc = '\0';
        this-> org = '\0';
        this-> end_ = '\0';
        this-> other = '\0';
    }
};

string first_line()
{
        string tag[8];

        tag[0]="BEGIN:";
        tag[1]="VERSION:";
        tag[2]="N:";
        tag[3]="FN:";
        tag[4]="TEL;CELL:";
        tag[5]="ORG:";
        tag[6]="END:";
        tag[7]="other info";

    string ttt = tag[0];
    for(int i=1; i<=7; i++)
    {
        ttt = ttt + "|" + tag[i];
    }

    return ttt;
}


int main()
{
    string linn, f_in, f_out;
    fstream ff_in, ff_out;
    int kn=0, endend=0;

    cout << "podaj nazwe pliku kontaktów (*.vcf): ";
    cin >> f_in;
    f_in = f_in + ".vcf";

    cout << "podaj nazwe pliku wyjsciowego (*.txt): ";
    cin >> f_out;
    f_out = f_out + ".txt";

    cout << '\n';

    //liczymy iloœæ wierszy pliku
    ff_in.open(f_in.c_str(), ios::in);
    while(getline(ff_in, linn, '\n'))
    {
        endend++;
    }
    ff_in.close();


    ff_in.open(f_in.c_str(), ios::in);

    //sprawdzamy czy plik wejœciowy istnieje
    if (ff_in.good()==false)
    {
        cout << "nie znaleziono pliku ";
        system("pause");
        exit(0);
    }

    ff_out.open(f_out.c_str(), ios::out);

    Kontakt *item = new Kontakt;

    cout << first_line() << '\n';
    ff_out << first_line() << '\n';

    while(kn<endend)
    {
        do
        {
            getline(ff_in, linn, '\n');   // read one line in input file (odczytujê jedn¹ liniê w pliku wejœciowym)
            (*item).t_choose(linn);       //funkcja wybierz-liniê przydziela odczytan¹ treœæ z linii do konkretnej kolumny
            kn++;
        } while(linn.substr(0,3) != "END");

        cout << (*item).write_line() << '\n';
        ff_out << (*item).write_line() << '\n';
        (*item).del_kont();
//        system("pause");
    }

    ff_in.close();
    ff_out.close();

    delete item;

    cout << '\n' << "KONIEC ";

    system("pause");
    return 0;
}
