class ProbSeq {
    public:
    int selected = 0;
    int probs[4][64];
    bool patt[4][64];
    short clockDiv[4][64];
    short clockDivision = 1;
    int prob = 5;
    int set = 0;
    int param = 0;
    int pos = 0;
    int morph = 0;
    int length = 32;
    int division = 0;
    int division_old = 0;
    bool view = 0;
    bool selparam = 0;
    byte follow = 0;


    void run();
    void clock();
    void updatePosition();
    void writeNewPosition();
    void pattMorph(int _pos);
    void output();
    void controls();
    void drawBg();
    void drawMatrix(int k);
    void drawMatrixLED(int k);
    void drawKey(int k, int i, int j);
    void setStep(int _selected, int _pos);
    void drawInfo();
    void drawDivision();
    void drawControls();
    void followPos();
};