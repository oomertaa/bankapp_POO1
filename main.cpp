#include <iostream>
#include <cstring>
#include <windows.h>
#include <conio.h>


class Client{
public:

   static int numarClienti;

   Client(){
         this->nume = nullptr;
         this->prenume = nullptr;
         this->initialaTata = '\0';
         this->dataNasterii = 0;
         this->CNP = 0;
         this->ID_client = 0;
         this->informationComplete = false;
   }

   Client(const char* nume, const char* prenume, long long CNP){
      this->nume = new char[strlen(nume) + 1];
      strcpy(this->nume, nume);
      this->prenume = new char[strlen(prenume) + 1];
      strcpy(this->prenume, prenume);
      this->CNP = CNP;
      this->ID_client = CNP % 10000;
      this->informationComplete = false;
   }

   Client(const char* nume, const char* prenume, char initialaTata, int dataNasterii, long long CNP){
      this->nume = new char[strlen(nume) + 1];
      strcpy(this->nume, nume);
      this->prenume = new char[strlen(prenume) + 1];
      strcpy(this->prenume, prenume);
      this->initialaTata = initialaTata;
      this->dataNasterii = dataNasterii;
      this->CNP = CNP;
      this->ID_client = CNP % 10000;
      this->informationComplete = true;
   };

   Client(const Client& obj){
      this->nume = new char[strlen(obj.nume) + 1];
      strcpy(this->nume, obj.nume);
      this->prenume = new char[strlen(obj.prenume) + 1];
      strcpy(this->prenume, obj.prenume);
      this->initialaTata = obj.initialaTata;
      this->dataNasterii = obj.dataNasterii;
      this->CNP = obj.CNP;
      this->ID_client = obj.ID_client;
      this->informationComplete = obj.informationComplete;
   };

   Client& operator=(const Client& obj) {
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
      }
      return *this;
   };

   ~Client() {
      delete[] nume;
      delete[] prenume;
   };


   //getteri la toate atributele pentru verificari de securitate
   char getInitialaTata() const {
      return initialaTata;
   };

   const char* getNume() const { 
      return this->nume;
   }

   long getID() const{
      return ID_client;
   };

   long long getCNP() const {
      return CNP;
   };

   //Clientul isi poate schimba numele..
   void setName(char* nume) {
      delete[] this->nume;
      this-> nume = new char[strlen(nume) + 1];
      strcpy(this->nume, nume);
   }

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

class Menu{
public:

   void run(){
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
                     actiuneConectat(cln);
                     return;
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
                  actiuneConectat(cln);
                  break;
               }
               case '3': {
                  afisareFAQ();
                  break;
               }
               case '4': {
                  std::cout << "La revedere!\n";
                  // localstorage
                  Sleep(4000);
                  return;
               }
            }
         }
      }
   }

private:

   Client listaClienti[30];


   void actiuneConectat(Client* cln) {

      std::cout << "Bine ati venit, Dl./Dna. " << cln->getNume() << "(Client ID: " << cln->getID() << ")!\n";
   }

   void afisareMeniuPrincipal() {
      std::cout<<"-----Optiuni disponibile-----\n";
      std::cout << "1. Conectare la contul dvs.\n";
      std::cout << "2. Creati-va un cont\n";
      std::cout << "3. FAQ\n";
      std::cout << "4. Iesire\n";
      }

   Client* verificareClient(){
      system("cls");
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

   Client* creareCont(){
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

      Client temp(nume, prenume, initialaTata, dataNasterii, CNP);
      listaClienti[Client::numarClienti] = temp;
      Client::numarClienti++;

      std::cout << "Cont creat! ID-ul dvs. este: " << temp.getID() << "\n";

      return &listaClienti[Client::numarClienti - 1];
   }

   void afisareFAQ(){
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
      std::cout << "Apasati orice tasta pentru a reveni la meniul principal.\n";
      while(true){
         if(_kbhit()){
            char optiune = _getch();
            if(optiune){
               system("cls");
               run();
               return;
            }
         }
      }

   }
};

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

int main() {
   Menu menu;
   menu.run();
   return 0;
}