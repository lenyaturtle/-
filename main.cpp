//========================================================================
//
#include "TXLib.h"
struct Spaceman
{
   int x;
   int y;
   HDC image_left;
   HDC image_right;
   HDC image;
   int w_image;
   int h_image;
   int vx;
   int vy;
};
void drawSpaceman(Spaceman spaceman)
{
    txTransparentBlt (txDC(), spaceman.x,  spaceman.y,  spaceman.w_image, spaceman.h_image, spaceman.image, 0, 0, TX_BLACK);
}

struct Bullet
{
    int x;
    int y;
    bool visible;
    int vx;
    int vy;

    void draw()
    {
       txSetColor (TX_WHITE);
       txSetFillColor (TX_BLACK);
       txCircle(x, y, 5);
    }
};

int main()
{
txCreateWindow (800, 600);

    HDC background = txLoadImage ("kartinka/fon.bmp");
    int xFon = -1800;
    int yFon = -1200;
    int y0Spaceman = 550;


    HDC spaceshipeUp = txLoadImage ("kartinka/spaceshipe_Up.bmp");
    HDC spaceshipeDown = txLoadImage ("kartinka/spaceshipe_Down.bmp");
    HDC spaceshipeLeft = txLoadImage ("kartinka/spaceshipe_Left.bmp");
    HDC spaceshipeRight = txLoadImage ("kartinka/spaceshipe_Right.bmp");

    HDC spaceshipe = spaceshipeUp;
    int xSpaceShip = 600;
    int ySpaceShip = 300;

   Spaceman spaceman = {400, 300,  txLoadImage ("kartinka/spaceman1Left.bmp"),
    txLoadImage ("kartinka/spaceman1Right.bmp"), spaceman.image_right, 150, 212};


    Spaceman spaceman2 = {100, 100, txLoadImage ("kartinka/spaceman2Left.bmp"),
    txLoadImage ("kartinka/spaceman2Right.bmp"), spaceman2.image_right, 147, 150, 10};

    Bullet bul[100];
    int n = 100;
    for (int i=0; i<n; i++)
    {
        bul [i]={0,0,false,0,10};
    }



    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin();
        txSetColor (TX_WHITE);
        txSetFillColor (TX_WHITE);
        txClear();

        txBitBlt (txDC(), xFon, yFon, 3600, 2400, background);

        drawSpaceman(spaceman);
        drawSpaceman(spaceman2);


        if(spaceshipe == spaceshipeUp || spaceshipe == spaceshipeDown)
            txTransparentBlt (txDC(), xSpaceShip, ySpaceShip, 131, 200, spaceshipe, 0, 0, TX_BLACK);
        else if(spaceshipe == spaceshipeLeft || spaceshipe == spaceshipeRight)
            txTransparentBlt (txDC(), xSpaceShip, ySpaceShip, 200, 131, spaceshipe, 0, 0, TX_BLACK);

        if(GetAsyncKeyState ('S'))
        {
            yFon -= 10;
            spaceshipe = spaceshipeDown;
        }
        if(GetAsyncKeyState ('W'))
        {
            yFon += 10;
            spaceshipe = spaceshipeUp;
        }
        if(GetAsyncKeyState ('D'))
        {
            xFon -= 10;
            spaceshipe = spaceshipeRight;
        }
        if(GetAsyncKeyState ('A'))
        {
            xFon += 10;
            spaceshipe = spaceshipeLeft;
        }

        spaceman.y +=20;
        if(spaceman.y > y0Spaceman - 212)
        {
            spaceman.y = y0Spaceman-212;
        }



        if(GetAsyncKeyState (VK_SPACE))
        {
            spaceman.y -= 80;
        }

        if(GetAsyncKeyState (VK_RIGHT))
        {
            spaceman.x += 10;
            spaceman.image = spaceman.image_right;
        }
        if(GetAsyncKeyState (VK_LEFT))
        {
            spaceman.x -= 10;
            spaceman.image = spaceman.image_left;
        }
        if(GetAsyncKeyState (VK_CONTROL))
        {
            for(int i=0;i<n; i++)
            {
                bul[i] = {spaceman.x+10, spaceman.y+70,true,0,10};
                bul[i].visible = true;
            }
        }

        if(bul[0].visible)
        {
            for(int i=0;i<n; i++)
            {
                if(bul[i].visible)
                {
                bul[n-1].draw();
                bul[n-1].y-=bul[n-1].vy;
                }
            }
        }
        spaceman2.x = spaceman2.x + spaceman2.vx;
        if(spaceman2.x > 800 - 147 || spaceman2.x < 0)
        {
            spaceman2.vx = - spaceman2.vx;
            if(spaceman2.vx > 0)
            {
                spaceman2.image = spaceman2.image_right;
            }
            else spaceman2.image = spaceman2.image_left;
        }


        txEnd();
        txSleep(10);

    }

    txDeleteDC (background);
    txDeleteDC (spaceman.image);

txTextCursor (false);
txDisableAutoPause ();
return 0;
}


