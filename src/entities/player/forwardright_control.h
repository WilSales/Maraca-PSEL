#ifndef FORWARDRIGHT_CONTROL_H
#define FORWARDRIGHT_CONTROL_H

#include <src/entities/player/player.h>
#include <src/entities/worldmap/worldmap.h>

class ForwardRight_Control
{
public:
    ForwardRight_Control(WorldMap *worldMap);

    void setPlayer(Player *player);

    void defend(QVector2D ballPos);
    void atack(int est);

private:

    Player *_player;
    WorldMap *_worldMap;
};

#endif // FORWARDRIGHT_CONTROL_H
