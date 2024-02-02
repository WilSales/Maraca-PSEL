#ifndef GOALKEEPER_CONTROL_H
#define GOALKEEPER_CONTROL_H

#include <src/entities/player/player.h>
#include <src/entities/worldmap/worldmap.h>


class GoalKeeper_Control
{
public:

    GoalKeeper_Control(WorldMap *worldMap);

    void setPlayer(Player *player);

    void defend(QVector2D ballPos);
    void pass( QVector2D ballPos , QVector2D target);

private:

    Player *_player;
    WorldMap *_worldMap;
};

#endif // GOALKEEPER_CONTROL_H
