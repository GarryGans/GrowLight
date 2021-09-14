#include "Screen.h"

void Screen::alignSimbols(byte W, byte H, PosX position_x, PosY position_y)
{
    switch (position_x)
    {
    case PosX::center:
        x = (screenWidth - W) / 2;
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

void Screen::textAlign(const char *string, PosX position_x, PosY position_y)
{
    alignSimbols(getStrWidth(string), getMaxCharWidth(), position_x, position_y);

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
    alignSimbols(getDigWidth(dig) + getStrWidth(string), getMaxCharWidth(), position_x, position_y);

    setCursor(x, y);

    print(dig);
    print(string);
}

void Screen::digAlign(byte dig, PosX position_x, PosY position_y)
{
    alignSimbols(getDigWidth(dig), getMaxCharWidth(), position_x, position_y);

    setCursor(x, y);
    print(dig);
}

void Screen::setPosition(const char *string, PosX position_x, PosY position_y)
{
    alignSimbols(getStrWidth(string), getMaxCharWidth(), position_x, position_y);

    setCursor(x, y);
}

void Screen::iconAlign(int icon, byte iconWH, PosX position_x, PosY position_y)
{
    alignSimbols(iconWH, iconWH, position_x, position_y);
    drawGlyph(x, y, icon);
}

byte Screen::nextX(byte value, byte prewX = 0, const char *simbol = 0)
{
    return (getDigWidth(value) + prewX + getStrWidth(simbol));
}

void Screen::frameAlign(byte W, byte H, PosX position_x, PosY position_y)
{
    W += W / 4;
    H += H / 2;

    alignSimbols(W, H, position_x, position_y);
    drawFrame(x, y, W, H);
}

void Screen::blinkFrame(byte value, byte x, byte y, Timer &timer)
{
    if (timer.blinkReady())
    {
        drawFrame(x, y - getMaxCharWidth(), getDigWidth(value) + 4, getMaxCharWidth() + 4);
    }
}

void Screen::mover(byte deep_x)
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

void Screen::moveString(Timer &timer, byte deep_x, byte bottom_y, const char *string)
{
    if (!move)
    {
        move_x = (screenWidth - getStrWidth(string)) / 2;
        move = true;
        moveLeft = true;
        moveRight = false;
    }

    setCursor(move_x, bottom_y);
    print(string);

    if (timer.moveReady())
    {
        start_x = (screenWidth - getStrWidth(string)) / 2;
        deep_x = constrain(deep_x, 0, start_x);
        mover(deep_x);
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