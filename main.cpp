/*Ertugrul Bilgic -402545
Hudahan Altun -394753
Irmak Silay Kara -402496
 */

//kod özet
/*
 * Neler yapabiliyor Neler Yapamıyor
 *
 * 1)takım adları ve teknik direktör adları takimlar.txt'den okunuyor lig başlamadan önce takım eklenecek mi diye soruyoruz
 * ama sebepsiz bir kod atlama yapıyor. txt dosyadan okunan takım adları içinde spor kelimesinin geçip geçmemesine göre kendine has bir
 * kısaltma üretiyor
 *
 * 2)Oyuncular txtden gelen isim ve soy isimlerle rastgele üretiliyor olup yaş ortalamaları ve performansları
 * yazmış olduğumuz Doubly Linked list sayesinde olabilecek en optimize yolla [25,32] ve [60,100] sınırı içinde yer alıyor
 *
 * 3)Fikstür algoritması internet üzerinden yapılan araştırmada algoritmayı öğrenmiş olup c++ kodlarına aktardık bu sayede
 * 18 takımlı bir ligde bir takım 9 maçta 1 maç yapıp hiçbir maç bir diğerinin aynısı olmamakta ve bu maçların kendine has 1001'den başlayan
 * id'leri bulunmakta
 *
 * 4)ID'si bilinen bir maç oynanmadığında ayrı oynandığında ayrı bir bilgi tablosu göstermekte oynanmamış bir maçın oranları
 * isimleri takım adları yazmaktadır
 *
 * 5)takım classına ait objeler set fonksiyonlarının kopyaları setlemesinden kaynaklı değişmemekte fakat bundan kaynaklı oynanan maç
 * takımlara etki etmyor ve dolaylı yoldan lig tablosu tam çalışmıyor.
 *
 * 6)Maç verilen standartta oynanarak maç üstünde tutuluyor
 *
 * 7)main kod tamı tamına 4 satır olup fonkiyonların recusive zincirleme çağrılması ile moduler programlama sağlandı.
 * hatta stringler const static olarak tanımlanarak yazı tekrarı engellendi
 *
 * 8)OOP prensiplerinden comprehension tüm classlarda kullanılmış olup:
 *
 * lig maçlardan ve takımlardan,
 * maçlar takımlardan,
 * takımlar Doubly Linked listlerden,
 * doubly linked list ise player'ladan oluşmaktadır.
 *
 * ayrıca encapsulation yüksek mertebede kullanılıp neredeyse her özelliğe ulaşmak için getter ve setter fonksiyon kullanımı gerekmektedir.
 * inheritance playerlar için forvet, ortasaha, ve defans subclasslarına ayrılmak istenmiş fakat linked list'in override'ı zorladığı için
 * vazgeçilmiştir. Polymorphism kullanılma fırsatı bulunamammıştır.
 *
 * */

#include <vector>
#include <iostream>
#include <string>
#include<sstream>
#include<fstream>
#include <random>
#include<time.h>

using namespace std;

#pragma region Texts
class Texts {

public:
    static const string greetings;
    static const string logo;
    static const string credits;
    static const string teamFileInputWarning;
    static const string nameFileInputWarning;
    static const string fileInputError;
    static const string menuInfo;
    static const string wrongButtonPushError;
    static const string formations;
    static const string teamValueChaning;
    static const string playerValueChanging;


    static const string profilePic;
    static void println(const string& s);

};

string const Texts::greetings = "Uygulamaya Hos Geldiniz\n";

string const Texts:: logo = R"(
           %%%%% %%%  %% %%%%%
       %%%%%%%. %%%%%%%%% %% %%%%%
     %%%%%%%%%#           %%%%   %%%
   %%% % %%   &&&&&&&&&&&&&   %%%%%%%%
  %% %%%%  &&&&&&&     &&&&&&&  %%% %%%
 %%%%%%% &&&&&             &&&&& %%% %%%
 %%% %%  &&&&               &&&&  %%%%%%
%%%  %% &&&&    &&&   &&&    &&&& %%,%%%
 %% %%%  &&&&   &&&   &&&   &&&&  % % %%
 %%%%%%% &&&&&  &&&   &&&  &&&&& %   %%%
  %%%%%%%  &&&&&&&&   &&&&&&&&  % %%%%%
   %%%   %%   &&&&&   &&&&&   %%% %%%%
     %%%%%%%%%%           %%%%%%%%%%
       %%%%% %%% %%%%%%  %%% %%%%%
           %%%%%%% .%/%%%%%%%%\n)";

string const Texts::credits = R"(

Bu program 2021 guz donemi COM2001 Object Oriented Programming
dersi kapsaminda donem odevi olarak alfabetik sirasiyla:

*Ertugrul Bilgic -402545
*Hudahan Altun -394753
*Irmak Silay Kara -402496

tarafindan hazirlanmistir. Baskalarinca kullanim dagitim ve yayinlanmasi
hakki adi belirtilen kisiler ve COM2001 Object Oriented Programming
dersi ogretmeni SN.Dr.ogr.uyesi BESTE USTUBIOGLU'na aittir.


)";

string const Texts::teamFileInputWarning = R"(
#000 UYARI: TAKIM DOSYASI YUKLEME REHBERI

takimlar.txt dosyasinda yer alan takimlar

[Teknik Direktor Adi]-[Takim adi]
[Teknik Direktor Adi]-[Takim adi]

seklinde siralanmalidir.
)";

string const Texts::nameFileInputWarning = R"(
#001 UYARI: AD VE SOYAD DOSYALARI YuKLEME REHBERI

isim.txt||soyisim.txt dosyasinda yer alan isimler ve soyisimler
[isim]
[isim]

seklinde siralanmalidir.
)";

string const Texts::fileInputError ="uzantili dosya acilamadi.... #0000 HATA";

string const Texts::wrongButtonPushError ="yanlis tuslama yapildi... #001 HATA:";

string const Texts::menuInfo = R"(
1-Mac Oynat
2-Takim Listesi
3-Lig Tablosu
4-Fikstur
5-Emegi Gecenler
6-Tum maclari oyna
7-cikis
)";

string const Texts::profilePic = R"(
........................................
........................................
........................................
........................................
...............,*********,..............
..............************,.............
.............**************,............
............ ***************............
............ ,,************, ...........
.............. *********** .............
................. . . ..................
...........,,****************,..........
....... ************************* ......
......****************************,.....
.... ,*****************************,....
.....*******************************....
)";
string const Texts::formations = R"(
Formasyonlar:
1)4-3-3
2)4-5-1
3)4-4-2
4)3-2-5
5)3-3-4
6)3-4-3
7)3-5-2
8)4-2-4
9)5-2-3
10)5-3-2
11)5-4-1
12)6-3-1
)";

string const Texts::teamValueChaning = R"(
1)Isim Degistir
2)Kisaltma Degistir
3)Teknik Direktor degistir
4)Formasyon degistir
5)Ad Soyad'a gore oyuncuyu goruntule ve degistir.
)";


const string Texts::playerValueChanging =R"(
1)Adini Degistir
2)Soyadini degistir
3)Forma Numarasini degistir
4)Yasini Degistir
5)Performans Puanini degistir
)";


void Texts::println(const string& s) { // cout<< bir sey bir sey birsey<< endl; yapmaktan yoruldum endl'yi unutmayan fonksiyon
    cout<<s<<endl;
}

#pragma endregion

#pragma region Player
class Player{ //Player.h
    //ozellikler
private:
    int age{}; // oyuncu yası 18 36 arası random sayı
    string name; // adı txt'den gelecek
    string surname;// soyadı txt'den gelecek
    int num{};// forma numarası 0 99 arası rastgele sayı
    int position{}; // oynadıgı pozisyon playera ait static sayıya gore sekilleniyor
    int perform{};// oyuncu performansı 30 100 arası

public:

    //listeleme icin gerekli next ve prev
    Player* next{};
    Player* prev{};



    static const int ATTACKER = 1;// oynadıgı pozisyon forvet ise
    static const int MID = 2;// oynadıgı poazisyon  orta saha ise
    static const int DEFENCE = 3;// oynadıgı pozisyon defans ise


    //Constructorlar
    Player(int age, const string& name, const string& surname, int num, int position, int perform);// kullanılan constructor
    Player(); // default constructor<


    /*simdi odevde bizden oyuncu yaslarını[18, 36] aralıgından secmemiz gerektigini soyluyor
    fakat yine odevde oyuncuların ortalama yaslarının [25,32] aralıgında olması gerektigini de soyluyor
    bu yuzden Team.h icinde yer alacak meanAgeController() fonksiyonunda ortalama aralık dısında deger
    cıkarsa en genc oyuncuyu 1 yaslandıracak ya da en yaslı oyuncuyu 1 yas genclestriecek fonksiyonlarımız
    olamalıdır.*/

    //class ozel fonksiyonlar
    void benButtonPotion(); // genclestiren fonksiyon benjamin button gondermesi
    void lifeDrainer(); // yaslandırıcı
    void train(); //takım ortalama gucu [60,100] aralıgında olmalı bu yuzden en gucsuz oyuncuya +1 veren sistem
    void playerInfos() const;

    int getAge() const;

    void setAge(int age);

    const string &getName() const;

    void setName(const string &name);

    const string &getSurname() const;

    void setSurname(const string &surname);

    int getNum() const;

    void setNum(int num);

    int getPosition() const;

    void setPosition(int position);

    int getPerform() const;

    void setPerform(int perform);
//oyuncu bilgilerini bastıran fonksiyon


};
Player::Player() = default;

Player::Player(int age, const string& name, const string& surname, int num, int position, int perform) {
    setAge(age);
    setName(name);
    setSurname(surname);
    setNum(num);
    setPosition(position);
    setPerform(perform);


}


void Player::benButtonPotion() {
    setAge(getAge()-1); //yasını al 1 azalt
}

void Player::lifeDrainer() {
    setAge(getAge()+1); //yasını al 1 arttır
}

void Player::train() {
    setPerform(getPerform()+1); // performansını 1 arttır.
}

void Player::playerInfos() const {


    string s;
    switch (getPosition()) {
        case Player::ATTACKER:
            s = "Forvet";
            break;
        case Player::MID:
            s= "Orta Saha";
            break;
        case Player::DEFENCE:
            s="Defans";
            break;
        default:
            s="Oyuncu Mevki Bilgisi Yok!";
            break;

    }


    cout<<Texts::profilePic<<endl<<endl;

    cout<<"Adi Soyadi: "<<getName()<<" "<<getSurname()<<endl;
    cout<<"Forma Numarasi: "<<getNum()<<endl;
    cout<<"Yasi: "<<getAge()<<endl;
    cout<<"Oynadigi Mevki: "<< s <<endl;
    cout<<"Performans Puani: "<<getPerform()<<endl;
    cout<<"Degeri: "<<getPerform()/(getAge())<<"M$"<<endl;

}

int Player::getAge() const {
    return age;
}

void Player::setAge(int age) {
    Player::age = age;
}

const string &Player::getName() const {
    return name;
}

void Player::setName(const string &name) {
    Player::name = name;
}

const string &Player::getSurname() const {
    return surname;
}

void Player::setSurname(const string &surname) {
    Player::surname = surname;
}

int Player::getNum() const {
    return num;
}

void Player::setNum(int num) {
    Player::num = num;
}

int Player::getPosition() const {
    return position;
}

void Player::setPosition(int position) {
    Player::position = position;
}

int Player::getPerform() const {
    return perform;
}

void Player::setPerform(int perform) {
    Player::perform = perform;
}

#pragma endregion

#pragma region DoublyLinkedListForPlayer

class DoublyLinkedListForPlayer{//DoubleLinkedListforPlayer.h
public:

    Player* header;
    Player* trailer;

    DoublyLinkedListForPlayer(); // bos liste olusturucu
    ~DoublyLinkedListForPlayer(); // destructor

    bool empty() const;	// liste bos mu kontrolu


    void addFront(const string& name, const string& surname,
                  const int& age, const int& num,const int& position,const int& perform) const; // player olusturarak liste basına ekler
    void addFront(const Player& p) const; // var olan playerın kopyasını listenin basına ekler

    void addBack(const string& name, const string& surname,
                 const int& age, const int& num, const int& position, const int& perform) const; // player olusturarak veriyi sona ekler

    void addBack(const Player& p) const;//var olan playerın kopyasını listenin sonuna ekler




    void removeFront() const;	//bastaki elemanı siler
    void removeBack() const;	// sondaki elemanı siler

    void printH2T() const; // header'dan trailer'a yazar
    void printT2H() const; // trailer'dan header'a yazar



    static void add(Player* v, const string& name,
             const string& surname, const int& age, const int& num, const int& position, const int& perform);	//parametreye sub classlardan ekler



    static void remove(Player* v); // verilen dugumu siler

    void insertAgeOrdered(const string& name, const string& surname,
                          const int& age, const int& num, const int& position, const int& perform) const; // yasa gore ekler



    void insertAgeOrdered(Player* newNode, Player* current);// yasa gore ekler

    void insertPerformOrdered(const string& name, const string& surname, const int& age, const int& num,
                              const int& position, const int& perform) const; // performans degerine gore ekleme

    void removeOrdered(const string& name, const string& surname) const;

    DoublyLinkedListForPlayer* mergeByAgeLists(DoublyLinkedListForPlayer* list2) const; // liste birlestirici

    void orderByAge();// listetyi yasa gore sıralar
    void orderByPerform(); // listeyi performansa gore sıralar

    int length() const; // listenin uzunlugunu doner

    int totalAge() const; // listenin toplam yasını dondurur
    int totalAP() const; //toplam Attack Power'ı dondurur
    int totalMP() const; //toplam Midfield Power'ı dondurur
    int totalDP() const; // toplam Defence Power'ı dondurur
    Player findPlayerByNameAndSurname(const string& name, const string& surname, Player *startPointer);

};

//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
DoublyLinkedListForPlayer::DoublyLinkedListForPlayer(){
    header = new Player;
    trailer = new Player;
    header->next = trailer;
    trailer->prev = header;

}
//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
DoublyLinkedListForPlayer::~DoublyLinkedListForPlayer(){
    while (!empty()) removeFront();
    delete header;
    delete trailer;
}
//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
bool DoublyLinkedListForPlayer::empty() const	{

    return (header->next == trailer);
}


//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::addFront(const string& name, const string& surname,
                                         const int& age, const int& num, const int& position, const int& perform) const
{
    add(header->next, name, surname, age, num, position, perform);
}
//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::addFront(const Player& p) const {

    add(header->next, p.getName(),p.getSurname(),p.getAge(),p.getNum(),p.getPosition(),p.getPerform());

}
//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::addBack(const string& name, const string& surname,
                                        const int& age, const int& num, const int& position, const int& perform) const{
    add(trailer, name,surname,age,num,position,perform);
}
//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::addBack(const Player& p) const {

    add(trailer, p.getName(), p.getSurname(), p.getAge(), p.getNum(), p.getPosition(), p.getPerform());

}

//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::add(Player* v, const string& name, const string& surname, const int& age,
                                    const int& num, const int& position, const int& perform)
{
    Player* u = new Player;
    u->setName(name);
    u->setSurname(surname);
    u->setAge(age);
    u->setNum(num);
    u->setPerform(perform);
    u->setPosition(position);


    u->next = v;
    u->prev = v->prev;

    v->prev->next = u;
    v->prev = u;


}

//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::removeFront() const{

    if (empty()) {
        return;
    }

    remove(header->next);
}
//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::removeBack() const{
    // Liste bos mu?
    if (empty()) {

        return;
    }

    remove(trailer->prev);
}
//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::remove(Player* v) {
    Player* u = v->prev;
    Player* w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}
//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::insertAgeOrdered(const string& name, const string& surname,
                                                 const int& age, const int& num, const int& position, const int& perform) const {

    Player* u = new Player;
    u->setName(name);
    u->setSurname(surname);
    u->setAge(age);
    u->setNum(num);
    u->setPerform(perform);
    u->setPosition(position);



    Player* current = header->next;

    while (current != trailer) {
        if (u->getAge() >= current->getAge())
            current = current->next;
        else
            break;
    }

    // newNode'u current'tan once ekle (add() ile aynı)
    u->next = current;
    u->prev = current->prev;
    current->prev->next = u;
    current->prev = u;
}

//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::insertAgeOrdered(Player* newNode, Player* current) {

    if ((current == trailer) || (newNode->getAge() <= current->getAge())) {
        // newNode'u current'tan once ekle (add() ile aynı)
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    else
        insertAgeOrdered(newNode, current->next);
}
//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::insertPerformOrdered(const string& name, const string& surname, const int& age,
                                                     const int& num, const int& position, const int& perform) const {
    Player* u = new Player;
    u->setName(name);
    u->setSurname(surname);
    u->setAge(age);
    u->setNum(num);
    u->setPerform(perform);
    u->setPosition(position);

    Player* current = header->next;

    while (current != trailer) {
        if (u->getPerform() >= current->getPerform())
            current = current->next;
        else
            break;
    }

    // newNode'u current'tan once ekle (add() ile aynı)
    u->next = current;
    u->prev = current->prev;
    current->prev->next = u;
    current->prev = u;


}
//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
void DoublyLinkedListForPlayer::removeOrdered(const string& name, const string& surname) const{
    // Liste bos mu?
    if (empty()) {

        return;
    }

    Player* current = header->next;

    while (current != trailer) {
        if ((name == current->getName()) && (surname.compare(current->getSurname()))) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            return;
        }

        current = current->next;
    }


}
//calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır
DoublyLinkedListForPlayer* DoublyLinkedListForPlayer::mergeByAgeLists(DoublyLinkedListForPlayer* list2) const {
    DoublyLinkedListForPlayer* mergedList = new DoublyLinkedListForPlayer();

    Player* plist1 = this->header->next;
    Player* plist2 = list2->header->next;

    while ((plist1 != this->trailer) || (plist2 != list2->trailer)) {

        if (plist1 == this->trailer) {
            mergedList->addBack(plist2->getName(), plist2->getSurname(),
                                plist2->getAge(), plist2->getNum(), plist2->getPosition(), plist2->getPerform());

            plist2 = plist2->next;
            continue;
        }

        if (plist2 == list2->trailer) {
            mergedList->addBack(plist1->getName(), plist1->getSurname(), plist1->getAge(),
                                plist1->getNum(),plist1->getPosition(),plist1->getPerform());
            plist1 = plist1->next;
            continue;
        }

        if (plist1->getAge() <= plist2->getAge()) {
            mergedList->addBack(plist1->getName(), plist1->getSurname(),
                                plist1->getAge(), plist1->getNum(), plist1->getPosition(), plist1->getPerform());
            plist1 = plist1->next;
        }
        else {
            mergedList->addBack(plist2->getName(), plist2->getSurname(),
                                plist2->getAge(), plist2->getNum(), plist2->getPosition(), plist2->getPerform());
            plist2 = plist2->next;
        }
    }

    return mergedList;
}

void DoublyLinkedListForPlayer::orderByAge() {
    /*prensipte var olan listedeki elemanları tek tek insertOrdered fonksiyonu ile sıralı bir listeye ekler
      ve var olan listenin header ve trailer'ını yeni listeye esitler*/

    Player* listIterator = header->next;
    DoublyLinkedListForPlayer* orderedList = new DoublyLinkedListForPlayer;

    while(listIterator != trailer){
        orderedList->insertAgeOrdered(listIterator->getName(),listIterator->getSurname(),
                                      listIterator->getAge(),listIterator->getNum(), listIterator->getPosition(),listIterator->getPerform());
        listIterator = listIterator->next;


    }
    header = orderedList->header;
    trailer = orderedList->trailer;

}

void DoublyLinkedListForPlayer::orderByPerform() {
    /*prensipte var olan listedeki elemanları tek tek insertOrdered fonksiyonu ile sıralı bir listeye ekler
     ve var olan listenin header ve trailer'ını yeni listeye esitler*/

    Player* listIterator = header->next;
    DoublyLinkedListForPlayer* orderedList = new DoublyLinkedListForPlayer;

    while (listIterator != trailer) {
        orderedList->insertPerformOrdered(listIterator->getName(), listIterator->getSurname(),
                                          listIterator->getAge(), listIterator->getNum(), listIterator->getPosition(), listIterator->getPerform());
        listIterator = listIterator->next;

    }
    header = orderedList->header;
    trailer = orderedList->trailer;


}

int DoublyLinkedListForPlayer::length() const {

    // trailer'a ulasasaya kadar count'u arttırarak sayar ve sonucu dondurur
    int count = 0;

    if(empty()){
        return 0;
    }
    Player* first = header->next;
    while(first != trailer){
        count++;
        first = first->next;
    }
    return count;
}

int DoublyLinkedListForPlayer::totalAge() const {
    int totalAge = 0;
    //length fonksiyonu ile aynı mantıkta calısır bu sefer ama dugumun ilgili degerini count'a ekler ve onu dondurur

    if (empty()) {
        return 0;
    }
    Player* first = header->next;
    while (first != trailer) {
        totalAge+= first->getAge();
        first = first->next;
    }
    return totalAge;
}

int DoublyLinkedListForPlayer::totalAP() const {
    int totalAP = 0;
    //length fonksiyonu ile aynı mantıkta calısır bu sefer ama dugumun ilgili degerini count'a ekler ve onu dondurur

    if (empty()) {
        return 0;
    }
    Player* first = header->next;
    while (first != trailer) {
        if(first->getPosition()==Player::ATTACKER){
            totalAP += first->getPerform();
        }
        first = first->next;
    }
    return totalAP;
}

int DoublyLinkedListForPlayer::totalMP() const {
    //length fonksiyonu ile aynı mantıkta calısır bu sefer ama dugumun ilgili degerini count'a ekler ve onu dondurur
    int totalMP = 0;

    if (empty()) {
        return 0;
    }
    Player* first = header->next;
    while (first != trailer) {
        if (first->getPosition() == Player::MID) {
            totalMP += first->getPerform();
        }
        first = first->next;
    }
    return totalMP;
}

int DoublyLinkedListForPlayer::totalDP() const {
    //length fonksiyonu ile aynı mantıkta calısır bu sefer ama dugumun ilgili degerini count'a ekler ve onu dondurur
    int totalDP = 0;

    if (empty()) {
        return 0;
    }
    Player* first = header->next;
    while (first != trailer) {
        if (first->getPosition() == Player::DEFENCE) {
            totalDP += first->getPerform();
        }
        first = first->next;
    }
    return totalDP;
}

void DoublyLinkedListForPlayer::printH2T() const {
    //calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır en yaslıdan ya da performansı en yuksekten dusuge sıralar
    if (empty()) {
        cout << "List is empty !" << endl;
        return;
    }

    Player* first = header->next;
    while (first != trailer) {
        cout << first->getName() << "\t" << first->getSurname() << "\t" << first->getAge() << "\t" << first->getNum() << endl;
        first = first->next;
    }
}

void DoublyLinkedListForPlayer::printT2H() const {
    //calısma prensipleri ogr.Gor. omer cAKIR'ın ders notlarında yer almaktadır en gencten ya da performansı en dusukte yuksege sıralar
    if (empty()) {
        cout << "List is empty !" << endl;
        return;
    }

    Player* last = trailer->prev;
    while (last != header) {
        cout << last->getName() << "\t" << last->getSurname() << "\t" << last->getAge() << "\t" << last->getNum() << endl;
        last = last->prev;
    }
}
Player DoublyLinkedListForPlayer::findPlayerByNameAndSurname(const string& name, const string& surname, Player *startPointer) {
    if ((startPointer->getName()==name)&&(startPointer->getSurname()==surname)) {
        return *startPointer;

    }
    else
        return findPlayerByNameAndSurname(name,surname,startPointer->next);
}

#pragma endregion

#pragma region Team
class Team{

//ozellikleri
//-------------------------------------------------------------------------------------------------------------------------
private:
    // takım genel ozellikleri
    string name;// yskım adı
    string abbrev; //abbreviation kısaltması
    string coachName; // Teknik direktor adı
    static int TEAM_COUNT;// olusan takım sayısını tutan degisken

    int atck;//dizilimdeki forvet sayısı DEF 2
    int mid;// dizilimdeki orta saha sayısı DEF 4
    int def;// dizilimdeki defans sayısı DEF 4


    //takım statları
    double meanAge; // ortalama yas [25,32]
    double meanAP; // ortalama saldırı gucu [60,100]
    double meanMP; // ortalama ortasaha gucu [60,100]
    double meanDP; // ortalama defans gucu [60,100]
    double meanPower; // takım ortalama gucu


    //lig tablosu icin gerekli ozellikler
    int played; // oynadıgı mac sayısı fikstrur olusturuken de lazım olacak
    int won; // kazandıgı maclar
    int draw; // berabere
    int loss; // kaybedilen maclar
    int gs; //(Goals scored) atılan gol sayısı
    int ga; //(Goals Against) yenilen gol sayısı
    int av; //averaj gs-ga
    int pts; //puanı kazandıgı maca +3 berabere +1

//fonksiyonlar
//-------------------------------------------------------------------------------------------------------------------------
public:
    static void SET_TEAM_COUNT(const int& c);
    static int GET_TEAM_COUNT();


    //Listeler

    /*olustururken en kucuk en buyuk performansı en yuksek en dusuk gibi verilere ulasım gerekliliginden
    kaynaklı Array yerine LinkedList Kullanılmalı bunun tanımlaması icim ogr.Gor.omer cakır'ın derslerinden
    yardım alınmıstır*/

    //baska listeler de olabilir

    DoublyLinkedListForPlayer* playerList = new DoublyLinkedListForPlayer(); // 16 tane olmalı
    DoublyLinkedListForPlayer* teamAttackerList = new DoublyLinkedListForPlayer();// 5 tane olmalı 3-2-5 formasyonu saglanabilmesi ici
    DoublyLinkedListForPlayer* teamMidfieldList = new DoublyLinkedListForPlayer(); // 5 tane olamalı 3-5-2 formasyonu saglanabilmesi ici
    DoublyLinkedListForPlayer* teamDefenceList = new DoublyLinkedListForPlayer(); // 6 tane olmalı 6-3-1 formasyonu saglanabilmesi ici

    //Constructor
    Team();
    Team(const string& nameAdress, const string& surnameAdress, string name, string abbrev, string coachName);// isimleri ve soy isimlerini uretmesi icin gerekli file nameler ve isim kısaltma ve koc bilgisi gerekli


    //ozel fonksiyonlar

    void matchEnded(bool isWon,bool isLost, int gs,int ga); //mac bittiginde cagrılan fonksiyon
    void ageController(); // yas kontrolu yapıp alcak veya yuksek degerde en yaslı veya en genc oyuncuya yas arttırması yapan fonksiyon
    void performanceController(int param); // param pozisyonuna gore o pozisyonun ort gucunu kontrol eder eger 60 altı ise en zayı oyuncuyu gelistirir


    void calcMeanAP();// ortalama AP hesaplar
    void calcMeanMP(); //ortalama MP hesaplar
    void calcMeanDP(); // ortalama DP hesaplar
    void calcMeanPower(); //ortalama gucu hesaplar
    void calcMeanAge(); // ortalama yası hesaplar

    static  vector<string>nameFactory(const string& fileName); //nameAdress verisini aldıgı dosysyı acar okur vector dondurur
    void teamInfos(); // takımın tum infosunu basar
    string teamStandig() const;

    const string &getName() const;

    void setName(const string &name);

    const string &getAbbrev() const;

    void setAbbrev(const string &abbrev);

    const string &getCoachName() const;

    void setCoachName(const string &coachName);

    static int getTeamCount();

    static void setTeamCount(int teamCount);

    int getAttacker() const;

    void setAttacker(int atck);

    int getMidfield() const;

    void setMidfield(int mid);

    int getDefence() const;

    void setDefence(int def);

    double getMeanAge() const;

    void setMeanAge(double meanAge);

    double getMeanAp() const;

    void setMeanAp(double meanAp);

    double getMeanMp() const;

    void setMeanMp(double meanMp);

    double getMeanDp() const;

    void setMeanDp(double meanDp);

    double getMeanPower() const;

    void setMeanPower(double meanPower);

    int getPlayed() const;

    void setPlayed(int played);

    int getWon() const;

    void setWon(int won);

    int getDraw() const;

    void setDraw(int draw);

    int getLoss() const;

    void setLoss(int loss);

    int getGS() const;

    void setGS(int gs);

    int getGA() const;

    void setGA(int ga);

    int getAV() const;

    void setAV(int av);

    int getPts() const;

    void setPts(int pts);
// takımın lig bilgilerini dondurur




};
int Team::TEAM_COUNT = 0;

void Team::SET_TEAM_COUNT(const int& c) {
    TEAM_COUNT =c;
}

int Team::GET_TEAM_COUNT() {
    return TEAM_COUNT;
}

Team::Team() {

    meanAge =0;
    meanAP = 0;
    meanDP = 0;
    meanPower = 0;
    meanMP = 0;
    atck= 2;
    mid =4;
    def = 4;
    played = 0;
    won = 0;
    draw = 0;
    loss = 0;
    gs=0;
    ga = 0;
    av =0;
    pts = 0;

}


Team::Team(const string& nameAdress, const string& surnameAdress,string name,string abbrev,string coachName) {
    TEAM_COUNT++;
    this->name = name;
    this->abbrev = abbrev;
    this->coachName = coachName;
    atck =2;
    mid =4;
    def =4;


    vector<string> names = nameFactory(nameAdress);
    vector<string> surnames = nameFactory(surnameAdress);




    for (int i = 0; i < 5; i++) {// forvetlerin olusumu
        Player newAttacker((rand()%18)+18, names.at( rand()%(names.size()-1)),
                           surnames.at(rand() %(surnames.size()-1)), (rand()%98)+1 ,Player::ATTACKER, (rand()%70)+30);


        teamAttackerList->addFront(newAttacker);
        playerList->addFront(newAttacker);


    }
    for (int i = 0; i < 5; i++) { // ortasahanın olusumu
        Player newMid((rand()%18)+18, names.at(rand() % (names.size() - 1)),
                           surnames.at(rand() % (surnames.size() - 1)), (rand()%98)+1, Player::MID, (rand()%70)+30);

        teamMidfieldList->addFront(newMid);
        playerList->addFront(newMid);


    }
    for (int i = 0; i < 6; i++) {//defansın olusumu
        Player newDefence((rand()%18)+18, names.at(rand() % (names.size() - 1)),
                           surnames.at(rand() % (surnames.size() - 1)), (rand()%98)+1, Player::DEFENCE, (rand()%70)+30);

        teamDefenceList->addFront(newDefence);
        playerList->addFront(newDefence);


    }



    meanAge =0;
    meanAP = 0;
    meanMP = 0;
    meanDP = 0;
    meanPower = 0;


    calcMeanAge();
    calcMeanAP();
    calcMeanMP();
    calcMeanDP();
    calcMeanPower();

    ageController();
    performanceController(Player::ATTACKER);
    performanceController(Player::MID);
    performanceController(Player::DEFENCE);
    calcMeanPower();

    played = 0;
    won = 0;
    draw = 0;
    loss = 0;
    gs = 0;
    ga = 0;
    av = 0;
    pts = 0;




}

void Team::matchEnded(const bool isWon, const bool isLost, const int gs, const int ga) {
    setPlayed(getPlayed()+1);
    setGA(getGA()+ga); //daha onceki maclarda atııgı golle bu mac attıgı golu topla setle
    setGS(getGS()+gs);
    setAV(getGS()-getGA());

    if (isWon){
        setWon(getWon()+1);
        setPts(getPts()+3);

    }
    else if(isLost){
        setLoss(getLoss()+1);
    }
    else{
        setDraw(getDraw()+1);
        setPts(getPts()+1);
    }

}

void Team::ageController() {

    calcMeanAge();

    while(meanAge < 25 || meanAge>32){

        if(meanAge<25){
            playerList->header->next->lifeDrainer();
            playerList->orderByAge();
        }
        else {
            playerList->trailer->prev->benButtonPotion();
            playerList->orderByAge();
        }
        calcMeanAge();
    }


}

void Team::performanceController(const int param) {
    switch (param) {

        case Player::ATTACKER:
            calcMeanAP();
            while(meanAP<60){
                teamAttackerList->header->next->train();
                teamAttackerList->orderByPerform();
                calcMeanAP();
            }
            break;
        case Player::MID:
            calcMeanDP();
            while(getMeanMp()<60){
                teamMidfieldList->header->next->train();
                teamMidfieldList->orderByPerform();
                calcMeanMP();
            }
            break;
        case Player::DEFENCE:
            calcMeanDP();
            while(getMeanDp()<60){
                teamDefenceList->header->next->train();
                teamDefenceList->orderByPerform();
                calcMeanDP();
            }
        default:
            break;
    }

}

void Team::calcMeanAP() {
    setMeanAp(teamAttackerList->totalAP()/teamAttackerList->length());

}

void Team::calcMeanMP() {
    setMeanMp(teamMidfieldList->totalMP()/teamMidfieldList->length());

}

void Team::calcMeanDP() {
    setMeanDp(teamDefenceList->totalDP()/teamDefenceList->length());

}

void Team::calcMeanPower() {
    setMeanPower((getMeanAp()+getMeanMp()+getMeanDp())/3);
}

void Team::calcMeanAge() {
    setMeanAge((playerList->totalAge()/playerList->length()));
}

vector<string> Team::nameFactory(const string& fileName) {

    vector<string> names;
    fstream readName;
    string nameLine;
    vector<string> emptyVector;

    readName.open(fileName,ios::in);

    if(readName.fail()){
        cout<<Texts::fileInputError<<endl;
        return emptyVector;
    }


    while (getline(readName, nameLine)) {
        names.push_back(nameLine);
    }
    readName.close();

    return names;

}


void Team::teamInfos() {

    cout<<"***************** " <<getName()<<" *****************"<< endl;
    cout<<"Kisaltmasi: "<<getAbbrev()<<endl;
    cout<<"Teknik Direktor: "<<getCoachName()<<endl;
    cout<<"Formasyon Bilgisi: "<<getDefence()<<"-"<<getMidfield()<<"-"<<getAttacker()<<endl;
    cout<<"Oyuncu Yas Ort.: "<<getMeanAge()<<endl;
    cout<<"Ort. Guc: "<<getMeanPower()<<endl<<endl;
    cout<<teamStandig()<<endl;


    cout<<"Forvetler:"<<endl;
    teamAttackerList->printT2H();
    cout<<endl;
    cout<<"Orta Sahalar:"<<endl;
    teamMidfieldList->printT2H();
    cout<<endl;
    cout<<"Defanslar:"<<endl;
    teamDefenceList->printT2H();
    cout<<endl;

}

string Team::teamStandig() const {

    string s = getName()+" "+to_string(getPlayed())+" "+to_string(getWon())+" "+to_string(getDraw())+" "+to_string(getLoss())
            +" "+to_string(getGS())+" "+to_string(getGA())+" "+to_string(getAV())+" "+to_string(getPts());
    return s;



}

const string &Team::getName() const {
    return name;
}

void Team::setName(const string &name) {
    Team::name = name;
}

const string &Team::getAbbrev() const {
    return abbrev;
}

void Team::setAbbrev(const string &abbrev) {
    Team::abbrev = abbrev;
}

const string &Team::getCoachName() const {
    return coachName;
}

void Team::setCoachName(const string &coachName) {
    Team::coachName = coachName;
}

int Team::getTeamCount() {
    return TEAM_COUNT;
}

void Team::setTeamCount(int teamCount) {
    TEAM_COUNT = teamCount;
}

int Team::getAttacker() const {
    return atck;
}

void Team::setAttacker(int atck) {
    Team::atck = atck;
}

int Team::getMidfield() const {
    return mid;
}

void Team::setMidfield(int mid) {
    Team::mid = mid;
}

int Team::getDefence() const {
    return def;
}

void Team::setDefence(int def) {
    Team::def = def;
}

double Team::getMeanAge() const {
    return meanAge;
}

void Team::setMeanAge(double meanAge) {
    Team::meanAge = meanAge;
}

double Team::getMeanAp() const {
    return meanAP;
}

void Team::setMeanAp(double meanAp) {
    meanAP = meanAp;
}

double Team::getMeanMp() const {
    return meanMP;
}

void Team::setMeanMp(double meanMp) {
    meanMP = meanMp;
}

double Team::getMeanDp() const {
    return meanDP;
}

void Team::setMeanDp(double meanDp) {
    meanDP = meanDp;
}

double Team::getMeanPower() const {
    return meanPower;
}

void Team::setMeanPower(double meanPower) {
    Team::meanPower = meanPower;
}

int Team::getPlayed() const {
    return played;
}

void Team::setPlayed(int played) {
    Team::played = played;
}

int Team::getWon() const {
    return won;
}

void Team::setWon(int won) {
    Team::won = won;
}

int Team::getDraw() const {
    return draw;
}

void Team::setDraw(int draw) {
    Team::draw = draw;
}

int Team::getLoss() const {
    return loss;
}

void Team::setLoss(int loss) {
    Team::loss = loss;
}

int Team::getGS() const {
    return gs;
}

void Team::setGS(int gs) {
    Team::gs = gs;
}

int Team::getGA() const {
    return ga;
}

void Team::setGA(int ga) {
    Team::ga = ga;
}

int Team::getAV() const {
    return av;
}

void Team::setAV(int av) {
    Team::av = av;
}

int Team::getPts() const {
    return pts;
}

void Team::setPts(int pts) {
    Team::pts = pts;
}


#pragma endregion

#pragma region Match

class Match {
private:

    Team home; // ev sahibi takım
    Team visitor; // deplasman takımı
    int id{}; // fiksturdeki id
    double homeWinRate{}; //ev sahibi takımın kazanma oranı
    double visitorWinRate{}; // deplasman takımının kazanma oranı
    bool isPlayed= false; // oynandı mı?

    int homeScore{}; //1. takım skoru
    int visitorScore{}; //2. takım skoru
    static int matchCount; // olusturulmıs mac sayısı


public:

    Match(const Team& home,const Team& visitor);
    Match();
    void playMatch();// mac oynatma

    void matchInfo() const;

    const Team &getHome() const;

    void setHome(const Team &home);

    const Team &getVisitor() const;

    void setVisitor(const Team &visitor);

    int getID() const;

    void setID(int id);

    double getHWR() const;

    void setHWR(double homeWinRate);

    double getVWR() const;

    void setVWR(double visitorWinRate);

    void setIsPlayed(bool isPlayed);

    int getHomeScore() const;

    void setHomeScore(int homeScore);

    int getVisitorScore() const;

    void setVisitorScore(int visitorScore);

    static int getMatchCount();

    static void setMatchCount(int matchCount);

    static int playedMatchCount;
};
int Match::matchCount=0;
int Match::playedMatchCount=0;

Match::Match(const Team& home, const Team& visitor) {
    isPlayed = false; // yeni olusan mac daha oynanmamıstır
    this->home = home;
    this->visitor = visitor;

    matchCount++; // uretilmis mac sayısını arttırır
    setID(matchCount+1000);//daha bir id id gozuksun diye +1000

    setHWR((home.getMeanPower()/(home.getMeanPower()+visitor.getMeanPower()))*100);//home win rate hesabı
    setVWR((visitor.getMeanPower() /(home.getMeanPower() + visitor.getMeanPower()))*100);// visitor win rate hesabı


}
Match::Match()= default;

void Match::playMatch() {

    srand(time(NULL));

    int homeScore = rand()%6;
    int visitorScore = rand()%6;

    if (home.getMeanAp()<visitor.getMeanAp()){
        visitorScore++;
    }
    else{
        homeScore++;
    }

    if (home.getMeanMp() < visitor.getMeanMp()) {

        visitorScore++;

        if(homeScore > 0){
            homeScore--;
        }
    }
    else {

        homeScore++;
        if(visitorScore>0){
            visitorScore--;
        }
    }
    if (home.getMeanDp() < visitor.getMeanDp()) {

        if (homeScore > 0) {
            homeScore--;
        }
    }
    else {

        if (visitorScore > 0) {
            visitorScore--;
        }
    }
    if(home.getMeanPower()<visitor.getMeanPower()){
        int orCondition = rand()%1;
        if (orCondition ==1){
            visitorScore++;
        } else{
            if(homeScore > 0){
                homeScore--;
            }
        }
    }
    else{
        int orCondition = rand()%1;
        if (orCondition ==1){
            homeScore++;
        } else{
            if(visitorScore>0){
                visitorScore--;
            }
        }
    }

    if(homeScore<visitorScore){
        home.matchEnded(false,true,homeScore,visitorScore);
        visitor.matchEnded(true,false,visitorScore,homeScore);

    }
    else if (homeScore == visitorScore) {
        home.matchEnded(false,false, homeScore, visitorScore);
        visitor.matchEnded(false,false,visitorScore,homeScore);
    }
    else{
        home.matchEnded(true,false,homeScore,visitorScore);
        visitor.matchEnded(false,true,visitorScore,homeScore);

    }
    setIsPlayed(true); // mac bitti artık oynandı
    playedMatchCount++;

    setHomeScore(homeScore);
    setVisitorScore(visitorScore);
    matchInfo();

}


void Match::matchInfo() const {

    if(isPlayed){
        cout<<getID()<<"\t" << getHome().getAbbrev() <<" "<< getHomeScore() << " - "<<getVisitorScore()<<" "<<getVisitor().getAbbrev()<<endl;}
    else{
        cout<<"\t\t"<<getID()<<endl;
        cout<<getHome().getName()<<"\t\t\t"<<getVisitor().getName()<<endl;
        cout<<getHome().getCoachName()<<"\t\t\t"<<getVisitor().getCoachName()<<endl;
        cout<<getHWR()<<"\t\t\t\t"<<getVWR()<<endl;

    }


}

const Team &Match::getHome() const {
    return home;
}

void Match::setHome(const Team &home) {
    Match::home = home;
}

const Team &Match::getVisitor() const {
    return visitor;
}

void Match::setVisitor(const Team &visitor) {
    Match::visitor = visitor;
}

int Match::getID() const {
    return id;
}

void Match::setID(int id) {
    Match::id = id;
}

double Match::getHWR() const {
    return homeWinRate;
}

void Match::setHWR(double homeWinRate) {
    Match::homeWinRate = homeWinRate;
}

double Match::getVWR() const {
    return visitorWinRate;
}

void Match::setVWR(double visitorWinRate) {
    Match::visitorWinRate = visitorWinRate;
}

void Match::setIsPlayed(bool isPlayed) {
    Match::isPlayed = isPlayed;
}

int Match::getHomeScore() const {
    return homeScore;
}

void Match::setHomeScore(int homeScore) {
    Match::homeScore = homeScore;
}

int Match::getVisitorScore() const {
    return visitorScore;
}

void Match::setVisitorScore(int visitorScore) {
    Match::visitorScore = visitorScore;
}

int Match::getMatchCount() {
    return matchCount;
}

void Match::setMatchCount(int matchCount) {
    Match::matchCount = matchCount;
}



#pragma endregion

#pragma region League
class League {


private:
    vector<string> teamNames; // takım isimlerini tutan string vectoru
    vector<string> teamAbrevs;// takım kısaltmaları
    vector<string> teamCoachs;// takım teknik direktorleri

    vector<Team> teams;// takımlar
    vector<Match> fixture; // fikstur



public:
    League();

     vector<string> &getTeamNames() ;

    void setTeamNames(const vector<string> &teamNames);

     vector<string> &getTeamAbrevs() ;

    void setTeamAbrevs(const vector<string> &teamAbrevs);

     vector<string> &getTeamCoachs() ;

    void setTeamCoachs(const vector<string> &teamCoachs);

    vector<struct Team> &getTeams() ;

    void setTeams(const vector<Team> &teams);

     vector<Match> &getFixture() ;

    void setFixture(const vector<Match> &fixture);

    static  int NUM_TEAM;




    void fillTheFixture();// fixture olusturucu
    vector<string> abrevCreator(const vector<string>& names);// kısaltma olusturcu
    vector<string> readTeamNameTxt(const string& fileName);//takım adı okuyucu
    vector<string> readCoachNameTxt(const string& fileName);// koc adı okuyucu
    void showTeamInfos(); // tum takımların bilgisini gosterir.
    void showLeugeStandig(); // lig puan tablosunu gosterir
    void showFixture(); // tum fiksturu gosterir
    void showMatchByID(int id); // id'si girilen macı gosterir
    Team findTeamByAbrev(string abrev,int startIndex);



};

int  League::NUM_TEAM=18;



vector<string> League::abrevCreator(const vector<string>& names) {


    vector<string> vector; // kısaltmalar

    string line; //vektorden gelen strignleri tutacak

    for (const string& name : names) {//vektor dongusu

        line = name;//vektorun her bir elemanını alıp line aatıyoruz

        if (line.find("spor") != string::npos) { //line da spor kelimesi geciyorsa

            string temp; //takımın ilk harfini tutacak degisken
            string temp2;
            temp = line.front(); //ilk harf donuruluyor
            temp2 = line.at(2);
            string s = "s";//s harfini tutuyor
            string abr = temp + temp2 + s;// yeni degskene bunlar atanıyor
            vector.push_back(abr);

        }
        else {//takım adında spor kelimesi yoksa

            string temp;
            temp = line.front();
            string fourth;
            fourth = line.at(4);
            string abr = temp + fourth;
            vector.push_back(abr);
        }
    }
    return vector;
}
vector<string> League::readTeamNameTxt(const string& fileName) {

    vector<string> teamNames; // dondurulecek deger
    fstream fin; //dosyanın tanımlanması


    fin.open(fileName,ios::in);// dosyayı acma

    string line;

    if(fin.fail()){
        cout<<fileName<<Texts::fileInputError<<endl;
        return teamNames;
    }

    while(getline(fin,line)){
        int pos = line.find("-");
        string sub =  line.substr(pos+1);
        teamNames.push_back(sub);


    }
    fin.close();
    return  teamNames;

}
vector<string> League::readCoachNameTxt(const string& fileName) {


    vector<string> coachNames;
    fstream fin; //txt yi oku

    fin.open(fileName,ios::in);

    string line;

    if(fin.fail()){
        cout<<fileName<<Texts::fileInputError<<endl;
        return coachNames;
    }
    while(getline(fin,line)){
        int pos = line.find("-");
        string sub =  line.substr(0,pos);
        coachNames.push_back(sub);

    }
    fin.close();

    return  coachNames;



}

League::League() {



   teamNames = readTeamNameTxt("takimlar.txt");
   teamCoachs = readCoachNameTxt("takimlar.txt");
   teamAbrevs = abrevCreator(teamNames);



    for (int i = 0; i <NUM_TEAM; i++) {
        Team team("isim.txt","soyisim.txt",
                  teamNames.at(i),teamAbrevs.at(i),
                  teamCoachs.at(i));
        teams.push_back(team);
    }


    


}

void League::fillTheFixture() {
    //http://www.nuhazginoglu.com/2012/12/10/fikstur-algoritmasi/

    vector<Team> tempTeams; // takımları kopyalamak icin

    for (Team t : teams) {
        tempTeams.push_back(t);

    }

    Team constTeam = tempTeams.at(0);

    tempTeams.emplace_back();
    tempTeams.erase(tempTeams.begin());
    tempTeams.pop_back();


    for (int i = 0; i < Team::GET_TEAM_COUNT() - 1; i++) {

        Match match(constTeam, tempTeams[0]);
        fixture.push_back(match);

        for (int j = 0; j < (teams.size() - 2) / 2; j++) {

            Match matchA(tempTeams.at(j + 1), tempTeams.at(tempTeams.size() - j - 1));
            fixture.push_back(matchA);
        }
        tempTeams.push_back(tempTeams.at(0));
        tempTeams.erase(tempTeams.begin() + 0);

    }


}

void League::showTeamInfos() {

    for (Team t : teams) {
        t.teamInfos();

    }

}

void League::showFixture() {
    for(Match m : fixture){
        m.matchInfo();
    }

}

void League::showLeugeStandig() {

    for (int i = 0; i <teams.size() ; i++) {
        cout<<i+1<<" "<<teams.at(i).teamStandig()<<endl;

    }


}

void League::showMatchByID(int id) {
    int index = id-1001;
    fixture.at(index).matchInfo();

}

Team League::findTeamByAbrev(string abrev, int startIndex) {
    if(abrev == teams.at(startIndex).getAbbrev()){
        return teams.at(startIndex);
    } else{
        return findTeamByAbrev(abrev,startIndex+1);
    }
}

 vector<string> &League::getTeamNames()  {
    return teamNames;
}

void League::setTeamNames(const vector<string> &teamNames) {
    League::teamNames = teamNames;
}

 vector<string> &League::getTeamAbrevs()  {
    return teamAbrevs;
}

void League::setTeamAbrevs(const vector<string> &teamAbrevs) {
    League::teamAbrevs = teamAbrevs;
}

 vector<string> &League::getTeamCoachs()  {
    return teamCoachs;
}

void League::setTeamCoachs(const vector<string> &teamCoachs) {
    League::teamCoachs = teamCoachs;
}

 vector<Team> &League::getTeams()  {
    return teams;
}

void League::setTeams(const vector<Team> &teams) {
    League::teams = teams;
}

 vector<Match> &League::getFixture()  {
    return fixture;
}

void League::setFixture(const vector<Match> &fixture) {
    League::fixture = fixture;
}

#pragma endregion

#pragma region Interface
class Interface {
private:

    vector<Team> extraTeams;
public:
    void execute();
    void welcome();
     void startScreen();
     void addTeam();

     void menu(League &l);//ana sayfa
      void playMatchScreen(League &l);//1
      void playAllMatches(League &l);
     void setTeamsScreen(League &l);//2
     void seeFixtureScreen(League &l);//3
     void seeLeagueStandings(League &l);//4
     void seeCreditsScreen(League &l);//5

    vector<Team> getExtraTeams() const;
//5

};

void Interface::execute() {
    welcome();
    startScreen();
    League league;
    if(!extraTeams.empty()) {

        for (Team t: extraTeams) {
            league.getTeams().push_back(t);

        }
    }
    league.fillTheFixture();
    menu(league);



}

void Interface::welcome() {
    Texts::println(Texts::logo);
    Texts::println(Texts::greetings);
    Texts::println(Texts::credits);
    Texts::println(Texts::nameFileInputWarning);
    Texts::println(Texts::teamFileInputWarning);

}

void Interface::startScreen() {
    Texts::println("Oynayacak Takim Sayisini Giriniz: ");
    int num;
    cin>>num;
    if (num>League::NUM_TEAM){
        Texts::println("Girilen Deger Default Belirlenen 18 sayisindan fazla");
        Texts::println("Fazla Takim txt dosyasinda var mi?(y/n) ");
        string s;
        cin>>s;
        if (s=="y"){
            League::NUM_TEAM = num;
        }
        else if(s =="n"){
            while(League::NUM_TEAM!=num) {
                addTeam();
                League::NUM_TEAM = League::NUM_TEAM + 1;
            }
        }
        else{
            Texts::println(Texts::wrongButtonPushError);
            startScreen();
        }

    }
    else{
        League::NUM_TEAM = num;
    }

}

void Interface::addTeam() {
    string name;

    string abbrev;
    string coachName;

    Texts::println("Takim adi: ");
    cin>>name;
    Texts::println("Takim Kisaltmasi: ");
    cin>>abbrev;
    Texts::println("Takim Teknik Direktronun Adi Soyadi: ");
    cin>>coachName;

    Team team("isim.txt","soyisim.txt",name,abbrev,coachName);
    extraTeams.push_back(team);




}

void Interface::menu(League &l) {

    Texts::println(Texts::menuInfo);
    int n;
    cin>>n;
    switch (n) {
        case 1:{
            playMatchScreen(l);
            break;}
        case 2:{
            setTeamsScreen(l);
            break;}
        case 3:{
            seeLeagueStandings(l);
            break;}
        case 4:{
            seeFixtureScreen(l);
            break;}
        case 5:{
            seeCreditsScreen(l);
            break;}
        case 6:{
            playAllMatches(l);
            break;
        }
        case 7:{
            Texts::println("cikmak istediginize emin misiniz?(y/n)");
            string s;
            cin>>s;
            if (s=="y"){
                exit(1);
            }
            else if (s=="n"){
                menu(l);
            }
            else{
                Texts::println(Texts::wrongButtonPushError);
                menu(l);
            }
            break;}
        default:{
            Texts::println(Texts::wrongButtonPushError);
            menu(l);
            break;}
    }

}

void Interface::playMatchScreen(League &l) {
    l.getFixture().at(Match::playedMatchCount).matchInfo();
    l.getFixture().at(Match::playedMatchCount).playMatch();
    Texts::println("Menuye donmek icin sayi tuslayin...");
    getchar();
    menu(l);

}

void Interface::setTeamsScreen(League &l) {
    l.showTeamInfos();
    Texts::println("Degistirmek istediginiz takimin kisaltmasi: \nmenuye donmek icin 0'ı tuslayın");
    string s;
    cin>>s;
    if(s=="0"){
        menu(l);
    }

    Team team = l.findTeamByAbrev(s,0);
    team.teamInfos();
    Texts::println(Texts::teamValueChaning);
    int a;
    cin>>a;
    switch (a) {
        case 1:{
            cout<<"Yeni isim: "<<endl;
            string newName;
            cin>>newName;
            team.setName(newName);
            break;}
        case 2:{
            cout<<"Yeni kisaltma: "<<endl;
            string abbrev;
            cin>>abbrev;
            team.setAbbrev(abbrev);
            break;}
        case 3:{cout<<"Yeni Teknik direktor: "<<endl;
            string coach;
            cin>>coach;
            team.setCoachName(coach);
            break;}
        case 4:{
            cout<<Texts::formations<<endl;
            Texts::println("olmasini istediginiz formasyonu giriniz: ");
            int formation;
            cin>>formation;
            switch (formation) {
                case 1:{
                    team.setAttacker(3);
                    team.setMidfield(3);
                    team.setDefence(4);
                    break;}
                case 2:{
                    team.setAttacker(1);
                    team.setMidfield(5);
                    team.setDefence(4);
                    break;}
                case 3:{
                    team.setAttacker(2);
                    team.setMidfield(4);
                    team.setDefence(4);
                    break;}
                case 4:{
                    team.setAttacker(5);
                    team.setMidfield(2);
                    team.setDefence(3);
                    break;}
                case 5:{
                    team.setAttacker(4);
                    team.setMidfield(3);
                    team.setDefence(3);
                    break;}
                case 6:{
                    team.setAttacker(3);
                    team.setMidfield(4);
                    team.setDefence(3);
                    break;}
                case 7:{
                    team.setAttacker(2);
                    team.setMidfield(5);
                    team.setDefence(3);
                    break;}
                case 8:{
                    team.setAttacker(4);
                    team.setMidfield(2);
                    team.setDefence(4);
                    break;}
                case 9:{
                    team.setAttacker(3);
                    team.setMidfield(2);
                    team.setDefence(5);
                    break;}
                case 10:{
                    team.setAttacker(2);
                    team.setMidfield(3);
                    team.setDefence(5);
                    break;}
                case 11:{
                    team.setAttacker(1);
                    team.setMidfield(4);
                    team.setDefence(5);
                    break;}
                case 12:{
                    team.setAttacker(1);
                    team.setMidfield(3);
                    team.setDefence(6);
                    break;}
                default:{
                    Texts::println(Texts::wrongButtonPushError);
                    menu(l);
                    break;}
            }
            break;}
        case 5:{cout<<"Oyuncu Adi  "<<endl;
            string playerName;
            string playerSurname;
            cin>>playerName;
            cout<<"Oyuncu Soyadi  "<<endl;
            cin>>playerSurname;
            Player player = team.playerList->findPlayerByNameAndSurname( playerName,  playerSurname, team.playerList->header);
            player.playerInfos();
            Texts::println(Texts::playerValueChanging);
            int b;
            cout<<"Degistirmek istediginiz deger: "<<endl;
            cin>>b;
            switch (b) {
                case 1:{
                    cout<<"Yeni isim: "<<endl;
                    string newName;
                    cin>>newName;
                    player.setName(newName);

                    break;}
                case 2:{
                    cout<<"Yeni Soyisim: "<<endl;
                    string newSurname;
                    cin>>newSurname;
                    player.setSurname(newSurname);

                    break;
                }
                case 3:{
                    cout<<"Yeni forma numarasi: "<<endl;
                    int num;
                    cin>>num;
                    player.setNum(num);

                    break;
                }
                case 4:{
                    cout<<"Yeni Yas: "<<endl;
                    int age;
                    cin>>age;
                    player.setNum(age);
                    break;
                }
                case 5:{
                    cout<<"Yeni Performansi: "<<endl;
                    int perform;
                    cin>>perform;
                    player.setNum(perform);
                    break;
                }

                default:{
                    Texts::println(Texts::wrongButtonPushError);
                    menu(l);
                    break;

                }
            }
            break;}

        default:{
            Texts::println(Texts::wrongButtonPushError);
            menu(l);
            break;
        }
    }
    Texts::println("Menuye donmek icin sayi tuslayin...");
    getchar();
    menu(l);
}

void Interface::seeFixtureScreen(League &l) {
    Texts::println("Bilgisini gormek istediginiz macin id'si: ");
    int id;
    cin>>id;
    l.showMatchByID(id);
    Texts::println("Menuye donmek icin sayi tuslayin...");
    getchar();
    menu(l);

}

void Interface::seeLeagueStandings(League &l) {
    l.showLeugeStandig();
    Texts::println("Menuye donmek icin sayi tuslayin...");
    getchar();
    menu(l);


}

void Interface::seeCreditsScreen(League &l) {
    Texts::println(Texts::credits);
    Texts::println("Menuye donmek icin sayi tuslayin...");
    getchar();
    menu(l);

}

vector<Team> Interface::getExtraTeams() const {
    return extraTeams;
}

void Interface::playAllMatches(League &l) {
    for (int i = Match::playedMatchCount; i < l.getFixture().size(); ++i) {
        l.getFixture().at(i).playMatch();
    }

    Texts::println("Menuye donmek icin sayi tuslayin...");
    getchar();
    menu(l);



}


#pragma endregion

int main(){
    srand(time(NULL));
    Interface interface;
    interface.execute();
    exit(1);
}
