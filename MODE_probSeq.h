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
    bool view = 0;
    bool selparam = 0;
    byte follow = 0;


    void run();
    void clock();
    void updatePosition();
    void writeNewPosition();
    void pattMorph(int index);
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