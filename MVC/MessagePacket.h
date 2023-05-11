//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_MESSAGEPACKET_H
#define LCDTEST_MESSAGEPACKET_H

#include <vector>
#include <string>

enum MessageType{
    MESSAGE_TYPE_LOGO,
    MESSAGE_TYPE_MENU,
    MESSAGE_TYPE_DASHBOARD,
    MESSAGE_TYPE_INPUT,
    MESSAGE_TYPE_DISPLAY,
};

class MessagePacket {
public:
    MessageType messageType;
protected:
    explicit MessagePacket(MessageType messageType) : messageType(messageType) {}
};

class FramedMessagePacket : public MessagePacket{
public:
    const char *title;
    std::vector<const char*> options;
protected:
    FramedMessagePacket(const char *title, MessageType type) : MessagePacket(type), title(title){}
};

class MenuMessagePacket : public FramedMessagePacket{
public:
    std::vector<const char*> options;
    MenuMessagePacket() : FramedMessagePacket("", MESSAGE_TYPE_MENU) {}
};

class InputMessagePacket : public FramedMessagePacket{
public:
    std::string str;
    InputMessagePacket() : FramedMessagePacket("", MESSAGE_TYPE_INPUT) {}
};

class DisplayMessagePacket : public FramedMessagePacket{
public:
    std::vector<const char*> items;
    DisplayMessagePacket() : FramedMessagePacket("", MESSAGE_TYPE_DISPLAY) {}
};

class DashboardMessagePacket : public MessagePacket{
public:
    std::vector<uint8_t*> images;
    DashboardMessagePacket() : MessagePacket(MESSAGE_TYPE_DASHBOARD){}
};

class LogoMessagePacket : public MessagePacket{
public:
    uint8_t *logo;
    LogoMessagePacket() : MessagePacket(MESSAGE_TYPE_LOGO), logo(nullptr){}
};

#endif //LCDTEST_MESSAGEPACKET_H
