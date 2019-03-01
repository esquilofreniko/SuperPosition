class ProbSeq {
    public:
    int pos[4];
    int length[4] = {16,32,48,64};
    int selected = 0;
    int probs[4][64];
    bool patt[4][64];
    short clockDiv[4][64];
    short clockDivision = 1;
    int prob = 5;
    int set = 0;
    int param = 0;
    int morph = 0;
    int division = 0;
    bool view = 0;
    bool selparam = 0;
    byte follow = 0;

    void run();
    void clock();
    void updatePosition();
    void writeNewPosition();
    void pattMorph();
    void output();
    void controls();
    void drawBg();
    void drawMatrix();
    void drawMatrixLED();
    void drawKey(int i, int j);
    void setStep(int key);
    void drawInfo();
    void drawDivision();
    void drawControls();
    void followPos();
};