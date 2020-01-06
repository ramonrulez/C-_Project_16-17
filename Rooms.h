class Room {//this class represents a room of a hotel

     friend class Hotel ;
     friend class Reservation ;

     protected:
          int room_code, max_capacity  ;//room_code > 100
          Reservation *avail_board[30] = {NULL} ;
          double cost_person ;

     public:
          static int r_counter ;//counter for the unique room code

          Room(int max_cap, double cost_p )
               : max_capacity(max_cap), cost_person(cost_p)
               {room_code= ++r_counter ;}

          //function for adding a Reservation odject into a Room object
          virtual bool add_reservation( Reservation &res_obj) {
               bool ok= true ;//bool variable to check if every day that we want the room is clear
               //check if the Room object have enought capacity for the people in the Reservation object
               if (res_obj.p_sum<= this->max_capacity) {
                    for (size_t i= res_obj.arrival-1; i< (res_obj.arrival-1)+res_obj.accom_days; i++) {
                         if (this->avail_board[i]!= 0) {//check if the availibility board of the Room obj isn't empty in the specific days of the reservation
                              ok= false ;
                         }
                    }
                    //if the days that the Reservation obj needs are available in the Room obj
                    if (ok== true) {
                         for (size_t i= res_obj.arrival-1; i< (res_obj.arrival-1)+res_obj.accom_days; i++) {
                              this->avail_board[i]= &res_obj ;//assign in these days the Reservation obj
                         }
                    }
                    //the Room obj is NOT available for these days
                    else {
                    cout << "Το δωμάτιο "<< this->room_code<<" δεν είναι διαθέσιμο γι' αυτές τις μέρες!" << endl ;
                    }
               }
               //if the room can't handle the bigger number of people of the reservation
               else {
                    cout << "Τα άτομα της κράτησης "<< res_obj.reserv_code<< " ξεπερνούν την  μέγιστη χωρητικότητα του δωματίου "<< this->room_code<< "!" << endl ;
                    ok= false ;
               }

               //the room pointer of the reservation object points into the room that this reservation assigned
               if (ok== true) {
                    res_obj.room_to_resv(*this);
                    return true ;
               }
               else return false ;

          };

          //function that represents the overall earnings of tha particular Room obj
          virtual double pricing() {
               double sum= 0 ;
               for (int i = 0; i < 30; i++) {
                    if (this->avail_board[i]!= NULL) {
                         sum+= (this->avail_board[i]->p_sum*cost_person) ;
                    }
               }
               return sum ;

          };

          //function to cancel a Reservation obj
          virtual bool cancel(int &resv_code) {
               bool ok= false ;//boolean variable to check if there is the reservation in the room
               //check every day if the reservation is there
               for (int i= 0; i< 30; i++) {
                    if (this->avail_board[i]!= NULL) {
                         if (resv_code== this->avail_board[i]->reserv_code) {
                              this->avail_board[i]= {NULL};
                              ok= true ;
                         }
                         else
                              break ;
                    }
               }
               if (ok== false) {//if there isn't the reservation there
                    cout << "Δεν υπάρχει η κράτηση "<< resv_code<< " στο δωμάτιο "<< this->room_code << endl ;
                    return false ;
               }
               else return true ;
          };

          //function that returnes how full is the Room obj (in %)
          int occupancy() {
               int count= 0;
               for (int i = 0; i < 30; i++) {
                    if (avail_board[i]!=NULL) {
                         count++ ;
                    }
               }
               return {(count*100)/30} ;
          };

//MY FUNCTIONS------------------------------------------------------------------


          int get_roomcode();//returnes the room code

};


class RoomA: public Room {//subclass of the Room class

     protected:
          double cost_per_day ;

     public:
          RoomA(int max_cap, double cost_p_d, double cost_p= 0)
               : Room(max_cap, cost_p) {
                    cost_per_day= cost_p_d ;
               }

          //function that overwrites the same function of the Room
          double pricing() {
               double sum= 0;
               for (int i= 0; i < 30; i++) {
                    if (this->avail_board[i]!= NULL) {
                         sum+= cost_per_day ;
                    }
               }
               return sum ;
          };

};


class RoomB: public RoomA {//subclass of the RoomA class

     protected:
          double discount_per_day ;// (%)

     public:
          RoomB(int max_cap, double cost_p_d, double disc_p_d, double cost_p= 0)
               : RoomA(max_cap, cost_p_d, cost_p) {
                    discount_per_day=disc_p_d;
               }

          //function that overwrites the same function of the Room
          double pricing() {
               double sum= 0 ;//the sum of price for all the reservation in this room
               int day= 0 ;//days that the room is used from a particular reservation
               int r_search= 0 ;//reservation code to check if two different day's reservation are the same or not
               double discount= 0 ;//all the discount in a day of a particular reservation
               for (int i= 0; i< 30; i++) {
                    //check if the availibility board isn't empty
                    if (this->avail_board[i]!= NULL) {
                         //check if the saved reservation is the same as the reservation on the board
                         if (r_search!= this->avail_board[i]->reserv_code)  {
                              day= 0 ;//initialization in zero because the first day the costumers pay without discount
                              r_search= this->avail_board[i]->reserv_code ;
                         }
                         //price each reservation according the days that is active
                         if (day*discount_per_day> (cost_per_day/2)) {
                              discount= (cost_per_day/2) ;
                         }
                         else {
                              discount= day*discount_per_day ;
                         }
                         sum+= cost_per_day- discount ;
                         day++ ;
                    }
               }
               return sum ;
          };

          //function that overwrites the same function of the Room
          bool cancel(int &resv_code) {
               return false ;
          } ;

};


class RoomC: public Room {//subclass of the Room class

     protected:
          int min_capacity ;
          int min_days ;

     public:
          RoomC(int min_cap, int max_cap,int min_d, double cost_p)
               : Room(max_cap,cost_p) {
                    min_capacity= min_cap ;
                    min_days= min_d ;
               }

          //function that overwrites the same function of the Room
          bool add_reservation(Reservation &res_obj) {
               bool ok= false ;
               //check if the extra critiria is met then run the Room class function
               if (min_capacity<= res_obj.p_sum && min_days<= res_obj.accom_days)
                    ok= Room::add_reservation(res_obj) ;
               else {//show a message with the particular problem
                    if (min_capacity> res_obj.p_sum) cout<< "Η καταχώρηση δεν ήταν εφικτή γιατί τα άτομα είναι λίγα!"<< endl ;
                    if (min_days> res_obj.accom_days) cout<< "Η καταχώρηση δεν ήταν εφικτή γιατί οι μέρες είναι λίγες!"<< endl ;
               }
               return ok;
          };

};


/*RoomD derives from RoomC and overwrites the pricing() and add_reservation() of class RoomC.The
add_reservation() is the same as the RoomC add_reservation() and the pricing() works like this:
for every day after the room's minimum days every person have a standard discount for the rest
of their staying. */
class RoomD: public RoomC {

     protected:
          int discount ;// (%)

     public:
          RoomD(int min_cap, int max_cap, int min_d, double cost_p, int disc)
               :RoomC(min_cap, max_cap, min_d, cost_p) {
               discount= disc ;
          }

          //function that overwrites the same function of the Room
          //use the function of RoomC
          bool add_reservation(Reservation &res_obj) {
               return RoomC::add_reservation(res_obj) ;
          };
          //function that overwrites the same function of the Room
          double pricing() {
               double sum= 0 ;//the sum of price for all the reservation in this room
               int day= 0 ;//days that the room is used from a particular reservation
               int r_search= 0 ;//reservation code to check if two different day's reservation are the same or not
               for (int i= 0; i< 30; i++) {
                    //check if the availibility board isn't empty
                    if (this->avail_board[i]!= NULL) {
                         //check if the saved reservation is the same as the reservation on the board
                         if (r_search!= this->avail_board[i]->reserv_code)  {
                              day= 1 ;//sum the days of a particular reservation
                              r_search= this->avail_board[i]->reserv_code ;
                         }
                         //price each reservation according the days that is active
                         if (day<= min_days) {
                              sum+= this->avail_board[i]->p_sum* cost_person ;
                         }
                         else {
                              sum+= this->avail_board[i]->p_sum* (cost_person* (100-discount))/100 ;
                         }
                         day++ ;
                    }
               }
               return sum ;

          };

};


/*RoomE derives from RoomA and overwrites the add_reservation function of the RoomA class. The
RoomE class is designed with couples in mind (only one).So a couple pays together the price for
each day of staying. */
class RoomE: public RoomA {

     public:
          RoomE(double cost_p_d, int max_cap= 2, double cost_p= 0)
          : RoomA(max_cap, cost_p_d, cost_p) {}

          //function that overwrites the same function of the Room
          bool add_reservation(Reservation &res_obj) {
               bool state= false ;
               //check if the people is just 2 add run the Room's same function
               if (res_obj.p_sum== 2) {
                    state= Room::add_reservation(res_obj) ;
               } else {
                    cout<< "Η κράτηση "<< res_obj.reserv_code<< " δεν έχει ακριβώς 2 ατομα!"<< endl;
               }
               return state ;
          }
          //function that overwrites the same function of the Room
          //use the function of RoomA
          double pricing() {
               return RoomA::pricing() ;
          };
};


//static counter initialization for unique room number
int Room::r_counter= 100 ;
