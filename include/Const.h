#pragma once
#include <SFML/Graphics.hpp>
//all the consts in the program

const sf::Vector2f RIGHT = sf::Vector2f(1, 0);
const sf::Vector2f LEFT = sf::Vector2f(-1, 0);
const sf::Vector2f UP = sf::Vector2f(0, -1);
const sf::Vector2f DOWN = sf::Vector2f(0, 1);

const int LIFES = 3;
const int PANEL_SIZE = 50;
const int LEVELS = 3;

const float HOLE_TIME = 5.0f;

const float SNAP_TOLERANCE = 15.0f;

const float GRAVITY = 1000.f;
const float ENEMY_SPEED = 30.f;
const float PLAYER_SPEED = 50.f;

const float GAME_TIME =180.f;//2 minutes
const unsigned int TEXT_SIZE = 20;

const char PLAYER = '@';
const char EMPTY = ' ';
const char SAVE = '$';
const char FLOOR = '#';
const char CLEAR = '=';
const char ENEMY = '%';
const char COIN = '*';
const char LADDER = 'H';
const char POLE = '-';
const char GROUND = '^';
const char NONE = 'X';

const auto DEEP_PINK = sf::Color::Color(255, 20, 147);
const auto BACKGROUND_COLOR = sf::Color::Color(229, 115, 115);