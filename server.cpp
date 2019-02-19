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
#define pb push_back

using namespace std;

// Print the deck of player and player2
void print_deck(vector<string> player,vector<string> player2){

    cout << " Player 1:" << endl;
    for(int i=0; i<player.size(); i++){
        player[i][0]=='0'?
            cout << " [" << player[i][1] << player[i][2] << player[i][3] << "]" :
            cout << " [" << player[i] << "]" ;
    }
    cout << endl << endl;

    cout << " Player 2:" << endl;
    for(int i=0; i<player2.size(); i++){
        player2[i][0]=='0'?
            cout << " [---]" :
            cout << " [---]" ;
    }
    cout << endl;
}

// Print only one deck
void print_one_deck(vector<string> player){
    cout << " \n [Deck]:\n " << endl;
    for(int i=0; i<player.size(); i++){
        player[i][0]=='0'?
            cout << " [" << player[i][1] << player[i][2] << player[i][3] << "] " :
            cout << " [" << player[i] << "] " ;
    }
}

// Checking if theres hypen in the deck of player
int check_hyp(vector<string> player){
    int result = 0;
    for(int i=0; i<player.size(); i++){
        if(player[i][1]=='-')
            result++;
    }
    return result;
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

  // erase the first deck of player, it's sure a hypen character
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


// Linear Probing Algorithm / pass by reference
void get_card_on_deck(vector<string> &deck, vector<string> &player, vector<string> &player2){

    // Linear Probing
    int ctr=0;
    int binary=0;
    while(1){
        int index = rand()%deck.size();
        if(deck[index]!=""){

            binary==0?
                player.pb(deck[index]):
                player2.pb(deck[index]);

            deck[index]="";
            ctr++;
        }
        else {
            while(1){
                index = (index+1)%deck.size();
                if(deck[index]!=""){
                    break;
                }
            }
            binary==0?
                player.pb(deck[index]):
                player2.pb(deck[index]);

            deck[index]="";
            ctr++;
        }
        binary==0?
            binary=1:
            binary=0;

        if(ctr==deck.size())
            break;
    }
}

void clear_screen(){
    for(int i=0; i<30; i++)
        cout << endl;
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

void modified_print(vector<string> &player,vector<string> &player2){
     cout << " \n  Da Vinci Code - [GAME STARTS]  \n " << endl;
        cout << " Player 1:" << endl;
            for(int i=0; i<player.size(); i++){
                player[i][0]=='0'?
                    cout << " [" << player[i][1] << player[i][2] << player[i][3] << "]" :
                    cout << " [" << player[i] << "]" ;
            }
            cout << endl;

            cout << " Player 2:" << endl;

            for(int i=0; i<player2.size(); i++){
                if(player2[i][3]=='S'){
        player2[i][0]=='0'?
          cout << " [ " << player2[i][1] << player2[i][2] << "]":
          cout << " [" << player2[i][0] << player2[i][1] << player2[i][2] << "]";
      }
      else
        cout << " [---]";
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

//Server side
int main(int argc, char *argv[]){

    // This will execute if the input in the terminal is without a port number
    if(argc != 2){
        cout  << "Please Input Port Number!" << endl;
        exit(0);
    }

    int port = atoi(argv[1]);
    char msg[1500];

    //setup a socket and connection tools
    sockaddr_in servAddr; bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET; servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0){
        cout << "Error establishing the server socket" << endl;
        exit(0);
    }

    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, sizeof(servAddr));
    if(bindStatus < 0){
        cout << "Error binding socket to local address" << endl;
        exit(0);
    }

    // After the two if statement, it means that the server is successfully executed
    cout << "Waiting for a client to connect..." << endl;

    listen(serverSd, 2); sockaddr_in newSockAddr; socklen_t newSockAddrSize = sizeof(newSockAddr);
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0){
        cout << "Error accepting request from client!" << endl;
        exit(1);
    }

    cout << "Connected to the client!" << endl;
    clrscr();

// Start
    string data;
    srand(time(NULL)); // Generating Random #

    vector<string> player,player2,deck;

    string temp="";
    for(int i=0; i<10; i++){
        temp="0"; temp += char(i+'0'); temp+='B'; temp += 'F';
        deck.pb(temp);
        temp="0"; temp += char(i+'0'); temp+='W'; temp += 'F';
        deck.pb(temp);
    }
    deck.pb("10BF"); deck.pb("10WF");
    deck.pb("11BF"); deck.pb("11WF");
    deck.pb("0-BF"); deck.pb("0-WF");

    // Random Shuffle the Main Deck
    random_shuffle(deck.begin(),deck.end());
    get_card_on_deck(deck,player,player2);

    // Sort the player and player2 deck
    sort(player.begin(),player.end());
    sort(player2.begin(),player2.end());

     cout << " \n  Da Vinci Code \n " << endl;
    print_deck(player,player2);

    string temp_enc1, temp_enc2;
    temp_enc1 = temp_enc2 = "";

    temp_enc1 = encrypt(player);
    temp_enc2 = encrypt(player2);

        data = temp_enc1;
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());
        send(newSd, (char*)&msg, strlen(msg), 0);
        memset(&msg, 0, sizeof(msg));

        memset(&msg, 0, sizeof(msg));
        recv(newSd, (char*)&msg, sizeof(msg), 0);

        data = temp_enc2;
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());
        send(newSd, (char*)&msg, strlen(msg), 0);
        memset(&msg, 0, sizeof(msg));

        memset(&msg, 0, sizeof(msg));
        recv(newSd, (char*)&msg, sizeof(msg), 0);

    int player_hyp=0, player2_hyp=0;

    player_hyp = check_hyp(player);
    player2_hyp = check_hyp(player2);

    insert_hyp_func(player,player_hyp,1);

clrscr();
cout << " \n  Da Vinci Code \n " << endl;
print_deck(player,player2);
cout << " \n [ Command ]" << endl;
    cout << " \n    [ Waiting for Client ]" << endl;

        data = convert_int(player2_hyp);
        memset(&msg, 0, sizeof(msg)); //clear the buffer
        strcpy(msg, data.c_str());
        send(newSd, (char*)&msg, strlen(msg), 0);
        memset(&msg, 0, sizeof(msg)); //clear the buffer

   memset(&msg, 0, sizeof(msg));//clear the buffer
        recv(newSd, (char*)&msg, sizeof(msg), 0);

    player2 = tokenizer(msg);

    clrscr();

        data = encrypt(player);
        memset(&msg, 0, sizeof(msg)); //clear the buffer
        strcpy(msg, data.c_str());
        send(newSd, (char*)&msg, strlen(msg), 0);
        memset(&msg, 0, sizeof(msg)); //clear the buffer

//===========================================================================================================

        memset(&msg, 0, sizeof(msg));
        recv(newSd, (char*)&msg, sizeof(msg), 0);

 //===========================================================================================================

    int  doubt_location, doubt_number;
    string doubt_str;
    char doubt_color;

    int deck_rem1;
    int deck_rem2;

    deck_rem1 = deck_rem2 = 13;

    while(1){

        // Send
        while(1){
            clrscr();
            modified_print(player,player2);
            cout << " \n\n [ Command ]" << endl;
            cout << " \n    [ Player 1 Turn ]" << endl;

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

                    if(player2[doubt_location][3]=='S'){
                        cout << "   [[Error, the Card is already shown!]]\n " << endl;
                        goto tele;
                    }

                cout << endl;

                clrscr();
                modified_print(player,player2);
                cout << " \n [ Command ]" << endl;
                cout << " \n    [ Player 1 Turn ]" << endl;

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
                cout << " \n    [ Player 1 Turn ]" << endl;
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

                string substr_guess;
                substr_guess = doubt_str;
                substr_guess += doubt_color;

                string substr_main = "";
                for(int i=0; i<3; i++){
                    substr_main += player2[doubt_location][i];
                }

                int defold;
                if(substr_main==substr_guess){

                    player2[doubt_location][3] = 'S';
                    deck_rem2--;
                    data = encrypt(player2);

                     if(check(player2)==1){
          clrscr();
          cout << "\n\n 	You Win, Congratulations! \n\n" << endl;

          data = "lose";

                        memset(&msg, 0, sizeof(msg));
                        strcpy(msg, data.c_str());
                        send(newSd, (char*)&msg, strlen(msg), 0);
                        memset(&msg, 0, sizeof(msg));


          goto win_now;
        }

                        memset(&msg, 0, sizeof(msg));
                        strcpy(msg, data.c_str());
                        send(newSd, (char*)&msg, strlen(msg), 0);
                        memset(&msg, 0, sizeof(msg));

                }
                else{

                if(check_rem(player)==1){
          clrscr();
          cout << "\n\n 	You Lose, Better Luck Next time. \n\n" << endl;

          data = "win";

                        memset(&msg, 0, sizeof(msg));
                        strcpy(msg, data.c_str());
                        send(newSd, (char*)&msg, strlen(msg), 0);
                        memset(&msg, 0, sizeof(msg));

          goto win_now;
      }

                clrscr();
                modified_print(player,player2);
                cout << " \n [ Command ]" << endl;
                cout << " \n    [ Player 1 Turn ]" << endl;

                int defold;
      cout << "\n     Your guess is wrong, choose the location of your Card to Show" << endl;
                tele2:;
                cout << "   	Input: ";
                cin >> defold;
                    if(check_num(defold)==false){
                        cout << "   [[PLEASE Input 1-13 only!]]\n " << endl;
                        goto tele2;
                    }
                defold--;

                if(player[defold][3]=='S'){
                    cout << "   [[Error, the Card is already shown!]]\n " << endl;
                    goto tele2;
                }

                player[defold][3] = 'S';
                deck_rem1--;

                clrscr();
                modified_print(player,player2);
                cout << " \n [ Command ]" << endl;
                cout << " \n    [ Waiting for Player 2 ]" << endl;

                    data = "wrong";

                        memset(&msg, 0, sizeof(msg));
                        strcpy(msg, data.c_str());
                        send(newSd, (char*)&msg, strlen(msg), 0);
                        memset(&msg, 0, sizeof(msg));

                        memset(&msg, 0, sizeof(msg));
                        recv(newSd, (char*)&msg, sizeof(msg), 0);

                      data = encrypt(player);

                        memset(&msg, 0, sizeof(msg));
                        strcpy(msg, data.c_str());
                        send(newSd, (char*)&msg, strlen(msg), 0);
                        memset(&msg, 0, sizeof(msg));

                        memset(&msg, 0, sizeof(msg));
                        recv(newSd, (char*)&msg, sizeof(msg), 0);

                      data = encrypt(player2);

                        memset(&msg, 0, sizeof(msg));
                        strcpy(msg, data.c_str());
                        send(newSd, (char*)&msg, strlen(msg), 0);
                        memset(&msg, 0, sizeof(msg));

                    goto trans;
                }

                memset(&msg, 0, sizeof(msg));
                recv(newSd, (char*)&msg, sizeof(msg), 0);


        }// <-- 2nd
        trans:;

        while(1){

                memset(&msg, 0, sizeof(msg));
                recv(newSd, (char*)&msg, sizeof(msg), 0);

            if(strcmp(msg, "wrong") == 0){

                data = " nothing ";
                memset(&msg, 0, sizeof(msg));
                strcpy(msg, data.c_str());
                send(newSd, (char*)&msg, strlen(msg), 0);
                memset(&msg, 0, sizeof(msg));

                memset(&msg, 0, sizeof(msg));
                recv(newSd, (char*)&msg, sizeof(msg), 0);

                player = tokenizer(msg);

                data = " nothing ";
                memset(&msg, 0, sizeof(msg));
                strcpy(msg, data.c_str());
                send(newSd, (char*)&msg, strlen(msg), 0);
                memset(&msg, 0, sizeof(msg));

                memset(&msg, 0, sizeof(msg));
                recv(newSd, (char*)&msg, sizeof(msg), 0);

                player2 = tokenizer(msg);

                cout << " Your Turn" << endl;
                break;
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

            player = tokenizer(msg);

            clrscr();
    modified_print(player,player2);
    cout << " \n [ Command ]" << endl;
    cout << " \n    [ Player 2 doubt is correct... ]" << endl;
    cout << " \n    [ Waiting for Client... ]" << endl;

            // 5.Bs
            data = " nothing ";
            memset(&msg, 0, sizeof(msg));
            strcpy(msg, data.c_str());
            send(newSd, (char*)&msg, strlen(msg), 0);
            memset(&msg, 0, sizeof(msg));

        } // <-- 2nd

    }// <-- 1st

win_now:;

    close(newSd);
    close(serverSd);


    return 0;
}
