/**
 * \mainpage
 * Author: Juraj Skvarla / skvarjur
 * 
 * <b>Zadání:</b>
 * Naprogramujte hru Lodě proti počítači s několika stupni obtížnosti, 
 * kde například u jednoduché počítač náhodně vybírá políčka ke střelbě, 
 * u složitějších používá různé strategie k vítězství. Navíc podpora hry po síti.
 *
 */

#include "CPlayer.h"
#include "CPerson.h"
#include "CShip.h"
#include "CAI1.h"
#include "CAI2.h"
#include "CAI3.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory>

#define BUFSIZE 1000 //!< buffer for TCP communication

using namespace std;

/**
 * Function to be printed at the end of the game
 */

void theEnd() {
    cout << "===============================================================" << endl;
    cout << "Homework for BIK-PSI          By: Juraj Skvarla, FIT, CVUT, CZE" << endl;
    cout << "===============================================================" << endl;
}

/**
 * Function to serialize data to be sent into a "packet"
 * @param arr coordinates to serialize
 * @param hit answer to whether the player was hit by previous shot
 * @return string to be sent
 */
string serialize(int arr[], bool hit) {
    char x = (char) (arr[0] + 65);
    int y = arr[1] + 1;
    string packet;
    string temp;
    packet.insert(0, 1, x);
    temp = to_string(y);
    packet.append(temp.begin(), temp.end());
    if (packet.size() == 2)
        packet.insert(2, 1, '.');
    if (hit)
        packet.insert(3, 1, '1');
    else
        packet.insert(3, 1, '0');

    return packet;
}

/**
 * Function to unserialize data from the "packet"
 * @param vstup "packet" to be unserialized
 * @param arr coordinates that has been sent
 */

void unserialize(string vstup, int arr[]) {
    string tmp;
    arr[0] = ((int) vstup[0] - 65); // rozdelim string na 1 a 2
    tmp = vstup.substr(1, 2);
    arr[1] = atoi(tmp.c_str()) - 1;

}

/**
 * Function to print a menu of the game plus short rules
 * @return desired choice of a player whether to play singleplayer
 *, multiplayer or exit
 */

int menu() {
    bool ok = false;
    int choice;
    cout << endl << endl;
    cout << "##########################################" << endl;
    cout << "           BATTLESHIPS 1.0, 2014          " << endl;
    cout << "SHORT RULES:" << endl << "->The game is played on 2 10x10 grids" <<
            endl << "-> Fleet consists of 5 ships:" <<
            endl << "     1. patrol boat:         oo" <<
            endl << "     2. submarine:          ooo" <<
            endl << "     3. tanker:            oooo" <<
            endl << "     4. destroyer:           oo" <<
            endl << "                              o" <<
            endl << "     5. aircraft carrier: ooooo" <<
            endl << "-> The ships cannot overlap" <<
            endl << "-> Each player shoots only once" <<
            endl << "-> A HIT is marked as \'X\'" <<
            endl << "-> A MISS is marked as \'.\'" <<
            endl << "-> You can shoot and position the boats from A1 to J10" <<
            endl << "-> Before the game starts you can set automatic positioning " <<
            endl << "   of the boats  as well as resolving of the HIT/MISS" << 
            endl << "-> You can shoot at the same position several times" << endl;
    cout << "##########################################" << endl << endl << endl;

    cout << "1 - NEW SINGLE PLAYER GAME (Difficulty: Noob)" << endl;
    cout << "2 - NEW SINGLE PLAYER GAME (Difficulty: Beginner)" << endl;
    cout << "3 - NEW SINGLE PLAYER GAME (Difficulty: Advanced)" << endl;
    cout << "4 - NEW MULTIPLAYER GAME (Client)" << endl;
    cout << "5 - NEW MULTIPLAYER GAME (Server)" << endl;
    cout << "6 - EXIT" << endl;
    cout << "Choose 1-6." << endl;
    do {
        if (cin >> choice) {
            if (choice < 7 && choice > 0)
                ok = true;
            else {
                cout << "Not known choice, try again (1-6)" << endl;
            }
        } else {
            cout << "Not known choice, try again (1-6)" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
    } while (!ok);

    return choice;
}

/**
 * Function asks a player to enter number a port number to be connected to
 * @return number of the port
 */

int getPort() {
    int port;
    cout << "Please choose port number. (1024-5000)" << endl;
    cin >> port;
    return port;
}

/**
 * Function asks a player to enter an IP address of the server to be connected to
 * @return IP address of the server
 */

string getServerIP() {
    string ip;
    cout << "Please provide the IP of the Server computer." << endl;
    cin >> ip;
    return ip;
}

/**
 * Function asks a player to decide about the game settings
 * @return true if person agrees, false if not
 */

bool getCin() {
    string temp;
    bool ok = false;
    do {
        cin >> temp;
        if (temp == "yes" || temp == "no") ok = true;
        else {
            cout << "Wrong choice, please try again (yes/no)" << endl;
        }
    } while (!ok);

    if (temp == "yes") return true;
    else return false;
}

int main() {

    int arr[2];
    bool autoResp = false;
    bool autoPrep = false;
    int option;

    option = menu();
    if (option == 6) return 0; // exit
    else {
        cout << "Resolve HIT/MISS automatically? (yes/no)" << endl;
        autoResp = getCin();
        cout << "Position the boats automatically? (yes/no)" << endl;
        autoPrep = getCin();
    }

    unique_ptr<CPlayer> pp1;
    unique_ptr<CPlayer> pp2;

    switch (option) {
        case 1:
        {
            pp1.reset(new CPerson(autoResp, autoPrep));
            pp2.reset(new CAI1);
            break;
        }
        case 2:
        {
            pp1.reset(new CPerson(autoResp, autoPrep));
            pp2.reset(new CAI2);
            break;
        }
        case 3:
        {
            pp1.reset(new CPerson(autoResp, autoPrep));
            pp2.reset(new CAI3);
            break;
        }
        case 4:
        {
            //I am a client
            // This part I have created according to www.builder.cz
            int port = getPort();
            string serverIP = getServerIP();
            CPerson p1(autoResp, autoPrep);
            p1.prepareGame();
            p1.printmBatt();
            // Sent and received text
            string text;
            hostent *host;
            sockaddr_in serverSock;
            // Socket of the client
            int mySocket;
            int totalSize = 0;
            bool is_hit = false;
            char buf[BUFSIZE];
            // Number of accepted bytes
            int size;
            // First I will get info about the server
            in_addr_t data;
            data = inet_addr(serverIP.c_str());
            host = gethostbyaddr(&data, 4, AF_INET);
            // Error handling
            if (host == NULL) {
                herror("Textový popis chyby");
                //What kind of error it is
                switch (h_errno) {
                    case HOST_NOT_FOUND:
                        cerr << "Specifikovaný počítač je neznámý." << endl;
                        break;
                    case NO_ADDRESS:
                        cerr << "Jméno je platné, ale nemá žádnou IP adresu."
                                << endl;
                        break;
                    case NO_RECOVERY:
                        cerr << "Došlo k výskytu neodstranitelné chyby jmenného"
                                " serveru. (Nic nenaděláte.)"
                                << endl;
                        break;
                    case TRY_AGAIN:
                        cerr << "Došlo k dočasné chybě jmenného serveru."
                                "(Zkuste to za chvíli znovu.)"
                                << endl;
                        break;
                }
                return -1;

            }
            // Socket creation

            int counter = 0;
            if ((mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
                cerr << "Nelze vytvořit soket" << endl;
                return -1;
            }
            // Filling up the sockaddr structure
            // 1) Family of protocols
            serverSock.sin_family = AF_INET;
            // 2) Number of the port to connect to
            serverSock.sin_port = htons(port);
            // 3) IP setup
            memcpy(&(serverSock.sin_addr), host->h_addr, host->h_length);
            // Connection of the socket
            if (connect(mySocket, (sockaddr *) & serverSock, sizeof (serverSock)) == -1) {
                cerr << "Nelze navázat spojení" << endl;
                return -1;
            }
            // Communication
            while (true) {
                counter++;
                //Is hit?
                if (counter == 1) cout << "Successfully connected. You go first." << endl;
                p1.shoot(arr);
                text = serialize(arr, is_hit); // strielam

                if ((size = send(mySocket, text.c_str(), text.size() + 1, 0)) == -1) {
                    cerr << "Problém s odesláním dat" << endl;
                    return -1;
                }
                cout << "Shot fired, wait for the result. " << "Its enemy's turn." << endl;
                //Data receiving
                text = "";
                while (totalSize != 5) {
                    if ((size = recv(mySocket, buf, BUFSIZE - 1, 0)) == -1) {
                        cerr << "Problém s přijetím dat." << endl;
                        return -1;
                    }

                    totalSize += size;
                    text = buf;
                }
                // I will process what i have received

                if (text[3] == '2') {
                    cout << "CONGRATULATIONS, YOU HAVE WON!!!" << endl;
                    break;
                }

                if (text[3] == '1') {
                    cout << "GOOD WORK! YOU HIT A SHIP!" << endl;
                    p1.markMyShot(arr, true);

                } else {
                    cout << "YOU MISSED!" << endl;
                    p1.markMyShot(arr, false);
                }

                // unserializing the data
                unserialize(text, arr);

                is_hit = p1.amIHitted(arr);

                if (p1.getHits() == 17) {
                    cout << "YOU HAVE LOST, SORRY. :(" << endl;
                    text = "XXX2";
                    if ((size = send(mySocket, text.c_str(), text.size() + 1, 0)) == -1) {
                        cerr << "Problém s odesláním dat" << endl;
                        return -1;
                    }
                    break;
                }
                p1.printmBatt();
                totalSize = 0;
            }
            p1.printmBatt();
            // Connection closure
            close(mySocket);
            theEnd();
            return 0;
        }
        case 5:
        {
            // I am server
            // This part I have created according to www.builder.cz
            int port = getPort();
            CPerson p1(autoResp, autoPrep);
            p1.prepareGame();
            p1.printmBatt();
            //Accepted and sent text
            string text;
            //Name of the port
            sockaddr_in sockName;
            // Client which should connect
            sockaddr_in clientInfo;
            // Socket
            int mainSocket;
            // Buffer for TCP communication
            char buf[BUFSIZE];
            // Number of accepted and received bytes
            int size;
            //Size of the address of the server
            socklen_t addrlen;
            // Socket creation
            if ((mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
                cerr << "Nelze vytvořit soket" << endl;
                return -1;
            }
            // Filling up the sockaddr structure
            // 1) Family of the protocols
            sockName.sin_family = AF_INET;
            // 2) Number of port to listen on
            sockName.sin_port = htons(port);
            // 3) Set up where is possible to connect from 
            sockName.sin_addr.s_addr = INADDR_ANY;
            // Socket name
            if (bind(mainSocket, (sockaddr *) & sockName, sizeof (sockName)) == -1) {
                cerr << "Problém s pojmenováním soketu." << endl;
                return -1;
            }
 
            cout << "Listening at port No." << port << endl;
            if (listen(mainSocket, 10) == -1) {
                cerr << "Problém s vytvořením fronty" << endl;
                return -1;
            }

            // Size of the structure clinetinfo
            
            addrlen = sizeof (clientInfo);
            // Vyberu z fronty požadavek na spojení.
            // "client" is new socket to connect client with server
            int client = accept(mainSocket, (sockaddr*) & clientInfo, &addrlen);
            int totalSize = 0;
            if (client == -1) {
                cerr << "Problém s přijetím spojeni" << endl;
                return -1;
            }

            // IP of the client
            cout << "A player has connected from the IP address "
                    << inet_ntoa((in_addr) clientInfo.sin_addr) << endl;
            cout << "He shoots first." << endl;
            
            text = "";
            // Communication
            int counter = 0;
            while (true) {
                counter++;
                // Data receiving
                while (totalSize != 5) {
                    if ((size = recv(client, buf, BUFSIZE - 1, 0)) == -1) {
                        cerr << "Problem receiving data." << endl;
                        return -1;
                    }

                    totalSize += size;
                    text = buf;
                }
                // Process what i have received
                if (counter != 1) {

                    if (text[3] == '2') {
                        cout << "CONGRATULATIONS, YOU HAVE WON!!!" << endl;
                        break;
                    }
                    // Figure out if i have hit before
                    if (text[3] == '1') { 
                        cout << "GOOD WORK! YOU HIT A SHIP!" << endl;
                        p1.markMyShot(arr, true);

                    } else {
                        cout << "YOU MISSED!!" << endl;
                        p1.markMyShot(arr, false);
                    }
                }
                // unserialize data (where to shoot?)
                unserialize(text, arr); 

                bool is_hit = p1.amIHitted(arr); 
                if (p1.getHits() == 17) {
                    cout << "YOU HAVE LOST, SORRY. :(" << endl;
                    text = "XXX2";
                    if ((size = send(client, text.c_str(), text.size() + 1, 0)) == -1) {
                        cerr << "Problém s odesláním dat" << endl;
                        return -1;
                    }
                    break;
                }
                p1.printmBatt();
                totalSize = 0;
                text = "";

                p1.shoot(arr);
                text = serialize(arr, is_hit); // odosli spravu o tom, ci bol trafeny a kam striela
                if ((size = send(client, text.c_str(), text.size() + 1, 0)) == -1) {
                    cerr << "Problém s odesláním dat" << endl;
                    return -1;
                }
                cout << "Shot fired, wait for the result. " << "Its enemy's turn." << endl;
                text = "";
            }
            p1.printmBatt();
            // Close the connection with the client
            close(client);
            close(mainSocket);
            theEnd();
            return 0;
        }
    }

    CPlayer& p1 = *pp1;
    CPlayer& p2 = *pp2;

    p1.prepareGame();
    p2.prepareGame();

    std::cout << "Computer goes first." << std::endl;
    std::cout << "Press [ Enter ] to start the game." << std::endl;
    cin.clear();
    cin.get();
    cin.get();
    p1.printmBatt();

    do { // hra
        p2.shoot(arr); // hrac 2 vyberie miesto kam bude strielat
        p2.markMyShot(arr, p1.amIHitted(arr)); // obaja si poznacia ci trafil alebo nie
        p1.printmBatt();
        if (p1.getHits() == 17) {
            cout << "===============================" << endl;
            cout << "       YOU HAVE LOST :(        " << endl;
            cout << "===============================" << endl;
            break;
        }
        p1.shoot(arr); // hrac 1 vyberie miesto kam bude strielat
        p1.markMyShot(arr, p2.amIHitted(arr)); // obaja si poznacia ci trafil alebo nie
        p1.printmBatt();
        if (p2.getHits() == 17) {
            cout << "=============================" << endl;
            cout << "CONGRATULATIONS, YOU HAVE WON" << endl;
            cout << "=============================" << endl;
            break;
        }
    } while (true);

    cout << "Enemy ships: " << endl;
    p2.printmBatt();
    theEnd();
    return 0;
}

