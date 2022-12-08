#include "server.h"

Server::Server()
{
}

std::vector<User> Server::get_users()
{
    return users;
}
std::map<std::string, std::string> Server::get_public_keys()
{
    return public_keys;
}
std::vector<Message*> Server::get_messages()
{
    return messages;
}

User Server::create_user(std::string username)
{
    // crypto::generate_key(public_key, private_key);

    std::string public_key {}, private_key {};
    crypto::generate_key(public_key, private_key);

    int count {};

    for (size_t i {}; i < users.size(); i++) {
        if (users[i].get_username() == username)
            count++;
    }

    if (count != 0)
        throw std::logic_error("This username already exist");
    else {
        User new_user(username, private_key, this);
        users.push_back(new_user);
        public_keys[username] = public_key;
        return new_user;
    }
}

bool Server::create_message(Message* msg, std::string signature)
{
    std::string aa {msg->get_sender()};
    std::string public_key {public_keys[aa]};
    //std::string signature = crypto::signMessage(private_key, "my data");
    bool authentic = crypto::verifySignature(public_key, "my data", signature);
    if(authentic)
    {
        messages.push_back(msg);
    }
    return authentic;
}