const int INTERRUPT_SIGNAL_PIN = 18;
const int MEASUREMENT_BUFFER_SIZE = 1000;

volatile uint32_t interruptCounter = 0;
volatile uint32_t cumulativeTimeSum = 0;
uint32_t timeDeltaBuffer[MEASUREMENT_BUFFER_SIZE];
uint32_t lastInterruptTime = 0;

void setup() {
    Serial.begin(9600);
    pinMode(INTERRUPT_SIGNAL_PIN, INPUT);
    attachInterrupt(
        digitalPinToInterrupt(INTERRUPT_SIGNAL_PIN), 
        handleInterrupt, 
        HIGH
    );
}

void loop() {
    if (interruptCounter >= MEASUREMENT_BUFFER_SIZE) {
        noInterrupts();
        computeAndPrintStatistics();
        interruptCounter = 0;
        cumulativeTimeSum = 0;
        interrupts();
    }
}

void handleInterrupt() {
    uint32_t currentTime = micros();
    uint32_t timeSinceLastInterrupt = currentTime - lastInterruptTime;
    
    if (interruptCounter < MEASUREMENT_BUFFER_SIZE) {
        timeDeltaBuffer[interruptCounter] = timeSinceLastInterrupt;
        cumulativeTimeSum += timeSinceLastInterrupt;
        interruptCounter++;
    }
    
    lastInterruptTime = currentTime;
}

void computeAndPrintStatistics() {
    float meanInterval = cumulativeTimeSum / (float)MEASUREMENT_BUFFER_SIZE;
    float sumSquaredDeviations = 0;
    
    for (int i = 0; i < MEASUREMENT_BUFFER_SIZE; i++) {
        float deviation = timeDeltaBuffer[i] - meanInterval;
        sumSquaredDeviations += deviation * deviation;
    }
    
    float rootMeanSquareDeviation = sqrt(sumSquaredDeviations / MEASUREMENT_BUFFER_SIZE);
    
    Serial.print("Mean interval: ");
    Serial.print(meanInterval);
    Serial.print(" us, RMS deviation: ");
    Serial.print(rootMeanSquareDeviation);
    Serial.println(" us");
}