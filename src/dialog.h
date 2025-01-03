#ifndef SRC_DIALOG_H_
#define SRC_DIALOG_H_

#include <object.h>
#include <vector>
#include <controller.h>
#include <string>
#include <utils.h>



class GameWindow;

typedef enum DialogTypes
{
    LEVEL_CUSTCENE,
    LEVEL_PAUSE

} DialogTypes_t;

class Dialog: public Object 
{
    public:

    Dialog();
    Dialog(DialogTypes_t type, Vec2D pos, int width, int height);
    Dialog(
        DialogTypes_t type, 
        Vec2D pos, 
        int width, 
        int height,
        CutsceneLevelStates_t state,
        std::string message);
    
    virtual void draw(GameWindow &window) override;

    void update(uint32_t delta_type);
    void addExtraBoxes(Rectangle & rect);
    Controller &getController(){return mDialogControl;}
    void setController(Controller control) {mDialogControl = control;}

    inline void setOn(bool on){mOn=on;}
    inline bool getOn(){return mOn;}

    void setLevelState(CutsceneLevelStates_t state){mState = state;}
    CutsceneLevelStates_t getDialogState(){return mState;}

    DialogTypes_t getType(){return mType;}



    private:
        DialogTypes_t mType;
        std::vector<Rectangle> mExtraBoxes;
        Controller mDialogControl;
        bool mOn;
        std::string mMessage;
        CutsceneLevelStates_t mState;
     

        
     

};


#endif /* SRC_DIALOG_H_ */