#include <iostream>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include <unordered_map>
#include <cmath>

class Investment{

   public:
      Investment();
      Investment(double suma, double rata, int perioada);

      friend std::ostream& operator<<(std::ostream& out, const Investment& obj);

      //getter
      double getSumaInitiala() const;
      double getRataDobanzii() const;
      int getLuni() const;

      //setteri
      void setSumaInitiala(double suma);
      void setRataDobanzii(double rata);
      void setLuni(int nrLuni);


      double calculeazaProfit() const;
      double getSumaFinala() const;

   private:
      double sumaInitiala;
      double rataDobanzii;
      int luni;

};

Investment::Investment() {
   this->sumaInitiala = 0;
   this->rataDobanzii = 0;
   this->luni = 0;
}

Investment::Investment(double suma, double rata, int perioada){
   this->sumaInitiala=suma;
   this->rataDobanzii=rata;
   this->luni = perioada;
}

double Investment::getSumaInitiala() const{
   return sumaInitiala;
}

double Investment::getRataDobanzii() const{
   return rataDobanzii;
}

int Investment::getLuni() const{
   return luni;
}

void Investment::setSumaInitiala(double suma){
   this->sumaInitiala = suma;
}

void Investment::setRataDobanzii(double rata){
   this->rataDobanzii = rata;
}

void Investment::setLuni(int nrLuni){
   this->luni = nrLuni;
}

double Investment::calculeazaProfit() const{
   double rataLunara = rataDobanzii/ 12.0;
   double sumaFinala = sumaInitiala * std::pow(1.0 + rataLunara, luni);

   return sumaFinala - sumaInitiala;
}

double Investment::getSumaFinala() const{
   return sumaInitiala + calculeazaProfit();
}

std::ostream& operator<<(std::ostream& out, const Investment& obj) {
    out << "\n------- RAPORT INVESTITIE -------\n";
    out << "Suma initiala:    " << obj.sumaInitiala << " RON\n";
    out << "Rata dobanzii:   " << obj.rataDobanzii * 100 << "%\n";
    out << "Durata:          " << obj.luni << " luni\n";
    out << "---------------------------------\n";
    out << "Profit estimat:  " << obj.calculeazaProfit() << " RON\n";
    out << "Total final:     " << obj.getSumaFinala() << " RON\n";
    out << "---------------------------------\n";
    return out;
}

class BankAccount{
   public:
      BankAccount();
      BankAccount(int suma);
      BankAccount(const BankAccount& obj);
      BankAccount& operator=(const BankAccount& obj);

      friend std::ostream& operator<<(std::ostream& out, const BankAccount& obj);
      friend std::istream& operator>>(std::istream& in, BankAccount& obj);

      void depunereFonduri(int suma);
      void retragereFonduri(int suma);
      int getSold() const;
      int getID() const;
      void setSold(int val);
      void setID(int val);

   private:
      int sold;
      int accID;

};

BankAccount::BankAccount(){
   this->sold = 0;
   this->accID = rand()%1357;
}

BankAccount::BankAccount(int val){
   this->sold = val;
   this->accID = rand()%1357;   
}

BankAccount::BankAccount(const BankAccount& obj){
   this->sold = obj.sold;
   this->accID = obj.accID;
}

BankAccount& BankAccount::operator=(const BankAccount& obj){
   if(this != &obj){
      this->sold = obj.sold;
      this->accID = obj.accID;
   }
   return *this;
}

std::ostream& operator<<(std::ostream& out, const BankAccount& obj){
   out << "[Cont ID=" << obj.accID << "] Sold curent: " << obj.sold << " RON";
   return out;
}

std::istream& operator>>(std::istream& in, BankAccount& obj){
   std::cout << "Introduceti depozitul initial: ";
   in >> obj.sold;
   return in;
}

void BankAccount::depunereFonduri(int suma){
   this->sold += suma;
}

void BankAccount::retragereFonduri(int suma){
   if(suma <= this->sold){
      this->sold -= suma;
   }
   else{
      std::cout << "Fonduri insuficiente!\n";
   }
}

int BankAccount::getSold() const{
   return this->sold;
}

void BankAccount::setSold(int val){
   this->sold = val;
}

int BankAccount::getID() const{
   return this->accID;
}

void BankAccount::setID(int ID){
   this->accID = ID;
}


class Client{
public:

   static int numarClienti;

   BankAccount* conturi[5];
   int nrConturi;

   Client();
   Client(const char* nume, const char* prenume, long long CNP);
   Client(const char* nume, const char* prenume, char initialaTata, int dataNasterii, long long CNP);
   Client(const Client& obj);
   Client& operator=(const Client& obj);
   ~Client();


   //getteri la toate atributele pentru verificari de securitate
   char getInitialaTata() const;
   const char* getNume() const;
   long getID() const;
   long long getCNP() const;
   void afisareCompletaConturi();

   //Clientul isi poate schimba numele..
   void setName(const char* nume);

   friend std::ostream& operator<<(std::ostream& out, const Client& obj);
   friend std::istream& operator>>(std::istream& in, Client& obj);

private:
   char* nume;
   char* prenume;
   char initialaTata;
   int dataNasterii;
   long long CNP;
   long ID_client;
   bool informationComplete;
   
};

Client::Client(){
         this->nume = nullptr;
         this->prenume = nullptr;
         this->initialaTata = '\0';
         this->dataNasterii = 0;
         this->CNP = 0;
         this->ID_client = 0;
         this->informationComplete = false;
         nrConturi = 0;
         for(int i = 0; i < 5; i++) this->conturi[i] = nullptr;

}

Client::Client(const char* nume, const char* prenume, long long CNP){
      this->nume = new char[strlen(nume) + 1];
      strcpy(this->nume, nume);
      this->prenume = new char[strlen(prenume) + 1];
      strcpy(this->prenume, prenume);
      this->CNP = CNP;
      this->ID_client = CNP % 10000;
      this->informationComplete = false;
      conturi[0] = new BankAccount();
      nrConturi = 1;
}


Client::Client(const char* nume, const char* prenume, char initialaTata, int dataNasterii, long long CNP){
      this->nume = new char[strlen(nume) + 1];
      strcpy(this->nume, nume);
      this->prenume = new char[strlen(prenume) + 1];
      strcpy(this->prenume, prenume);
      this->initialaTata = initialaTata;
      this->dataNasterii = dataNasterii;
      this->CNP = CNP;
      this->ID_client = CNP % 10000;
      this->informationComplete = true;

      for(int i = 0; i < 5; i++)
         this->conturi[i] = nullptr;
      this->conturi[0] = new BankAccount();
      this->nrConturi = 1;
};

Client::Client(const Client& obj){
      this->nume = new char[strlen(obj.nume) + 1];
      strcpy(this->nume, obj.nume);
      this->prenume = new char[strlen(obj.prenume) + 1];
      strcpy(this->prenume, obj.prenume);
      this->initialaTata = obj.initialaTata;
      this->dataNasterii = obj.dataNasterii;
      this->CNP = obj.CNP;
      this->ID_client = obj.ID_client;
      this->informationComplete = obj.informationComplete;

      for(int i = 0; i < 5; i++) this->conturi[i] = nullptr;
      
      for (int i = 0; i < obj.nrConturi; i++) {
        this->conturi[i] = new BankAccount(*obj.conturi[i]);
    }
};

Client& Client::operator=(const Client& obj) {
      if (this != &obj) {
         delete[] this->nume;
         delete[] this->prenume;
         this->nume = new char[strlen(obj.nume) + 1];
         strcpy(this->nume, obj.nume);
         this->prenume = new char[strlen(obj.prenume) + 1];
         strcpy(this->prenume, obj.prenume);
         this->initialaTata = obj.initialaTata;
         this->dataNasterii = obj.dataNasterii;
         this->CNP = obj.CNP;
         this->ID_client = obj.ID_client;
         this->informationComplete = obj.informationComplete;
         this->nrConturi = obj.nrConturi;

         for (int i = 0; i < this->nrConturi; i++) {
             if(this->conturi[i] != nullptr){
               delete this->conturi[i];
               this->conturi[i] = nullptr; 
             }
        }

         for (int i = 0; i < obj.nrConturi; i++) {
            this->conturi[i] = new BankAccount(*obj.conturi[i]);
        }
      }
      return *this;
};

Client::~Client() {
      delete[] nume;
      delete[] prenume;
      for (int i = nrConturi-1; i >= 0; i--){
         delete conturi[i];
      }
};

char Client::getInitialaTata() const {
    return initialaTata;
}

const char* Client::getNume() const {
    return this->nume;
}

long Client::getID() const {
    return ID_client;
}

long long Client::getCNP() const {
    return CNP;
}

void Client::setName(const char* nume) {
    if (nume != nullptr) {
        delete[] this->nume;
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
    }
}

void Client::afisareCompletaConturi(){
   for (int i = 0; i < nrConturi; i++){
      std:: cout << *conturi[i] << std::endl;
   }
}

std::ostream& operator<<(std::ostream& out, const Client& obj) {
   out << "Date Client:\n";
   out << "ID: " << obj.ID_client << "\n";
   out << "CNP: " << obj.CNP << "\n";
   out << "Nume: " << obj.nume << " " << obj.initialaTata << " " << obj.prenume << "\n";
   out << "Data Nasterii: " << obj.dataNasterii << "\n";
   return out;
}

std::istream& operator>>(std::istream& in, Client& obj) {
   char buffer[100];
   std::cout << "Nume: ";
   in.getline(buffer, 100);
   obj.setName(buffer);
   return in;
}

int Client::numarClienti = 0;

class Menu{
public:
  
   void run();

private:

   Client listaClienti[30];

   int actiuneConectat(Client* cln);
   void afisareMeniuConectat(const char* nume, const int id);
   void afisareMeniuPrincipal();
   Client* verificareClient();
   Client* creareCont();
   void afisareFAQ();
};

void Menu::run(){
   afisareMeniuPrincipal();
   while(true){
      Sleep(500);
      if(_kbhit()){
         char optiune = _getch();
         switch(optiune){
            case '1': {
               Client* cln = verificareClient();
               if(cln != nullptr){
                  system("cls");
                  int next = actiuneConectat(cln);
                  if (next == 1)
                     return;
                  afisareMeniuPrincipal();
                  break;
               }
               else{
                  std::cout << "Acest cont nu exista.\n";
                  Sleep(2500);
                  system("cls");
                  afisareMeniuPrincipal();
               }
               break;
            }
            case '2': {
               system("cls");
               Client *cln = creareCont();
               Sleep(2500);
               system("cls");
               int next = actiuneConectat(cln);
               if (next == 1)
                  return;
               system("cls");
               afisareMeniuPrincipal();
               break;
            }
            case '3': {
               afisareFAQ();
               afisareMeniuPrincipal();
               break;
            }
            case '4': {
               std::cout << "La revedere!\n";
               Sleep(4000);
               return;
            }
         }
      }
   }
}

void Menu::afisareMeniuConectat(const char* nume, const int id){
   std::cout << "Bine ati venit, Dl./Dna. " << nume << "(Client ID: " << id << ")!\n";
   std::cout << "1. Vizualizare completa conturi:\n";
   std::cout << "2. Depunere fonduri\n";
   std::cout << "3. Retragere fonduri\n";
   std::cout << "4. Simulare investitii\n";
   std::cout << "5. Deschideti un cont bancar nou\n";
   std::cout << "6. Deconectare.\n";
   std::cout << "7. Inchidere aplicatie.\n";
}

int Menu::actiuneConectat(Client* cln) {
   while(true){

      std::cout<< "\033[?25l";
      std::cout<< "\033[H";
      afisareMeniuConectat(cln->getNume(), cln->getID());
      Sleep(500);
      if(_kbhit()){
         char optiune = _getch();
         switch(optiune){
            case '1': {
               system("cls");
               std::cout << "Conturile dvs.: (Vizibile pentru 10 secunde)\n";
               cln->afisareCompletaConturi();
               Sleep(13000);
               system("cls");
               break;
            }
            case '2': {
               system("cls");
               std::cout << "Depunere fonduri:\n";
               std::cout << "Selectati contul in care doriti sa depuneti fonduri:\n";
               for (int i = 0; i < cln->nrConturi; i++){
                  std::cout << "Cont: " << i+1<< " . ID: " << cln->conturi[i]->getID() << std::endl;
               }
               int optiuneCont, suma;
               std::cin >> optiuneCont;
               BankAccount* contSelectat = cln->conturi[optiuneCont-1];
               std::cout << "Introduceti suma pe care doriti sa o depuneti (in lei):\n";
               std::cin >> suma;
               contSelectat->depunereFonduri(suma);
               std::cout<<"Gata";
               Sleep(3000);
               system("cls");
               break;
            }
            case '3': {
               system("cls");
               std::cout << "Retragere fonduri:\n";
               std::cout << "Selectati contul din care doriti sa retrageti fonduri:\n";
               for (int i = 0; i < cln->nrConturi; i++){
                  std::cout << "Cont: " << i+1<< " . ID: " << cln->conturi[i]->getID() << std::endl;
               }
               int optiuneCont, suma;
               std::cin >> optiuneCont;
               BankAccount* contSelectat = cln->conturi[optiuneCont-1];
               std::cout << "Introduceti suma pe care doriti sa o retrageti (in lei):\n";
               std::cin >> suma;
               contSelectat->retragereFonduri(suma);
               std::cout<<"Gata";
               Sleep(3000);
               system("cls");
               break;
            }
            case '4':{
               system("cls");
               double s,r;
               int l;

               std::cout << "~~~Pagina de simulare investitii~~~\n";
               std::cout << "-----------------------Informatii-Importante---------------------------" << std::endl;
               std::cout << "| Dobanda anuala estimata (Index Fund - S&P 500)          |    10.0%  |" << std::endl;
               std::cout << "| Ajustat la inflatia dolarului (Profit Real)             |     7.0%  |" << std::endl;
               std::cout << "| Depozit la termen optim in lei (RON)                    |   > 5.5%  |" << std::endl;
               std::cout << "-----------------------------------------------------------------------" << std::endl;
               std::cout << "Suma de investit (RON): ";
               std::cin >> s;
               std::cout << "Rata dobanzii anuale (scrieti 7 pentru 7%): "; 
               std::cin >> r;
               std::cout << "Perioada (in luni): ";
               std::cin >> l;

               Investment simulare(s, r / 100.0, l);

               std::cout << simulare;

               Sleep(10000);
               system("cls");
               break;
            }
            case '5':{
               //newbankacc
               system("cls");
               if(cln->nrConturi < 5){
                  std::cout << "Daca doriti un depozit initial, scrieti suma pe care o doriti depozitata: ";
                  int suma_initiala = 0;
                  std::cin >> suma_initiala;
                  if(suma_initiala != 0){
                     cln->conturi[cln->nrConturi] = new BankAccount(suma_initiala);
                     
                  }
                  else{
                     cln->conturi[cln->nrConturi] = new BankAccount();
                  }
                  cln->nrConturi++;
                  std::cout << "\nFelicitari. Cont creat. ID cont nou: " << cln->conturi[cln->nrConturi-1]->getID();
               }
               else{
                  std::cout<<"Ati atins numarul maxim de conturi bancare deschise.";
               }
               Sleep(4500);
               system("cls");
               break;
            }
            case '6':{
               system("cls");
               return 0;
            }
            case '7':{
               return 1;
            }
            default:{
               break;
            }
         }
      }
   }
}

void Menu::afisareMeniuPrincipal() {
   std::cout<<"-----Optiuni disponibile-----\n";
   std::cout << "1. Conectare la contul dvs.\n";
   std::cout << "2. Creati-va un cont\n";
   std::cout << "3. FAQ\n";
   std::cout << "4. Iesire\n";
}

Client* Menu::verificareClient(){
      system("cls");

      if (std::cin.peek() == '\n' || std::cin.peek() == '\r') {
          std::cin.ignore();
      }

      char buffer[20] = "";
      while(strlen(buffer) != 13){
         std::cout << "Introduceti CNP-ul (13 cifre): \n";
         std::cin.getline(buffer, 20);
      }
      long long CNP_cautat = atoll(buffer);
      for(int i = 0; i < Client::numarClienti; i++){
         if(listaClienti[i].getCNP() == CNP_cautat){
            return &listaClienti[i];
         }
      }
      return nullptr;
   }

Client* Menu::creareCont(){
      char nume[50], prenume[50], initialaTata;
      int dataNasterii;
      long long CNP = 0;


      std::cout << "Nume: \n";
      std::cin.getline(nume, 50);
      std::cout << "Prenume: \n";
      std::cin.getline(prenume, 50);
      std::cout << "Initiala tatalui: \n";
      std::cin >> initialaTata;
      std::cout << "Data nasterii (format: YYYYMMDD): \n";
      std::cin >> dataNasterii;
      while(CNP <= 1000000000000 || CNP >= 9999999999999){
         std::cout << "Introduceti un CNP valid (13 cifre): \n";
         std::cin >> CNP;
      }
      std::cin.ignore();

      Sleep(1000);
      Client temp(nume, prenume, initialaTata, dataNasterii, CNP);
      listaClienti[Client::numarClienti] = temp;
      Client::numarClienti++;
      Sleep(1000);
      std::cout << "Cont creat! ID-ul dvs. este: " << temp.getID() << "\n";

      return &listaClienti[Client::numarClienti - 1];
   }

void Menu::afisareFAQ(){
      system("cls");
      std::cout << "FAQ:\n";
      std::cout << "1. Cum imi pot schimba parola?\n";
      std::cout << "Din pacate, din cauza mai multor incercari de frauda, pentru a va schimba parola este necesar sa va prezentati la sediul nostru cu un act de identitate.\n";
      std::cout << "2. Cum pot sa imi sterg contul?\n";
      std::cout << "Pentru a va sterge contul, va rugam sa ne contactati sau sa va prezentati la sediul nostru, pentru a efectua retragerea fondurilor.\n";
      std::cout << "3. Cum pot sa accesez modulul de investitii?\n";
      std::cout << "Pentru a accesa modulul de investitii, trebuie sa fiti conectat la contul dvs. si sa aveti informatiile complete. Meniul pentru utilizator conectat va pune la dispozitie optiunea de a face simulari de investitii sau de a investi.\n";
      std::cout << "4. Cum se numeste aceasta banca?\n";
      std::cout << "Banca.\n\n";
      
      Sleep(15000);
      system("cls");
      return;
}

int main() {
   Menu menu;
   menu.run();
   return 0;
}