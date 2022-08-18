#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <conio.h>

using namespace std;
int spool_capacity = 100, gym_capacity = 100, spa_capacity = 30;
double spool_tprice = 800;
double spool_price = 500, gym_price = 300, spa_price = 1500;
double room_price=600;
int no_of_rooms = 100;
string usrname("manager");
string precovery("recover");
int passwd=1234;
int trial=3;


struct book_room
{
	int room_number;
	string name;
	int phone_number;
	string sex;
	string nationality;
	float price;
	int pay_id;
};
struct restaurant
{
	string food;
	int quantity;
	double price;
	string type;
	int pay_id;
};
struct spool
{
    string trainer;
	int pay_id;
	float price;
};
struct gym
{
	int price;
	int pay_id;

};
struct spa
{
	int price;
	int pay_id;

};
struct food_menu
{
    string food;
    double price;
    string type;
    int pay_id;
};
// Login page manager function
int main_menu();
void guest_menu(vector<book_room> &,
	vector<restaurant> &,
	vector<spool> &,
	vector<gym> &,
	vector<spa> &,
	vector<food_menu>&);
void manager_menu(vector<book_room> &,
	vector<restaurant> &,
	vector<spool> &,
	vector<gym> &,
	vector<spa> &,
	vector<food_menu> &);

//guest menu functions
void room_service(vector<book_room> &);
void restaurant_service(vector<restaurant>&, vector<food_menu>&);
void swimming_service(vector<spool>&);
void gymnasium_service(vector<gym>&);
void spa_service(vector<spa>&);

//manager Menu functions
void manage_room(vector<book_room> &);
void manage_restaurant(vector<restaurant> &, vector<food_menu>&);
void manage_spool(vector<spool> &);
void manage_gym(vector<gym> &);
void manage_spa(vector<spa> &);

// specific funcion
bool password();
void readFile_room(vector<book_room> &);
void saveFile_room(vector<book_room>);
void readFile_restaurant(vector<restaurant>&);
void saveFile_restaurant(vector<restaurant>);
void readFile_spool(vector <spool>&);
void saveFile_spool(vector <spool>);
void readFile_gym(vector <gym>&);
void saveFile_gym(vector<gym>);
void readFile_spa(vector<spa>&);
void saveFile_spa(vector<spa>);
void readFile_food_menu(vector<food_menu>&);
void saveFile_food_menu(vector<food_menu>);

void readConstants();
void saveConstants();
void pchange();
void read_login_info();
void save_login_info();
//main function
int main()
{
	vector<book_room> v_book_room;
	vector<restaurant> v_restaurant;
	vector<spool> v_spool;
	vector<gym> v_gym;
	vector<spa> v_spa;
	vector<food_menu> v_food_menu;

	readConstants();
	read_login_info();

	readFile_room(v_book_room);
	readFile_restaurant(v_restaurant);
	readFile_spool(v_spool);
	readFile_gym(v_gym);
	readFile_spa(v_spa);
	readFile_food_menu(v_food_menu);
	bool close = false;
	do {
		cout << "\tWelcome To Hotel Management system ! " << endl <<
			"\t1. Guest Login " << endl <<
			"\t2. Manager Login " << endl <<
			"\t3. Forgot password "<<endl <<
			"\t4. Quit program " << endl;
		restart:

			cout << "\tPlease enter your choice.. \n\t";
		int choice;
		cin >> choice;
        system("cls");
		switch (choice)
		{
			case 1:
				{
					guest_menu(v_book_room, v_restaurant, v_spool, v_gym, v_spa,v_food_menu);
					break;
				}

			case 2:
				{
				    while (trial>0)
                    {
                        bool verify=password();
                        if(verify)
                        {
                            manager_menu(v_book_room, v_restaurant, v_spool, v_gym, v_spa,v_food_menu);
                        break;

                        }
                        else{cout<<"\n\t Wrong password or username \n\t"; trial--;}
                    }
                    if(trial==0){cout<<"\n\tYou exceed your trial limits!!!\n\n\t";}
				break;
				}
            case 3:
                {

                     string  recoverytemp;
                   int r=1;
                cout<<"\n\tEnter recovery code \n\t";
                cin.ignore();
                getline(cin, recoverytemp);
                r=recoverytemp.compare(precovery);
                if(r==0 )
                {
                        cout<<"\n\tEnter New password \n\t";
                        cin>>passwd;
                        cout<<"\n\t Enter New recovery code \n\t";
                        cin.ignore();
                        getline(cin, precovery);
                        cout<<"\n\tSuccessfully Changed! \n\t";
                        save_login_info();
                }
                else {cout<<"\n\tWrong username or code ! \n\t";}
                 break;
                }
			case 4:
				{
					close = true;
					break;
				}

			default:
				cout << "\n\tInvaid input! please try again\n";
				goto restart;
		}
	} while (!close);
	return 0;
}

void read_login_info()
{
    ifstream fin("log_info.txt");
    string line;
    getline (fin, line);
    istringstream iss(line);

    string fusrname,fprecovery,fpasswd;

    getline(iss, fusrname, ',');
    getline(iss, fprecovery, ',');
    getline(iss, fpasswd, ',');

    usrname=fusrname;
    precovery=fprecovery;
    passwd = atoi(fpasswd.c_str());
fin.close();
}

void save_login_info()
{
    ofstream fout("log_info.txt");
    fout<<usrname<<","<<precovery<<","<<passwd;
}
void pchange()
{
                    string utemp;
                    int ptemp,u=1,p=1;
                    cout<<"\n\tEnter current username : \n\t";
                    cin.ignore();
                    getline(cin, utemp);
                    cout<<"\n\tEnter current password : \n\t";
                    cin>>ptemp;
                    u=utemp.compare(usrname);
                    if(ptemp==passwd){p=0;}
                    if(u==0 && p==0)
                    {
                        cout<<"\n\tEnter New username \n\t";
                        cin.ignore();
                        getline(cin, usrname);
                        cout<<"\n\tEnter New password \n\t";
                        cin>>passwd;
                        cout<<"\n\t Enter recovery code \n\t";
                        cin.ignore();
                        getline(cin, precovery);
                        cout<<"\n\tSuccessfully Changed! \n\t";
                    }
                    else {cout<<"\n\tWrong user name or password! \n\t";}

}
void readConstants()
{
    ifstream fin("constants.txt");
    string line;
    getline(fin,line);
    istringstream iss(line);

    string fspool_capacity,fspool_price,fspool_tprice;
    string fgym_capacity,fgym_price;
    string fspa_capacity, fspa_price;
    string froom_price, fno_of_rooms;

        getline(iss, fspool_capacity, ',');
        getline(iss, fspool_price, ',');
        getline(iss, fspool_tprice, ',');
        getline(iss, fgym_capacity, ',');
        getline(iss, fgym_price, ',');
        getline(iss, fspa_capacity, ',');
        getline(iss, fspa_price, ',');
        getline(iss, froom_price, ',');
        getline(iss, fno_of_rooms, ',');

    spool_capacity=atoi(fspool_capacity.c_str());;
    spool_price=atof(fspool_price.c_str());
    spool_tprice=atof(fspool_tprice.c_str());
    gym_capacity=atoi(fgym_capacity.c_str());
    gym_price=atof(fgym_price.c_str());
    spa_capacity=atoi(fspa_capacity.c_str());
    spa_price=atof(fspa_price.c_str());
    room_price=atof(froom_price.c_str());
    no_of_rooms=atof(fno_of_rooms.c_str());

    fin.close();
}

void saveConstants()
{
    ofstream fout("constants.txt");
    fout<<spool_capacity<<","<<spool_price<<","<<spool_tprice
        <<","<<gym_capacity<<","<<gym_price
        <<","<<spa_capacity<<","<<spa_price
        <<","<<room_price<<","<<no_of_rooms;

    fout.close();
}
bool password()
{
    string uname;
    int pwd;
    int uverify=1,pverify=1;
    cout<<"\n\tEnter username : \n\t";
    cin.ignore();
    getline(cin, uname);
    cout<<"\n\tEnter your password :\n\t";
    cin>>pwd;
    uverify=uname.compare(usrname);
    if(pwd==passwd){pverify=0;}
    if(pverify==0 && uverify==0){return true;}
return false;
}

void readFile_room(vector<book_room> &v_book_room)
{
    ifstream fin("room.txt");
    string line;
    while(!fin.eof())
    {
        getline(fin, line);
        istringstream iss(line);

        // temprary strings used for allocating read values
        string file_name;
        string file_nationality;
        string file_sex;
        string file_room_number;
        string file_phone_number;
        string file_price;
        string file_pay_id;

        //extracting data from the file
        getline(iss, file_name, ',');
        getline(iss, file_nationality, ',');
        getline(iss, file_sex, ',');
        getline(iss, file_room_number, ',');
        getline(iss, file_phone_number, ',');
        getline(iss, file_price, ',');
        getline(iss, file_pay_id, ',');

        book_room temp;

        temp.phone_number = atoi(file_phone_number.c_str());
        temp.name = file_name;
        temp.price = atof(file_price.c_str());
        temp.pay_id = atoi(file_pay_id.c_str());
        temp.nationality =file_nationality;
        temp.sex =file_sex;
        temp.room_number=atoi(file_room_number.c_str());

        v_book_room.push_back(temp);
    }
        fin.close();

}

void saveFile_room(vector<book_room> v_book_room)
{
    ofstream fout("room.txt");
    int newline=0;
    for(vector <book_room>::iterator it = v_book_room.begin(); it!=v_book_room.end(); ++it)
    {
        fout<<it->name<<","<<it->nationality<<","<<it->sex<<","
            <<it->room_number<<","<<it->phone_number<<","
            <<it->price<<","<<it->pay_id;
            newline++;
        if(newline != (int)v_book_room.size()){fout<<endl;}
    }
    fout.close();

}

void readFile_restaurant(vector<restaurant>& v_restaurant)
{
    ifstream fin("restaurant.txt");
    string line;
    while(!fin.eof())
    {
        getline(fin, line);
        istringstream iss(line);

        // temprary strings used for allocating read values
        string file_food;
        string file_type;
        string file_quantity;
        string file_price;
        string file_pay_id;

        //extracting data from the file
        getline(iss, file_food, ',');
        getline(iss, file_type, ',');
        getline(iss, file_quantity, ',');
        getline(iss, file_price, ',');
        getline(iss, file_pay_id, ',');

        restaurant temp;

        temp.food = file_food;
        temp.quantity = atof(file_quantity.c_str());
        temp.pay_id = atoi(file_pay_id.c_str());
        temp.price =atof(file_price.c_str());
        temp.type=file_type;

        v_restaurant.push_back(temp);
    }
        fin.close();

}

void saveFile_restaurant(vector <restaurant> v_restaurant)
{
    ofstream fout("restaurant.txt");
    int newline=0;
    for(vector <restaurant>::iterator it = v_restaurant.begin(); it!=v_restaurant.end(); ++it)
    {
        fout<<it->food<<","<<it->type<<","<<it->quantity<<","
            <<it->price<<","<<it->pay_id;
            newline++;
        if(newline != (int)v_restaurant.size()){fout<<endl;}
    }
    fout.close();

}

void readFile_spool(vector <spool>& v_spool)
{
    ifstream fin("spool.txt");
    string line;
    while(!fin.eof())
    {
        getline(fin, line);
        istringstream iss(line);

        // temprary strings used for allocating read values
        string file_trainer;
        string file_price;
        string file_pay_id;

        //extracting data from the file
        getline(iss, file_trainer, ',');
        getline(iss, file_price, ',');
        getline(iss, file_pay_id, ',');

        spool temp;

        temp.trainer = file_trainer;
        temp.pay_id = atoi(file_pay_id.c_str());
        temp.price =atof(file_price.c_str());

        v_spool.push_back(temp);
    }
        fin.close();

}

void saveFile_spool(vector <spool> v_spool)
{
    ofstream fout("spool.txt");
    int newline=0;
    for(vector <spool>::iterator it = v_spool.begin(); it!=v_spool.end(); ++it)
    {
        fout<<it->trainer<<","
            <<it->price<<","<<it->pay_id;
            newline++;
        if(newline != (int)v_spool.size()){fout<<endl;}
    }
    fout.close();

}

void readFile_gym(vector <gym>& v_gym)
{
    ifstream fin("gym.txt");
    string line;
    while(!fin.eof())
    {
        getline(fin, line);
        istringstream iss(line);

        // temprary strings used for allocating read values
        string file_price;
        string file_pay_id;

        //extracting data from the file
        getline(iss, file_price, ',');
        getline(iss, file_pay_id, ',');

        gym temp;

        temp.pay_id = atoi(file_pay_id.c_str());
        temp.price =atof(file_price.c_str());

        v_gym.push_back(temp);
    }
        fin.close();

}

void saveFile_gym(vector <gym> v_gym)
{
    ofstream fout("gym.txt");
    int newline=0;
    for(vector <gym>::iterator it = v_gym.begin(); it!=v_gym.end(); ++it)
    {
        fout<<it->price<<","<<it->pay_id;
            newline++;
        if(newline != (int)v_gym.size()){fout<<endl;}
    }
    fout.close();

}

void readFile_spa(vector <spa>& v_spa)
{
    ifstream fin("spa.txt");
    string line;
    while(!fin.eof())
    {
        getline(fin, line);
        istringstream iss(line);

        // temprary strings used for allocating read values
        string file_price;
        string file_pay_id;

        //extracting data from the file
        getline(iss, file_price, ',');
        getline(iss, file_pay_id, ',');

        spa temp;

        temp.pay_id = atoi(file_pay_id.c_str());
        temp.price =atof(file_price.c_str());

        v_spa.push_back(temp);
    }
        fin.close();

}

void saveFile_spa(vector <spa> v_spa)
{
    ofstream fout("spa.txt");
    int newline=0;
    for(vector <spa>::iterator it = v_spa.begin(); it!=v_spa.end(); ++it)
    {
        fout<<it->price<<","<<it->pay_id;
            newline++;
        if(newline != (int)v_spa.size()){fout<<endl;}
    }
    fout.close();

}

void readFile_food_menu(vector<food_menu>& v_food_menu)
{
    ifstream fin("food_menu.txt");
    string line;
    while(!fin.eof())
    {
        getline(fin, line);
        istringstream iss(line);

        // temprary strings used for allocating read values
        string file_food;
        string file_type;
        string file_price;
        string file_pay_id;

        //extracting data from the file
        getline(iss, file_food, ',');
        getline(iss, file_type, ',');
        getline(iss, file_price, ',');
        getline(iss, file_pay_id, ',');

        food_menu temp;

        temp.food = file_food;
        temp.pay_id = atoi(file_pay_id.c_str());
        temp.price =atof(file_price.c_str());
        temp.type=file_type;

        v_food_menu.push_back(temp);
    }
        fin.close();

}

void saveFile_food_menu(vector<food_menu> v_food_menu)
{
    ofstream fout("food_menu.txt");
    int newline=0;
    for(vector <food_menu>::iterator it = v_food_menu.begin(); it!=v_food_menu.end(); ++it)
    {
        fout<<it->food<<","<<it->type<<","
            <<it->price<<","<<it->pay_id;
            newline++;
        if(newline != (int)v_food_menu.size()){fout<<endl;}
    }
    fout.close();

}

// Guest Menu functions
void guest_menu(vector<book_room> &v_book_room,
                vector<restaurant> &v_restaurant,
                vector<spool> &v_spool,
                vector<gym> &v_gym,
                vector<spa> &v_spa,
                vector<food_menu> &v_food_menu)
{
	bool back = false;

	do {
		cout << "\n\t1. Room service" <<
			"\n\t2. Restaurant " <<
			"\n\t3. Swimming pool" <<
			"\n\t4. Gymnasium" <<
			"\n\t5. Spa" <<
			"\n\t6. Back \n\t";

		int mchoise;
		retry:
			cin >> mchoise;
			system("cls");
		switch (mchoise)
		{
			case 1:
				{
					room_service(v_book_room);
					break;
				}

			case 2:
				{
					restaurant_service(v_restaurant,v_food_menu);
					break;
				}

			case 3:
				{
					swimming_service(v_spool);
					break;
				}

			case 4:
				{
					gymnasium_service(v_gym);
					break;
				}

			case 5:
				{
					spa_service(v_spa);
					break;
				}

			case 6:
				{
					back = true;
					break;
				}

			default:
				cout << "\n\t Invalid option, please try again!\n\t";
				goto retry;

		}
	} while (!back);
}

void room_service(vector<book_room> &v_book_room)
{
	int rchoise;

	cout << endl << "\t1. book a room" <<
		endl << "\t2. Check available rooms \n\t";
	cin >> rchoise;
	system("cls");
	switch (rchoise)
	{
		case 1:
			{
				book_room temp;
				bool check;
				do {
					check = true;
					cout << "\n\tRoom Number :\n\t";
					cin >> temp.room_number;
					if (temp.room_number < 1 || temp.room_number > no_of_rooms)
					{
						cout << "\n\tPlease enter between 1 and " << no_of_rooms << " only \n\t";
						check = false;
					}
					else
					{
						for (int i = 0; i < (int)v_book_room.size(); i++)
						{
							if (v_book_room[i].room_number == temp.room_number)
							{
								check = false;
								cout << "\n\tSorry the room is not available. please try again! \n\t";
							}
						}
					}
				} while (!check);
				cout << "\n\tFull Name :\n\t";
				cin.ignore();
				getline(cin, temp.name);
				cout << "\n\tPhone Number :\n\t";
				cin >> temp.phone_number;
				sx:
				cout << "\n\tSex (M/F) :\n\t";
				cin.ignore();
				cin >> temp.sex;
				if(temp.sex=="m"||temp.sex=="M"||temp.sex=="f"||temp.sex=="F"){;}
				else {cout<<"\n\tInvalid input! please try again \n"; goto sx;}
				cout << "\n\tNationality :\n\t";
				cin.ignore();
				getline(cin, temp.nationality);
				cout << "\n\tNet price is $"<<setprecision(2)<<fixed
                     <<room_price<<", do you want to continue? (y/n) :\n\t";
                    string price_check;
                    cin>>price_check;
                    if(price_check=="y"|| price_check=="Y")
                    {
                        temp.price=room_price;
                    }
                    else {break;}
				cout << "\n\tPayment id :\n\t";
				cin >> temp.pay_id;
				system("cls");
				v_book_room.push_back(temp);
                saveFile_room(v_book_room);

				cout << "\n\t Successfully Booked room number " << temp.room_number << " !\n\t";
				break;
			}

		case 2:
			{
				int count = 0;
				for (int i = 0; i <(int) v_book_room.size(); i++)
				{
					count++;
					if (v_book_room.size() != 0)
					{
						cout << "\n\t Room Number " << v_book_room[i].room_number << " is checked \n\t";
					}
					else cout << "\n\tAll rooms are available! \n\t";
				}

				cout << "\n\t A total of " << count << " rooms checked!\n\t";
				break;
			}
    }
}
void restaurant_service(vector <restaurant>& v_restaurant, vector<food_menu>& v_food_menu)
{
    cout <<"\n\t\t Guest Restaurant Service Menu \n";
	cout<<"\n\t1. Show food menu"
        <<"\n\t2.  Order food"
        <<"\n\t3. Back\n\t";
    int reschoice;
    cin>>reschoice;
    system("cls");
    switch(reschoice)
    {
    case 1:
        {
            cout <<"\n\t"<<setw(15)<<"Food Name"<<setw(15)<<"Price $";
            for(int i=0; i<(int)v_restaurant.size(); i++)
            {
                if(v_restaurant[i].type=="f"||v_restaurant[i].type=="F")
                {
                    cout <<"\n\t"<<setw(15)<<v_restaurant[i].food
                         <<setw(15)<<setprecision(2)<<fixed
                         <<v_restaurant[i].price<<"$";
                }
            }
            cout <<"\n\n\t"<<setw(15)<<"Beverage Name"<<setw(15)<<"Price $";
            for(int i=0; i<(int)v_restaurant.size(); i++)
            {
                if(v_restaurant[i].type=="d"||v_restaurant[i].type=="D")
                {
                    cout <<"\n\t"<<setw(15)<<v_restaurant[i].food
                         <<setw(15)<<setprecision(2)<<fixed
                         <<v_restaurant[i].price<<"$";
                }
            }
        break;
        }
    case 2:
        {
            bool fcheck=false;
            int ftemp=0;
            food_menu rtemp;
            cout<<"\n\tEnter the name of the food : \n\t";
            cin.ignore();
            getline(cin, rtemp.food);
            for(int i=0; i<(int)v_restaurant.size(); i++)
            {
                if(rtemp.food==v_restaurant[i].food){fcheck=true; ftemp=i;}
            }
            if(fcheck==false){cout<<"\n\tCan't find on the menu, Please try again! \n\t"; break;}
            cout<<"\n\tThe price is "<<setprecision(2)<<fixed
                <<v_restaurant[ftemp].price<<"$"
                <<" Do you want to continue ? :(y/n)\n\t";
            char rcont;
            cin>>rcont;
            if(rcont=='y'||rcont=='Y'){;}
            else {break;}
            cout<<"\n\tEnter transaction ID :\n\t";
            cin>>rtemp.pay_id;
            rtemp.price=v_restaurant[ftemp].price;
            rtemp.type=v_restaurant[ftemp].type;
            cout<<"\n\t "<<rtemp.food<<" Successfully ordered !\n\t";
            v_food_menu.push_back(rtemp);
            saveFile_food_menu(v_food_menu);
        }
    }
}

void swimming_service(vector <spool>& v_spool)
{
	cout <<"\n\t\tSwimming Pool Service Menu\n";
	cout<<"\n\t1. Check available space "
        <<"\n\t2. Get service"
        <<"\n\t3. Back\n\t";
    int choice;
    cin>>choice;
    system("cls");
    switch (choice)
    {
    case 1:
        {
            if((int)v_spool.size()<= spool_capacity)
            {
                cout<<"\n\tThere are "<<spool_capacity-(int)v_spool.size()<<" free space left currently! \n\t";
            }
            else {cout<<"\n\tSorry!! the pool has reached its maximum capacity, try next time! \n\t"; }
            break;
        }
    case 2:
        {  spool temp;
            if((int)v_spool.size()<= spool_capacity)
            {
                char trn;
                cout<<"\n\tDo you want  a personal trainer? (y/n)\n\t";
                cin>>trn;
                if (trn=='y'||trn=='Y')
                {
                    temp.trainer="Yes";
                    cout<<"\n\t The net price is "<<setprecision(2)<<fixed
                        <<spool_tprice<<"$, "
                        <<"Do you want to coninue? (y/n)\n\t";
                        char np;
                        cin>>np;
                        if(np=='y'||np=='Y')
                        {
                            cout<<"\n\tEnter transaction id \n\t";
                            cin>>temp.pay_id;
                            cout<<"\n\tYou have successfully subscribed for the swimming pool service \n\t";
                            temp.price= spool_tprice;

                            v_spool.push_back(temp);
                            saveFile_spool(v_spool);
                        }
                        else {cout<<"\n\tProcess canceled! \n\t";}

                }
                else if(trn=='n'||trn=='N')
                {
                    temp.trainer="No";
                    cout<<"\n\t The net price is "<<setprecision(2)<<fixed
                        <<spool_price<<"$, "
                        <<"Do you want to coninue? (y/n)\n\t";
                        char np;
                        cin>>np;
                        if(np=='y'||np=='Y')
                        {
                            cout<<"\n\tEnter transaction id \n\t";
                            cin>>temp.pay_id;
                            cout<<"\n\tYou have successfully subscribed for the swimming pool service \n\t";
                            temp.price= spool_price;

                            v_spool.push_back(temp);
                            saveFile_spool(v_spool);
                        }
                        else {cout<<"\n\tProcess Canceled! \n\t";}

                }
                else {cout<<"\n\tInvalid input! \n\t"; break;}
            }
            else {cout<<"\n\tSorry!! the pool has reached its maximum capacity, try next time! \n\t"; }
            break;
        }
    case 3:
        {
            break;
        }
    default : cout<<"\n\tInvalid input! \n\t";
    }
}

void gymnasium_service(vector <gym>& v_gym)
{
	cout <<"\n\t Gymnasium service menu \n";
	cout<<"\n\t1. Check available space "
        <<"\n\t2. Get service"
        <<"\n\t3. Back\n\t";
    int choice;
    cin>>choice;
    system("cls");
    switch (choice)
    {
    case 1:
        {
            if((int)v_gym.size()<= gym_capacity)
            {
                cout<<"\n\tThere are "<<gym_capacity-(int)v_gym.size()<<" free space left currently! \n\t";
            }
            else {cout<<"\n\tSorry!! the Gym has reached its maximum capacity, try next time! \n\t"; }
            break;
        }
    case 2:
        {
            gym temp;
            if((int)v_gym.size()<= gym_capacity)
            {
        cout<<"\n\t The net price is "<<setprecision(2)<<fixed
            <<gym_price<<"$, "
            <<"Do you want to coninue? (y/n)\n\t";
            char np;
            cin>>np;
            if(np=='y'||np=='Y')
            {
                cout<<"\n\tEnter transaction id \n\t";
                cin>>temp.pay_id;
                cout<<"\n\tYou have successfully subscribed for the gym service \n\t";
                temp.price= gym_price;

                v_gym.push_back(temp);
                saveFile_gym(v_gym);
             }
            else {cout<<"\n\tProcess canceled! \n\t";}
            }
        else {cout<<"\n\tSorry!! the gym has reached its maximum capacity, try next time! \n\t"; }
            break;
        }
    case 3:
        {
            break;
        }
    default : cout<<"\n\tInvalid input! \n\t";
    }
}

void spa_service(vector <spa>& v_spa)
{
    cout <<"\n\t Spa service menu \n";
	cout<<"\n\t1. Check available space "
        <<"\n\t2. Get service"
        <<"\n\t3. Back\n\t";
    int choice;
    cin>>choice;
    system("cls");
    switch (choice)
    {
    case 1:
        {
            if((int)v_spa.size()<= spa_capacity)
            {
                cout<<"\n\tThere are "<<spa_capacity-(int)v_spa.size()<<" free space left currently! \n\t";
            }
            else {cout<<"\n\tSorry!! the Spa has reached its maximum capacity, try next time! \n\t"; }
            break;
        }
    case 2:
        {
            spa temp;
        if((int)v_spa.size()<= spa_capacity)
        {
        cout<<"\n\t The net price is "<<setprecision(2)<<fixed
            <<spa_price<<"$, "
            <<"Do you want to coninue? (y/n)\n\t";
            char np;
            cin>>np;
            if(np=='y'||np=='Y')
            {
                cout<<"\n\tEnter transaction id \n\t";
                cin>>temp.pay_id;
                cout<<"\n\tYou have successfully subscribed for the Spa service \n\t";
                temp.price= spa_price;

                v_spa.push_back(temp);
                saveFile_spa(v_spa);
            }
            else {cout<<"\n\tProcess canceled! \n\t";}
        }
        else {cout<<"\n\tSorry!! the spa has reached its maximum capacity, try next time! \n\t"; }
            break;
        }
    case 3:
        {
            break;
        }
    default : cout<<"\n\tInvalid input! \n\t";
    }
}


// manager functions
void manager_menu(vector<book_room> &v_book_room,
                  vector<restaurant> &v_restaurant,
                  vector<spool> &v_spool,
                  vector<gym> &v_gym,
                  vector<spa> &v_spa,
                  vector<food_menu>& v_food_menu)
{
    trial=3;
	cout << "\n\tWelcome to manager menu!\n\t";
	bool back = false;
	while (!back)
	{
		cout << "\n\t1. Manage Rooms" <<
			"\n\t2. Manage Restaurant" <<
			"\n\t3. Manage Swimming Pool" <<
			"\n\t4. Manage Gymnasium" <<
			"\n\t5. Manage Spa" <<
			"\n\t6. Change Username & Password" <<
			"\n\t7. Back \n\t";
		retry:
			int option;
		cin >> option;
		system("cls");
		switch (option)
		{
			case 1:
				{
					manage_room(v_book_room);
					break;
				}

			case 2:
				{
					manage_restaurant(v_restaurant,v_food_menu);
					break;
				}

			case 3:
				{
					manage_spool(v_spool);
					break;
				}

			case 4:
				{
					manage_gym(v_gym);
					break;
				}

			case 5:
				{
					manage_spa(v_spa);
					break;
				}
            case 6:
                {
                    pchange();
                    save_login_info();
                    break;
                }

			case 7:
				{
					back = true;
					break;
				}

			default:
				cout << "\n\t Invalid option, please try again!\n\t";
				goto retry;
		}
	}
}

void manage_room(vector<book_room> &v_book_room)
{
	cout << "\n\t1. show checked rooms " <<
		"\n\t2. show report" <<
		"\n\t3. uncheck room" <<
		"\n\t4. search for a room data"
		"\n\t5. change room price"
		"\n\t6. change number of room"<<
		"\n\t7. back\n\t";
	int option;
	cin >> option;
	system("cls");
	switch (option)
	{
		case 1:
			{
				int count = 0;
				for (int i = 0; i <(int) v_book_room.size(); i++)
				{
					count++;
					if (v_book_room.size() != 0)
					{
						cout << "\n\t Room Number " << v_book_room[i].room_number << " is checked \n\t";
					}
					else cout << "\n\tAll rooms are available! \n\t";
				}

				cout << "\n\t A total of " << count << " rooms checked!\n\t";
				break;
			}

		case 2:
			{
			    double net=0;
				cout << "\t" << setw(10) << left << "Rm.No" <<
				setw(15) << left << "Name" <<
				setw(20) << right << "P.Nmbr" <<
				setw(10) << right << "Sex" <<
				setw(15) << right << "Nationality" <<
				setw(12) << right << "Price $" <<
				setw(15) << right << "Payment Id" <<
				endl << endl;
				for (int i = 0; i <(int) v_book_room.size(); i++)
				{
					cout << "\t" << setw(10) << left << v_book_room[i].room_number <<
						setw(15) << left << v_book_room[i].name <<
						setw(20) << right << v_book_room[i].phone_number <<
						setw(10) << right << v_book_room[i].sex <<
						setw(15) << right << v_book_room[i].nationality <<
						setw(10) << right<<setprecision(2)<< fixed << v_book_room[i].price <<"$"<<
						setw(15) << right << v_book_room[i].pay_id <<
						endl;
						net+= v_book_room[i].price;

				}
				cout <<"\n\t\t"<<"Total Revenue : $"<<setprecision(2)<<net;

				break;
			}

		case 3:
			{
				cout << "\n\tPlease Enter the room number to be unchecked :\n\t";
				int del, temp = -1;
				cin >> del;
				for (int i = 0; i <(int) v_book_room.size(); i++)
				{
					if (del == v_book_room[i].room_number)
					{
						temp = i;
					}
				}

				if (temp != (-1))
				{
					{
						cout << "\n\tAre you sure? (y/n)\n\t";
						char sure;
						cin >> sure;
						if (sure == 'Y' || sure == 'y')
						{
							cout << "\n\tSuccessfully cleared room number " << v_book_room[temp].room_number << ".\n\t";
							v_book_room.erase(v_book_room.begin() + temp);
								saveFile_room(v_book_room);

						}
					}
				}
				else
				{
					cout << "\n\tSorry, The room is already empty! \n\t";
				}

				break;
			}

		case 4:
			{
				cout << "\n\tEnter room number\n\t";
				int rn, no_result = 0;
				cin >> rn;
				for (int i = 0; i <(int) v_book_room.size(); i++)
				{
					if (rn == v_book_room[i].room_number)
					{
						cout << "\t" << setw(10) << left << "Rm.No" <<
							setw(15) << left << "Name" <<
							setw(20) << right << "P.Nmbr" <<
							setw(10) << right << "Sex" <<
							setw(15) << right << "Nationality" <<
							setw(15) <<right << "Price $" <<
							setw(15) << right << "Payment Id" <<
							endl;
						cout << "\t" << setw(10) << left << v_book_room[i].room_number <<
							setw(15) << left << v_book_room[i].name <<
							setw(20) << right << v_book_room[i].phone_number <<
							setw(10) << right << v_book_room[i].sex <<
							setw(15) << right << v_book_room[i].nationality <<
							setw(15) << right << setprecision(2)<<fixed<< v_book_room[i].price <<
							setw(15) << right << v_book_room[i].pay_id <<
							endl << "\t";
						no_result = 1;
					}
				}

				if (no_result == 0)
				{
					cout << "\n\tThe room is not booked yet! \n\t";
				}

				break;
			}
        case 5:
            {
                cout<<"\n\tEnter the new price \n\t";
                cin>>room_price;
                cout<<"\n\tPrice successfully updated!\n\t";
                saveConstants();
                break;
            }
        case 6:
            {
                cout<<"\n\tEnter the new number of rooms \n\t";
                cin>>no_of_rooms;
                cout<<"\n\tNumber of rooms successfully updated!\n\t";
                saveConstants();
                break;
            }
        case 7:
            {
                break;
            }
		default:
			cout << "\n\tInvlid input\n\t";
	}

}

void manage_restaurant(vector<restaurant> &v_restaurant, vector<food_menu>& v_food_menu)
{
	int choice;
	cout << "\n\tManage Restaurant Menu\n\t";
	cout << "\n\t1. display food menu " <<
		"\n\t2. Add food &drinks" <<
		"\n\t3. Modify food &drink data" <<
		"\n\t4. Show Report" <<
		"\n\t5. Back\n\t";
	cin >> choice;
	system("cls");
	switch (choice)
	{
		case 1:
			{
				cout << "\n\t\t\t Food Menu\n";
				cout << "\n\t" <<
				"    " << setw(15) << left << "food" <<
				setw(10) << "kind(f/d)" <<
				setw(10) << right << "Price" <<
				setw(10) << right << "Quantity";

				for (int i = 0; i <(int) v_restaurant.size(); i++)
				{
					cout << "\n\t" << i + 1 <<
						".  " << setw(15) << left << v_restaurant[i].food <<
						setw(10) << v_restaurant[i].type <<
						setw(10) << right << setprecision(2) << fixed << v_restaurant[i].price <<
						setw(10) << right << v_restaurant[i].quantity;

				}

				cout << endl;
				break;
			}

		case 2:
			{
				restaurant temp;
				cout << "\n\tAdd food menu\n\t";
				retry: cout << "\n\tEnter food Name :\n\t";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				getline(cin, temp.food);
				for (int i = 0; i <(int) v_restaurant.size(); i++)
				{
					if (temp.food == v_restaurant[i].food)
					{
						cout << "\n\tThe item already exists in the system. Retry again!\n\t";
						goto retry;
					}
				}

				retr: cout << "\n\tFood type or drink type? (f/d) :\n\t";
				cin >> temp.type;
				if (temp.type == "f" || temp.type == "F" || temp.type == "d" || temp.type == "D")
				{;
				}
				else
				{
					cout << "\n\tinvalid input!\tPlease type \"f\" or \"d\" only \n";
					goto retr;
				}

				cout << "\n\tHow much quantity? :\n\t";
				cin >> temp.quantity;
				cout << "\n\tSet price :\n\t";
				cin >> temp.price;

				v_restaurant.push_back(temp);
				saveFile_restaurant(v_restaurant);
				cout << "\n\t" << temp.food << " successfully added to the menu \n\t";
				break;
			}

		case 3:
			{
				restaurant temp;
				int check = 0;
				cout << "\n\tModify food Menu \n\t";
				cout << "\n\tEnter food or drink name \n\t";
				cin.ignore();
				getline(cin, temp.food);
				for (int i = 0; i <(int) v_restaurant.size(); i++)
				{
					if (temp.food == v_restaurant[i].food)
					{
						check = 1;
						cout << "\n\t1. change price :" <<
							"\n\t2. change quantity :" <<
							"\n\t3. delete from menu :" <<
							"\n\t4. back\n\t";
						int choice;
						cin >> choice;
						switch (choice)
						{
							case 1:
								{
									cout << "\n\tEnter price :\n\t";
									cin >> v_restaurant[i].price;
									cout << "\n\tSuccessfully changed! \n\t";
									break;
								}

							case 2:
								{
									cout << "\tEnter Quantity :\n\t";
									cin >> v_restaurant[i].quantity;
									cout << "\n\tSuccessfully changed! \n\t";
									break;
								}

							case 3:
								{
									v_restaurant.erase(v_restaurant.begin() + i);
									cout << "\n\tSuccessfully deleted!\n\t";
									break;
								}

							case 4:
								{
									break;
								}
							default:
								cout << "\n\tInvalid input\n\t";
						}
					}
				}

				if (check == 0)
				{
					cout << "\n\tThe food is not found on the menu! \n\t please try again. \n\t";
				}
								saveFile_restaurant(v_restaurant);
				break;
			}

		case 4:
			{
			    int netreveinue=0;
			    cout <<"\n\t\t Show Report Menu \n";
			    cout<<"\n\t"<<setw(20)<<"Food Name"<<setw(10)<<"Price $";
			    for (int i=0; i<(int)v_food_menu.size(); i++)
                {
                    cout<<"\n\t"<<setw(20)<<v_food_menu[i].food<<setw(10)
                        <<setprecision(2)<<fixed<<v_food_menu[i].price<<"$ ";
                        netreveinue += v_food_menu[i].price;
                }
                cout<<"\n\t\tNet Revenue : "<<"\t"<<netreveinue<<"$\n\t";
				break;
			}

		case 5:
			{
				break;
			}
	}
	saveFile_food_menu(v_food_menu);
}

void manage_spool(vector<spool> &v_spool)
{
	cout << "\n\t\tManager Swimming Pool Menu \n";
	cout << "\n\t1. Set the capacity" <<
		"\n\t2. Set price" <<
		"\n\t3. show report " <<
		"\n\t4. clear customer data " <<
		"\n\t5. Back \n\n\t";
	int choose;
	cin >> choose;
	system("cls");
	switch (choose)
	{
		case 1:
			{
				cout << "\n\tEnter the new capacity :\n\t";
				cin >> spool_capacity;
				cout << "\n\tThe capacity successfully changed! \n\t";
				saveConstants();
				break;
			}

		case 2:
			{
				cout << "\n\t1. price for trainer need customer" <<
				"\n\t2. price for without trainer customer\n\t";
				int trnr;
				cin >> trnr;
				switch (trnr)
				{
					case 1:
						{
							cout << "\n\tEnter the new Price :\n\t";
							cin >> spool_tprice;
							cout << "\n\tThe price successfully changed! \n\t";
							break;
						}

					case 2:
						{
							cout << "\n\tEnter the new Price :\n\t";
							cin >> spool_price;
							cout << "\n\tThe price successfully changed! \n\t";
							break;
						}

					default:
						cout << "\n\tInvalid input!\n\t";
				}
				saveConstants();
				break;
			}

		case 3:
			{
				int totuser = 0;
				double totprice = 0;
				cout << "\n\t Swimming pool Report \n\n";
				cout << "\t   " << setw(12) << "Users" <<
				setw(12) << "trainer" <<
				setw(12) << "Price" <<
				setw(15) << "pay ID\n";
				for (int i = 0; i <(int) v_spool.size(); i++)
				{
					cout << "\n\t" << i + 1 << ". " <<
						setw(10) << "User" << i + 1 <<
						setw(12) << v_spool[i].trainer <<
						setw(12) << setprecision(2) << fixed << v_spool[i].price <<
						setw(15) << v_spool[i].pay_id;
					totuser = i + 1;
					totprice += v_spool[i].price;
				}

				cout << "\n\n\t\t Total users : " << totuser << setw(20) << right << "Total Revenue : " << totprice << endl;
				break;
			}

		case 4:
			{
				int k = v_spool.size();
				for (int i = 0; i < k; i++)
				{
					v_spool.pop_back();
				}
				saveFile_spool(v_spool);
				cout << "\n\tcurrent data successfully cleared\n";
				break;
			}

		default:
			cout << "\n\tInvalid input!\n\t";
	}
}

void manage_gym(vector<gym> &v_gym)
{
	cout << "\n\t\t Manager gymnasium Menu \n";
	cout << "\n\t1. Set the capacity" <<
		"\n\t2. Set price" <<
		"\n\t3. show report " <<
		"\n\t4. clear customer data " <<
		"\n\t5. Back \n\n\t";
	int choice;
	cin >> choice;
	system("cls");
	switch (choice)
	{
		case 1:
			{
				cout << "\n\tEnter the new capacity :\n\t";
				cin >> gym_capacity;
				cout << "\n\tThe capacity successfully changed! \n\t";
				break;
				saveConstants();
			}

		case 2:
			{
				cout << "\n\tEnter the new Price :\n\t";
				cin >> gym_price;
				cout << "\n\tThe price successfully changed! \n\t";
				saveConstants();
				break;
			}

		case 3:
			{
				int totuser = 0;
				double totprice = 0;
				cout << "\n\t Gym Report \n\n";
				cout << "\t   " << setw(12) << "Users" <<
				setw(12) << "Price" <<
				setw(15) << "Pay ID\n";
				for (int i = 0; i <(int) v_gym.size(); i++)
				{
					cout << "\n\t" << i + 1 << ". " << setw(10) << "User" << i + 1 <<
						setw(12) << setprecision(2) << fixed << v_gym[i].price <<
						setw(15) << v_gym[i].pay_id;
					totuser = i + 1;
					totprice += v_gym[i].price;
				}

				cout << "\n\n\t Total users : " << totuser << setw(20) << right << "Total Revenue : " << totprice << endl;
				break;
			}

		case 4:
			{
				int k = v_gym.size();
				for (int i = 0; i < k; i++)
				{
					v_gym.pop_back();
				}
				saveFile_gym(v_gym);
				cout << "\n\tcurrent data successfully cleared\n";
				break;
			}

		default:
			cout << "\n\tInvalid input!\n\t";
	}
}

void manage_spa(vector<spa> &v_spa)
{
	cout << "\n\t\t Manager Spa Menu \n";
	cout << "\n\t1. Set the capacity" <<
		"\n\t2. Set price" <<
		"\n\t3. show report " <<
		"\n\t4. clear customer data " <<
		"\n\t5. Back \n\n\t";
	int choice;
	cin >> choice;
	system("cls");
	switch (choice)
	{
		case 1:
			{
				cout << "\n\tEnter the new capacity :\n\t";
				cin >> spa_capacity;
				cout << "\n\tThe capacity successfully changed! \n\t";
				saveConstants();
				break;
			}

		case 2:
			{
				cout << "\n\tEnter the new Price :\n\t";
				cin >> spa_price;
				cout << "\n\tThe price successfully changed! \n\t";
				saveConstants();
				break;
			}

		case 3:
			{
				int totuser = 0;
				double totprice = 0;
				cout << "\n\t Spa Report \n\n";
				cout << "\t   " << setw(12) << "Users" <<
				setw(12) << "Price" <<
				setw(15) << "Pay ID\n";
				for (int i = 0; i <(int) v_spa.size(); i++)
				{
					cout << "\n\t" << i + 1 << ". " << setw(10) << "User" << i + 1 <<
						setw(12) << setprecision(2) << fixed << v_spa[i].price <<
						setw(15) << v_spa[i].pay_id;
					totuser = i + 1;
					totprice += v_spa[i].price;
				}

				cout << "\n\n\t Total users : " << totuser << setw(20) << right << "Total Revenue : " << totprice << endl;
				break;
			}

		case 4:
			{
				int k = v_spa.size();
				for (int i = 0; i < k; i++)
				{
					v_spa.pop_back();
				}
				saveFile_spa(v_spa);
				cout << "\n\tcurrent data successfully cleared\n";
				break;
			}

		default:
			cout << "\n\tInvalid input!\n\t";
	}
}
