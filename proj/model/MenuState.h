typedef struct {
    /**
     * buttonStates[]
     * 
     * 
     * 
     */

    /**
     * Which button is currently selected/hovered.
     * Useful for keyboard navigation or mouse hover.
     * MenuButton selected_button;
    /


    /**
     * True when the player chooses Play.
     * The main State wrapper will then change to PLAYING.
     */
    bool play;

    bool quit;
    
    
}  MenuState;
