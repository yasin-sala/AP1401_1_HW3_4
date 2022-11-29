#ifndef MESSAGE_H
#define MESSAGE_H
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

class Message {
public:
    Message(std::string type, std::string sender, std::string receiver);
    Message();

    std::string get_type();
    std::string get_sender();
    std::string get_receiver();
    std::string get_time();

    // void print(std::ostream &os);
    virtual void print(std::ostream& os)
    {
        os << "*************************" << std::endl;
        os << this->get_sender() << " -> " << this->get_receiver() << std::endl;
        os << "message type: text" << std::endl;
        os << "message time: " << this->get_time() << std::endl;
        os << "*************************" << std::endl;
    }

    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, const T& c)
    {
        // T msg = *(const_cast<T*>(&c));
        // msg.print(os);
        T* msg = (const_cast<T*>(&c));
        msg->print(os);
        return os;
    }

private: ///////////////////////////////////////////////////////////////////////////////////////////////
    std::string type; // type of the message ("text", "voice", ...)
    std::string sender; // the username who send this message
    std::string receiver; // the username whom this message is intended for
    std::string time; // creation time of the message
};

class TextMessage : public Message { ////////////////////////////////////////////////////////////////////////////
public:
    TextMessage(std::string text, std::string sender, std::string receiver);
    std::string get_text();
    virtual void print(std::ostream& os) override
    {
        os << "*************************" << std::endl;
        os << this->get_sender() << " -> " << this->get_receiver() << std::endl;
        os << "message type : text" << std::endl;
        os << "message time: " << this->get_time() << std::endl;
        os << "text :" << this->get_text() << std::endl;
        os << "*************************" << std::endl;
    }

private:
    std::string text;
};

class VoiceMessage : public Message { //////////////////////////////////////////////////////////////////////////
public:
    VoiceMessage(std::string sender, std::string receiver);

    virtual void print(std::ostream& os) override
    {
        os << "*************************" << std::endl;
        os << this->get_sender() << " -> " << this->get_receiver() << std::endl;
        os << "message type : voice" << std::endl;
        os << "message time: " << this->get_time() << std::endl;
        os << "voice : ";
        for (size_t i {}; i < voice.size() - 1; i++)
            std::cout << static_cast<int>(voice[i]) << " ";
        std::cout << static_cast<int>(voice[voice.size()]) << std::endl;
        os << "*************************" << std::endl;
    }

    std::vector<unsigned char> get_voice();

private:
    std::vector<unsigned char> voice;
};
#endif // MESSAGE_H
