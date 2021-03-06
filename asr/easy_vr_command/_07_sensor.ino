 /*
  * This is sensor module that takes care of the sensor mode of the Obedient. The Obedient will start at stop state when at current default state of -1.
  * Then based on what the user speaks to it, it will perform the action and keep performing until there is new command (only for backward and foward).
  * However, the turn will only perform once and the obedient will get back to its previous state.
  * This module will then be loaded into action module as part of the action function in easy_vr_command.
  */
  /**************************************End of module introduction ******************************************************/
 const int FOWARD = 0;
 const int BACKWARD = 1;
 const int STOP = 2;
 const int DEFAULT_STATE = -1;
 
/* The sensor function that will take one parameter of idx indicator and based on the value of idx to determine which function will be called inside itself.
 * The sensor function also call tonePlay(1000, 1000) inside it to annouce that it gets the word from the user.
 * The idx will then determine which movement the Obedient will carry out
 *     if idx = SENSOR_FOWARD, then call foward function, and set current state to 0
 *     if idx = SENSOR_BACKWARD, then call backward function, and set current state to 1
 *     if idx = SENSOR_LEFTTURN, then call turnLeft function, DO NOT set current state when call with LEFTTURN
 *     if idx = SENSOR_RIGHTTURN, then call turnRight function, DO NOT set current state when call with RIGHTTURN
 *     if idx = SENSOR_TURNBACKLEFT, then call turnBackLeft function, DO NOT set currentState when call with TURNBACKLEFT
 *     if idx = SENSOR_TURNBACKRIGHT, then call turnBackRight function, DO NOT set current state when call with TURNBACKRIGHT
 *     if idx = SENSOR_STOP, then call stop function to freeze Obedient, set currentState to 2 
 *     if idx = SENSOR_MAIN, set group back to list of option (GROUP_4)
 * We will use switch structure to recognize each case based on the value of idx.
 * Because we want the Obedient will keep doing what it was doing after being discontinued we will use fowardSecond and backwardSecond instead of default foward and backward
 * The function will return nothing.     
 */ 
void sensor(int idx) {
    int currentState;
    
    tonePlay(1000, 1000);
    switch(idx) {
        case SENSOR_FOWARD:
            obedient.fowardNonStop();
            obedient.setCurrentState(FOWARD);
            break;
        case SENSOR_BACKWARD:
            obedient.backwardNonStop();
            obedient.setCurrentState(BACKWARD);
            break;
        case SENSOR_LEFTTURN:
            obedient.turnLeft();
            break;
        case SENSOR_RIGHTTURN:
            obedient.turnRight();
            break;
        case SENSOR_BACKLEFT:
            obedient.turnBackLeft();
            break;
        case SENSOR_TURNBACKRIGHT:
            obedient.turnBackRight();
            break;
        case SENSOR_STOP:
            obedient.stop();
            obedient.setCurrentState(STOP);
            break;
        case SENSOR_SPEEDUP:
            obedient.speedUp();
            break;
        case SENSOR_SLOWDOWN:
            obedient.slowDown();
            break;
        case SENSOR_MAINMENU:
            group = GROUP_4;
            obedient.reset();         
            break;   
    }
    currentState = obedient.getCurrentState();
    resumeToCurrentState(currentState);    
}

/*
 * resumeToCurrentState.
 * 
 * Function will direct the Obedient back to its current when it hears the command for turnning left or right, or back.
 * @param {integer} current - this will hold the id of the current state and based on it to get the `Obedient` back to
 * its origial states.
 */
void resumeToCurrentState(int current) {
    switch(current) {
        case DEFAULT_STATE:
            obedient.stop();
            break;
        case FOWARD:
            obedient.fowardNonStop();
            break;
        case BACKWARD:
            obedient.backwardNonStop();
            break;
        case STOP:
            obedient.stop();
            break;  
    }
}

