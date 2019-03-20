class ProbSeq {
    public:
    bool menu = 0;
    bool view = 0;
    short set = 0;
    short channel = 0;
    short division = 0;
    short pos[4];
    short probs[4][64];
    bool patt[4][64];
    short clockDiv[4][64];
    short clockDivCount[4];
    short lengthMin[4] = {0,0,0,0};
    short lengthMax[4] = {15,15,15,15};
    short clockDivOp;
    short clockDivision = 2;
    short lengthMinTemp = 0;
    bool lengthSet = 1;
    short prob = 5;
    short pattMorph = 0;
    short temp = 0;
    short posNote[4];
    short note[4][64];
    bool selParam = 0;
    short timeParam = 0;
    short eventParam = 0;
    short timeMenuParam = 0;
    short eventMenuParam = 0;
    short eventMode[4];
    short eventStep[4];
    const String eventModeName[2] = {"Probability","Markov Chain"};
    const String eventStepName[2] = {"Sync","Trig"};
    short eventPos[4];
    short eventNote[4][16];
    short eventMorph[4];
    short eventProbSetMin = 0;
    short eventProbSetMax = 96;
    bool eventProbActive[4][16];
    short eventProbSetNote = 0;
    short eventProbMin[4][16];
    short eventProbMax[4][16];
    short eventQuantMode[4];
    bool eventQuant[4][96];

    ProbSeq();
    void run();
    void clock();
    void updatePosition();
    void writeNewPosition();
    void morph();
    void output();
    void controls();
    void drawBg();
    void drawMatrix();
    void drawMatrixLED();
    void drawKey(int key);
    void setStep(int key);
    void drawInfo();
    void drawDivision();
    void drawParams();
    void drawMenu();
};