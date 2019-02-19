#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <cstring>
#include <iomanip>
using namespace std;

// Print the deck of player and player2
void print_deck(vector<string> player,vector<string> player2){

    cout << " Player 1:" << endl;
    for(int i=0; i<player.size(); i++){
        player[i][0]=='0'?
            cout << " [---]" :
            cout << " [---]" ;
    }
    cout << endl << endl;

    cout << " Player 2:" << endl;
    for(int i=0; i<player2.size(); i++){
        player2[i][0]=='0'?
            cout << " [" << player2[i][1] << player2[i][2] << player[i][3] <<  "]" :
            cout << " [" << player2[i] << "]" ;
    }
    cout << endl;
}

bool check_num(int n){
    if(n>=1 && n<=13)
        return true;
    else
        return false;
}

// Modify the array in the main and insert the hypen in array
void insert_hyp_func(vector<string> &player, int player_hyp,int whosplayer){

	if(player_hyp>0){
		cout << " \n\n Your turn to Arrange your Deck\n Initial Deck:\n" << endl;
		int insert_hyp;

		vector<string> vec_temp;
		for(int i=0; i<player_hyp; i++){
			vec_temp.push_back(player[0]);
			player.erase(player.begin());
		}

			for(int i=0; i<player.size(); i++){
				player[i][0]=='0'?
					cout << " [" << player[i][1] << player[i][2] << player[i][3] << "]" :
					cout << " [" << player[i] << "]" ;
			}
			cout << endl;

		string temp_hyp;
		for(int i=0; i<player_hyp; i++){
			cout << "\n\n Input the LOCATION to insert  [" << ' ' << vec_temp[i][1] << vec_temp[i][2]  << "]  dash to your Cards" << endl;
			tele5:;
			cout << " Input: ";
			cin >> insert_hyp;  // this is an index
				if(check_num(insert_hyp)==false){
					cout << " [[PLEASE Input 1-13 only!]]\n " << endl;
					goto tele5;
			}
			insert_hyp--;		// to make it 0 index
			temp_hyp = vec_temp[i];

			player.insert(player.begin()+insert_hyp,temp_hyp);

			cout << " \n\n Updated Cards:\n" << endl;
			for(int i=0; i<player.size(); i++){
				player[i][0]=='0'?
					cout << " [" << player[i][1] << player[i][2] << player[i][3] << "]" :
					cout << " [" << player[i] << "]" ;
			}
			cout << endl;

		}
	}
}

string convert_str(string str){
    if(str=="0")        return "00";
    else if(str=="1")   return "01";
    else if(str=="2")   return "02";
    else if(str=="3")   return "03";
    else if(str=="4")   return "04";
    else if(str=="5")   return "05";
    else if(str=="6")   return "06";
    else if(str=="7")   return "07";
    else if(str=="8")   return "08";
    else if(str=="9")   return "09";
    else if(str=="10")  return "10";
    else if(str=="11")  return "11";
    else if(str=="-")   return "0-";

    else
        return "ERROR";
}

string encrypt(vector<string> vec){
    string temp="";
    for(int i=0; i<vec.size(); i++){
        temp += vec[i] + ' ';
    }
    return temp;
}

vector<string> tokenizer(string str){
    vector<string> temp;
    stringstream ss(str);
    ss << str;
    while(ss>>str)
        temp.push_back(str);

    return temp;
}

int convert_string(string str){
    int x;
    stringstream ss(str);
    ss << str;
    ss >> x;

    return x;
}

string convert_int(int x){
    stringstream ss;
    ss << x;
    return ss.str();
}

void print_token(string player){
    vector<string> temp;
    stringstream ss(player);
    ss << player;
    cout << ' ';
    while(ss>>player){
        player[0]=='0'?
                    cout << " [" << player[1] << player[2] << player[3] << "]" :
                    cout << " [" << player << "]" ;
    }
}

void modified_print(vector<string> &player,vector<string> &player2){
         cout << " \n  Da Vinci Code - [GAME STARTS]  \n " << endl;
            cout << " Player 1:" << endl;
                for(int i=0; i<player.size(); i++){
					if(player[i][3]=='S'){
						player[i][0]=='0'?
							cout << " [ " << player[i][1] << player[i][2] << "]":
							cout << " [" << player[i][0] << player[i][1] << player[i][2] << "]";
					}
					else
						cout << " [---]";
                }
                cout << endl;

                cout << " Player 2:" << endl;
                for(int i=0; i<player2.size(); i++){
                    player2[i][0]=='0'?
                        cout << " [" << player2[i][1] << player2[i][2] << player2[i][3] <<  "]" :
                        cout << " [" << player2[i] << "]" ;
                }
    }

	int check(vector<string> &player){
		for(int i=0; i<player.size(); i++){
			if(player[i][3]=='F')
				return 0;
		}
		return 1;
	}

	int check_rem(vector<string> &player){
		int ctr = 0;
		for(int i=0; i<player.size(); i++){
			if(player[i][3]=='F')
				ctr++;
		}
		return ctr;
	}

//Client side
int main(int argc, char *argv[]){

    vector<string> player,player2;

    if(argc != 3){
        cout << "Usage: ip_address port" << endl;
        exit(0);
    }

    char *serverIp = argv[1]; int port = atoi(argv[2]);
    char msg[1500];

    //setup a socket and connection tools
    struct hostent* host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr;
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);

    int clientSd = socket(AF_INET, SOCK_STREAM, 0);

    int status = connect(clientSd,(sockaddr*) &sendSockAddr, sizeof(sendSockAddr));

    if(status < 0){
        cout <<"Error connecting to socket!" << endl;
        exit(0);
    }

    cout << "Connected to the server!" << endl;
    clrscr();
    string data;

    cout << " \n Da Vinci Code \n " << endl;

    string temp_enc1, temp_enc2;
    temp_enc1 = temp_enc2 = "";

        memset(&msg, 0, sizeof(msg));
        recv(clientSd, (char*)&msg, sizeof(msg), 0);

    	player = tokenizer(msg);

        data = " nothing";
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());
        send(clientSd, (char*)&msg, strlen(msg), 0);
        memset(&msg, 0, sizeof(msg));

        memset(&msg, 0, sizeof(msg));//clear the buffer
        recv(clientSd, (char*)&msg, sizeof(msg), 0);

    	player2 = tokenizer(msg);

        data = " nothing";
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());
        send(clientSd, (char*)&msg, strlen(msg), 0);
        memset(&msg, 0, sizeof(msg));

    print_deck(player,player2);

    int player2_hyp=0;

        memset(&msg, 0, sizeof(msg));//clear the buffer
        recv(clientSd, (char*)&msg, sizeof(msg), 0);

	    player2_hyp = convert_string(msg);
	    insert_hyp_func(player2,player2_hyp,2);

        data = encrypt(player2);
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());
        send(clientSd, (char*)&msg, strlen(msg), 0);
        memset(&msg, 0, sizeof(msg));

        memset(&msg, 0, sizeof(msg));//clear the buffer
        recv(clientSd, (char*)&msg, sizeof(msg), 0);

    	player = tokenizer(msg);

		clrscr();
        modified_print(player,player2);
        cout << " \n [ Command ]" << endl;
        cout << " \n    [ Waiting for Server ]" << endl;

//===========================================================================================================

        data = " 5 Send from client";
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());
        send(clientSd, (char*)&msg, strlen(msg), 0);
        memset(&msg, 0, sizeof(msg));

    int  doubt_location, doubt_number;
    string doubt_str;
    char doubt_color;

    int deck_rem1;
    int deck_rem2;

    deck_rem1 = deck_rem2 = 13;

    while(1){
        while(1){

            	memset(&msg, 0, sizeof(msg));//clear the buffer
                recv(clientSd, (char*)&msg, sizeof(msg), 0);

        		if(strcmp(msg, "wrong") == 0){

                data = " nothing ";
                memset(&msg, 0, sizeof(msg));
                strcpy(msg, data.c_str());
                send(clientSd, (char*)&msg, strlen(msg), 0);
                memset(&msg, 0, sizeof(msg));

                memset(&msg, 0, sizeof(msg));//clear the buffer
                recv(clientSd, (char*)&msg, sizeof(msg), 0);
                cout << " 5.C Received: " << msg << endl;

                player = tokenizer(msg);

                data = " nothing ";
                memset(&msg, 0, sizeof(msg));
                strcpy(msg, data.c_str());
                send(clientSd, (char*)&msg, strlen(msg), 0);
                memset(&msg, 0, sizeof(msg));

                memset(&msg, 0, sizeof(msg));//clear the buffer
                recv(clientSd, (char*)&msg, sizeof(msg), 0);
                cout << " 5.C Received: " << msg << endl;

			    player2 = tokenizer(msg);

                cout << " Your Turn" << endl;
                goto trans;
            }

            else if(strcmp(msg, "lose") == 0){
				clrscr();
				cout << "\n\n 	You Lose, Better Luck Next time. \n\n" << endl;
				goto win_now;
			}

			else if(strcmp(msg, "win") == 0){
				clrscr();
				cout << "\n\n 	You Win, Congratulations! \n\n" << endl;
				goto win_now;
			}

            player2 = tokenizer(msg);

			clrscr();
			modified_print(player,player2);
			cout << " \n [ Command ]" << endl;
			cout << " \n    [ Player 1 doubt is correct... ]" << endl;
			cout << " \n    [ Waiting for Server... ]" << endl;

            data = " nothing ";
            memset(&msg, 0, sizeof(msg));
            strcpy(msg, data.c_str());
            send(clientSd, (char*)&msg, strlen(msg), 0);
            memset(&msg, 0, sizeof(msg));

        } // <-- 2nd

        trans:;

        // <--3rd
        while(1){
				clrscr();
                modified_print(player,player2);
                cout << " \n [ Command ]" << endl;
                cout << " \n    [ Player 2 Turn ]" << endl;

                cout << "\n     Input the LOCATION of Card you want to guess. Range: 1-13" << endl;

                tele:;
                cout << "   	Input: ";
                cin >> doubt_location;

                //check if not a number is inputed -Justin
                if(cin.fail()){
                    cout << "   [[PLEASE Input 1-13 only!]]\n " << endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    goto tele;
                }

                if(check_num(doubt_location)==false){
                    cout << "   [[PLEASE Input 1-13 only!]]\n " << endl;
                    goto tele;
                }
                doubt_location--;

                    if(player[doubt_location][3]=='S'){
                        cout << "   [[Error, the Card is already shown!]]\n " << endl;
                        goto tele;
                    }

                clrscr();
                modified_print(player,player2);
                cout << " \n [ Command ]" << endl;
                cout << " \n    [ Player 2 Turn ]" << endl;

                cout << "\n     Input your guess VALUE of that Card. Range: 0-11 or -" << endl;
                tele3:;
                cout << "   	Input: ";
                cin >> doubt_str;

                string temp_s;
                temp_s = doubt_str;
                doubt_str = convert_str(temp_s);
                    if(doubt_str=="ERROR"){
                        cout << "   [[PLEASE Input 0-11 or hypen only!]]\n " << endl;
                        goto tele3;
                    }

                clrscr();
                modified_print(player,player2);
                cout << " \n [ Command ]" << endl;
                cout << " \n    [ Player 2 Turn ]" << endl;

                cout << "\n     Input your guess COLOR of that Card. Range: b or w" << endl;
                tele4:;
                cout << "   	Input: ";
                cin >> doubt_color;
                doubt_color = toupper(doubt_color);
                    if(doubt_color=='W' || doubt_color=='B'); // <- this is semicolon, designed
                    else{
                        cout << "   [[PLEASE Input 'b' for Black and 'w' for White only!]]\n " << endl;
                        goto tele4;
                    }

                // substr method
                string substr_guess;
                substr_guess = doubt_str;
                substr_guess += doubt_color;

                string substr_main = "";
                for(int i=0; i<3; i++){
                    substr_main += player[doubt_location][i];
                }

                int defold;
                if(substr_main==substr_guess){

                    player[doubt_location][3] = 'S';
                    deck_rem1--;

					if(check(player)==1){
						clrscr();
						cout << "\n\n 	You Win, Congratulations! \n\n" << endl;

						data = "lose";

						memset(&msg, 0, sizeof(msg));
						strcpy(msg, data.c_str());
						send(clientSd, (char*)&msg, strlen(msg), 0);
						memset(&msg, 0, sizeof(msg));

						goto win_now;
					}
                    data = encrypt(player);

                        memset(&msg, 0, sizeof(msg));
                        strcpy(msg, data.c_str());
                        send(clientSd, (char*)&msg, strlen(msg), 0);
                        memset(&msg, 0, sizeof(msg));
                }
                else{
					if(check_rem(player2)==1){
							clrscr();
							cout << "\n\n 	You Lose, Better Luck Next time. \n\n" << endl;

							data = "win";

                            memset(&msg, 0, sizeof(msg));
                            strcpy(msg, data.c_str());
                            send(clientSd, (char*)&msg, strlen(msg), 0);
                            memset(&msg, 0, sizeof(msg));

							goto win_now;
					}

                    clrscr();
                    modified_print(player,player2);
                    cout << " \n [ Command ]" << endl;
                    cout << " \n    [ Wrong ]" << endl;

                int defold;

                cout << "\n     Your guess is wrong, choose the location of your Card to Show" << endl;
                tele2:;
                cout << " 	Input: ";
                cin >> defold;
                    if(check_num(defold)==false){
                        cout << "   [[PLEASE Input 1-13 only!]]\n " << endl;
                        goto tele2;
                    }
                defold--;

                if(player2[defold][3]=='S'){
                    cout << "   [[Error, the Card is already shown!]]\n " << endl;
                    goto tele2;
                }

                player2[defold][3] = 'S';
                deck_rem2--;

			clrscr();
			modified_print(player,player2);
			cout << " \n [ Command ]" << endl;
			cout << " \n    [ Waiting for Server... ]" << endl;

                    data = "wrong";

                        memset(&msg, 0, sizeof(msg)); //clear the buffer
                        strcpy(msg, data.c_str());
                        send(clientSd, (char*)&msg, strlen(msg), 0);
                        memset(&msg, 0, sizeof(msg)); //clear the buffer

                        memset(&msg, 0, sizeof(msg));//clear the buffer
                        recv(clientSd, (char*)&msg, sizeof(msg), 0);

                    	data = encrypt(player);

                        memset(&msg, 0, sizeof(msg)); //clear the buffer
                        strcpy(msg, data.c_str());
                        send(clientSd, (char*)&msg, strlen(msg), 0);
                        memset(&msg, 0, sizeof(msg)); //clear the buffer

                        memset(&msg, 0, sizeof(msg));//clear the buffer
                        recv(clientSd, (char*)&msg, sizeof(msg), 0);

                    	data = encrypt(player2);

                        memset(&msg, 0, sizeof(msg)); //clear the buffer
                        strcpy(msg, data.c_str());
                        send(clientSd, (char*)&msg, strlen(msg), 0);
                        memset(&msg, 0, sizeof(msg)); //clear the buffer

                    break;

                }

                memset(&msg, 0, sizeof(msg));//clear the buffer
                recv(clientSd, (char*)&msg, sizeof(msg), 0);

        }// <-- 2nd

    } // <-- 1st

	win_now:;

    close(clientSd);

    return 0;
}
