#include "midfielder_control.h"
#include <iostream>
#include <cmath>

#define ROBOT_RADIUS 0.09f
#define ROBOT_DIAMATER ( 2.0f * ROBOT_RADIUS )
#define BALL_RADIUS 0.0215f
#define BALL_DIAMATER ( 2.0f * BALL_RADIUS )

Midfielder_Control::Midfielder_Control(WorldMap *worldMap)
{
    _worldMap = worldMap;
    _player = nullptr;
}

void Midfielder_Control::setPlayer(Player *player){
    _player = player;
}

void Midfielder_Control::defend(QVector2D ballPos){
    _player->goTo(QVector2D( _worldMap->ourGoalCenter().x() - (_worldMap->length()/4)  , 0.000f  ));
    _player->rotateTo(ballPos);
}

int counting = 0;

void Midfielder_Control::atack( QVector2D target ){
    if(_player != nullptr){
        _player->dribble(true);
        _player->rotateTo(_worldMap->ballPosition());
        _player->goTo(_worldMap->ballPosition());
        if( _player->getPosition().distanceToPoint(_worldMap->ballPosition()) <= ( ROBOT_RADIUS + BALL_RADIUS ) ){
            if( ( _worldMap->ballPosition().x() <= (_worldMap->theirGoalCenter().x() + (_worldMap->length()/4)) ) && _worldMap->ballPosition().y() < 0.000f  ){
                _player->goTo(QVector2D( ( _worldMap->theirGoalCenter().x() + (_worldMap->length()/8) ) ,  (-0.250f  ) ) );
                _player->rotateTo(target);
                counting++;
                if(counting >= 170){
                    _player->kick( 3.500f , false );
                    counting = 0;
               }
            }
            else if( ( _worldMap->ballPosition().x() > (_worldMap->theirGoalCenter().x() + (_worldMap->length()/4)) ) && ( _worldMap->ballPosition().x() <= 0 ) && _worldMap->ballPosition().y() < 0.000f  ){
                _player->goTo(QVector2D( ( _worldMap->theirGoalCenter().x() + (3*(_worldMap->length()/4)) ) ,  (-0.250f  ) ) );
                _player->rotateTo(target);
                counting++;
                if(counting >= 170){
                    _player->kick( 4.500f , false );
                    counting = 0;
               }
            }
            else if( ( _worldMap->ballPosition().x() > 0.000f ) && ( _worldMap->ballPosition().x() < ( _worldMap->ourGoalCenter().x() - _worldMap->length()/4) )  && (_worldMap->ballPosition().y() < 0.000f) ){
                _player->goTo(QVector2D( ( _worldMap->theirGoalCenter().x() + (3*(_worldMap->length()/4)) ) ,  (-0.250f  ) ) );
                _player->rotateTo(target);
                counting++;
                if(counting >= 170){
                    _player->kick( 4.500f , false );
                    counting = 0;
               }
            }
            else if( ( _worldMap->ballPosition().x() > 0.000f ) && ( _worldMap->ballPosition().x() >= ( _worldMap->ourGoalCenter().x() - _worldMap->length()/4) )  && (_worldMap->ballPosition().y() < 0.000f) ){
                _player->goTo(QVector2D( ( _worldMap->theirGoalCenter().x() + (3*(_worldMap->length()/4)) ) ,  (-0.250f  ) ) );
                _player->rotateTo(target);
                counting++;
                if(counting >= 170){
                    _player->kick( 4.500f , false );
                    counting = 0;
               }
            }
            else if( ( _worldMap->ballPosition().x() <= (_worldMap->theirGoalCenter().x() + (_worldMap->length()/4)) ) && _worldMap->ballPosition().y() >= 0.000f  ){
                _player->goTo(QVector2D( ( _worldMap->theirGoalCenter().x() + (_worldMap->length()/8) ) ,  (0.250f  ) ) );
                _player->rotateTo(target);
                counting++;
                if(counting >= 170){
                    _player->kick( 3.500f , false );
                    counting = 0;
               }
            }
            else if( ( _worldMap->ballPosition().x() > (_worldMap->theirGoalCenter().x() + (_worldMap->length()/4)) ) && ( _worldMap->ballPosition().x() <= 0 ) && _worldMap->ballPosition().y() >= 0.000f  ){
                _player->goTo(QVector2D( ( _worldMap->theirGoalCenter().x() + (3*(_worldMap->length()/4)) ) ,  (0.250f  ) ) );
                _player->rotateTo(target);
                counting++;
                if(counting >= 170){
                    _player->kick( 4.500f , false );
                    counting = 0;
               }
            }
            else if( ( _worldMap->ballPosition().x() > 0.000f ) && ( _worldMap->ballPosition().x() < ( _worldMap->ourGoalCenter().x() - _worldMap->length()/4) )  && (_worldMap->ballPosition().y() >= 0.000f) ){
                _player->goTo(QVector2D( ( _worldMap->theirGoalCenter().x() + (3*(_worldMap->length()/4)) ) ,  (0.250f  ) ) );
                _player->rotateTo(target);
                counting++;
                if(counting >= 170){
                    _player->kick( 4.500f , false );
                    counting = 0;
               }
            }
            else if( ( _worldMap->ballPosition().x() > 0.000f ) && ( _worldMap->ballPosition().x() >= ( _worldMap->ourGoalCenter().x() - _worldMap->length()/4) )  && (_worldMap->ballPosition().y() >= 0.000f) ){
                _player->goTo(QVector2D( ( _worldMap->theirGoalCenter().x() + (3*(_worldMap->length()/4)) ) ,  (0.250f  ) ) );
                _player->rotateTo(target);
                counting++;
                if(counting >= 170){
                    _player->kick( 4.500f , false );
                    counting = 0;
               }
            }

        }
    }
}
