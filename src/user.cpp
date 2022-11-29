#include "user.h"
#include "search.h"

// User::User(std::string username, std::string private_key, Server* server)
// {
//     this->username = username;
//     this->private_key = private_key;
//     this->server = server;
// }

std::string User::get_username()
{
    return username;
}

bool User::send_text_message(std::string text, std::string receiver)
{
    return false;
}
