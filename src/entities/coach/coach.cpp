/***
 * Maracatronics Robotics
 * Federal University of Pernambuco (UFPE) at Recife
 * http://www.maracatronics.com/
 *
 * This file is part of Armorial project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#include "coach.h"

#define ROBOT_RADIUS 0.09;
#define ROBOT_DIAMATER ( 2.0f * ROBOT_RADIUS );
#define BALL_RADIUS 0.0215;
#define BALL_DIAMATER ( 2.0f * BALL_RADIUS );



Coach::Coach(const QMap<bool, QList<Player*>>& players, WorldMap* worldMap)
    : _players(players), _worldMap(worldMap)
{
    // Create QTimer and connects to the runCoach() slot
    _actuatorTimer = new QTimer(this);
    QObject::connect(_actuatorTimer, &QTimer::timeout, this, &Coach::runCoach);
    _actuatorTimer->start(COACH_ITERATION_INTERVAL_MS);
}

std::optional<Player*> Coach::getPlayer(const bool& isTeamBlue, const quint8& playerId) {
    // Get list of players
    QList<Player*> playersForColor = _players.value(isTeamBlue);

    // Iterate searching for playerId
    for(const auto& player : playersForColor) {
        if(player->getPlayerId() == playerId) {
            return player;
        }
    }

    // If could not found, just return std::nullopt (should trait later)
    return std::nullopt;
}

WorldMap* Coach::getWorldMap() {
    return _worldMap;
}

int estado = 0;
QVector2D BeforeBallPosition = QVector2D(0.0f, 0.0f);
int counter = 0;

void Coach::runCoach() {
    // Here you can control the robots freely.
    // Remember that the getPlayer(color, id) function can return a std::nullopt object, so
    // be careful when you use it (remember to only use ids from 0-2 and the BLUE and YELLOW
    // defines).

    // Example 1: here we get the ball position and set the BLUE and YELLOW player 0 to follow it

        //QVector2D ballPosition = getWorldMap()->ballPosition();
        //getPlayer(BLUE, 0).value()->goTo(ballPosition);
        //getPlayer(YELLOW, 0).value()->goTo(ballPosition);

    //getPlayer(YELLOW, 0).value()->goTo(ballPosition);

    // Example 2: here we set the BLUE and YELLOW players 1 and 2 to rotate to the ball
    //getPlayer(BLUE, 1).value()->rotateTo(ballPosition);
    //getPlayer(BLUE, 2).value()->rotateTo(ballPosition);
    //getPlayer(YELLOW, 1).value()->rotateTo(ballPosition);
    //getPlayer(YELLOW, 2).value()->rotateTo(ballPosition);

   // getPlayer(BLUE, 3).value()->dribble(true);
  //  getPlayer(YELLOW, 3).value()->dribble(true);
  //  getPlayer(BLUE, 2).value()->dribble(true);
   // getPlayer(YELLOW, 2).value()->dribble(true);



    //while( run == 1){


       QVector2D ballPosition = getWorldMap()->ballPosition();
       float distPB0toBall = getPlayer(BLUE, 0).value()->getPosition().distanceToPoint(ballPosition);
       float distPB1toBall = getPlayer(BLUE, 1).value()->getPosition().distanceToPoint(ballPosition);
       float distPB2toBall = getPlayer(BLUE, 2).value()->getPosition().distanceToPoint(ballPosition);
       float distPB3toBall = getPlayer(BLUE, 3).value()->getPosition().distanceToPoint(ballPosition);
       float distPB4toBall = getPlayer(BLUE, 4).value()->getPosition().distanceToPoint(ballPosition);
       //QVector2D ballPosition2 = ballPosition;
       QVector2D playerBLUE0Position = getPlayer(BLUE, 0).value()->getPosition();
       QVector2D playerBLUE1Position = getPlayer(BLUE, 1).value()->getPosition();
       QVector2D playerBLUE2Position = getPlayer(BLUE, 2).value()->getPosition();
       QVector2D playerBLUE3Position = getPlayer(BLUE, 3).value()->getPosition();
       QVector2D playerBLUE4Position = getPlayer(BLUE, 4).value()->getPosition();


       getPlayer(BLUE, 1).value()->rotateTo(ballPosition);
       getPlayer(BLUE, 2).value()->rotateTo(ballPosition);
       getPlayer(YELLOW, 1).value()->rotateTo(ballPosition);
       getPlayer(YELLOW, 2).value()->rotateTo(ballPosition);
       QVector2D random = QVector2D(4.0f , 2.0f);
       getPlayer(YELLOW, 0).value()->goTo(random);
       getPlayer(YELLOW, 2).value()->goTo(QVector2D( 1.160f , -2.300f));

     //  getPlayer(BLUE, 0).value()->goTo(ballPosition);
     //  getPlayer(BLUE, 0).value()->rotateTo(ballPosition);

    if(estado == 0){

        getPlayer(BLUE, 0).value()->goTo(ballPosition);
        getPlayer(BLUE, 0).value()->rotateTo(ballPosition);
        if(distPB0toBall <= 0.3f){
            BeforeBallPosition = getWorldMap()->ballPosition();
            estado = 1;
        }

    }

    if(estado == 1){

        getPlayer(BLUE, 0).value()->goTo(ballPosition);
        getPlayer(BLUE, 0).value()->rotateTo(ballPosition);
        getPlayer(BLUE, 0).value()->kick( 8.0, false);
        if(distPB0toBall > 0.3f){
            estado = 2;
        }

     }


    if(estado == 2){
        //playerBLUE0Position = getPlayer(BLUE, 0).value()->getPosition();
        getPlayer(BLUE, 0).value()->goTo(BeforeBallPosition);
        estado = 3;
    }

    //2600 e 1170
    QVector2D posDiagLefMedium = QVector2D(2.600f , 1.170f);
    QVector2D posDiagRightDeep = QVector2D(3.500f , -1.900f);
    QVector2D posCenterRightMediumAtack = QVector2D(1.800f , -0.600f);
    QVector2D posCenterDefenseAtack = QVector2D(-1.700f, 0.0f);
    //QVector2D diagonalLeft = QVector2D(getWorldMap()->theirGoalLeftPost() - )

    if(estado == 3){

        //getPlayer(BLUE, 2).value()->goTo(ballPosition);
        //getPlayer(BLUE, 2).value()->dribble(true);
        getPlayer(BLUE, 0).value()->goTo(BeforeBallPosition);
        getPlayer(BLUE, 3).value()->goTo( posDiagLefMedium );
        getPlayer(BLUE, 1).value()->goTo( posCenterRightMediumAtack );
        if(playerBLUE1Position.distanceToPoint( posCenterRightMediumAtack ) <= 0.15f && playerBLUE3Position.distanceToPoint( posDiagLefMedium ) <= 0.15f){
            estado = 4;
        }

    }

    if(estado == 4){
        getPlayer(BLUE, 0).value()->goTo(BeforeBallPosition);
        getPlayer(BLUE, 2).value()->goTo(ballPosition);
        getPlayer(BLUE, 2).value()->rotateTo( ballPosition );
        getPlayer(BLUE, 3).value()->goTo( posDiagLefMedium );
        ballPosition = getWorldMap()->ballPosition();
        distPB2toBall = getPlayer(BLUE, 2).value()->getPosition().distanceToPoint(ballPosition);
        if( distPB2toBall <= 0.12f ){
            getPlayer(BLUE, 2).value()->dribble(true);
            estado = 5;
            //getPlayer(BLUE, 2).value()->rotateTo( ballPosition );

        }

    }

    if(estado == 5){
        getPlayer(BLUE, 0).value()->goTo(BeforeBallPosition);
        getPlayer(BLUE, 3).value()->goTo( posDiagLefMedium );
        getPlayer(BLUE, 2).value()->dribble(true);
        getPlayer(BLUE, 2).value()->goTo( posDiagRightDeep );
        playerBLUE1Position = getPlayer(BLUE, 1).value()->getPosition();
        getPlayer(BLUE, 2).value()->rotateTo(QVector2D( 2.130f , -0.850));
        getPlayer(BLUE, 1).value()->rotateTo(playerBLUE2Position);
        getPlayer(BLUE, 4).value()->goTo( posCenterDefenseAtack );
        getPlayer(BLUE, 1).value()->dribble(true);
        playerBLUE2Position = getPlayer(BLUE, 2).value()->getPosition();
        playerBLUE1Position = getPlayer(BLUE, 1).value()->getPosition();
        if(playerBLUE2Position.distanceToPoint(posDiagRightDeep) <= 0.15f){
            for(int a = 0; a < 1000000; a++){
                //playerBLUE1Position = getPlayer(BLUE, 1).value()->getPosition();
                getPlayer(BLUE, 2).value()->rotateTo(QVector2D( 2.700f , -1.600));
            }
            getPlayer(BLUE, 1).value()->dribble(true);
            estado = 6;
            counter = 0;
        }
    }

    if(estado == 6){
        counter++;
        getPlayer(BLUE, 4).value()->goTo( posCenterDefenseAtack );
        getPlayer(BLUE, 3).value()->goTo( posDiagLefMedium );
        getPlayer(BLUE, 2).value()->kick( 3.1f, false);
        getPlayer(BLUE, 2).value()->dribble(false);
        ballPosition = getWorldMap()->ballPosition();
        playerBLUE1Position = getPlayer(BLUE, 1).value()->getPosition();
        playerBLUE3Position = getPlayer(BLUE, 3).value()->getPosition();
        getPlayer(BLUE, 1).value()->rotateTo(ballPosition);
        distPB1toBall = getPlayer(BLUE, 1).value()->getPosition().distanceToPoint(ballPosition);
        //getPlayer(BLUE, 1).value()->goTo(ballPosition);
        getPlayer(BLUE, 1).value()->dribble(true);
        if( distPB1toBall <= 0.121f){
            getPlayer(BLUE, 1).value()->goTo( ballPosition );
            getPlayer(BLUE, 1).value()->rotateTo(ballPosition);
            getPlayer(BLUE, 3).value()->rotateTo(playerBLUE1Position);
            estado = 7;
            counter = 0;
        }
        if( counter >= 500){
            getPlayer(BLUE, 1).value()->dribble(true);
            getPlayer(BLUE, 1).value()->goTo( ballPosition );
            getPlayer(BLUE, 1).value()->rotateTo(ballPosition);
            if( distPB1toBall <= 0.121f){
                getPlayer(BLUE, 1).value()->goTo( ballPosition );
                getPlayer(BLUE, 1).value()->rotateTo(ballPosition);
                getPlayer(BLUE, 3).value()->rotateTo(playerBLUE1Position);
                estado = 7;
                counter = 0;
            }
        }

    }

    if(estado == 7){

        ballPosition = getWorldMap()->ballPosition();
        getPlayer(BLUE, 1).value()->dribble(true);
        getPlayer(BLUE, 4).value()->goTo( posCenterDefenseAtack );
        getPlayer(BLUE, 3).value()->goTo( posDiagLefMedium );
        getPlayer(BLUE, 1).value()->goTo( QVector2D( 3.000f , -0.600) );
        getPlayer(BLUE, 1).value()->rotateTo(playerBLUE3Position);
        getPlayer(BLUE, 3).value()->rotateTo(playerBLUE1Position);
        playerBLUE1Position = getPlayer(BLUE, 1).value()->getPosition();
        if(playerBLUE1Position.distanceToPoint(QVector2D( 3.000f , -0.600)) <= 0.30f){
            if(playerBLUE1Position.distanceToPoint(ballPosition) <= 0.13f){
            counter++;
            getPlayer(BLUE, 3).value()->dribble(true);
            getPlayer(YELLOW, 5).value()->goTo(QVector2D(4.000f , 0.000f));
            if(counter >= 50){
                getPlayer(BLUE, 3).value()->dribble(true);
                getPlayer(BLUE, 1).value()->kick( 2.3f, false);
                estado = 8;
                counter = 0;
            }
            }
            else{
                  counter = 500;
                  estado = 6;
            }
        }


    }

    if(estado == 8){
        counter++;
        getPlayer(YELLOW, 5).value()->goTo(QVector2D(4.000f , 0.000f));
        getPlayer(BLUE, 3).value()->dribble(true);
        getPlayer(BLUE, 4).value()->goTo( posCenterDefenseAtack );
        getPlayer(BLUE, 3).value()->goTo( posDiagLefMedium );
        ballPosition = getWorldMap()->ballPosition();
        getPlayer(BLUE, 3).value()->rotateTo(ballPosition);
        ballPosition = getWorldMap()->ballPosition();
        distPB3toBall = getPlayer(BLUE, 3).value()->getPosition().distanceToPoint(ballPosition);
        if( distPB3toBall <= 0.121f ){
            getPlayer(BLUE, 3).value()->dribble(true);
            getPlayer(BLUE, 3).value()->goTo( ballPosition );
            getPlayer(BLUE, 3).value()->rotateTo(ballPosition);
            estado = 9;
            counter = 0;
        }
        if(counter >= 200){
            getPlayer(BLUE, 3).value()->dribble(true);
            getPlayer(BLUE, 3).value()->goTo( ballPosition );
            getPlayer(BLUE, 3).value()->rotateTo(ballPosition);
            if( distPB3toBall <= 0.121f ){
                getPlayer(BLUE, 3).value()->goTo( ballPosition );
                getPlayer(BLUE, 3).value()->rotateTo(ballPosition);
                estado = 9;
                counter = 0;
            }
        }

    }

    if(estado == 9){
        counter++;
        getPlayer(YELLOW, 5).value()->goTo(QVector2D(4.000f , 0.000f));
        getPlayer(BLUE, 3).value()->dribble(true);
        getPlayer(BLUE, 4).value()->goTo( posCenterDefenseAtack );
        getPlayer(BLUE, 3).value()->goTo( posDiagLefMedium );
        ballPosition = getWorldMap()->ballPosition();
        getPlayer(BLUE, 3).value()->goTo( posDiagLefMedium  );
        getPlayer(BLUE, 3).value()->rotateTo( QVector2D(4.5f, 0.0f) );
        if(counter == 100){
            getPlayer(BLUE, 3).value()->kick( 4.0f, false);
            //counter = 0;
            estado = 10;
        }
        if(counter > 170){
            counter = 0;
            estado = 8;
        }
    }



//}










}
