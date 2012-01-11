#include "mex.h"
#include <string.h>
#include "../cppsrc/Joysticks.cpp"
#include "../cppsrc/Joystick.cpp"

#define NUMBER_OF_STRUCTS 1

const char *field_names[] = {"name", "axes", "buttons"};
#define NAME_FIELD 0
#define AXES_FIELD 1
#define BUTTONS_FIELD 2
#define NUMBER_OF_FIELDS (sizeof(field_names)/sizeof(*field_names))

int firstRun = 1;
int joyIdx;

Joysticks * jss = NULL;

static void cleanup(void){
    if (jss != NULL){
        delete jss;
        jss = NULL;
    }
}

void
printListOfJoysticks(void){
    mexPrintf("Connected joysticks:\n");
    for (int k=0; k<SDL_NumJoysticks(); k++){
        if (SDL_JoystickOpened(k))
            mexPrintf("%d: %s (opened)\n", k, SDL_JoystickName(k));
        else
            mexPrintf("%d: %s\n", k, SDL_JoystickName(k));
    }
}

void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    mwSize dims[1] = {1};
    
    if (firstRun){
        mexAtExit(cleanup);
        jss = new Joysticks();
        jss->grabStates();
        firstRun = 0;
    }

    // no inputs or outputs: print list of joysticks
    if (nrhs == 0 && nlhs == 0){
        printListOfJoysticks();
        return;
    }

    // one input: populate joystick
    if (nrhs == 1 && nlhs < 2){
        jss->grabStates();

        // get index();
        int jsIdx = round(mxGetPr(prhs[0])[0]);
        if (jsIdx < 0)
            mexErrMsgTxt("The joystick index provided is negative");
        if (jsIdx >= jss->numJs()){
            printListOfJoysticks();
            mexErrMsgTxt("The joystick index provided is too high");
        }

        Joystick & js = jss->get(jsIdx);
        /* Create a 1-by-1 array of structs. */ 
        plhs[0] = mxCreateStructArray(1, dims, NUMBER_OF_FIELDS, field_names);

        // set name
        mxSetFieldByNumber(plhs[0], 0, NAME_FIELD, mxCreateString(js.getName().c_str()));
    
        // set axes
        mxArray *axesArray;
        axesArray = mxCreateDoubleMatrix(js.getNumAxes(),1,mxREAL);
        for (int k = 0; k < js.getNumAxes(); k++)
            mxGetPr(axesArray)[k] = js.getAxis(k);
        mxSetFieldByNumber(plhs[0], 0, AXES_FIELD, axesArray);

        // set buttons
        mxArray *buttonsArray;
        buttonsArray = mxCreateDoubleMatrix(js.getNumButtons(),1,mxREAL);
        for (int k = 0; k < js.getNumButtons(); k++)
            mxGetPr(buttonsArray)[k] = js.getButton(k);
        mxSetFieldByNumber(plhs[0], 0, BUTTONS_FIELD, buttonsArray);

        //        cout << js;
        return;
    }

    // improper arguments
    mexErrMsgTxt("Improper arguments. Either call with no inputs and no outputs (print all connected joysticks), or call with one input (joystick index) to get joystick struct");
}
