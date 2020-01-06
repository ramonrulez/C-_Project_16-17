#include <iostream>
#include <string>
#include <list>

using namespace std;

#include "class_prototypes.h"
#include "Reservation.h"
#include "Rooms.h"
#include "Hotel.h"
#include "my_functions.h"

#define res_loops 5 //in the begining of the program how much reservations will be generated
#define c_prob (100/50) //probability of cancellation (100/the probability that is wanted)

//pools of characters to generate the reservation's name
static const char pool[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int poolsize= sizeof(pool)-1;

//this function will return an uppercase random characters
char get_random_char() {
     return pool[rand() % poolsize];
};

//this loop gives a full name
string name_loop(int &passlength) {
     string name;
     for (int i = 1; i < passlength; i++) {
          name+= get_random_char();
     };
     return name;
};

//this function gives a random name of random length
string get_name() {
     int passlengthF= 5 + rand() % 12 ;//length of a first name between 5-16 characters
     int passlengthL= 5 + rand() % 21 ;//length of a last name between 5-20 characters
     string name;
     //generate a name with passlength characters
     name= name_loop(passlengthF);//first name
     name+= " ";
     name+= name_loop(passlengthL);//last name
     return name;
};

//Random generation of a reservation
void res_gen(Hotel &the_hotel) {
     string name=get_name();
     int arriV=1 + rand() % 30;//random choise for arrival date (1-30)
     int set=30-arriV;
     int accoM= 1+ rand()% (set+1);//random choise accomodation days (arriV-30)
     int peopleSum=rand() % 10+1;//random people sum of reservation (1-10)//max capacity of a room is 8
     Reservation *res= new Reservation(name,arriV,accoM,peopleSum);
     the_hotel.add_reserv(*res);
};

//probability of cancellation of reservation and the cancellation
void res_cancel(Hotel &the_hotel) {
     int cancelProb= 1 + rand() % c_prob;//cancel probability is a random number 1-4 (1/4=25%)
     //cancellation if cancelProb=1
     int sum=0;
     int elemCode=0;
     if (cancelProb==1) {
          //the sum of all the reservations
          for (auto a : the_hotel.reservations){
               sum++;
          }
          int randResv= 1 + rand() % sum;//random reservation from the list
          //for finding the exast reservation code of the chosen reservation
          for (auto b : (the_hotel.reservations)){
               randResv--;
               if (randResv==0){
                    elemCode=b->get_rescode();
                    break;
               }
          }
          the_hotel.cancel_reserv(elemCode);
     }

};

int main() {

//Hotel initializatin
     Hotel hotel_1("GORINTHOS PALACE");//create a new hotel
     Hotel* hotel_ptr= &hotel_1;//here you set the hotel_ptr(the pointer witch you use in main)

//10 Rooms initialization
     //Room ( maximum capacity, price per person)
     Room r_1(3,20);
     Room r_2(4,15);
     // RoomA ( maximum capacity, price per day)
     RoomA r_A1(3,36);
     RoomA r_A2(4,48);
     //RoomB ( maximum capacity, price per day, discount per day)
     RoomB r_B1(8,65,10);
     RoomB r_B2(10,100,13);
     //RoomC ( minimum capacity, maximum capacity, minimum days, cost per person)
     RoomC r_C1(4,8,2,50);
     RoomC r_C2(5,10,3,65);
     //RoomD ( minimum capacity, maximum capacity, minimum days, cost per person, discount)
     RoomD r_D1(3,6,3,30,10);
     //RoomE (cost per day)
     RoomE r_E1(100);

//adding the rooms to the hotel
     hotel_ptr->add_room(r_1);
     hotel_ptr->add_room(r_2);
     hotel_ptr->add_room(r_A1);
     hotel_ptr->add_room(r_A2);
     hotel_ptr->add_room(r_B1);
     hotel_ptr->add_room(r_B2);
     hotel_ptr->add_room(r_C1);
     hotel_ptr->add_room(r_C2);
     hotel_ptr->add_room(r_D1);
     hotel_ptr->add_room(r_E1);

//loop for adding some reservations in the hotel
     for (int i = 0; i < res_loops; i++) {
          res_gen(*hotel_ptr);
     }

     string choise_input ;//input of the menu
     bool menu_state= true ;//bool check the menu loop
//menu
     while ( menu_state!= false ) {
          cout<< "o---------------------------------"<< endl;
          cout<< "|  1. Επόμενη Επανάληψη"<< endl;
          cout<< "|  2. Προσθήκη Κράτησης"<< endl;
          cout<< "|  3. Ακύρωση Κράτησης"<< endl;
          cout<< "|  4. Προβολή Κρατήσεων"<< endl;
          cout<< "|  5. Προβολή Δωματίου"<< endl;
          cout<< "|  6. Προβολή Πλάνου Κρατήσεων"<< endl;
          cout<< "|  7. Προβολή Εσόδων"<< endl;
          cout<< "|  8. Τερματισμός"<< endl;
          cout<< "o---------------------------------"<< endl;
          cout<< "Επιλέξτε κάτι από τα παραπάνω:" ;

          getline(cin,choise_input);//take input
          int choise=atoi(choise_input.c_str());//if is int saved in choise else choise=0

          switch (choise) {
          //next loop
               case 1: {//OK
                    res_gen(*hotel_ptr);
                    res_cancel(*hotel_ptr);
                    break;}
          //add reservation
               case 2: {//OK
                    string input;//input string
                    //bool ok=false;//check for the whole reservation loop

                    do {
                    //name initialization
                         cout<< "Δώστε όνομα: ";
                         getline(cin, input);
                         string name= input;//name initialization without check
                    //arrival day initialization
                         int arr_day;
                         do {
                              cout<< "Δώστε ημέρα άφιξης(1-30): ";
                              getline(cin, input);
                              arr_day=atoi(input.c_str());
                         } while(!(arr_day>0 && arr_day<=30));
                    //accomodation days initialization
                         int acc_days;
                         do {
                              cout<< "Δώστε ημέρες διαμονής(1-30): ";
                              getline(cin, input);
                              acc_days=atoi(input.c_str());
                         } while(!(acc_days>0 && acc_days<=(30-arr_day+1)));
                    //people sum initialization
                         int people;
                         do {
                              cout<< "Δώστε άτομα: ";
                              getline(cin, input);
                              people=atoi(input.c_str());
                         } while(!(people>0));
                    //establishing the reservation
                         cout<< "Όνομα πελατη: "<< name << " Ημέρα άφιξης: "<< arr_day << " Ημέρες διαμονής: "<< acc_days << " Άτομα: "<< people << endl;
                         cout<< "Θέλετε να κατοχυρώσετε την παραπάνω κράτηση(ENTER για κράτηση)(άλλο για ακύρωση): " ;
                         getline(cin, input);
                    //add reservation
                         if (input.empty()) {
                              Reservation *res = new Reservation (name, arr_day, acc_days, people);
                              do {
                                   cout<< "Θέλετε να κάνετε κράτηση σε συγκεκριμένο δωμάτιο; (ΝΑΙ->δώστε κωδικό δωματίου)(ΟΧΙ->πατήστε ENTER): ";
                                   getline(cin, input);
                                   int room=atoi(input.c_str());
                                   //add reservation without specific room
                                   if (input.empty()) {
                                        hotel_ptr->add_reserv(*res);
                                        break;
                                   //add reservation in a specific room
                                   } else {
                                        if (room> 100 && room<= Room::r_counter) {
                                             hotel_ptr->add_reserv_to_code(*res, room);
                                             break;
                                        } else {
                                             cout<< "Προσπαθήστε να μην πατάτε τυχαία κουμπιά!"<< endl;
                                        }
                                   }
                              } while(1);
                              break;
                         } else {
                              break;
                         }
                    } while (1);

                    break;}
          //cancel reservation
               case 3: {//OK
                    string resv_input;
                    while (1) {//LOOPS TO INFINITY
                         cout<< "Παρακαλώ δώστε τον κωδικό κράτησης: ";
                         getline(cin,resv_input);
                         int res_choise=atoi(resv_input.c_str());
                         if (res_choise>0 && res_choise<=Reservation::res_counter) {
                              hotel_ptr->cancel_reserv(res_choise);
                              break;
                         } else
                              cout<< "Προσπαθήστε περισσότερο! ";
                    }
                    break;}
          //see reservations
               case 4: {//OK
                    for (auto res: hotel_ptr->reservations) {
                         cout<< "Κωδικός Κράτησης: "<< res->get_rescode()<< " | 'Ονομα Πελάτη: "<< res->get_name()<< " | Κωδικός Δωματίου: "<< res->get_room()<< endl;
                    }
                    break;}
          //see rooms
               case 5: {//OK
                    for (auto roo: hotel_ptr->rooms) {
                         cout<< "Κωδικός Δωμαίου: "<< roo->get_roomcode()<< " | Πληρότητα: "<< roo->occupancy()<< "%" << " | Έσοδα: "<< roo->pricing()<< " ευρώ"<< endl;
                    }
                    break;}
          //see hotel plan
               case 6: {//OK
                    hotel_ptr->reserv_plan();
                    break;}
          //see earnings
               case 7: {//OK
                    string room_input;//input string
                    while (1) {//LOOPS TO INFINITY
                         cout<< "Δώστε κωδικό δωματίου ή αλλίώς πατήστε ENTER: ";
                         getline(cin,room_input);//take input
                         int room_choise=atoi(room_input.c_str());//if is int saved in room_choise

                         if (room_input.empty()) {//check if string is empty (just pressed ENTER)
                              cout<< "Τα συνολικά έσοδα είναι: "<< hotel_ptr->earning_calculation()<< " ευρώ!"<< endl;
                              break;
                         } else {//if the string is not empty is int or a string
                              if (room_choise> 100 && room_choise<= Room::r_counter) {
                                   cout<< "Τα έσοδα του δωματίου "<< room_choise<< " είναι "<< hotel_ptr->earning_calculation(room_choise)<< " ευρώ!"<< endl;
                                   break;

                              } else if (room_choise== 0) {//the conversion from string to int gives 0 if the input is not int
                                   cout<< "Προσπαθήστε να μην πατάτε τυχαία κουμπιά!"<< endl;

                              } else if (room_choise<=100 || room_choise>Room::r_counter) {
                                   cout<< "Δεν υπάρχει τέτοιος κωδικός δωματίου!"<< endl;

                              }
                         }


                    }
                    break;}
          //exit
               case 8: {//EXIT     //OK
                    menu_state= false;
                    break;}
          //not relevant input
               default: {//other inputs than 1-8  //OK
                    cout<< endl<< "Προσπαθήστε ξανά!"<< endl;
                    break;}

          }
     }
     return 0;

};
