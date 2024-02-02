#include "forwardleft_control.h"
#include <iostream>
#include <cmath>

#define ROBOT_RADIUS 0.09f
#define ROBOT_DIAMATER ( 2.0f * ROBOT_RADIUS )
#define BALL_RADIUS 0.0215f
#define BALL_DIAMATER ( 2.0f * BALL_RADIUS )

ForwardLeft_Control::ForwardLeft_Control(WorldMap *worldMap)
{
    _worldMap = worldMap;
    _player = nullptr;
}

void ForwardLeft_Control::setPlayer(Player *player){
    _player = player;
}

void ForwardLeft_Control::defend(QVector2D ballPos){
    if(_player != nullptr ){
        if( ( ( ballPos.y() ) >= ( -(( _worldMap->width()/2 ) - ( (_worldMap->width()/2) - (_worldMap->penaltyWidth()/2)  ) ) )  &&  ( ballPos.x() < 0.000f ) )  ){
            _player->goTo( QVector2D( 0.000f + ROBOT_DIAMATER , -(( _worldMap->width()/2 ) - ( (_worldMap->width()/2) - (_worldMap->penaltyWidth()/2) - ROBOT_RADIUS ) )));
            _player->rotateTo(ballPos);
        }
        else if( ( ( ( ballPos.y() ) < ( -(( _worldMap->width()/2 ) - ( (_worldMap->width()/2) - (_worldMap->penaltyWidth()/2)  ) ) ) && ( ballPos.x() < 0.000f )) )){
            _player->goTo( QVector2D( 0.000f + ROBOT_DIAMATER , ballPos.y()));
            _player->rotateTo(ballPos);
        }
        else if( ballPos.x() <= ( (_worldMap->length()/2 ) - ( _worldMap->penaltyDepth() + ROBOT_DIAMATER ) )){
            _player->goTo( QVector2D( ballPos.x() , -(( _worldMap->width()/2 ) - ( (_worldMap->width()/2) - (_worldMap->penaltyWidth()/2) - ROBOT_RADIUS ) )));
            _player->rotateTo(ballPos);
        }
        else{
            _player->goTo( QVector2D( (_worldMap->length()/2 ) - ( _worldMap->penaltyDepth() + ROBOT_DIAMATER ) , -(( _worldMap->width()/2 ) - ( (_worldMap->width()/2) - (_worldMap->penaltyWidth()/2) - ROBOT_RADIUS ) )));
            _player->rotateTo(ballPos);
        }
    }
}

int ct = 0;

void ForwardLeft_Control::atack(int est){
    if(_player != nullptr){
        if(est == 0){
            _player->rotateTo(_worldMap->ballPosition());
            _player->goTo(QVector2D( _worldMap->theirGoalCenter().x() + _worldMap->penaltyDepth() , _worldMap->ourGoalRightPost().y() - 1.500f ));
        }
        else{
            _player->rotateTo(_worldMap->ballPosition());
            if( _player->getPosition().distanceToPoint(_worldMap->ballPosition()) >= (ROBOT_RADIUS + BALL_RADIUS) ){
                _player->dribble(true);
                 _player->goTo(_worldMap->ballPosition());

            }
            else{
                _player->dribble(true);
                _player->goTo(QVector2D( _worldMap->theirGoalCenter().x() + _worldMap->penaltyDepth() , _worldMap->ourGoalRightPost().y() - 1.500f ) );
                _player->rotateTo(QVector2D(_worldMap->theirGoalLeftPost().x() , _worldMap->theirGoalLeftPost().y() + 0.200f ));
                if( _player->getPosition().distanceToPoint(QVector2D( _worldMap->theirGoalCenter().x() + _worldMap->penaltyDepth() , _worldMap->ourGoalRightPost().y() - 1.500f ) ) < (ROBOT_DIAMATER)){
                    ct++;
                    if(ct >= 70){
                        _player->kick(3.500f , false);
                        ct = 0;
                    }
                }

            }

        }

    }
}
