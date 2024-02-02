#ifndef DEFENSERRIGHT_CONTROL_H
#define DEFENSERRIGHT_CONTROL_H

#include <src/entities/player/player.h>
#include <src/entities/worldmap/worldmap.h>


class DefenserRight_Control
{
public:
    DefenserRight_Control(WorldMap *worldMap);

    void setPlayer(Player *player);

    void defend(QVector2D ballPos);
    void atack(int Id , QVector2D target);

private:

    Player *_player;
    WorldMap *_worldMap;

};

#endif // DEFENSERRIGHT_CONTROL_H
