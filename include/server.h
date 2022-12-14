#ifndef SERVER_H
#define SERVER_H

#include "Message.h"
#include "crypto.h"
#include "user.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

class Message;
class User; // forward decleration
class Server {
public:
    Server();
    std::vector<User> get_users();
    std::map<std::string, std::string> get_public_keys();
    std::vector<Message*> get_messages();

    User create_user(std::string username);
    bool create_message(Message* msg, std::string signature);

    //  S T L
    std::vector<Message*> get_all_messages_from(std::string username);
    std::vector<Message*> get_all_messages_to(std::string username);
    std::vector<Message*> get_chat(std::string user1, std::string user2);
    static void sort_msgs(std::vector<Message*> msgs);

private:
    std::vector<User> users; // to store our users
    std::map<std::string, std::string> public_keys; // map usernames to their publickeys
    std::vector<Message*> messages; // to store all the messages sent by users
};

#endif // SERVER_H