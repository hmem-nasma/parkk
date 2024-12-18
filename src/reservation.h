#ifndef RESERVATION_H
#define RESERVATION_H



// Define the Reservation structure
typedef struct {
    int num_reservation;
    int num_citoyen;
    int num_parking;
    char matricule_vehicule[50];
    char date_reservation[20];
    char service_reservation[50];
    char status_reservation[20]; 
} Reservation;



#endif 

