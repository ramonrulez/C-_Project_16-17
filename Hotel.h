class Hotel {// this class represents a hotel

     //friend functions of Hotel to use it's members
     friend int main();
     friend void res_cancel(Hotel&);

     protected:
          string hotel_name ;
          list<Room*> rooms ;//list of rooms in a specific Hotel object
          list<Reservation*> reservations ;//list of reservations in a specific Hotel object

     public:
          Hotel(string hotname): hotel_name(hotname) {} ;

          //adding a room in the hotel
          void add_room(Room &room_obj) {
               Room* found= code_list_search(rooms, room_obj.room_code) ;//check the list for the room
               //if the room is there
               if (found!= NULL) {
                    cout << "Το δωμάτιο "<< room_obj.room_code<<" υπάρχει ήδη!" << endl ;
               }
               //if it isn't add it in the list
               else {
                    rooms.push_back(&room_obj);
                    cout << "Το δωμάτιο "<< room_obj.room_code<<" προστέθηκε επιτυχώς!" << endl ;
               }

          };

          //find a room from the Room list
          Room* retrieve_room_from_code(int &room_code) {
               Room* found= code_list_search(rooms, room_code) ;//check the list for the room
               //if the room is there return the Room*
               if (found!= NULL) {
                    cout<< "Το δωμάτιο "<< room_code<< " υπάρχει!"<< endl ;
                    return found ;
               }
               //if it isn't return NULL
               else {
                    cout<< "Το δωμάτιο "<< room_code<< " δεν υπάρχει!"<< endl ;
                    return NULL ;
               }

          };

          //find a reservation from the Reservation list
          Reservation* retrieve_reserv_from_code(int &resv_code) {
               Reservation* found= code_list_search(reservations, resv_code) ;//check the list for the reservation
               //if the room is there return the Reservation*
               if (found!= NULL) {
                    cout<< "Η κράτηση "<< resv_code<< " υπάρχει!"<< endl ;
                    return found ;
               }
               //if it isn't return NULL
               else {
                    cout<< "Η κράτηση "<< resv_code<< " δεν υπάρχει!"<< endl ;
                    return NULL ;
               }
          };

          //add a reservations to a specific room
          bool add_reserv_to_code(Reservation &resv_obj, int &room_code) {
               bool resv_ok= false ;//to check if the reservation CAN be assigned in the room
               bool found= false ;//check if the reservation is allready in the list
               Room* room_point= retrieve_room_from_code(room_code) ;//check the list for the room
               //if the room IS in the list
               if (room_point != NULL) {
                    found= code_list_search(reservations, resv_obj.reserv_code) ;//check if the reservation is in the list
               //if the room ISN'T in the list
               }else{
                    cout<< "Δεν υπάρχει το δωμάτιο "<< room_code<< " !"<< endl;
               }
               resv_ok= room_point->add_reservation(resv_obj) ;//if the reservation can be assigned in the room this will return TRUE
               //if the reservation isn't in the list
               if (found== false) {
                    //if the reservation can be assigned
                    if (resv_ok== true) {//assign it
                         reservations.push_back(&resv_obj);//add reservation to the list
                         resv_obj.room=code_list_search(rooms,room_code);//add Room* to reservation's room variable
                         cout << "H κράτηση "<< resv_obj.reserv_code<< " έγινε με επιτυχία στο δωμάτιο "<< room_code<< "!"<< endl ;
                         return true ;//reservation done
                    }
                    //if reservation can't be assigned
                    else return false;
               //if the reservation is already in the list
               }else{
                    cout << "H κράτηση "<< resv_obj.reserv_code<< " υπάρχει ήδη!" << endl ;
                    return false ;
               }

          };

          //add a reservation to any room
          int add_reserv(Reservation &resv_obj) {
               bool done= false ; //to chech if the reservation has made
               int r_code= 0 ;
               for (auto r: rooms) {//run add_reserv_to_code function for every room
                    done= add_reserv_to_code(resv_obj, r->room_code);//try to do the reservation
                    if (done==true) {//the first room that the reservation can be done
                         r_code= r->room_code;//return code
                         break;
                    }
               }
               //if the reservation done
               if (done== true) {
                    return r_code ;
               //if the reservation ISN't done
               }else{
                    return 0 ;
               }



          };

          //cancel a reservation
          void cancel_reserv(int &resv_code) {
               Reservation* resv= NULL;//reservation pointer to aquire room
               bool done= false ;//to chech if the reservation is canceled
               //if there is this reservation in the list
               resv= retrieve_reserv_from_code(resv_code) ;//retrieve the reservation
               if (resv!= NULL) {
                    done= resv->room->cancel(resv_code);//cancel the reservation from the room
               }
               //if you cancel the reservation from the room
               if (done== true) {
                    reservations.remove(resv);//remove reservation from the list
                    cout<< "Η κράτηση "<< resv_code<< " διαγράφηκε με επιτυχία!"<< endl ;
               }
               //if there in no reservation
               else
                    cout<< "Η κράτηση "<< resv_code<< " δεν μπορεί να διαγραφεί!"<< endl ;

          };

          //calculate the earnings of a room
          double earning_calculation(int &room_code) {
               Room* room_obj= retrieve_room_from_code(room_code);
               return room_obj->pricing();
          };

          //calculate the earnings of the hotel
          double earning_calculation() {
               double sum= 0;
               for (auto i: rooms) {//for all the rooms
                    sum+= earning_calculation(i->room_code);
               }
          };

          //print the reservation plan of the hotel
          void reserv_plan() {
               cout<< "ROOM |" ;
               for (size_t i = 1; i < 31; i++) {
                    if (i< 10)
                         cout<< "0"<< i << "|" ;
                    else
                         cout<< i << "|" ;
               }
               cout<< endl ;
               for (auto l: rooms) {
                    cout<< l->room_code << "  |" ;
                    for (size_t j = 0; j < 30; j++) {
                         if (l->avail_board[j]== NULL)
                              cout<< "~ |" ;
                         else
                              cout<< "o |" ;
                    }
                    cout<< endl ;
               }
          };


//-------MY FUNCTIONS-----------------------------------------------------------

          //function that returnes a pointer type Room if the room is in the list of the hotel
          Room* code_list_search(list<Room*>, int);

          //function that returnes a pointer type Reservation if the reservation is in the list of the hotel
          Reservation* code_list_search(list<Reservation*>, int);

};
