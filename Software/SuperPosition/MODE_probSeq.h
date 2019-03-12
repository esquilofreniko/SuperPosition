class ProbSeq {
    public:
    //Time
    short pos[4];
    short selected = 0;
    short probs[4][64];
    bool patt[4][64];
    short clockDiv[4][64];
    short clockDivCount[4];
    short lengthMin[4] = {0,0,0,0};
    short lengthMax[4] = {15,15,15,15};
    short clockDivOp;
    short clockDivision = 2;
    short lengthMinTemp = 0;
    bool lengthSet = 0;
    short prob = 5;
    short set = 0;
    short param = 0;
    short morph = 0;
    short division = 0;
    bool view = 0;
    bool selparam = 0;
    short follow = 0;
    short temp = 0;
    //Event
    short posNote[4];
    short note[4][64];
    bool activeNote[4][64];

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
    void drawKey(int key);
    void setStep(int key);
    void drawInfo();
    void drawDivision();
    void drawControls();
    void followPos();
};