#ifndef FORWARDLEFT_CONTROL_H
#define FORWARDLEFT_CONTROL_H

#include <src/entities/player/player.h>
#include <src/entities/worldmap/worldmap.h>

class ForwardLeft_Control
{
public:
    ForwardLeft_Control(WorldMap *worldMap);

    void setPlayer(Player *player);

    void defend(QVector2D ballPos);
    void atack(int est);

private:

    Player *_player;
    WorldMap *_worldMap;
};

#endif // FORWARDLEFT_CONTROL_H
