#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class TemperatureChart {
public:
    TemperatureChart(int minTemp, int maxTemp, int degreeStep) {
        minTemperature = minTemp;
        maxTemperature = maxTemp;
        step = degreeStep;
    }

    void readTemperaturesFromFile(const std::string& fileName) {
        std::ifstream inputFile(fileName);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open file: " << fileName << std::endl;
            return;
        }

        int temperature;
        while (inputFile >> temperature) {
            if (temperature >= minTemperature && temperature <= maxTemperature) {
                temperatures.push_back(temperature);
            }
        }

        inputFile.close();
    }

    void generateChart() {
        int numBars = (maxTemperature - minTemperature) / step + 1;
        int barWidth = 50;

        for (int temp = maxTemperature; temp >= minTemperature; temp -= step) {
            std::cout << temp << " | ";
            int count = 0;

            for (int temperature : temperatures) {
                if (temperature >= temp && temperature < temp + step) {
                    count++;
                }
            }

            int barLength = 0;  // Default value for barLength

            if (!temperatures.empty()) {
                barLength = (count * barWidth) / temperatures.size();
            }

            for (int i = 0; i < barLength; i++) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }

private:
    int minTemperature;
    int maxTemperature;
    int step;
    std::vector<int> temperatures;
};

int main() {
    TemperatureChart chart(-30, 120, 3);
    chart.readTemperaturesFromFile("temperatures.txt");
    chart.generateChart();

    return 0;
}
