#include <iostream>
#include <cstring>
#include <windows.h>


class Client{
public:

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

int main() {
   return 0;
}