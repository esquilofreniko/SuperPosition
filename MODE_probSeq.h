class ProbSeq {
    public:
    int selected = 0;
    int selected_old = 0;
    int probs[4][64];
    bool patt[4][64];
    int prob = 5;
    int set = 0;
    int param = 0;
    int pos = 0;
    int morph = 0;
    int length = 16;

    void run();
    void clock();
    void updatePosition();
    void writeNewPosition();
    void pattMorph(int _pos);
    void output();
    void controls();
    void drawBg();
    void drawMatrix(int _k);
    void drawMatrixLED(int _k);
    void setPatt(int _i, int _pos);
    void setProb(int _i, int _pos);
    void drawInfo();
};