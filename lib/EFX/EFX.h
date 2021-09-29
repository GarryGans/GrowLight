#ifndef EFX_H
#define EFX_H

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#include <Timer.h>

// class EFX : public U8G2_SSD1306_128X64_NONAME_1_HW_I2C
class EFX : public U8G2_SH1106_128X64_NONAME_1_HW_I2C

{
private:
    Timer timer;

    const byte screenWidth = 128;
    const byte screenHeight = 64;

    byte borderW;
    byte borderH;

    byte width;
    byte height;

    byte x;
    byte y;

    byte blockWidth;

    byte move_x[10];
    boolean move[10];
    boolean moveLeft[10];
    boolean moveRight[10];
    byte start_x[10];
    byte start_y[10];

    int icon;
    int lock = 79;
    int unlock = 68;
    byte WH = 48;

public:
    char str[sizeof(String)];
    byte setX;
    byte setY;
    enum class PosX
    {
        center,
        left,
        leftSpace,
        leftHalf,
        right,
        rightSpace,
        rightHalf,
        centerFrame,
        rightFrameSide,
        rightFrameHalfSide,
        custom,
        customFrame
    } pos_x;

    enum class PosY
    {
        center,
        up,
        upSpace,
        upHalf,
        down,
        downSpace,
        downHalf,
        centerFrame,
        upFrame,
        upFrameHalf,
        downFrame,
        downFrameSpace,
        downFrameHalf,
        custom
    } pos_y;

    EFX();
    ~EFX();

    byte nextY(byte num, byte id);

    byte getDigWidth(byte value);

    void alignSimbols(byte WH, byte H, PosX pos_x, PosY pos_y);
    void frameAlign(byte W, byte H, PosX pos_x, PosY pos_y);
    void iconAlign(int icon, byte iconWH, PosX pos_x, PosY pos_y);
    void digStringAlign(byte dig, const char *string, PosX pos_x, PosY pos_y);
    void strDigAlign(const char *string, byte dig, PosX pos_x, PosY pos_y);

    void digAlign(byte dig, PosX pos_x, PosY pos_y);
    void setPosition(const char *format, PosX pos_x, PosY pos_y);
    void textAlign(const char *string, PosX pos_x, PosY pos_y);
    void stringAlign(String str, byte size, PosX pos_x, PosY pos_y);
    void setHeight(const uint8_t *font);
    char convStr(const String string);
    void convertStr(const String string);

    void mover(byte &move_x, byte deep_x, byte id);
    void moveString(const char *string, PosX pos_x, PosY pos_y, byte id);
    void escapeBar(Timer &timer);

    void blinkFrame(byte value, boolean dig, PosX pos_x, PosY pos_y, boolean tempBlock);
    void blinkFrame(const char *format, byte digAmount, PosX pos_x, PosY pos_y, boolean tempBlock);
};

#endif