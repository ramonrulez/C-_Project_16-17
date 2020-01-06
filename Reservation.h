class Reservation {//this class represents a reservation to a hotel

     friend class Room ;
     friend class RoomA ;
     friend class RoomB ;
     friend class RoomC ;
     friend class RoomD ;
     friend class RoomE ;
     friend class Hotel ;


     protected:
          string costumer_name ;
          int reserv_code, arrival, accom_days, p_sum ;
          Room *room= {NULL} ;

     public:
          static int res_counter ; //counter for the unique reservations id

          Reservation(string cosname, int arr, int days, int sum )
               : costumer_name(cosname),arrival(arr),
               accom_days(days), p_sum(sum)
               {reserv_code= ++res_counter ;//generate a unique for an object class Reservation
               cout<< "Η Κράτηση "<< reserv_code<<" έγινε από τον πελάτη "<<cosname
               <<" και αφορά "<< sum<<" άτομα που φτάνουν στίς "<< arr<<" του μήνα και θα μείνουν "
               << days<<" μέρες δηλαδή από τις "<<arr <<" μέχρι και τις "<<(arr+days)-1
               <<" του μήνα."<<endl;
               }

          //method which takes an Room object and assign it to room variable
          void room_to_resv( Room &room_obj) {
               room= &room_obj ;//room pointing in the Room class object
          };

//MY FUNCTIONS------------------------------------------------------------------

          int get_rescode();//returnes the reservation code

          string get_name();//returnes the name of the reservation

          int get_room();//returns the room pointer

};

//static counter initialization for unique reservation id
int Reservation::res_counter= 0 ;
