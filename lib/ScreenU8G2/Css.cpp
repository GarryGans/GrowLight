#include "Screen.h"

void Screen::alignSimbols(byte W, byte H, PosX position_x, PosY position_y)
{
    switch (position_x)
    {
    case PosX::center:
        x = (screenWidth - W) / 2;
        break;

    case PosX::centerFrame:
        x = (screenWidth - W) / 2 + width + width / 2;
        break;

    case PosX::left:
        x = 0;
        break;

    case PosX::leftSpace:
        x = W / 8;
        break;

    case PosX::leftHalf:
        x = (screenWidth / 2 - W) / 2;
        break;

    case PosX::right:
        x = screenWidth - W;
        break;

    case PosX::rightSpace:
        x = screenWidth - (W + W / 8);
        break;

    case PosX::rightHalf:
        x = (screenWidth + screenWidth / 2 - W) / 2;
        break;

    case PosX::rightFrameSide:
        x = screenWidth - width - (screenWidth - W) / 2;
        break;

    case PosX::rightFrameHalfSide:
        x = screenWidth - width - (screenWidth / 2 - W) / 2;
        break;

    case PosX::custom:
        x = setX;
        break;

    default:
        break;
    }

    switch (position_y)
    {
    case PosY::center:
        y = (screenHeight + H) / 2;
        break;

    case PosY::up:
        y = H;
        break;

    case PosY::upSpace:
        y = H + H / 4;
        break;

    case PosY::upHalf:
        y = (screenHeight / 2 - H) / 2 + H;
        break;

    case PosY::down:
        y = screenHeight;
        break;

    case PosY::downSpace:
        y = screenHeight - H / 4;
        break;

    case PosY::downHalf:
        y = (screenHeight + screenHeight / 2 - H) / 2 + H;
        break;

    case PosY::centerFrame:
        y = (screenHeight - H) / 2;
        break;

    case PosY::upFrame:
        y = 0;
        break;

    case PosY::upFrameHalf:
        y = (screenHeight / 2 - H) / 2;
        break;

    case PosY::downFrame:
        y = screenHeight - H;
        break;

    case PosY::downFrameSpace:
        y = screenHeight - H - H / 4;
        break;

    case PosY::downFrameHalf:
        y = (screenHeight + screenHeight / 2 - H) / 2;
        break;

    case PosY::custom:
        y = setY;
        break;

    default:
        break;
    }
}

byte Screen::getDigWidth(byte value)
{
    char val[4];
    String(value).toCharArray(val, 4);

    return getStrWidth(val);
}

void Screen::setHeight(const uint8_t *font)
{
    setFont(font);

    if (font == u8g2_font_courB08_tn || font == u8g2_font_courB08_tf)
    {
        height = 6;
    }

    else if (font == u8g2_font_pressstart2p_8f)
    {
        height = 8;
    }

    else if (font == u8g2_font_pixelmordred_tf)
    {
        height = 12;
    }

    else if (font == u8g2_font_profont22_tn || font == u8g2_font_9x18_tn || font == u8g2_font_crox4h_tf)
    {
        height = 14;
    }
    else if (font == u8g2_font_crox5tb_tf)
    {
        height = 16;
    }
    else if (font == u8g2_font_ncenB18_tf)
    {
        height = 18;
    }

    // else
    // {
    //     Serial.println("undefiner");
    // }
}

void Screen::textAlign(const char *string, PosX position_x, PosY position_y)
{
    alignSimbols(getStrWidth(string), height, position_x, position_y);

    setCursor(x, y);
    print(string);
}

void Screen::stringAlign(String str, byte size, PosX position_x, PosY position_y)
{
    char light[size];

    String(str).toCharArray(light, size);

    textAlign(light, position_x, position_y);
}

void Screen::digStringAlign(byte dig, const char *string, PosX position_x, PosY position_y)
{
    alignSimbols(getDigWidth(dig) + getStrWidth(string), height, position_x, position_y);

    setCursor(x, y);

    print(dig);
    print(string);
}

void Screen::digAlign(byte dig, PosX position_x, PosY position_y)
{
    alignSimbols(getDigWidth(dig), height, position_x, position_y);

    setCursor(x, y);
    print(dig);
}

void Screen::setPosition(const char *format, PosX position_x, PosY position_y)
{
    alignSimbols(getStrWidth(format), height, position_x, position_y);

    setCursor(x, y);
}

void Screen::iconAlign(int icon, byte iconWH, PosX position_x, PosY position_y)
{
    alignSimbols(iconWH, iconWH, position_x, position_y);
    drawGlyph(x, y, icon);
}

void Screen::frameAlign(byte W, byte H, PosX position_x, PosY position_y)
{
    borderW = 6;
    borderH = 6;

    W += borderW;
    H += borderH;

    alignSimbols(W, H, position_x, position_y);
    drawFrame(x, y, W, H);
}

void Screen::blinkFrame(byte value, boolean dig, PosX position_x, PosY position_y, Timer &timer)
{
    if (timer.blinkReady())
    {
        if (dig)
        {
            width = getMaxCharWidth() * 2;
        }
        else
        {
            width = getDigWidth(value);
        }

        frameAlign(width, height, position_x, position_y);
    }
}

void Screen::blinkFrame(const char *format, byte digAmount, PosX pos_x, PosY pos_y, Timer &timer)
{
    if (timer.blinkReady())
    {
        width = getMaxCharWidth() * digAmount;

        setPosition(format, pos_x, pos_y);

        borderW = 6;
        borderH = 6;

        width += borderW;
        height += borderH;

        drawFrame(x - borderW / 2, y - borderH / 2, width, height);
    }
}

void Screen::mover(byte &move_x, byte deep_x)
{
    if (move_x > (start_x - deep_x) && moveLeft)
    {
        move_x--;
        if (move_x == start_x - deep_x)
        {
            moveLeft = false;
            moveRight = true;
        }
    }
    else if (move_x < (deep_x + start_x) && moveRight)
    {
        move_x++;
        if (move_x == deep_x + start_x)
        {
            moveRight = false;
            moveLeft = true;
        }
    }
}

void Screen::moveString(const char *string, PosX position_x, PosY position_y, Timer &timer)
{
    setPosition(string, PosX::center, PosY::upSpace);

    if (!move)
    {
        move_x = start_x = x;

        move = true;
        moveLeft = true;
        moveRight = false;
    }

    setCursor(move_x, y);
    print(string);

    if (timer.moveReady())
    {
        mover(move_x, start_x);
    }
}

void Screen::escapeBar(Timer &timer)
{
    if (!timer.escBar)
    {
        blockWidth = screenWidth / timer.maxEscapeCounter;
        timer.escBar = true;
    }

    width = blockWidth * (timer.maxEscapeCounter - timer.escapeCounter);
    drawBox(0, 58, width, 6);

    if (width == blockWidth * timer.maxEscapeCounter)
    {
        timer.escBar = false;
    }
}