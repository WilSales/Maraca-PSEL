#ifndef MIDFIELDER_CONTROL_H
#define MIDFIELDER_CONTROL_H

#include <src/entities/player/player.h>
#include <src/entities/worldmap/worldmap.h>

class Midfielder_Control
{
public:
    Midfielder_Control(WorldMap *worldMap);

    void setPlayer(Player *player);

    void defend(QVector2D ballPos);
    void atack(QVector2D target);

private:

    Player *_player;
    WorldMap *_worldMap;
};

#endif // MIDFIELDER_CONTROL_H
