#include "user.h"
#include "search.h"
#include "server.h"

User::User(std::string username, std::string private_key, Server* server)
    : username { username }
    , private_key { private_key }
    , server { server }
{
}

std::string User::get_username()
{
    return username;
}

bool User::send_text_message(std::string text, std::string receiver)
{
    bool flag { false };
    std::string sender { this->get_username() };
    std::vector<User> xx { server->get_users() }; // all users
    for (size_t i {}; i < xx.size(); i++) {
        if (xx[i].get_username() == receiver && sender != receiver) {

            TextMessage* aa { new TextMessage(text, sender, receiver) };
            // Message* aa = dynamic_cast<Message*>(aa);
            std::string signature = crypto::signMessage(private_key, "my data");
            bool a { server->create_message(aa, signature) };
            flag = true;
        }
    }
    return flag;
}

bool User::send_voice_message(std::string receiver)
{

    bool flag { false };
    std::string sender { this->get_username() };
    std::vector<User> xx { server->get_users() }; // all users
    for (size_t i {}; i < xx.size(); i++) {
        if (xx[i].get_username() == receiver && sender != receiver) {

            VoiceMessage* aa { new VoiceMessage(sender, receiver) };
            // Message* aa = dynamic_cast<Message*>(aa);
            std::string signature = crypto::signMessage(private_key, "my data");
            bool a { server->create_message(aa, signature) };
            flag = true;
        }
    }
    return flag;
}