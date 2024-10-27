#include <iostream>
#include <cstring>
#include <fstream> // for file handling
#include <regex> // for email validation
#include <conio.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stack> // for stacks

using namespace std;
// class declarations

class Client{ // variables for client
	protected:
		string clientName,clientAddress,clientContact,clientEmail, clientID;
		stack <char> number;
	public:

		static vector<Client> clients; 

	    static void loadClients();
		bool registeredClient();
		void diplayInformation();
		string generateClientID();
};

vector<Client> Client::clients;

class User {   //for options (client/receptionist/manager)
     public:    
  	    int option,reg; 
  	    void userType();
  	 public:
  	    User() {
        Client::loadClients();
    	}
};

class Room {
public:
    Room(float roomPrice) : roomPrice(roomPrice){}
    virtual float getRoomCost(int numNight, int guest, int& extraguest, int& extraguestcharge) = 0;
    string facilityStr,roomPriceStr;
    float facilityCost;
    int roomPrice;

};

class Single : public Room {
public:
    Single() : Room(1500) {}
    float getRoomCost(int numNight, int guest, int& extraguest, int& extraguestcharge) {
        facilityCost = numNight * roomPrice;
        roomPriceStr="1500";
        facilityStr="Single Room";
        if (guest > 2) {
            cout << "\tNOTE : There is an additional Php500.00 for every extra person for room accommodation." << endl;
            extraguest = guest - 2;
            extraguestcharge = (extraguest) * 500;
        }
        return facilityCost += extraguestcharge;
    }
};

class Double : public Room {
public:
    Double() : Room(2000) {}
    float getRoomCost(int numNight, int guest, int& extraguest, int& extraguestcharge) {
        facilityCost = numNight * roomPrice;
        roomPriceStr="2000";
        facilityStr="Double Room";
        if (guest > 3) {
            cout << "\tNOTE : There is an additional Php500.00 for every extra person for room accommodation." << endl;
            extraguest = guest - 3;
            extraguestcharge = (extraguest) * 500;
        }
        return facilityCost += extraguestcharge;
    }
};

class King : public Room {
public:
    King() : Room(3000) {}
    float getRoomCost(int numNight, int guest, int& extraguest, int& extraguestcharge) {
        facilityCost = numNight * roomPrice;
        roomPriceStr="3000";
        facilityStr="King Room";
        if (guest > 4) {
            cout << "\tNOTE : There is an additional Php500.00 for every extra person for room accommodation." << endl;
            extraguest = guest - 4;
            extraguestcharge = (extraguest) * 500;
        }
        return facilityCost += extraguestcharge;
    }
};

class Suite : public Room {
public:
    Suite() : Room(4000) {}
    float getRoomCost(int numNight, int guest, int& extraguest, int& extraguestcharge) {
        facilityCost = numNight * roomPrice;
        roomPriceStr="4000";
        facilityStr="Suite Room";
        if (guest > 6) {
            cout << "\tNOTE : There is an additional Php500.00 for every extra person for room accommodation." << endl;
            extraguest = guest - 6;
            extraguestcharge = (extraguest) * 500;
        }
        return facilityCost += extraguestcharge;
    }
};

class Reservation:protected Client{ // reservation details
	protected:
		int resMonth,resDay,resYear,maxDays,guest,facility,numFacility,numNight,roomPrice,extraguest, extraguestcharge;
		float facilityCost,totalCost,paymentType,downPayment,lunchCost,dinnerCost,roomPrices, paymentAmount, remainingBal;
		string monthName,roomPriceStr;
		char choose;
		string facilityStr,paymentTypestr;
		bool checkedIn;
	
	protected:
		int reservationDate();
		void payment();
		void lunchDetails();
		void dinnerDetails();
	
	public:
	    Reservation() : checkedIn(false) {}
        Reservation(const Client& client) : Client(client), checkedIn(false) {}
        void clientDetails();
   		void reservationDetails();
		void print();
		void saveReservationDetails();
        void viewCheckedInGuests();
        void checkIn();
        void roomDetails();
        void printRegisteredClient();
        
};

class Receptionist : public Reservation {
    
    public:
        bool fileIsEmpty;
	public:
		void viewClientDetails();
		void viewReservations();
		void verifyCheckIn();
		void viewRemainingBalance();
		void viewFullyPaid();
		void sortByDate();
};    

class Manager : public Receptionist {
	
	public:
		bool fileIsEmpty;
	public:
		void fileCancellationRequests();
		void viewCheckedInGuests();
		void viewCancellationRequests();
		void cancelReservation();
		void viewCancelledReservations();
};

//class User functions
void User::userType(){
Reservation objResv; // reservation object created 
Client objCli; //client object created
Receptionist objRecep; // receptionist object created
Manager objManager; // manaager object created
	
	do{		
		cout<<"---------------------------------------"<<endl;
		cout<<"                WELCOME"<<endl;
		cout<<"---------------------------------------"<<endl;
		cout<<"\t[1] Client"<<endl;
		cout<<"\t[2] Receptionist"<<endl;
		cout<<"\t[3] Manager"<<endl;
		cout<<"---------------------------------------"<<endl;
		cout<<"Please enter your choice: ";
		cin>>option;			
		
		if (option < 1 || option > 3) {
        cout << "\nInvalid choice. Please enter a valid option." << endl << endl;
    	}
					
	}while(option < 1 || option > 3);
	
	system("cls");
	
	switch(option){
			case 1:
				int reg;			
					cout<<"---------------------------------------"<<endl;
					cout<<"Client Menu:"<<endl<<endl;
					cout<<"\t[1] Sign In"<<endl;
					cout<<"\t[2] Sign Up"<<endl;
					cout<<"\t[3] File a Cancellation Request"<<endl;
					cout<<"\t[4] Exit"<<endl;
					cout<<"---------------------------------------"<<endl;
					cout<<"Please enter your choice: ";
					cin>>reg;
					system("cls");

						if (reg == 1) {
                            if (objCli.registeredClient()) {
                            	
                            	cout<<"\nPress ANY KEY to continue...";
                                // Client is registered, proceed with reservation
                                objResv.reservationDetails();
                                objResv.printRegisteredClient();
                                objResv.saveReservationDetails();
                                objResv.checkIn();  // Added for check-in
                                break;
				            }
                        } else if (reg == 2) {
                        	
                            objResv.clientDetails();
                            objResv.reservationDetails();
                            objResv.print();
                            objResv.saveReservationDetails();
                            objResv.checkIn();  // Added for check-in
                            break;
                        }
                          else if (reg == 3) {
                          	
                            objManager.fileCancellationRequests();
                            break;
                        }
                          else if (reg == 4) {
                        
                          	cout<<"Exiting Client Menu."<<endl;
                          	break;
						  }
                    break;    
	        
			case 2:
				int receptionistOption;
                    do {
                    	cout<<"---------------------------------------"<<endl;
                        cout << "Receptionist Menu:" << endl;
                        cout<<"\n\t[1] View Client Details" << endl;
                        cout <<"\t[2] View Reservation Details" << endl;
                        cout <<"\t[3] Verify Check-In" <<endl;
                        cout <<"\t[4] Exit" << endl;
                        cout<<"---------------------------------------"<<endl;
                        cout << "\nEnter option: ";
                        cin >> receptionistOption;
                        
                        if (receptionistOption < 1 || receptionistOption > 4) {
				        cout << "\nInvalid choice. Please enter a valid option." << endl << endl;
    					}
                        
                    } while (receptionistOption < 1 || receptionistOption > 4);
                                                      	                                                                                                             	
                        switch (receptionistOption) {
                        	case 1:
                            	objRecep.viewClientDetails();
                            	break;
                            case 2:
                                int sortOption;
                                    do{
                                        
                                        cout << "\n\t[1] View all reservation records" << endl <<endl;
                                        cout << "Sort Reservations by:" << endl<<endl;
                                        cout << "\t[2] Date" << endl;
                                        cout << "\t[3] Remaining Balance" << endl;
                                        cout << "\t[4] Fully Paid" << endl;
                                        cout << "\t[5] Exit" << endl;
                                        cout << "\nEnter option: ";
                                        cin >> sortOption;
                                        
                                        if (sortOption < 1 || sortOption > 5) {
								        cout << "\nInvalid choice. Please enter a valid option." << endl << endl;
				    					}
                                        
                                    }while (sortOption <1 || sortOption>5);
                                        if (sortOption == 1) {
                                        	    cout<<"Here are all the reservation records:"<<endl;
                                        	    cout<<endl;
                                        	    objRecep.viewReservations();
                                        	    break;
										}
                                        if (sortOption == 2) {
                                                cout<<"Here are the reservations sorted by date: "<<endl;
                                                cout<<endl;
                                                objRecep.sortByDate();
                                                break;  
                                        }
										                      
                                        if (sortOption == 3) {
                                                cout<<"Here are the reservations sorted by remaining balance: "<<endl;
                                                cout<<endl;
                                                objRecep.viewRemainingBalance();
                                                break;
                                        }
                                        if (sortOption == 4) {
                                                cout<<"Here are the fully paid reservations: "<<endl;
                                                cout<<endl;
                                                objRecep.viewFullyPaid();   
												break;                                          
                                        }
                                        if (sortOption == 5) {
                                        	    cout<<"Exiting Receptionist Menu."<<endl;
                                                break;    
                                        }
                                break;
                            case 3:
							    cout<<"Verify checked in guests "<<endl;
								objRecep.verifyCheckIn();            
                                break;
                            case 4:
                                cout << "Exiting Receptionist Menu." << endl;
                                break;
                                
                            default:
                                cout << "Invalid option. Please try again." << endl;
                            }
                    				break;
			case 3:
				int managerOption;
				    do {
				    	cout<<endl<<"---------------------------------------"<<endl;
				    	cout<<"Manager Menu:"<<endl<<endl;
				        cout<<"\t[1] View all existing records in the system"<< endl;
				        cout<<"\t[2] View checked-in guests of the hotel"<< endl;
				        cout<<"\t[3] View cancellation requests"<<endl;
				        cout<<"\t[4] Cancel Reservation"<<endl;
				        cout<<"\t[5] View Cancelled Reservations" << endl;
				        cout<<"\t[6] Exit" << endl;
				        cout<<"---------------------------------------"<<endl;
				        cout<<"\nEnter option: ";  
				        cin>>managerOption;
				        
				        switch (managerOption) {
				        	case 1:
				        	    cout<<endl<<"-----Records-----: "<<endl;
				        		objManager.viewReservations();
				        		break;
				        	case 2:
								objManager.viewCheckedInGuests();
								break;
				        	case 3:		        		
				        		cout<<endl<<"-----View Cancellation Requests-----"<<endl;
				            	objManager.viewCancellationRequests();
				            	break;
				            case 4:
				            	cout<<endl<<"-----Cancel Reservation-----"<<endl;
				        		objManager.cancelReservation();
				        		break;
				            case 5:
				        		cout<<endl<<"-----View Cancelled Reservations-----"<<endl;
				        		objManager.viewCancelledReservations();
				        		break;
				        	case 6:
				        		cout<<endl<<"Exiting Manager Menu." << endl;
				        		break;
				        	default:
				        		cout<<" Invalid option. Please try again." <<endl;
				        	}
						} while (managerOption!=6);
				        break;
			default:
			    cout<<"Ending program";	
					}
				
				
		}
		
string Client::generateClientID()
{
    	// reverse contact number
    for (char c:clientContact) 
	    {
            number.push(c);
        }

        string reverseContact;
        while (!number.empty()) 
	    {
            reverseContact += number.top();
            number.pop();
        }


        // replace the reversed contact number into client id
        clientID = reverseContact;
        for (char& c:clientID) 
	    {
            switch (c) 
		    {
		    	case '0':
		    		c = '0';
		    		break;
		    	case '1':
		    		c = '1';
		    		break;
		    	case '2':
		    		c = 'Z';
		    		break;
		    	case '3':
		    		c = '4';
		    		break;
		    	case '4':
		    		c = 'A';
		    		break;
		    	case '5':
		    		c = '5';
		    		break;
		    	case '6':
		    		c = 'G';
		    		break;
		    	case '7':
		    		c = '3';
		    		break;
		    	case '8':
		    		c = 'B';
		    		break;
		    	case '9':
		    		c = '9';
		    		break;
                default:
                    break;
            }
        }
    
	return clientID; 
}

//class Reservation functions
void Reservation::clientDetails(){
    
        cout<<"---------------------------------------"<<endl;
	    cout<<"            CLIENT DETAILS:"<<endl;
	    cout<<"---------------------------------------"<<endl;
		cout<<"Enter the following information: "<<endl;
		cout<<endl<<"\tFull Name: ";
		cin.ignore();
		getline(cin,clientName);
		cout<<"\tAddress: ";
		getline(cin,clientAddress);
	
	bool numCheck = false;
		
		do {
			
			cout<<"\tContact Number: ";
			getline(cin, clientContact);
			
			for(int i = 0; i < clientContact.length(); i++) {
				if(!isdigit(clientContact[i]) || clientContact.length()!=11) {
					cout << "\nPlease input a valid contact number!\n";
					numCheck = false;
					break;
				
				} else {
					numCheck = true;
				}
			}
		} while (numCheck == false);
			
		bool eCheck = true;
		do {
			cout<<"\tEmail Address: ";	
			getline(cin, clientEmail);
			
		 	const regex emailPattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))");		//email must have: word, followed by optional . or _ followed by a word, an @ symbol, followed by a word and then a dot followed by a word	
		
		    if(regex_match(clientEmail, emailPattern)) {		//email validation
		        eCheck = true;
		    } else {
		        cout << "Invalid email address. Please follow the format: <sample>@<site>.com\n";
		        eCheck = false;
		    }
		} while (eCheck != true);
		
		cout<<endl<<"Registration successful!"<<endl;
        cout<<"\nYour Client ID is: "<<generateClientID();
        cout<<endl<<"\n\tPress ANY KEY to continue...";
		
		ofstream fout("CLIENT.txt", ios::app);
            if (fout.is_open()) {
                
                fout<<"Client ID: "<<generateClientID()<<endl;
                fout<<"Name: "<<clientName <<endl;
                fout<<"Address: "<<clientAddress<<endl;
                fout<<"Contact Number: "<<clientContact<<endl;
                fout<<"Email: "<<clientEmail<<endl;
                fout<<endl;
                fout.close();
                cout<<endl;

            } else {
                cout << "Error: Unable to register client." << endl;
            }
}

void Reservation::checkIn() {
    cout<<endl;
    cout << "Are the details correct? (Y/N): ";
    char checkInOption;
    cin >> checkInOption;

    if (checkInOption == 'Y' || checkInOption == 'y') {
        checkedIn = true;
        cout<<"Reservation Saved! See you soon!"<<endl;
    }
}

bool Client::registeredClient() {
	string clientIdToCheck;
    cout<<"---------------------------------------"<<endl;
    cout << "Enter your Client ID: ";
    cin >> clientIdToCheck;

    // Check if the client file exists
    ifstream fin("CLIENT.txt");
    if (!fin.is_open()) {
        cout << "Error: Client ID unavailable." << endl;
        return false;
    }
    
    string line;
    bool foundClient = false;

    while (getline(fin, line)) {
        // check for client existence
        size_t pos = line.find("Client ID: "); //check if the current line contains the substring "Client ID:"
        if (pos != string::npos) {
            string clientIdInFile = line.substr(pos + 11); // client id has 11 characters
            if (clientIdInFile == clientIdToCheck) {
                foundClient = true;
                cout << endl<< "CLIENT DETAILS FOUND" << endl<<endl;
                cout << "\t" << line << endl; // print
                
                
                while (getline(fin, line)) {
                    if (line.empty()) break; 
                    cout << "\t" << line << endl;
                }

                break; 
            }
        }
    }

    fin.close(); // close file

    if (!foundClient) {
        cout << "Client not found with Client ID: " << clientIdToCheck << endl;
        return false;
    }

    return true;
    
}

void Client::loadClients() {
    ifstream fin("CLIENT.txt");
    if (fin.is_open()) {
        Client client;
        while (fin >> client.clientID >> client.clientName >> client.clientAddress >> client.clientContact >> client.clientEmail) {
            clients.push_back(client);
        }
        fin.close();
    }
}

void Reservation::reservationDetails(){
		getch();
        system ("cls");
        cout<<"---------------------------------------"<<endl;
	    cout<<"         RESERVATION DETAILS: "<<endl;
	    cout<<"---------------------------------------"<<endl;
		reservationDate(); // date
		roomDetails(); // room computations
		lunchDetails(); // lunch 
		dinnerDetails(); // dinner
		payment(); // payment computations
}

void Reservation::roomDetails() {
    int choice;
    
	do{
    cout<<endl;
    cout << "Rooms to choose from:" << endl;
    cout << "\n\t[1] Single - Php1,500.00 per night (Max of 2 pax)" << endl;
    cout << "\t[2] Double - Php2,000.00 per night (Max of 3 pax)"<<endl;
    cout<<"\t[3] King   - Php3,000.00 per night (Max of 4 pax)"<<endl;
    cout<<"\t[4] Suite  - Php4,000.00 per night (Max of 6 pax)"<<endl;
	
    cout<<"\nWhat room would you like to avail: ";
    cin >> choice;
    
	    if (choice < 1 || choice > 4) {
		cout << "\nInvalid choice. Please enter a valid option." << endl << endl;
		}
    
    } while (choice < 1 || choice > 4);
    Room* room;
    switch (choice) {
        case 1:
            room = new Single();
            break;
        case 2:
            room = new Double();
            break;
        case 3:
            room = new King();
            break;
        case 4:
            room = new Suite();
            break;
        default:
            cout << "Invalid choice." << endl;
            return;
    }
    cout << "For how many nights would you like to stay?: ";
    cin>>numNight;
    cout << "How many guests?: ";
    cin >> guest;
    
    room->getRoomCost(numNight, guest, extraguest, extraguestcharge);
    
    this->extraguest = extraguest;
    this->extraguestcharge = extraguestcharge;
    
    facilityCost = room->facilityCost;
    roomPriceStr = room->roomPriceStr;
    facilityStr  = room->facilityStr;
}

int Reservation::reservationDate()
{
				do {
			        cout<<"\tEnter Year [Current Year Onwards]: ";
			        cin>>resYear;
			        
			        if (resYear < 2024 || resYear > 2100) {
					cout << "\nInvalid Year. Please enter a valid year." << endl << endl;
					}
			        
			    } while (resYear < 2024 || resYear > 2100);
				do {
			        cout<<"\tEnter Month [1-12]: ";
			        cin>>resMonth;
			        
			        if (resMonth < 1 || resMonth > 12) {
					cout << "\nInvalid Month. Please enter a valid month." << endl << endl;
					}
			        
			    } while (resMonth < 1 || resMonth > 12);
			    	    
			    switch (resMonth){
					case 1:
						monthName = "January";
						maxDays = 31;
						break;
					case 2:
						if (resYear % 4 == 0 && (resYear % 100 != 0 || resYear % 400 == 0))
							{
							monthName = "February";
			            	maxDays = 29; // Leap year
			            	break;
							}				
			        	else {
			           		monthName = "February";
			            	maxDays = 28;
			            	break;
			   				}
			        case 3:
						monthName = "March";
						maxDays = 31;
						break;
					case 4:
						monthName = "April";
						maxDays = 30;
						break;
					case 5:
						monthName = "May";
						maxDays = 31;
						break;
					case 6:
						monthName = "June";
						maxDays = 30;
						break;
					case 7:
						monthName = "July";
						maxDays = 31;
						break;
					case 8:
						monthName = "August";
						maxDays = 31;
						break;
					case 9:
						monthName = "September";
						maxDays = 30;
						break;
					case 10:
						monthName = "October";
						maxDays = 31;
						break;
					case 11:
						monthName = "November";
						maxDays = 30;
						break;
					case 12:
						monthName = "December";
						maxDays = 31;
						break;
					default:
						cout<<"Invalid Month";
						return -1;
	           }
			    do {
			        cout<<"\tEnter Day: ";
			        cin>>resDay;
			        
			        if (resDay < 1 || resDay > maxDays) {
					cout << "\nInvalid Day. Please enter a valid date." << endl << endl;
					}
			        
			    } while (resDay < 1 || resDay > maxDays);
    return resDay;
	
}

void Reservation::saveReservationDetails() {
    // Save reservation details in RESERVE text file
    //Client objCli;
    ofstream fout ("RESERVE.txt", ios::app);
    if (fout.is_open()) {
            fout<<"Client ID: "<<clientID<<endl;
            fout<<"Client Name: "<<clientName<<endl;
            fout<<"Reservation Date [Year/Month/Date]: " << resYear << " / " << resMonth << " / " << resDay<<endl;
            fout<<"Guests: "<< guest<<endl; 
            fout<<"Facility: "<< facilityStr<<endl;
            fout<<"Nights: " << numNight<<endl;
            fout<<"Room Price: "<<roomPriceStr<<endl;
            fout<<"Extra Guests: "<<extraguest<<endl;
            fout<<"Extra Charge: "<<extraguestcharge<<endl;
            fout<<"Facility Cost: "<<facilityCost<<endl;
            fout<<"Price of Lunch: "<<lunchCost<<endl;
            fout<<"Price of Dinner: "<<dinnerCost<<endl;
            fout<<"Total: "<< totalCost<<endl;
            fout<<"Payment Type: "<< paymentTypestr<<endl;
            fout<<"Downpayment:" << downPayment<<endl;
            fout<<"Amount Paid: "<<paymentAmount<<endl;
            fout<<"Remaining Balance: "<<remainingBal<<endl;
            fout<<endl;
        fout.close();
        cout<<endl;
        cout<<endl;
    } else {
        cout << "Error: Reservations unavailable." << endl;
    }
}

void Receptionist::verifyCheckIn(){
	cout<<endl<<"-------------------------------------"<<endl;
    cout<<"\tVerify Check-In"<<endl;
    cout<<"-------------------------------------"<<endl<<endl;
    string clientIdToCancel;
    cout <<"Enter the Client ID to verify your reservation: ";
    cin >> clientIdToCancel;

    // Check if the reservation exists
    ifstream fin("RESERVE.txt");
    if (!fin.is_open()) {
        cout << "Client ID unavailable." << endl;
        return;
    }

    vector<string> reservationLines;
    string line;
    bool foundReservation = false;

    while (getline(fin, line)) {
        if (line.find("Client ID: " + clientIdToCancel) != string::npos) {
            foundReservation = true;
            cout << "Reservation found!" << endl << endl ;
            cout<<"\tGUEST CHECKED IN"<<endl;
            // Save the reservation details to the CANCELREQUEST file
            ofstream fout("CHECKED-IN.txt", ios::app);
            if (fout.is_open()) {
                fout << line << endl;  // Save the Client ID line
                // Save the rest of the reservation details
                for (int i = 0; i < 16; ++i) {
                    getline(fin, line);
                    fout << line << endl;
                }
                fout << endl;  // Add an extra line for separation
                fout.close();
            } else {
                cout << "Error: Unable to save cancelled requests." << endl;
            }
        } else {
            reservationLines.push_back(line);
        }
    }
	
}

void Manager::viewCheckedInGuests() {
	cout<<endl<<"-------------------------------------"<<endl;
    cout<<"\tChecked-In Guests"<<endl;
    cout<<"-------------------------------------"<<endl<<endl;
    ifstream file("CHECKED-IN.txt");
   
    string line;
    fileIsEmpty = true;  // Flag to check if the file is empty

    while (getline(file, line)) {
        cout << "\t" << line << endl;
        fileIsEmpty = false;  // Set flag to false if there is at least one line in the file
    }

    file.close();

    if (fileIsEmpty) {
        cout << "\tThere are no available checked-in guests at this moment." << endl;
    }
}

void Reservation::lunchDetails()
{

	do {
	    cout << endl << "Would you like to include lunch upon reservation?";
	    cout << endl << "\tNOTE: Lunch is P250.00 per person\n";
	    cout << endl << "Enter Option [Y/N]: ";
	    cin >> choose;
	
	    if (choose == 'Y' || choose == 'y') {
	        cout << endl << "Lunch Added!";
	        lunchCost = 250 * guest;
	        cout << endl << "Total Lunch Cost: " << lunchCost << endl;
	    } else if (choose == 'N' || choose == 'n') {
	        cout << endl << "Lunch not added!" << endl;
	        lunchCost = 0;
	    } else {
	        cout << "Invalid input. Please enter 'Y' or 'N'." << endl<<endl;
	    }
	
	} while (choose != 'Y' && choose != 'y' && choose != 'N' && choose != 'n');
	
}

void Reservation::dinnerDetails()
{

	do {
	    cout << endl << endl << "Would you like to include dinner upon reservation?";
	    cout << endl << "\tNOTE: Dinner is P350.00 per person\n";
	    cout << endl << "Enter Option [Y/N]: ";
	    cin >> choose;
	
	    if (choose == 'Y' || choose == 'y') {
	        cout << endl << "Dinner Added!";
	        dinnerCost = 350 * guest;
	        cout << endl << "Total Dinner Cost: " << dinnerCost << endl;
	    } else if (choose == 'N' || choose == 'n') {
	        cout << endl << "Dinner not added!" << endl;
	        dinnerCost = 0;
	    } else {
	        cout << "Invalid input. Please enter 'Y' or 'N'." << endl<<endl;
	    }
	
	} while (choose != 'Y' && choose != 'y' && choose != 'N' && choose != 'n');

}

void Reservation::payment()
{
    system ("cls");
	totalCost=facilityCost+lunchCost+dinnerCost;
	cout<<endl<<"---------------------------------------"<<endl;
	cout<<"         RESERVATION PAYMENT"<<endl;
	cout<<"---------------------------------------"<<endl;
	cout<<endl<<"\tNo. of guests: "<<guest;
	cout<<endl<<"\tNo. of nights: "<<numNight;
	cout<<endl<<"\tRoom Cost per Night: "<<roomPriceStr;
	cout<<endl<<"\tExtra Guest/s: "<<extraguest;
	cout<<endl<<"\tExtra Guest Charge: "<<extraguestcharge;
	cout<<endl<<"\tFacility to Reserve: "<<facilityStr;
	cout<<endl<<"\tFacility Cost: "<<facilityCost;
	cout<<endl<<"\tLunch Cost: "<<lunchCost;
	cout<<endl<<"\tDinner Cost: "<<dinnerCost;
	cout<<endl<<"\tTotal Cost: "<<totalCost<<endl;
	cout<<"---------------------------------------"<<endl;
	cout<<"\nPayment Types:"<<endl;
	cout<<"\t[1] 30% Down Payment."<<endl;
	cout<<"\t[2] Full Payment."<<endl;
  		do {
        cout<<endl<<"\tPlease choose payment type: ";
        cin>>paymentType;
        
        if (paymentType < 1 || paymentType > 2) {
		cout << "\nInvalid Input. Please enter a valid choice." << endl << endl;
		}
        
   		} while ( paymentType < 1 || paymentType > 2 );
   
   		if ( paymentType == 1 ) {
   	     paymentTypestr="30% Down Payment";
   	     cout<<"\tPayment Type : 30% Down Payment"<<endl;
   	     downPayment=totalCost*.30;
   	     cout<<"---------------------------------------"<<endl;
   	     cout<<endl<<"\tPlease pay an amount of PHP " <<downPayment<<endl;
   	     
   	     do{
   	         cout<<"\tInput your payment: PHP ";
   	         cin>>paymentAmount;
   	         
   	         // Check if the payment is valid (not negative and not less than downPayment and not more than the total cost)
                if (paymentAmount < 0 || paymentAmount < downPayment || paymentAmount > totalCost) {
                    cout << "Invalid payment amount. Please enter a valid amount." << endl;
                }
            } while (paymentAmount < 0 || paymentAmount < downPayment || paymentAmount > totalCost);
        
            // Subtract the payment from the total to calculate the remaining balance
            remainingBal = totalCost - paymentAmount;
            
            cout<<"---------------------------------------"<<endl;
            cout<<"\tPayment accepted."<<endl;
            cout<<"\tRemaining balance: PHP " << remainingBal << endl;
            cout<<"---------------------------------------"<<endl;
            cout<<"\n\tPress ANY KEY to continue...";
            getch();
   		}
   
   		if ( paymentType == 2 ) {
   	     downPayment=0;
   	     paymentTypestr="Full Payment";
   	     cout<<"\tPayment Type : Full Payment"<<endl;
   	     cout<<"\tPlease pay an amount of PHP " <<totalCost<<endl;
   	     
   	     do{
   	         cout<<"---------------------------------------"<<endl;
   	         cout<<"\tInput your payment: PHP ";
   	         cin>>paymentAmount;
   	         
   	         // Check if the payment is valid (not negative and not less than total cost)
                if (paymentAmount < 0 || paymentAmount < totalCost || paymentAmount > totalCost) {
                    cout << "Invalid payment amount. Please enter a valid amount." << endl;
                }
            } while (paymentAmount < 0 || paymentAmount < totalCost || paymentAmount > totalCost);
        
            // Subtract the payment from the total to calculate the remaining balance
            remainingBal = totalCost - paymentAmount;
            
            cout<<"---------------------------------------"<<endl;
            cout<<"\tPayment accepted."<<endl;
            cout<<"\tRemaining balance: PHP " << remainingBal << endl;
            cout<<"---------------------------------------"<<endl;
            cout<<"\n\tPress ANY KEY to continue...";
            getch();
	   	}
   
}
void Manager::fileCancellationRequests(){
	string clientIdToCancel;
    cout <<"Enter the Client ID to file a request for cancellation: ";
    cin >> clientIdToCancel;

    // Check if the reservation exists
    ifstream fin("RESERVE.txt");
    if (!fin.is_open()) {
        cout << "Error: Unable to file a cancellation request." << endl;
        return;
    }

    vector<string> reservationLines;
    string line;
    bool foundReservation = false;

    while (getline(fin, line)) {
        if (line.find("Client ID: " + clientIdToCancel) != string::npos) {
            foundReservation = true;
            cout << "Cancellation request sent, please wait for the approval of the manager!" << endl;
            // Save the reservation details to the CANCELREQUEST file
            ofstream fout("CANCELREQUEST.txt", ios::app);
            if (fout.is_open()) {
                fout << line << endl;  // Save the Client ID line
                // Save the rest of the reservation details
                for (int i = 0; i < 16; ++i) {
                    getline(fin, line);
                    fout << line << endl;
                }
                fout << endl;  // Add an extra line for separation
                fout.close();
            } else {
                cout << "Error: Unable to cancel request." << endl;
            }
        } else {
            reservationLines.push_back(line);
        }
    }

    fin.close();
	
	if (!foundReservation) {
        cout << "Reservation not found with Client ID: " << clientIdToCancel << endl;
        return;
    }
}
void Manager::cancelReservation() {
    string clientIdToCancel;
    cout << endl<< "Enter the Client ID to cancel reservation: ";
    cin >> clientIdToCancel;

    // Check if the reservation exists
    ifstream fin("RESERVE.txt");
    if (!fin.is_open()) {
        cout << "Error: Reservation unavailable." << endl;
        return;
    }

    vector<string> reservationLines;
    string line;
    bool foundReservation = false;

    while (getline(fin, line)) {
        if (line.find("Client ID: " + clientIdToCancel) != string::npos) {
            foundReservation = true;
            cout << "Reservation found. Canceling..." << endl;
            // Save the reservation details to the CANCELLED file
            ofstream fout("CANCELLED.txt", ios::app);
            if (fout.is_open()) {
                fout << line << endl;  // Save the Client ID line
                // Save the rest of the reservation details
                for (int i = 0; i < 16; ++i) {
                    getline(fin, line);
                    fout << line << endl;
                }
                fout << endl;  // Add an extra line for separation
                fout.close();
            } else {
                cout << "Error: Unable to save cancelled reservation." << endl;
            }
        } else {
            reservationLines.push_back(line);
        }
    }

    fin.close();

    if (!foundReservation) {
        cout << "Reservation not found with Client ID: " << clientIdToCancel << endl;
        return;
    }

    // Rewrite the RESERVE file without the cancelled reservation
    ofstream fout("RESERVE.txt");
    if (fout.is_open()) {
        for (const string& line : reservationLines) {
            fout << line << endl;
        }
        fout.close();
        cout <<endl<<"\tReservation cancelled successfully." << endl <<endl;
    } else {
        cout << "Error: Unable to save cancelled reservation." << endl;
    }
    
    ofstream fout2("CANCELREQUEST.txt");
    if (fout2.is_open()) {	
        for (const string& line : reservationLines) {
            fout << line << endl;
        }
        fout2.close();
        
    } else {
        cout << "Error: Unable to save cancelled reservation." << endl;
    }
}

void Receptionist::sortByDate() {
	// Check if the client file exists
	 fstream f;  
	 string room;
	 f.open("Reserve.Txt",ios::in);   //biniksan yung file na may laman nung mga reservations
	 string reservationinfo[17];
	 int index=0;
	 while(getline(f, room))
	 {
	  reservationinfo[index]=room;
	  if(index==17)
	  {
	  for(int index=0;index<=17;index++)
	 {
      cout<<reservationinfo[index]<<endl;
	 }
  cout<<"-----------------------------------------"<<endl;
    index=0;
    }
    else{
    	index++;
	}
    }
	 f.close(); // Close the file after reading
}

void Receptionist::viewRemainingBalance() {
	// Check if the client file exists
	 fstream f;  
	 string room;
	 f.open("Reserve.Txt",ios::in);   //biniksan yung file na may laman nung mga reservations
	 string reservationinfo[17];
	 int index=0;
	 while(getline(f, room))
	 {
	  reservationinfo[index]=room;
	  if(index==17)
	  {
	  if(reservationinfo[17]!="Remaining Balance: 0")
	 {
	 for(int index=0;index<=17;index++)
	 {
      cout<<reservationinfo[index]<<endl;
	 }
  cout<<"-----------------------------------------"<<endl;
    }
    index=0;
    }
    else{
    	index++;
	}
    }
	 f.close(); // Close the file after reading
}

void Receptionist::viewFullyPaid() {
	// Check if the client file exists
	 fstream f;  
	 string room;
	 f.open("Reserve.Txt",ios::in);   //biniksan yung file na may laman nung mga reservations
	 string reservationinfo[17];
	 int index=0;
	 while(getline(f, room))
	 {
	  reservationinfo[index]=room;
	  if(index==17)
	  {
	  if(reservationinfo[17]=="Remaining Balance: 0")
	 {
	 for(int index=0;index<=17;index++)
	 {
      cout<<reservationinfo[index]<<endl;
	 }
  cout<<"-----------------------------------------"<<endl;
    }
    index=0;
    }
    else{
    	index++;
	}
    }
	 f.close(); // Close the file after reading
}

void Receptionist::viewReservations() {
    cout<<endl<<"-------------------------------------"<<endl;
    cout<<"\tReservation Details"<<endl;
    cout<<"-------------------------------------"<<endl<<endl;
    ifstream file("RESERVE.txt");
   
    string line;
    fileIsEmpty = true;  // Flag to check if the file is empty

    while (getline(file, line)) {
        cout << "\t" << line << endl;
        fileIsEmpty = false;  // Set flag to false if there is at least one line in the file
    }

    file.close();

    if (fileIsEmpty) {
        cout << "\tThere are no available reservations at this moment." << endl;
    }
 }

void Receptionist::viewClientDetails() {
    cout<<endl<<"-------------------------------------"<<endl;
    cout<<"\tClient Details"<<endl;
    cout<<"-------------------------------------"<<endl<<endl;
    ifstream file("CLIENT.txt");
   
    string line;
    
    fileIsEmpty = true;  // Flag to check if the file is empty

    while (getline(file, line)) {
        cout << "\t" << line << endl;
        fileIsEmpty = false;  // Set flag to false if there is at least one line in the file
    }

    file.close();

    if (fileIsEmpty) {
        cout << "\tThere are no available clients at this moment." << endl;
    }
}
 
void Manager::viewCancellationRequests() {
    ifstream file("CANCELREQUEST.txt");

    cout << endl << "--------------------------------------------" << endl;
    cout << "\tCancellation Requests" << endl;
    cout << "--------------------------------------------" << endl << endl;

    string line;
    fileIsEmpty = true;  // Flag to check if the file is empty

    while (getline(file, line)) {
        cout << "\t" << line << endl;
        fileIsEmpty = false;  // Set flag to false if there is at least one line in the file
    }

    file.close();

    if (fileIsEmpty) {
        cout << "\tThere are no available cancellation requests at this moment." << endl;
    }
}

void Manager::viewCancelledReservations() {
    ifstream file("CANCELLED.txt");

    cout << endl << "--------------------------------------------" << endl;
    cout << "\tCancelled Reservations" << endl;
    cout << "--------------------------------------------" << endl << endl;

    string line;
	fileIsEmpty = true;  // Flag to check if the file is empty

    while (getline(file, line)) {
        cout << "\t" << line << endl;
        fileIsEmpty = false;  // Set flag to false if there is at least one line in the file
    }

    file.close();

    if (fileIsEmpty) {
        cout << "\tThere are no available cancelled reservations at this moment." << endl;
    }
}

void Reservation::print() //print receipt
{
	system("cls");
	cout<<endl<<"============================================================";
	cout<<endl<<"CLIENT DETAILS:"<<endl;
	cout<<endl<<"\tFull Name                 :          "<<clientName;
	cout<<endl<<"\tAddress                   :          "<<clientAddress;
	cout<<endl<<"\tContact Number            :          "<<clientContact;
	cout<<endl<<"\tEmail Address             :          "<<clientEmail;
	cout<<endl<<"\tClient ID                 :          "<<generateClientID()<<endl;
	cout<<endl<<"============================================================";
	cout<<endl<<"RESERVATION DETAILS:"<<endl;
	cout<<endl<<"\tDate of Reservation       :          " << monthName << " " << resDay << ", " << resYear;
	cout<<endl<<"\tNumber of Guests          :          "<<guest;
	cout<<endl<<"\tExtra Guests              :          "<<extraguest;
	cout<<endl<<"\tExtra Guest Charge        :          "<<extraguestcharge;
	cout<<endl<<"\tFacilities to Reserve     :          "<<facilityStr;
	cout<<endl<<"\t  Room Cost per Night     :             PHP "<<roomPriceStr;
    cout<<endl<<"\t  Facility Cost           :             PHP "<<facilityCost;
    cout<<endl<<"\t  Lunch Cost              :             PHP "<<lunchCost;
    cout<<endl<<"\t  Dinner Cost             :             PHP "<<dinnerCost<<endl;
    cout<<endl<<"\t  Payment Type            :          "<<paymentTypestr;
    cout<<endl<<"\t  Down Payment            :             PHP "<<downPayment;
    cout<<endl<<"\t  Amount Paid             :             PHP "<<paymentAmount;
    cout<<endl<<"\t  Remaining Balance       :             PHP "<<remainingBal;
    cout<<endl<<"____________________________________________________________";
	cout<<endl<<"\t  TOTAL PAYMENT COST      :             PHP "<<totalCost;
}

void Reservation::printRegisteredClient() //print receipt for registered clients

{
	string clientIdToCheck;
	system("cls");
	cout << endl << "============================================================";
	cout<< endl<<"Type in your Client ID to verify: ";
	cin>>clientIdToCheck;
	cout << endl << "CLIENT DETAILS:" << endl;

	ifstream fin("CLIENT.txt");
	if (!fin.is_open()) {
    cout << "Error: Client ID unavailable." << endl;
    return;
	}

	string line;
	bool foundClient = false;

	while (getline(fin, line)) {
    	size_t pos = line.find("Client ID: ");
    	if (pos != string::npos) {
        string clientIdInFile = line.substr(pos + 11);
        if (clientIdInFile == clientIdToCheck) {
            foundClient = true;
            cout << "\n\t" << "Client ID: " << clientIdInFile << endl;
            getline(fin, clientName);
            getline(fin, clientAddress);
            getline(fin, clientContact);
            getline(fin, clientEmail);

            cout << "\t" << clientName << endl;
            cout << "\t" << clientAddress << endl;
            cout << "\t" << clientContact << endl;
            cout << "\t" << clientEmail << endl;

            	break; 
       	 	}
    		}
		}

		fin.close(); 

		cout<<endl<<"============================================================";
		cout<<endl<<"RESERVATION DETAILS:"<<endl;
		cout<<endl<<"\tDate of Reservation       :          " << monthName << " " << resDay << ", " << resYear;
		cout<<endl<<"\tNumber of Guests          :          "<<guest;
		cout<<endl<<"\tExtra Guests              :          "<<extraguest;
		cout<<endl<<"\tExtra Guest Charge        :          "<<extraguestcharge;
		cout<<endl<<"\tFacilities to Reserve     :          "<<facilityStr;
		cout<<endl<<"\t  Room Cost per Night     :             PHP "<<roomPriceStr;
    	cout<<endl<<"\t  Facility Cost           :             PHP "<<facilityCost;
    	cout<<endl<<"\t  Lunch Cost              :             PHP "<<lunchCost;
    	cout<<endl<<"\t  Dinner Cost             :             PHP "<<dinnerCost<<endl;
    	cout<<endl<<"\t  Payment Type            :          "<<paymentTypestr;
    	cout<<endl<<"\t  Down Payment            :             PHP "<<downPayment;
    	cout<<endl<<"\t  Amount Paid             :             PHP "<<paymentAmount;
    	cout<<endl<<"\t  Remaining Balance       :             PHP "<<remainingBal;
    	cout<<endl<<"____________________________________________________________";
		cout<<endl<<"\t  TOTAL PAYMENT COST      :             PHP "<<totalCost;
}

int main()
{
	char tryagain;

	do {
	    system("cls");
	    User objUser; //class user
	    objUser.userType(); 
	    
	    cout << "\n\nDo you want to try again?"; // try again option
	    cout << "\nChoose an option [Y/N]: ";
	    
	    cin >> tryagain;
	    
	    if (tryagain != 'Y' && tryagain != 'y' && tryagain != 'N' && tryagain != 'n') {
	        cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
	    }
	
	} while (tryagain == 'Y' || tryagain == 'y');
	 
	cout << "Thank You! Closing...";
	return 0;
}