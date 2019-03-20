class MainMenu {
    public:
    int selected = 0;
    static const int size = 2;
    String menu[size] = {"MIDI Setup", "Gen"};
    
    void run();
};
