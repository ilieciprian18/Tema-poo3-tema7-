#include <iostream>
#include <cstring>
#include <tuple>
#include <typeinfo>
using namespace std;
class Film
{
protected :
    int incasari,durata;
    string nume,tip;    //am considerat tip actiune/drama
public :
    Film(string nume="",int incasari=0,int durata=0,string tip=""):nume(nume),tip(tip),incasari(incasari),durata(durata){}
    friend istream& operator>> (istream& in, Film & ob)
    {
        in>>ob.nume;
        in>>ob.tip;
        in>>ob.incasari;
        in>>ob.durata;
        return in;
    }
    friend ostream& operator<< (ostream& out,const Film& ob)
    {
        out<<"Numele filmului este "<<ob.nume<<" ,genul filmului este "<<ob.tip<<" durata este de "<<ob.durata<<" minute, iar incasarile totale sunt in valoare de " << ob.incasari<<" dolari"<<"\n";

        return out;
    }
    int getincasari(){return incasari;}
};
class Personal
{
protected :
    int CNP;
    string nume,nume_film;
public :
    Personal(int CNP=0,string nume="",string nume_film=""):CNP(CNP),nume(nume),nume_film(nume_film){}
    virtual int GetCNP(){return CNP;}
    virtual  string GetNume(){return nume;}
    virtual  string GetNume_film(){return nume_film;}
    virtual void Print(){cerr<<"Nu exista film"<<"\n";}
    ~Personal()
    {
       nume.resize(0);
       CNP=0;
       nume_film.resize(0);
    }
};
class Regizor : virtual public Personal
{
protected :
    int procent,suma_regizor;
public :
    Regizor(int CNP=0,string nume="",string nume_film="",int procent=0,int suma_regizor=0):Personal(CNP,nume,nume_film),procent(procent),suma_regizor(suma_regizor){}
    void Print()
    {
        cout<<"CNP: "<<GetCNP()<<" / Nume :"<<GetNume()<<" / Nume film :"<<GetNume_film()<<" / Suma fixa este de: "<<suma_regizor<<" / Procentul este de :"<<procent<<"%"<<endl;
    }
    friend istream& operator>> (istream& in, Regizor & ob)
    {
        in>>ob.CNP>>ob.nume>>ob.nume_film>>ob.procent>>ob.suma_regizor;
        return in;
    }
    Regizor(const Regizor &p2)
    {
        nume=p2.nume;
        CNP=p2.CNP;
        procent=p2.procent;
        suma_regizor=p2.suma_regizor;
        nume_film=p2.nume_film;
    }
    //primeste % din incasari

};
class Actor : public Personal
{
protected :
    bool rol;
    int procent_actor;
public :
    Actor(int CNP=0,string nume="",string nume_film="",bool rol=0,int procent_actor=0):Personal(CNP,nume,nume_film),rol(rol),procent_actor(procent_actor){}
    int getrol(){return rol;}
    void Print()
    {
        if(getrol() == 1)
            cout<<"Rol principal--> + 10% bonus ; ";
        else cout<<"Rol secundar; ";
        cout<<"CNP: "<<GetCNP()<<" / Nume :"<<GetNume()<<" / Nume film :"<<GetNume_film()<<" / Procentul este de :"<<procent_actor<<"\n";
    }
    friend istream& operator>> (istream& in, Actor & ob)
    {
         in>>ob.CNP>>ob.nume>>ob.nume_film>>ob.rol>>ob.procent_actor;
        return in;
    }
    //ia bonus daca este actor principal
};
class Staff : public Personal
{
protected :
    int procent_bani;
public :
    Staff(int CNP=0,string nume="",string nume_film="",int procent_bani=0):Personal(CNP,nume,nume_film),procent_bani(procent_bani){}
    void Print()
    {
        cout<<"CNP: "<<GetCNP()<<" / Nume :"<<GetNume()<<" / Nume film :"<<GetNume_film()<<" / Procentul este de :"<<procent_bani<<"\n";
    }
    friend istream& operator>> (istream& in, Staff & ob)
    {
         in>>ob.CNP>>ob.nume>>ob.nume_film>>ob.procent_bani;
        return in;
    }
};
//specializare actori
//template ca in model
template <class T,int n>
T nractori(T vector[])
{
    int nr=0;
    for(int i=0;i<n;i++)
        if(vector[i].getrol()==1)
        nr=nr+1;
    return nr;
}
template <class A, class B, class C>
class setu
{
private :
    A film;
    B personal;
    C procent;
public :
    setu(A x,B y,C z):film(x),personal(y),procent(z){}
};
using Set=setu<int,int,int>;
template <typename T>
class FirmaDistributie
{
protected :
    T *ptr;
    int size;
    int nrpers;
    int nractori;
    static const std::string name(){return typeid(T).name();}
public :
    FirmaDistributie(T arr[],int s);
};
template <typename T>
FirmaDistributie<T>::FirmaDistributie(T arr[],int s)
{
    ptr=new T[s];
    size=s;
    for(int i=0;i< size;i++)
        ptr[i]=arr[i];
}
int main()
{

    Film e[10];
    Regizor ee[10];
    Actor eee[10];
    Staff eeee[10];
    int i=0;
    int ii=0;
    int iii=0;
    int iiii=0;
    int menu=5;
    cout<<"Operatiunile valabile sunt:"<<endl;
    cout<<"- 1 Pentru a adauga un nou film"<<endl;
    cout<<"- 2 pentru a afisa lista de filme"<<endl;
    cout<<"- 3 pentru a adauga regizor" <<endl;
    cout<<"- 4 pentru a afisa lista de regizori"<<endl;
    cout<<"- 5 pentru a adauga actor" <<endl;
    cout<<"- 6 pentru a afisa lista de actor"<<endl;
    cout<<"- 7 pentru a adauga staff" <<endl;
    cout<<"- 8 pentru a afisa lista de staff"<<endl;
    cout<<"- 9 nr actori roluri principale"<<endl;
    cout<<"- 10 cel mai mare nr al incasarilor"<<endl;
    cout<<"- 0 pentru a inchide programul"<<endl;

    while (menu !=0)
    {
        cout<<"Alegeti o operatiune"<<endl;
        cin>>menu;
        if(menu == 1 )
        {
            cout<<"Introduceti in ordine : Numele(char),tipul(char),incasarile(int),durata(int)"<<endl;
            cin>>e[i];
            i=i+1;
        }
        if(menu == 2 )
        {
            if(i==0)
                cout<<"Nu exista filme in lista"<<endl;
            cout<<"Numarul de filme este: "<<i<<endl;
            for(int j=0;j<i;j++)
                cout<<e[j];
        }
         if(menu == 3 )
        {
            cout<<"Introduceti in ordine : CNP(int),nume(char),nume film(char),procent(int),prima(int)"<<endl;
            cin>>ee[ii];
            ii=ii+1;
        }
        if(menu == 4 )
        {
            cout<<"Nu exista regizori in lista"<<endl;
            for(int o=0;o<ii;o++)
                ee[o].Print();
        }
         if(menu == 5 )
        {
            cout<<"Introduceti in ordine : CNP(int),nume(char),nume film(char),rol(bool),procent(int)"<<endl;
            cin>>eee[iii];
            iii=iii+1;
        }
        if(menu == 6 )
        {
            cout<<"Nu exista filme in actori"<<endl;
            for(int o=0;o<iii;o++)
                eee[o].Print();
        }
        if(menu == 7 )
        {
            cout<<"Introduceti in ordine : CNP(int),nume(char),nume film(char),proct(int)"<<endl;
            cin>>eeee[iiii];
            iiii=iiii+1;
        }
        if(menu == 8 )
        {
            cout<<"Nu exista staff in lista"<<endl;
            for(int o=0;o<iiii;o++)
                eeee[o].Print();
        }
        if (menu == 9 )
        {
            int nra=0;
            for(int j=0;j<iii;j++)
                if(eee[j].getrol()==1)
                nra++;
            cout<<nra<<endl;


        }
        if ( menu == 10)
        {
            int maxi=0;
            for(int j=0;j<i;j++)
                if(e[j].getincasari()>maxi)
                maxi=e[j].getincasari();
            for(int j=0;j<i;j++)
                if(e[j].getincasari()==maxi)
            {
                cout<<e[j];
            }
            cout<<"Incasari maxime = "<<maxi<<endl;

        }
    }

    //Film d2,d3;
    //cin>>d2;
    //cin>>d3;
    //cout<<d2<<d3;
    //------------
    //Regizor r1;
//cin>>r1;
    //cin>>r2;
    //r1.Print();
    //r2.Print();
    //-----------
    //cout<<r1.GetCNP();



    return 0;
}
