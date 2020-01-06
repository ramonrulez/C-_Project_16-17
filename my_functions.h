//class Reservation functions

//returnes the room of the reservation
int Reservation::get_room() {
     return room->get_roomcode();
};

//returnes the reservation code
int Reservation::get_rescode() {
     return reserv_code;
};

//returnes the name of the reservation
string Reservation::get_name() {
     return costumer_name;
};

//class Room functions----------------------------------------------------------

//returnes the room code
int Room::get_roomcode() {
     return room_code;
};

//class Hotel functions---------------------------------------------------------

//function that returnes a pointer type Room if the room is in the list of the hotel
Room* Hotel::code_list_search(list<Room*> list, int room_code) {
     Room* found= NULL ;
     for (auto k:list) {
          if (k->room_code==room_code) {
               found= k ;
               break ;
          }
     }
     return found ;
};

//function that returnes a pointer type Reservation if the reservation is in the list of the hotel
Reservation* Hotel::code_list_search(list<Reservation*> list, int resv_code) {
     Reservation* found= NULL ;
     for (auto k:list) {
          if (k->reserv_code==resv_code) {
               found= k ;
               break ;
          }
     }
     return found ;
};
