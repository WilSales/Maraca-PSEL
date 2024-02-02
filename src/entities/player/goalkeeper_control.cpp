#include "goalkeeper_control.h"
#include <iostream>
#include <cmath>

#define ROBOT_RADIUS 0.09f
#define ROBOT_DIAMATER ( 2.0f * ROBOT_RADIUS )
#define BALL_RADIUS 0.0215f
#define BALL_DIAMATER ( 2.0f * BALL_RADIUS )

GoalKeeper_Control::GoalKeeper_Control(WorldMap *worldMap)
{
    _worldMap = worldMap;
    _player = nullptr;
}

void GoalKeeper_Control::setPlayer(Player *player){
    _player = player;
}

void GoalKeeper_Control::defend(QVector2D ballPos){
    //veremos
    if(_player != nullptr){

        //circunferenciaRight

        float raio = 0.500f;
        //centro da circnferencia: x = 4.500 , y = 0.000
        //Equação da circunferência:  X2 + Y2 – 2XcX – 2YcY + Xc2 + Yc2 – R2 = 0
        float Xc = 4.500f;
        float Yc = 0.000f;
        // Como Yc = 0 -> X2 + Y2 - 2XcX - R2 = 0;


        //Equação da reta descrita pelos pontos da posição da bola e o centro do gol: y - yp = m( x - xp )
        float Xball = ballPos.x();
        float Yball = ballPos.y();
        float m = ( Yball - Yc ) / ( Xball - Xc );
        float Yp = Yball;
        float Xp = Xball;
        float mXp = m * Xp;
        //float C = -Yp + mXp;
        //spdlog::info( "C = {}", C );

        // y - yp + mxp - mx = 0 -> y - mx + C = 0;
        // X = ( y + C ) / m ;
        //...
        //Interseção:
        // Y2 + 2YC + C2 + Y2m2 - 2Xc( Y + C )m - 2YcYm2 + Xc2m2 + Yc2m2 - R2m2 = 0
        //
        //Calculando o delta:
        //float a = m*m + 1;
        //float a = ( ( 1 - 2*Yball + m*m  ) / (m*m) );
        //float a = ( (1 / m*m) + 1 );
        float a = ( 1 + (m*m) );
        //float b = ( 2*C* - 2*Xc*m );
        //float b = (2*m*Xball) - ( 2*Xc*m) - ( 2*Yc*m*m );
        //float b = ( -2*Yp / m*m ) + ( 2*Xp / m ) - ( 2*Yc ) - ( 2*Xc / m );
        float b = ((-2*Yp) + (2*m*Xp) - (2*m*Xc) - (2*m*m*Yc));
        //float c = (2*Yc*m*m) + (C*C) - (2*Xc*m*C) + (Xc*Xc*m*m) + (Yc*Yc*m*m) - (raio*raio*m*m);
        //float c = (C*C) - (2*Xc*m*C) + (Xc*Xc*m*m) - (raio*raio*m*m);
        //float c = ((Yball*Yball)/m*m) - ( (2*Xball*Yball) / m) + (Xball) + ((2*Yball*Xc) / m) - (2*Xball*Xc) + Xc*Xc + Yc*Yc - raio*raio;
        //float c = ( Yp*Yp / m*m ) - ( 2*Xp*Yp / m ) + ( Xp*Xp ) + ( Xc*Xc ) + ( Yc*Yc ) - ( raio*raio ) + ( 2*Xc*Yc / m ) - ( 2*Xc*Xp );
        float c = ( (Yp*Yp) - (2*Yp*m*Xp) + (2*Yp*m*Xc) + (m*m*Xp*Xp) - (2*m*m*Xp*Xc) + (m*m*Xc*Xc) + (m*m*Yc*Yc) - (raio*raio*m*m) );
        float delta = ( b*b ) - (4*a*c);
        float Raizdelta = sqrt(delta);
        if( delta < 0 ){
            _player->goTo(_worldMap->ourGoalCenter());
        }
        else{

            float Y1 = (-b + Raizdelta) / (2*a);

            float Y2 = (-b - Raizdelta) / (2*a);

            float X1 = (( Y1 - Yp + m*Xp ) / m);

            float X2 = (( Y2 - Yp + m*Xp ) / m);

            float Ypos;
            float Xpos;
            if( Yp <= 0 ){
                if( Y1 <= Y2 ){
                    Ypos = Y1;
                    Xpos = X1;
                }
                else{
                    Ypos = Y2;
                    Xpos = X2;
                }
                _player->goTo(QVector2D( Xpos, Ypos ));
            }
            else{
                if( Y1 >= Y2 ){
                    Ypos = Y1;
                    Xpos = X1;
                }
                else{
                    Ypos = Y2;
                    Xpos = X2;
                }

                _player->goTo( QVector2D( Xpos, Ypos ));
            }

        }

        //_player->goTo(_worldMap->ourGoalCenter());
    }
}

int cnt = 0;

void GoalKeeper_Control::pass(QVector2D ballPos , QVector2D target){
    //we'll see
    if(_player != nullptr){
        _player->dribble(true);
        _player->goTo(ballPos);
        _player->rotateTo(ballPos);
        if(_player->getPosition().distanceToPoint(ballPos) <=  (ROBOT_RADIUS + BALL_DIAMATER)){
            if(ballPos.y() <= 0){
                _player->goTo(QVector2D(_worldMap->ourGoalCenter().x() - 0.500f , -0.500f ));
                _player->rotateTo(target);
                if( _player->getPosition().distanceToPoint(QVector2D(_worldMap->ourGoalCenter().x() - 0.500f , -0.500f )) <= ( ROBOT_RADIUS )){
                    cnt++;
                    if(cnt >= 60){
                        _player->kick(2.500f, false);
                        cnt = 0;
                    }
                }
            }
            else{
                _player->goTo(QVector2D(_worldMap->ourGoalCenter().x() - 0.500f , 0.500f ));
                _player->rotateTo(target);
                if( _player->getPosition().distanceToPoint(QVector2D(_worldMap->ourGoalCenter().x() - 0.500f , 0.500f )) <= ( ROBOT_RADIUS )){
                    cnt++;
                    if(cnt >= 60){
                        _player->kick(2.500f, false);
                        cnt = 0;
                    }
                }
            }
        }
    }
}
