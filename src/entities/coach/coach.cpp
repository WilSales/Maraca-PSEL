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
#include <iostream>

#define ROBOT_RADIUS 0.09f;
#define ROBOT_DIAMATER ( 2.0f * ROBOT_RADIUS );
#define BALL_RADIUS 0.0215f;
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

//bool isBallMoving(  )

int estado = 0;
QVector2D BeforeBallPosition;
QVector2D AfterBallPosition;
int counter = 0;

QVector2D Intersectar( QVector2D Antes, QVector2D Depois , QVector2D PosPlayer ){
    float xA = Antes.x();
    float yA = Antes.y();
    float xD = Depois.x();
    float yD = Depois.y();
    float m = ( yA - yD ) / ( xA - xD );
    //Fórmula eh: y - yp = m( x - xp )
    //Escolhendo o ponto Antes:
    float yP = yA;
    float mxP = m * xA;
    float c = -yP + mxP;
    // logo: y - yP - mx + mxp = y - mx + c = 0   OU   y = mx - c
    //...
    // Para intersectar, trassarei uma reta perpendicular a reta da trajetória da bola passando pelo ponto onde está o player qe irá interromper a jogada
    float mPerpendicular = -1/m;
    float xPlayer = PosPlayer.x();
    float yPlayer = PosPlayer.y();
    float mxPlayer = mPerpendicular * xPlayer;
    float b = -yPlayer + mxPlayer;
    // fica: y' - yPlayer - mPerpendicularx + mxPlayer = y - mPerpendicularx + b = 0    OU    y = mPerpendicularx - b;
    //...
    // Agora achando o ponto de intersecção das duas retas: y = y ->  mx - c = mPerpendicularx - b  ->  mx - mPerpendicularx = ( c - b )  ->  x ( da interseção ) = ( c - b ) / ( m - mPerpendicular );
    // Com isso: y = m(x encontrado) - c;
    float NewX = ( c - b ) / ( m - mPerpendicular );
    float NewY = ( m * NewX ) - c;
    QVector2D Target = QVector2D( NewX , NewY );
    return Target;


}


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



       QVector2D ballPosition = getWorldMap()->ballPosition();
       float distPB0toBall = getPlayer(BLUE, 0).value()->getPosition().distanceToPoint(ballPosition);
       float distPB1toBall = getPlayer(BLUE, 1).value()->getPosition().distanceToPoint(ballPosition);
       float distPB2toBall = getPlayer(BLUE, 2).value()->getPosition().distanceToPoint(ballPosition);
       float distPB3toBall = getPlayer(BLUE, 3).value()->getPosition().distanceToPoint(ballPosition);
       float distPB4toBall = getPlayer(BLUE, 4).value()->getPosition().distanceToPoint(ballPosition);
       float distPB5toBall = getPlayer(BLUE, 5).value()->getPosition().distanceToPoint(ballPosition);
       float distPY0toBall = getPlayer(YELLOW, 0).value()->getPosition().distanceToPoint(ballPosition);
       float distPY1toBall = getPlayer(YELLOW, 1).value()->getPosition().distanceToPoint(ballPosition);
       float distPY2toBall = getPlayer(YELLOW, 2).value()->getPosition().distanceToPoint(ballPosition);
       float distPY3toBall = getPlayer(YELLOW, 3).value()->getPosition().distanceToPoint(ballPosition);
       float distPY4toBall = getPlayer(YELLOW, 4).value()->getPosition().distanceToPoint(ballPosition);
       float distPY5toBall = getPlayer(YELLOW, 5).value()->getPosition().distanceToPoint(ballPosition);
       //QVector2D ballPosition2 = ballPosition;
       QVector2D playerBLUE0Position = getPlayer(BLUE, 0).value()->getPosition();
       QVector2D playerBLUE1Position = getPlayer(BLUE, 1).value()->getPosition();
       QVector2D playerBLUE2Position = getPlayer(BLUE, 2).value()->getPosition();
       QVector2D playerBLUE3Position = getPlayer(BLUE, 3).value()->getPosition();
       QVector2D playerBLUE4Position = getPlayer(BLUE, 4).value()->getPosition();
       QVector2D playerBLUE5Position = getPlayer(BLUE, 5).value()->getPosition();
       QVector2D playerYELLOW0Position = getPlayer(YELLOW, 0).value()->getPosition();
       QVector2D playerYELLOW1Position = getPlayer(YELLOW, 1).value()->getPosition();
       QVector2D playerYELLOW2Position = getPlayer(YELLOW, 2).value()->getPosition();
       QVector2D playerYELLOW3Position = getPlayer(YELLOW, 3).value()->getPosition();
       QVector2D playerYELLOW4Position = getPlayer(YELLOW, 4).value()->getPosition();
       QVector2D playerYELLOW5Position = getPlayer(YELLOW, 5).value()->getPosition();


       getPlayer(BLUE, 1).value()->rotateTo(ballPosition);
       getPlayer(BLUE, 2).value()->rotateTo(ballPosition);
       getPlayer(YELLOW, 1).value()->rotateTo(ballPosition);
       getPlayer(YELLOW, 2).value()->rotateTo(ballPosition);
       //QVector2D random = QVector2D(4.0f , 2.0f);
       //getPlayer(YELLOW, 0).value()->goTo(random);

       //getPlayer(YELLOW, 2).value()->goTo(QVector2D( 1.160f , -2.300f));

       QVector2D posDiagLefMedium = QVector2D(2.600f , 1.170f);
       QVector2D posDiagRightDeep = QVector2D(3.500f , -1.900f);
       QVector2D posCenterRightMediumAtack = QVector2D(1.800f , -0.600f);
       QVector2D posCenterDefenseAtack = QVector2D(-1.700f, 0.0f);

       QVector2D Target;



       if(estado == 0){

               getPlayer(BLUE, 0).value()->goTo(QVector2D( -0.600f , 2.100f));
               getPlayer(BLUE, 2).value()->goTo(QVector2D( -0.600f , -2.000f));
               getPlayer(BLUE, 3).value()->goTo(QVector2D( 0.000f , -0.550f));
               getPlayer(BLUE, 3).value()->rotateTo(ballPosition);
               getPlayer(YELLOW, 2).value()->goTo(QVector2D( 1.160f , -2.300f));
               //getPlayer(BLUE, 0).value()->rotateTo(ballPosition);
               getPlayer(BLUE, 2).value()->rotateTo(ballPosition);
               std::cout << "estado 0" << std::endl;

           if( getPlayer(BLUE, 3).value()->getPosition().distanceToPoint(QVector2D( 0.000f , -0.550f)) <= 0.5 ){
               getPlayer(BLUE, 3).value()->dribble(true);
               estado = 1;
           }
       }

       if(estado == 1){

           getPlayer(BLUE, 3).value()->goTo(ballPosition);
           getPlayer(BLUE, 0).value()->goTo(QVector2D( -0.600f , 2.100f));
           getPlayer(BLUE, 2).value()->goTo(QVector2D( -0.600f , -2.000f));
           std::cout << "estado 1" << std::endl;
           if( distPB3toBall <= 1.0 ){
               //std::cout << "a dist eh menor que 03" << std::endl;
               getPlayer(BLUE, 3).value()->rotateTo(QVector2D( -0.600f , 2.100f));
               if( distPB3toBall <= 0.12){
                   //std::cout << "o cara chegou" << std::endl;
                    getPlayer(BLUE, 3).value()->kick( 2.4, false);
                    counter++;
                    if(counter >= 2){
                        estado = 2;
                        counter = 0;
                    }
               }
           }

       }


    if(estado == 2){
        getPlayer(BLUE, 0).value()->goTo(QVector2D( -0.600f , 2.100f));
        getPlayer(BLUE, 0).value()->rotateTo(ballPosition);
        getPlayer(BLUE, 3).value()->goTo(QVector2D( 0.000 , 0.000 ));
        std::cout << "estado 2" << std::endl;
        getPlayer(BLUE, 0).value()->dribble(true);
        getPlayer(BLUE, 3).value()->dribble(false);
        counter++;
        if( distPB0toBall <= 0.150 || counter >= 150 ){
            counter = 0;
            estado = 3;
        }

    }

    if(estado == 3){
        getPlayer(BLUE, 0).value()->dribble(true);
        getPlayer(BLUE, 0).value()->rotateTo(ballPosition);
        getPlayer(BLUE, 0).value()->goTo(ballPosition);
        std::cout << "estado 3" << std::endl;
        if( distPB0toBall <= 0.15 ){
            estado = 4;
        }
    }

    if(estado == 4){
        getPlayer(BLUE, 0).value()->dribble(true);
        getPlayer(BLUE, 0).value()->goTo(QVector2D( 0.600f , 2.100f));
        //getPlayer(BLUE, 0).value()->rotateTo(ballPosition);
        getPlayer(BLUE, 2).value()->goTo(QVector2D( -0.120f ,-1.300f));
        getPlayer(BLUE, 2).value()->rotateTo(ballPosition);
        getPlayer(YELLOW, 0).value()->goTo(QVector2D( 1.500f , 2.100f));
        getPlayer(YELLOW, 2).value()->goTo(QVector2D( 1.200f , -1.300f));
        getPlayer(YELLOW, 5).value()->goTo(QVector2D( 4.000f , 0.200f));
        std::cout << "estado 4" << std::endl;
        if( getPlayer(YELLOW, 2).value()->getPosition().distanceToPoint(QVector2D( 1.200f, -1.000f )) <= 0.300){
            counter++;
        }

        if(counter >= 70){
            getPlayer(BLUE, 0).value()->rotateTo(QVector2D(-1.500, 0.000));
            if(counter >= 130){
                getPlayer(BLUE, 0).value()->kick( 3.1, false);
                estado = 5;
                counter = 0;
                getPlayer(BLUE, 1).value()->dribble(true);
            }
        }


    }


    if(estado == 5){
        std::cout << "estado 5" << std::endl;
        getPlayer(YELLOW, 5).value()->goTo(QVector2D( 4.000f , 0.000f));
        getPlayer(YELLOW, 2).value()->goTo(QVector2D( 1.200f , -1.300f));
        getPlayer(BLUE, 1).value()->dribble(true);
        if( distPB1toBall <= 0.14 ){
            getPlayer(BLUE, 1).value()->rotateTo(QVector2D( 2.300, -0.600 ));
            estado = 6;
            counter = 0;
        }
        else{
            counter++;
            if(counter >= 100){
                getPlayer(BLUE, 1).value()->goTo(ballPosition);
            }
        }

    }


    if(estado == 6){
        std::cout << "estado 6" << std::endl;
        getPlayer(YELLOW, 5).value()->goTo(QVector2D( 4.000f , 0.150f));
        getPlayer(YELLOW, 2).value()->goTo(QVector2D( 1.200f , -1.300f));
        getPlayer(BLUE, 1).value()->dribble(true);
        getPlayer(BLUE, 1).value()->rotateTo(QVector2D( 2.300, -0.950 ));
        counter++;
        if( counter >= 80){
            BeforeBallPosition = ballPosition;
            getPlayer(BLUE, 1).value()->kick( 4.2, false);
            counter = 0;
            estado = 7;
        }
    }


    if(estado == 7){
        std::cout << "estado 7" << std::endl;
        AfterBallPosition = ballPosition;
        //getPlayer(YELLOW, 2).value()->goTo(QVector2D( 1.200f , -1.000f));
        getPlayer(YELLOW, 2).value()->rotateTo(ballPosition);
        getPlayer(BLUE, 0).value()->goTo(QVector2D( 2.000f , 0.800f));
        getPlayer(BLUE, 1).value()->dribble(false);
        getPlayer(YELLOW, 4).value()->rotateTo(ballPosition);
        getPlayer(BLUE, 2).value()->goTo(QVector2D( 2.300f , -0.950f));
        Target = Intersectar( BeforeBallPosition , AfterBallPosition, playerYELLOW2Position );
        getPlayer(YELLOW, 2).value()->goTo(Target);
    }




    /*


    if( estado == 7 ){
        std::cout << "estado 7" << std::endl;
        AfterBallPosition = ballPosition;

        getPlayer(YELLOW, 2).value()->goTo(QVector2D( 1.200f , -1.000f));
        getPlayer(YELLOW, 2).value()->rotateTo(ballPosition);
        getPlayer(BLUE, 0).value()->goTo(QVector2D( 2.000f , 0.800f));
        getPlayer(BLUE, 1).value()->dribble(false);
        getPlayer(YELLOW, 4).value()->rotateTo(ballPosition);
        getPlayer(BLUE, 2).value()->goTo(QVector2D( 2.300f , -0.950f));
        if( distPY4toBall <= 1.200 ){
            getPlayer(YELLOW, 4).value()->dribble(true);
            getPlayer(YELLOW, 4).value()->goTo(ballPosition);
            if( distPY4toBall <= 0.14 ){
                estado = 8;
            }
        }
    }

    if( estado == 8 ){
        std::cout << "estado 8" << std::endl;
        getPlayer(YELLOW, 2).value()->goTo(QVector2D( 1.200f , -1.000f));
        getPlayer(YELLOW, 4).value()->dribble(true);
        getPlayer(YELLOW, 4).value()->goTo(QVector2D( 2.500f, -2.600f ));
        getPlayer(YELLOW, 4).value()->rotateTo(QVector2D(-4.300f , 0.000f));
        counter++;
        if(counter == 100){
            getPlayer(YELLOW, 4).value()->kick( 8.0 , false);
        }
    }




    */









   /* if(estado == 0){

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
        //std::cout << "estou no estado 6" << std::endl;
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
        //getPlayer(BLUE, 3).value()->goTo( posDiagLefMedium );
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
        else{
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
            //counter = 0;
            estado = 8;
        }
    }







*/






}
