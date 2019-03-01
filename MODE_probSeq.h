class ProbSeq {
    public:
    short pos[4];
    short selected = 0;
    short probs[4][64];
    bool patt[4][64];
    short clockDiv[4][64];
    short clockDivCount[4];
    short lengthMin[4] = {0,0,0,0};
    short lengthMax[4] = {3,7,0,15};
    short clockDivOp;
    short clockDivision = 1;
    bool lengthSet = 0;
    short prob = 5;
    short set = 0;
    short param = 0;
    short morph = 0;
    short division = 0;
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