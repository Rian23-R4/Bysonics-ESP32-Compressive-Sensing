double vImagF[DATA_SIZE];

double vRealOximeter[DATA_SIZE];
double vRealEKG[DATA_SIZE];
double vRealMyoware[DATA_SIZE];
double vRealTemperature[DATA_SIZE];
double vRealAccelerometerx[DATA_SIZE];
double vRealAccelerometery[DATA_SIZE];
double vRealAccelerometerz[DATA_SIZE];

double HvReal[DATA_SIZE];
double HvImag[DATA_SIZE];

char Send[100];
int y;
int i;
char start[100];
double Temperature;
double timedelay = 15;

static uint8_t taskCoreOne = 1;
