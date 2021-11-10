#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager
{
    public:
    InputManager() = default;
    ~InputManager() = default;

    void handleInput();
    void clearInput();
    inline bool getMoveUp() const {return m_move_Up;}
    inline bool getMoveDown() const {return m_move_Down;}
    inline bool getMoveLeft() const {return m_move_Left;}
    inline bool getMoveRight() const {return m_move_Right;}
    inline bool getQuit() const {return m_running;}
    private:
    bool m_move_Up {false};
    bool m_move_Down{false};
    bool m_move_Left{false};
    bool m_move_Right{false};
    bool m_running{true};
};

#endif