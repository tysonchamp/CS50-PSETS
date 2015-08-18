/**
 * breakout.c
 * 
 * Computer Science 50
 * Prblem Set 3
 */

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // initial velocity
    double xvelocity = drand48();
    double yvelocity = 2.0;
    
    updateScoreboard(window, label, points);

    // wait for mouse clicked
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // bounce off top edge of window
        if (getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xvelocity = -xvelocity;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }

        // detect collision
        if (detectCollision(window,ball) != NULL)
        {           
            GObject collision = detectCollision(window, ball);
            
            if (strcmp(getType(collision), "GRect") == 0)
            {
                // if ball collided with any bricks remove
                if (collision != paddle)
                {
                    removeGWindow(window, collision);
                    points++;
                    bricks--;
                    updateScoreboard(window, label, points);
                    yvelocity = -yvelocity;
                }
                
                // if ball collided with paddle bounce 
                else if (collision == paddle)
                {
                    yvelocity = -yvelocity;
                }           
            }
        } 

        // restart ball if hit bottom edge of window
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            --lives;
            if (lives <= 0)
            {
                continue;
            }
            waitForClick();
            removeGWindow(window, ball);
            ball = initBall(window);
        }

        // start moving the ball
        move(ball, xvelocity, yvelocity);
        pause(10);

        // wait for mouse event
        GEvent start_paddle = getNextEvent(MOUSE_EVENT);
            
        if (start_paddle != NULL)
        {
            // move paddle with the mouse
            if (getEventType(start_paddle) == MOUSE_MOVED)
            {            
                // ensure paddle follows top cursor
                double x = getX(start_paddle) - getWidth(paddle) / 2;
                if (x >= 0 && x <= WIDTH - 60)
                {
                    setLocation(paddle, x, HEIGHT - 60);
                }
            }
        }        
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // Declaration of width and hight
    int x = 2, y = 50;

    // Initialize Bricks
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            GRect Bricks = newGRect(x, y, WIDTH / 10 - 5, 10);
            setFilled(Bricks, true);
            
            // set different colors to the bricks in each row
            if (i == 0)
            {
                setColor(Bricks, "RED");
            }
            else if (i == 1)
            {
                setColor(Bricks, "ORANGE");
            }
            else if (i == 2)
            {
                setColor(Bricks, "YELLOW");
            }
            else if (i == 3)
            {
                setColor(Bricks, "GREEN");
            }
            else if (i == 4)
            {
                setColor(Bricks, "BLUE");
            }
            
            add(window, Bricks);
            x = x + 40;
            if (j == COLS - 1)
            {
                // reset x and y
                x = 2;
                y = y + 15;
            }
        }
    }

}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{   
    // Initializing Ball
    GOval ball = newGOval((WIDTH / 2) - RADIUS, HEIGHT / 2, RADIUS * 2, RADIUS * 2);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Initializing the paddle
    GRect paddle = newGRect(WIDTH / 2 - .5 * 60, HEIGHT - 60, 60, 10);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // Initializing Score Board
    GLabel scoreboard = newGLabel("");
    setFont(scoreboard, "Ubuntu-50");
    add(window, scoreboard);
    
    return scoreboard;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
