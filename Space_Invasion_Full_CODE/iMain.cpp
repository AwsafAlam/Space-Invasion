# include "iGraphics.h"


#define screen_width 1350
#define screen_height 670
#define h 45
#define w 30
#define r 10
#define a 150

void settime();
void gametimer();
void startlevel();
void newgame();
void score();
void drawscore();
void gameover();
void distfromopp();
void healthbar();
void imgmove();
void highscore();
void drawhighscore();
void initialise();
void makebullets();
void intro();
void controls();
void overrect();
void up();
void down();
void right();
void left();
void shoot();
void blastimag(int);
void blastimg_player(int );
void changeflag();
void opponentfire();
void mainsnd();
void gameovrsnd();






int  x=50, y=200; //player
int oppx[6]= {2000,3400,5650,1350,1450,1500},oppy[6]= {200,500,300,450,370,100};//oppnents
int i=0 ,t1,t2,t3,t4;//timers
int curr_score=0, prevHigh_score[5]= {}, currHigh_score=0 , no_of_players=3, health=200;
int p= screen_width/2 - a/2 ,g=0;//g changes postn of image;
int tim[3]= {1,60,100},dx[6]= {2,4,1,3,1,2} ,dy[6]= {1,2,4,0,3,1} , rec=1, bulflag=1;
int distance[6]= {} , imgflag=1,f=0,f1=0,cntflag=0;
char ch1[50];
int shotFlag=0,upMoveFlag=0,downMoveFlag=0,rightMoveFlag=0 ,leftMoveFlag=0; //motion flag
int oppbulletx[100]= {}, oppbullety[100]= {},mbx[100]= {} ,mby[100]= {} ,make,makeopp;//bullet



//initialise all vairibles
void initialise()
{
    int i;
    tim[0]=1;
    tim[1]=60;
    tim[2]=100;
    health=200;
    currHigh_score=curr_score;
    curr_score=0;
    iPauseTimer(t1);
    iPauseTimer(t3);
    iPauseTimer(t2);
    iPauseTimer(t4);

    highscore();
    x=50;
    y=200;
    make=0;
    makeopp=0;
    f1=0;
    no_of_players=3;
    imgflag=1;
    cntflag=0;
    for(i=0; i<100; i++)
    {
        mbx[i]=0;
        mby[i]=0;
    }
}
void callOpponent()
{
    //change motion of opponent
    for(i=0; i< no_of_players; i++)
    {
        oppx[i] -=dx[i];
        oppy[i] +=dy[i];



        if(oppx[i] <-100)
        {
            oppx[i]=1400;
        }
        if(oppy[i] > screen_height-150 || oppy[i] < 150)
        {
            dy[i] = -dy[i];
        }

    }
}
void opponentfire()
{
    //opponent fires after 50 score ---f1==1
    if(f1==1)
    {
        //for(i=0; i< no_of_players; i++){
        oppbulletx[makeopp]=oppx[0] ;
        oppbullety[makeopp]=oppy[0];
        makeopp++;

        if(makeopp>99)
        {
            makeopp=0;
        }
    }
}
void makeoppbullet()
{
    //draws bullets on scrn
    int j;
    if(f1 ==1 )
    {
        for(j=0; j<makeopp; j++)
        {
            //iFilledRectangle(oppbulletx[j],oppbullety[j],35,7);
            drawTexture(oppbulletx[j],oppbullety[j],opponent);
            oppbulletx[j]=oppbulletx[j]-2;


            if(oppbulletx[j]<0)
            {
                continue;
            }
            if( (oppbulletx[j]>x && oppbulletx[j]<x+h+w) && (oppbullety[j]>y && oppbullety[j]<y+h+20))
            {
                //guli lagle health komai
                blastimg_player(j);
                health--;
                if(health==0)
                {
                    // GAME OVER
                    gameovrsnd();
                    initialise();
                    f=2;
                }

            }

        }

    }

}


void healthbar()
{
    iSetColor(230, 230, 230);
    iText( 5 ,screen_height-60, "HEALTH :", GLUT_BITMAP_HELVETICA_18);
    iSetColor(900, 0, 0);
    iFilledRectangle(90,screen_height-60,200,20);
    iSetColor(20, 200, 0);
    iFilledRectangle(90,screen_height-60,health,20);

}

void highscore()
{
    FILE * fp;
    int i=0,j=0,temp;

    /* fp = fopen("Gamescore.txt", "r");
     if (fp == NULL)
     {
         //printf("File doesn't exists!\n");
         exit(1);
     }


     if(currHigh_score> prevHigh_score[4])
     {
         fp = fopen("Gamescore.txt", "w"); // to open file in write mode
         if (fp == NULL)
         {
             //printf("File doesn't exists!\n");
             exit(1);
         }

         prevHigh_score[4]=currHigh_score;

         for(j=0; j<5; j++)
         {
             maxx=prevHigh_score[j];
             for(i=j+1; i<5; i++)
             {

                 if(maxx<=prevHigh_score[i])
                 {
                     maxx=prevHigh_score[i];
                     indx=i;
                 }
             }
             temp=prevHigh_score[j];
             prevHigh_score[j]=prevHigh_score[indx];
             prevHigh_score[indx]=temp;
         }
         for(i=0; i<5; i++)
         {
             fprintf(fp,"%d ",prevHigh_score[i]);
             printf("SCORE OVERRIDE\t%d\n",prevHigh_score[i]);

         }


         fclose(fp);
     }
     printf("File successfully opened\n");
    */

    //make highscore 0
/*
    int ab[5]={};
    fp = fopen("gamescore", "wb");
    if (fp == NULL) {
        printf("File doesn't exists!\n");
        exit(1);
    }


    if ( fwrite(ab, sizeof(ab), 1, fp) != 1) {    //   if ( fwrite(a, sizeof(int), N, fp) != N ) will work too
        printf("Write Error\n");
        exit(1);
    }
    fclose(fp);

*/


//file highscore set kore binary te

    fp = fopen("gamescore", "rb");
    if (fp == NULL)
    {
        printf("File doesn't exists!\n");
        exit(1);
    }

    if ( fread(prevHigh_score , sizeof(prevHigh_score), 1, fp) != 1)
    {
        printf("Read Error\n");
        exit(1);
    }
    fclose(fp);

//    for (i = 0; i < 5; i++) {
//        printf("%d ", prevHigh_score[i]);
//    }
//    printf("\n");
    if(currHigh_score>prevHigh_score[4])
    {

        prevHigh_score[4]=currHigh_score;

        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
            if(prevHigh_score[i]>prevHigh_score[j])
            {
                temp=prevHigh_score[j];
                prevHigh_score[j]=prevHigh_score[i];
                prevHigh_score[i]=temp;
            }
            }
        }




        fp = fopen("gamescore", "wb");
        if (fp == NULL)
        {
            printf("File doesn't exists!\n");
            exit(1);
        }

        if ( fwrite(prevHigh_score, sizeof(prevHigh_score), 1, fp) != 1)      //   if ( fwrite(a, sizeof(int), N, fp) != N ) will work too
        {
            printf("Write Error\n");
            exit(1);
        }
        fclose(fp);
//    for(i=0; i<5; i++)
//        {
////            fprintf(fp,"%d ",prevHigh_score[i]);
//            printf("SCORE OVERRIDE\t%d\n",prevHigh_score[i]);
////
//        }

    }


}
void makebullets()
{
    //amar guli banai screen e
    int j,i,n;
    iSetColor(255,90,90);

    for(j=0; j<make; j++)
    {
        //iFilledRectangle(mbx[j],mby[j],35,7);
        drawTexture(mbx[j],mby[j],bullet);
        mbx[j]++;

        for(i=0; i<no_of_players; i++)
        {
            if(mbx[j]>1350)
            {

                break;
            }
            if( (mbx[j]>oppx[i]-w && mbx[j]<oppx[i]+h) && (mby[j]>oppy[i] && mby[j]<oppy[i]+h+20))
            {
                if(imgflag==0)
                {
                    blastimag(j);
                }
                // guli lagle explosion..... opponent morbe
                if(i==1)
                {
                    // blastimag(j);
                    oppx[i] =1450;
                    mbx[j]=1400;

                }
                else if(i==2)
                {
                    // blastimag(j);
                    oppx[i]=1550;
                    mbx[j]=1400;

                }
                else if(i==3)
                {
                    // blastimag(j);
                    oppx[i]=1370;
                    mbx[j]=1400;
                }
                else if(i==4)
                {
                    //blastimag(j);
                    oppx[i]=1420;
                    mbx[j]=1400;
                }
                else
                {
                    // blastimag(j);
                    oppx[i] =1400;
                    mbx[j]=1400;
                }
                if(imgflag==0)
                {
                    //guli lagle score barbe
                    blastimag(j);
                    curr_score++;
                    break;
                }
            }



        }

    }
}
void drawhighscore()
{
    // screen e dekhai highscore...
    int i,c=0;
    drawTexture(0,-20,Mars);

    iSetColor( 0,277, 115);
    iText( p-350 ,screen_height/2+160,"HIGH SCORES ARE :" , GLUT_BITMAP_HELVETICA_18);
    for(i=0; i<5; i++)
    {
        sprintf(ch1,"%d",prevHigh_score[i] );
        iText( p-300 ,screen_height/2+107-c, ch1 , GLUT_BITMAP_HELVETICA_18);

        c+=40;

    }
    drawTexture(p-300-35 ,screen_height/2+100,h1);
    drawTexture(p-300-35 ,screen_height/2+100-40,h2);
    drawTexture(p-300-35 ,screen_height/2+100-80,h3);
    drawTexture(p-300-35 ,screen_height/2+100-120,h4);
    drawTexture(p-300-35 ,screen_height/2+100-160,h5);


    drawTexture(-20,0,menuborder);
    iText(60,80,"MAIN MENU" , GLUT_BITMAP_HELVETICA_18);
}

void startlevel()
{
    //akhom 1st e ja dekha jabe
    drawTexture(-210,-350,start);
    overrect();
    iSetColor(900, 0, 0);

    iText( p ,screen_height/2, "NEW GAME", GLUT_BITMAP_HELVETICA_18);
    iText( p ,screen_height/2-30, "RESUME GAME", GLUT_BITMAP_HELVETICA_18);
    iText( p ,screen_height/2-60, "HIGHSCORE", GLUT_BITMAP_HELVETICA_18);
    iText( p ,screen_height/2-90 , "CONTROLS", GLUT_BITMAP_HELVETICA_18);
    iText( p ,screen_height/2-120 , "EXIT GAME", GLUT_BITMAP_HELVETICA_18);
    iSetColor(20, 200, 0);
    iText(30, 30, "Copyright Awsaf.Mahmud & co. please do not use this code without permission");
    iSetColor(0, 0, 0);

}


void imgmove()
{
    int x=600,  y=360 ;

    if(g== -600)
    {
        g=0;//loops arounf image;
    }
    drawTexture(g,0,character);
    drawTexture(x+g,0,character);
    drawTexture(g,y,character);
    drawTexture(x+g,y,character);
    drawTexture(x+x+g,0,character);
    drawTexture(x+x+g,y,character);
    drawTexture(x+x+x+g,0,character);
    drawTexture(x+x+x+g,y,character);

    g-- ;

}
void intro()
{
    int box_x=400, box_y=100,hbox=450,wbox=600;

    iSetColor(900, 0, 0);
    iRectangle(box_x,box_y,wbox,hbox);
    iSetColor( 0,277, 115);
    iText( box_x+wbox/2-100,box_y+hbox/2+30, "Allien invaders have arrived", GLUT_BITMAP_HELVETICA_18);
    iText( box_x+wbox/2-120,box_y+hbox/2, "You are humanity's last stand", GLUT_BITMAP_HELVETICA_18);
    iText( box_x+wbox/2-100,box_y+hbox/2-30, "Fight for your survival", GLUT_BITMAP_HELVETICA_18);
    iText( box_x+wbox/2-100,box_y+hbox/2-170, "Right click to fire", GLUT_BITMAP_HELVETICA_18);
    iText( box_x+wbox/2-150,box_y+hbox/2-200, "Press: w-up; s-down; d-right; a-left", GLUT_BITMAP_HELVETICA_18);

    iSetColor(20, 200, 0);
    iText(30, 20, "Copyright Awsaf.Mahmud & co. please do not use this code without permission");
    iSetColor(0, 0, 0);

}
void controls()
{
    drawTexture(-200,0,Earth);
    drawTexture(screen_width/2+150,screen_height/2-50,Mouse);

    int box_x=400, box_y=100,hbox=450,wbox=600;

    iSetColor( 0,277, 115);
    iText( box_x+wbox/2-100,box_y+hbox/2+280, "Allien invaders are coming!", GLUT_BITMAP_HELVETICA_18);
    iText( box_x+wbox/2-120,box_y+hbox/2+250 ,"You are humanity's last stand", GLUT_BITMAP_HELVETICA_18);
    iText( box_x+wbox/2-170,box_y+hbox/2-30+250, "Your are the pilot of a next generation spacecraft", GLUT_BITMAP_HELVETICA_18);
    iText( box_x+wbox/2-170,box_y+hbox/2-60+250, "Use the high tech laser beams onboard your ship", GLUT_BITMAP_HELVETICA_18);
    iText( box_x+wbox/2-90,box_y+hbox/2-90+250, "to kill all allien ships.", GLUT_BITMAP_HELVETICA_18);

    iText( box_x+wbox/2-100,box_y+hbox/2+30, "Forward:         D", GLUT_BITMAP_HELVETICA_18);
    iText( box_x+wbox/2-100,box_y+hbox/2,    "Backward:      A", GLUT_BITMAP_HELVETICA_18);
    iText( box_x+wbox/2-100,box_y+hbox/2-30, "UP:                 W", GLUT_BITMAP_HELVETICA_18);
    iText( box_x+wbox/2-100,box_y+hbox/2-60, "Down:             S", GLUT_BITMAP_HELVETICA_18);

    drawTexture( box_x+wbox/2-90,box_y+hbox/2-200,spacebar);
    iText( box_x+wbox/2,box_y+hbox/2-240,"Shoot", GLUT_BITMAP_HELVETICA_18);

    //drawTexture( screen_width/2+230,box_y+hbox/2-200,motion);
    //iText( box_x+wbox/2+210,box_y+hbox/2-240,"MOTION", GLUT_BITMAP_HELVETICA_18);

    iSetColor(278,116,0);
    iText( box_x+wbox/2+50,box_y+hbox/2-110,"OR", GLUT_BITMAP_HELVETICA_18);

    iSetColor(900, 0, 0);

    iText( box_x+wbox-150,box_y+hbox/2, "SHOOT", GLUT_BITMAP_9_BY_15);
    iText( box_x+wbox+220,box_y+hbox/2-20, "PAUSE GAME",GLUT_BITMAP_9_BY_15);

//    iSetColor(20, 200, 0);
//    iText(30, 30, "Copyright Awsaf.Mahmud & co. please do not use this code without permission");
//    iSetColor(0, 0, 0);
    iSetColor( 0,277, 115);
    drawTexture(-20,0,menuborder);
    iText(60,80,"MAIN MENU" , GLUT_BITMAP_HELVETICA_18);

}

void newgame()
{
    imgmove();
    iResumeTimer(t1);
    iResumeTimer(t3);
    iResumeTimer(t2);
    iResumeTimer(t4);
    healthbar();
    gametimer();

    //distfromopp();
    makebullets();
    makeoppbullet();
    if(cntflag==0)
    {
        intro();
    }

    iSetColor(0, 105, 294);

    drawTexture(x,y,ship);


    score();
    drawscore();

    if(imgflag==0)
    {

        for(i=0; i< no_of_players; i++)
        {
            iSetColor(255, 0, 0);
            if(i==1)
            {
                iSetColor(278,116,0);
            }
            if(i==2)
            {
                iSetColor(0,210,204);
            }
            if(i==3)
            {
                iSetColor(100,5,241);
            }
            iFilledRectangle(oppx[i],oppy[i],h,w);
            iFilledRectangle(oppx[i]+h,oppy[i]-7,h-10,7);
            iFilledRectangle(oppx[i]+h,oppy[i]+w,h-10,7);
            iFilledRectangle(oppx[i]-h+15,oppy[i],h-15,7);
            iFilledRectangle(oppx[i]-h+15,oppy[i]+w-7,h-15,7);
            iFilledRectangle(oppx[i]-h-2,oppy[i]+7,w-10,w-14);

        }
    }

    iSetColor(20, 200, 0);
    iText(40, 40, "Right click to pause game");

}
void distfromopp()
{
    int i;
    for(i=0; i<no_of_players; i++)
    {

        distance[i]=sqrt( ((oppx[i]-x)*(oppx[i]-x)) + ((oppy[i]-y)*(oppy[i]-y)) );

        //printf("%d\n\n",distance[i]);
        if(imgflag==0){
        if(distance[i]<100)
        {
            health--;
            if(health==0)
            {
                // GAME OVER
                gameovrsnd();
                initialise();
                f=2;
            }

        }
        }
    }
}
void gameover()
{
    //imgmove();
    drawTexture(screen_width/2-a-100 ,screen_height/2-200,gameovr);

    iSetColor( 0,277, 115);
    iText( p ,screen_height/2-170 , "EXIT GAME", GLUT_BITMAP_HELVETICA_18);
    iSetColor( 0,277, 115);
    drawTexture(-20,0,menuborder);
    iText(60,80,"MAIN MENU" , GLUT_BITMAP_HELVETICA_18);
    if(f==0)
    {
        startlevel();
    }
}

void drawscore()
{
    int scr=2;
    int s[5]= {};
    int i,c=0,sx=screen_width-200,sy=screen_height-60,m;
    iSetColor(0,0,255);
    iText( screen_width-350,screen_height-60, "SCORE:", GLUT_BITMAP_HELVETICA_18);

    if(curr_score<100)
    {
        s[0]=curr_score/10;
        s[1]=curr_score%10;
    }
    else if(curr_score<1000)
    {
        s[0]=curr_score/100;
        s[1]=curr_score%100;
        s[1]=s[1]/10;
        s[2]=curr_score%10;
        sx-=25;
    }
    else if(curr_score<10000)
    {
        s[0]=curr_score/1000;
        s[1]=curr_score%1000;
        s[1]=s[1]/100;
        s[2]=curr_score/10;
        s[2]=s[2]%10;
        s[3]=curr_score%10;
        sx-=50;
    }


    m=17; //adjusts the rectangles of 7 segment

    if(curr_score>99)
    {
        scr=3;
    }
    if(curr_score>999)
    {
        scr=4;
    }
    if(curr_score>9999)
    {
        scr=5;
    }
    for(i=0; i<scr; i++)
    {
        int sw[7]= {2,2,2,2,2,2,2};
        int sh=15;
        iSetColor( 0,277, 115);
        if(s[i]==0)
        {
            sw[6]=0;
        }
        else if(s[i]==1)
        {

            sw[0]=0;
            sw[1]=0;
            sw[2]=0;
            sw[5]=0;
            sw[6]=0;
        }
        else if(s[i]==2)
        {
            sw[2]=0;
            sw[3]=0;
        }
        else if(s[i]==3)
        {
            sw[1]=0;
            sw[2]=0;
        }
        else if(s[i]==4)
        {
            sw[0]=0;
            sw[1]=0;
            sw[5]=0;
        }
        else if(s[i]==5)
        {
            sw[4]=0;
            sw[1]=0;
        }
        else if(s[i]==6)
        {
            sw[4]=0;
        }
        else if(s[i]==7)
        {
            sw[6]=0;
            sw[5]=0;
            sw[2]=0;
            sw[1]=0;
        }
        else if(s[i]==9)
        {
            sw[1]=0;
        }

        iFilledRectangle(sx +c  , sy    ,sw[1],sh);//rec 1
        iFilledRectangle(sx +c  , sy+m  ,sw[2],sh);//rec 2
        iFilledRectangle(sx+m+c , sy    ,sw[3],sh);//rec3
        iFilledRectangle(sx+m+c ,sy+m   ,sw[4],sh);//rec4
        iFilledRectangle(sx+2+c ,sy-2   ,sh,sw[5]);//rec5
        iFilledRectangle(sx+2+c ,sy+15  ,sh,sw[6]);//rec6
        iFilledRectangle(sx+2+c ,sy+m+15,sh,sw[0]);//rec7

        c+= 25;

    }
}
void settime()
{

    tim[2]--;
    if(tim[2]==0)
    {
        tim[2]=100;
        tim[1]--;
    }
    if(tim[1]==0)
    {
        tim[1]=60;
        tim[0]--;
    }
    if(tim[0]==-1 && tim[1]==60 )
    {
        // GAME OVER
        initialise();
        f=2;
    }

    if(tim[1]==56 && tim[0]==1) // 4 secs for intro box
    {
        // initialise opponents
        imgflag=0;
        cntflag=1;
        oppx[0]=1500;
        oppx[1]=1400;
        oppx[2]=1650;
        oppx[3]=1350;
        oppx[4]=1450;
        oppx[5]=1500;
    }



}
void gametimer()
{
    //draws timer
    int s[6]= {},i;
    int c=0, cx= screen_width/2, cy=screen_height-60;

    s[0]=tim[0]/10;
    s[1]=tim[0]%10;
    s[2]=tim[1]/10;
    s[3]=tim[1]%10;
    s[4]=tim[2]/10;
    s[5]=tim[2]%10;


    for(i=0; i<6; i++)
    {


        if(s[i]==0)
        {
            iText(cx+c,cy,"0",GLUT_BITMAP_HELVETICA_18);
        }
        if(s[i]==1)
        {
            iText(cx+c,cy,"1",GLUT_BITMAP_HELVETICA_18);
        }
        if(s[i]==2)
        {
            iText(cx+c,cy,"2",GLUT_BITMAP_HELVETICA_18);
        }
        if(s[i]==3)
        {
            iText(cx+c,cy,"3",GLUT_BITMAP_HELVETICA_18);
        }
        if(s[i]==4)
        {
            iText(cx+c,cy,"4",GLUT_BITMAP_HELVETICA_18);
        }
        if(s[i]==5)
        {
            iText(cx+c,cy,"5",GLUT_BITMAP_HELVETICA_18);
        }
        if(s[i]==6)
        {
            iText(cx+c,cy,"6",GLUT_BITMAP_HELVETICA_18);
        }
        if(s[i]==7)
        {
            iText(cx+c,cy,"7",GLUT_BITMAP_HELVETICA_18);
        }
        if(s[i]==8)
        {
            iText(cx+c,cy,"8",GLUT_BITMAP_HELVETICA_18);
        }
        if(s[i]==9)
        {
            iText(cx+c,cy,"9",GLUT_BITMAP_HELVETICA_18);
        }
        if((i+1)%2==0 && (i+1)!=6)
        {
            iText(cx+c,cy+2," : ");
            c+=4;
        }

        c+= 13;

    }

}

void score()
{
    // adjusts level according to score
    if(x>screen_width)
    {
        curr_score+=5;
        x=50;
    }
    if(curr_score>50 && curr_score<=100)
    {
        f1=1;//opponent fire starts

    }
    else if(curr_score>100 && curr_score<=200)
    {
        no_of_players=4;
        dx[3]=4;
    }
    else if(curr_score>200 && curr_score<=300)
    {
        dx[0]=3;
        dx[2]=3;
        no_of_players=5;
    }
    else if(curr_score>300 )
    {
        dx[0]=4;
        dx[1]=6;

    }
}
void iDraw()
{

    iClear();

    if(f==0) //opening page
    {
        startlevel();
    }
    else if(f==1) //game
    {
        newgame();
        healthbar();
    }
    else if(f==2) // gameover
    {
        gameover();
    }
    else if(f==3) // shows highscore
    {
        drawhighscore();
    }
    else if(f==4) //controls menu
    {
        controls();
    }

}
void overrect()
{
    //shows rectangle on mouse hover
    iSetColor(255,90,90);
    int hm=23, wm=150;
    if(rec==1)
    {
        iRectangle(screen_width/2-a/2-10,screen_height/2-5,wm,hm);
    }
    else if(rec==2)
    {
        iRectangle(screen_width/2- a/2-10,screen_height/2-35,wm,hm);
    }
    else if(rec==3)
    {
        iRectangle(screen_width/2- a/2-10,screen_height/2-65,wm,hm);
    }
    else if(rec==4)
    {
        iRectangle(screen_width/2- a/2-10,screen_height/2-95,wm,hm);
    }
    else if(rec==5)
    {
        iRectangle(screen_width/2- a/2-10,screen_height/2-125,wm,hm);
    }
}

void iMouseOver(int mx,int my)
{
    if(f==0)
    {
        if( mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2 &&my<screen_height/2+20 )
        {
            //startsnew game
            rec=1;

        }
        else if(mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2-30 &&my<screen_height/2-10)
        {
            rec=2;
        }
        else if(mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2-60 &&my<screen_height/2-40)
        {
            rec=3;
        }
        else if(mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2-90 &&my<screen_height/2-70)
        {

            rec=4;
        }
        else if(mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2-120 &&my<screen_height/2-100)
        {
            //exit game
            rec=5;
        }
    }
    else if(f==0 ||f==2)
    {
        if(mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2-120 &&my<screen_height/2-100)
        {
            rec=5;
        }
    }
}


void shoot()
{
    // bulflag changes after 50 ms.. to avoid continuous fire
    if(bulflag==1){

    mbx[make]=x+298 ;
    mby[make]=y+w-20;
    make++;
    //printf("bullmade %d\n",make);
    if(make>98)
    {
        make=0;
    }
  }
}
void up()
{
    y+=9;
    if(y>= screen_height-120)
    {
        y-=9;
    }
}

void down()
{
    y-=9;
    if(y<= 90)
    {
        y+=9;
    }
}
void right()
{
    x+=5;
}
void left()
{
    x-=5;
    if(x<4)
    {
        x+=5;
    }
}


void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //printf("x = %d, y= %d\n",mx,my);
        if(f==0)
        {
            if( mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2 &&my<screen_height/2+20 )
            {
                //startsnew game

                initialise();
                f=1;
            }
            else if(mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2-30 &&my<screen_height/2-10)
            {
                iResumeTimer(t1);
                iResumeTimer(t3);
                iResumeTimer(t2);
                iResumeTimer(t4);
                f=1;//resume game;
            }
            else if(mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2-60 &&my<screen_height/2-40)
            {
                //highscore();
                f=3; // shows highscore
            }
            else if(mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2-90 &&my<screen_height/2-70)
            {

                f=4; // controls
            }
            else if(mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2-120 &&my<screen_height/2-100)
            {
                //exit game
                //highscore();
                exit(0);
            }
        }
        if(f==2)
        {
            if(mx<screen_width/2+a && mx>screen_width/2- a && my>screen_height/2-170 &&my<screen_height/2-150)
            {
                //exit game
                //highscore();
                exit(0);
            }
        }
        if(f==2 ||f==3||f==4)
        {
            if(mx<200&& mx>40 && my>40 &&my<150)
            {
                mainsnd();
               f=0;
            }
        }
        mbx[make]=x+298 ;
        mby[make]=y+w-20;
        make++;
        if(make>98)
        {
            make=0;
        }

    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        if(f==1){
        iPauseTimer(t1);
        iPauseTimer(t3);
        iPauseTimer(t2);
        iPauseTimer(t4);
        currHigh_score=curr_score;
        highscore();
        f=0;
        }

    }
}
void iKeyboard(unsigned char key)
{
    if (key == 'z')
    {
        x-=4;
        y-=4;
    }
    if(key== 'w')
    {
        upMoveFlag=1;
    }
    if(key== 's')
    {
        downMoveFlag=1;
    }
    if(key==' ')
    {
        shotFlag=1;
    }
    if(key== 'a')
    {
        leftMoveFlag=1;
    }

    if(key== 'd')
    {
        rightMoveFlag=1;
    }

    if(key== 'x')
    {
        x+=4;
        y-=4;
    }
    if(key== 'q')
    {
        x-=4;
        y+=4;
    }
    if(key== 'e')
    {
        x+=4;
        y+=4;
    }
    if(shotFlag==1)shoot();
    if(upMoveFlag==1)up();
    if(downMoveFlag==1)down();
    if(rightMoveFlag==1)right();
    if(leftMoveFlag==1)left();
    //place your codes for other keys here
}


void iKeyUpboard(unsigned char key)
{
    if(key==' ')
    {
        shotFlag=0;
    }
    if(key=='w')
    {
        upMoveFlag=0;
    }
    if(key=='s')
    {
        downMoveFlag=0;
    }
    if(key== 'a')
    {
        leftMoveFlag=0;
    }

    if(key== 'd')
    {
        rightMoveFlag=0;
    }

}

void iSpecialUpKeyboard(unsigned char key)
{
/*
    if(key== GLUT_KEY_DOWN )
    {
        downMoveFlag=0;
    }
    if(key== GLUT_KEY_UP )
    {
        upMoveFlag=0;
    }
    if(key== GLUT_KEY_LEFT )
    {
        rightMoveFlag=0;
    }
    if(key== GLUT_KEY_RIGHT )
    {
        leftMoveFlag=0;
    }
    */


}

void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_END)
    {
        currHigh_score=curr_score;
        highscore();
        exit(0);
    }
    /*
    if(key== GLUT_KEY_DOWN )
    {
        downMoveFlag=1;
    }
    if(key== GLUT_KEY_UP )
    {
        upMoveFlag=1;
    }
    if(key== GLUT_KEY_LEFT )
    {
        leftMoveFlag=1;
    }
    if(key== GLUT_KEY_RIGHT )
    {
        rightMoveFlag=1;
    }
    if(upMoveFlag==1)up();
    if(downMoveFlag==1)down();
    if(rightMoveFlag==1)right();
    if(leftMoveFlag==1)left();
    */

}

void blastimag(int i)
{
    drawTexture(mbx[i],mby[i],blastimg);
}
void blastimg_player(int i)
{
    if(f1==1)
    {
        drawTexture(oppbulletx[i],oppbullety[i],blastimg);
    }

}

void changeflag()
{
    bulflag=bulflag*-1;
}
void mainsnd()
{
     PlaySound("main_music.wav",NULL,SND_ASYNC|SND_LOOP);
}
void gameovrsnd()
{
     PlaySound("bulletfire.wav",NULL,SND_ASYNC);
}

int main()
{

    t2=iSetTimer(5, callOpponent);
    t1=iSetTimer(1, settime);
    t3=iSetTimer(25,distfromopp );
    iSetTimer(50,changeflag );
    t4=iSetTimer(1000,opponentfire);


    PlaySound("main_music.wav",NULL,SND_ASYNC|SND_LOOP);
    initialise();
    highscore();
    iInitialize(screen_width,screen_height, "Space_invasion");
    return 0;

}
