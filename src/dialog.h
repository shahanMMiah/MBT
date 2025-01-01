#ifndef SRC_DIALOG_H_
#define SRC_DIALOG_H_

#include <object.h>

class GameWindow;

typedef enum DialogTypes
{
    LEVEL_CUTSCENE,
    LEVEL_DIALOG,
    LEVEL_PAUSE

} DialogTypes_t;

class Dialog: public Object 
{
    public:

    Dialog();
    Dialog(DialogTypes_t type, Vec2D pos, int width, int height);
    
    virtual void draw(GameWindow &window) override;
    virtual void update() override;
    void setupContols();


    private:

        
        
        

};


#endif /* SRC_DIALOG_H_ */