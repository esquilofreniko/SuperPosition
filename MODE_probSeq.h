class ProbSeq {
    public:
    int selected = 0;
    int probs[4][64];
    bool patt[4][64];
    int prob = 5;
    int set = 0;
    int param = 0;
    int pos = 0;
    int morph = 0;
    int length = 16;
    int division = 0;
    bool view = 1;

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
    void setPatt(int _selected, int _pos);
    void setProb(int _selected, int _pos);
    void drawInfo();
    void drawDivision();
};