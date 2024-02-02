#ifndef DEFENSERLEFT_CONTROL_H
#define DEFENSERLEFT_CONTROL_H

#include <src/entities/player/player.h>
#include <src/entities/worldmap/worldmap.h>


class DefenserLeft_Control
{
public:
    DefenserLeft_Control(WorldMap *worldMap);

    void setPlayer(Player *player);

    void defend(QVector2D ballPos);
    void atack(int Id , QVector2D target);

private:

    Player *_player;
    WorldMap *_worldMap;
};

#endif // DEFENSERLEFT_CONTROL_H
