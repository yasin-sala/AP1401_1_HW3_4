#include "message.h"

Message::Message(std::string type, std::string sender, std::string receiver)
{
    this->type = type;
    this->sender = sender;
    this->receiver = receiver;

    time_t curr_time;
    curr_time = std::time(NULL);
    char* tm = ctime(&curr_time);
    std::string tm1 = static_cast<std::string>(tm);

    this->time = tm1.substr(0, tm1.size() - 1);
}

Message::Message()
    : Message("", "", "")
{
}

std::string Message::get_type()
{
    return type;
}

std::string Message::get_sender()
{
    return sender;
}

std::string Message::get_receiver()
{
    return receiver;
}

std::string Message::get_time()
{
    return time;
}

TextMessage::TextMessage(std::string text, std::string sender, std::string receiver)
    : Message("text", sender, receiver)
    , text { text }
{
}

std::string TextMessage::get_text()
{
    return text;
}

VoiceMessage::VoiceMessage(std::string sender, std::string receiver)
    : Message("voice", sender, receiver)
{
    std::vector<unsigned char> a {};
    for (size_t i {}; i < 5; i++)
        a.push_back(static_cast<unsigned char>(rand() % 256));

    voice = a ;
}

std::vector<unsigned char> VoiceMessage::get_voice()
{
    return voice;
}