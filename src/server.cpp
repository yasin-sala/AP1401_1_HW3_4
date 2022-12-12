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
    std::string aa { msg->get_sender() };
    std::string public_key { public_keys[aa] };
    // std::string signature = crypto::signMessage(private_key, "my data");
    bool authentic = crypto::verifySignature(public_key, "my data", signature);
    if (authentic) {
        messages.push_back(msg);
    }
    return authentic;
}

std::vector<Message*> Server::get_all_messages_from(std::string username)
{
    std::vector<Message*> user_msgs_from(messages.size());

    auto end_user_msgs = std::copy_if(messages.begin(), messages.end(), user_msgs_from.begin(),
        [username](Message* msg) { return msg->get_sender() == username; });

    user_msgs_from.erase(end_user_msgs, user_msgs_from.end());
    return user_msgs_from;
}

std::vector<Message*> Server::get_all_messages_to(std::string username)
{
    std::vector<Message*> user_msgs_to(messages.size());

    auto end_user_msgs = std::copy_if(messages.begin(), messages.end(), user_msgs_to.begin(),
        [username](Message* msg) { return msg->get_receiver() == username; });

    user_msgs_to.erase(end_user_msgs, user_msgs_to.end());
    return user_msgs_to;
}

std::vector<Message*> Server::get_chat(std::string user1, std::string user2)
{
    std::vector<Message*> chats(messages.size());

    auto end_user_msgs = std::copy_if(messages.begin(), messages.end(), chats.begin(),
        [user1, user2](Message* msg) { return (msg->get_receiver() == user1 && msg->get_sender() == user2)
                                           || (msg->get_receiver() == user2 && msg->get_sender() == user1); });

    chats.erase(end_user_msgs, chats.end());
    return chats;
}

void Server::sort_msgs(std::vector<Message*> msgs)
{
    std::cout << std::endl;
    std::cout << "after using random engine" << std::endl;
    std::cout << msgs[0]->get_time() << std::endl;
    std::cout << msgs[1]->get_time() << std::endl;
    std::cout << msgs[2]->get_time() << std::endl;
    std::cout << msgs[3]->get_time() << std::endl;
    std::sort(msgs.begin(), msgs.end(),
        [](Message* first, Message* second) {
            std::string str1 { first->get_time() };
            std::string str2 { second->get_time() };
            // (6,5,str2,4,5)
            if (str1.compare(17, 2, str2, 17, 2) < 0)
                return true;
            return false;
        });

    std::cout << std::endl;
    std::cout << "after using sort_msgs" << std::endl;
    std::cout << msgs[0]->get_time() << std::endl;
    std::cout << msgs[1]->get_time() << std::endl;
    std::cout << msgs[2]->get_time() << std::endl;
    std::cout << msgs[3]->get_time() << std::endl;
}