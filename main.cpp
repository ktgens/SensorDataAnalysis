#include <iostream>
#include <windows.h>
using namespace std;

void inputData(float *p, int n) {

    float num;
    cout << "Введите " << n << " значений (от -50 до 50): ";
    for (int i = 0; i < n; i++) {
        float num;
        while (true) {
            cin >> num;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Ошибка, введите число" << endl;
                continue;
            }

            if (num > 50 || num < -50) {
                cout << "Ошибка, введите число от -50 до 50" << endl;
                continue;
            }

            break;
        }
        *(p + i) = num;
    }
    return;
}

float average(const float *p, int n) {
    float sum;
    for (int i = 0; i < n; i++) {
        sum += *(p + i);
    }
    return sum / n;
}

float minValue(const float *p, int n) {
    float mi = 10000;
    for (int i = 0; i < n; i++) {
        mi = min(*(p + i), mi);
    }
    return mi;
}
float maxValue(const float *p, int n) {
    float ma = -10000;
    for (int i = 0; i < n; i++) {
        ma = max(*(p + i), ma);
    }
    return ma;
}

float *filterAboveAverage(float *p, int n, int &newCount) {
    float avg = average(p, n);
    newCount = 0;
    for (int i = 0; i < n; i++) {
        if (*(p + i) > avg)
            newCount++;
    }

    float *abvAvg = new float[newCount];
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (*(p + i) > avg) {
            *(abvAvg + count) = *(p + i);
            count++;
        }
    }

    return abvAvg;
}

int main() {
    cout << "=== Анализ сенсора ===" << endl;

    int n;
    cout << "Введите количество измерений: ";
    while (true) {
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка, введите число" << endl;
            continue;
        }

        if (n < 1) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка, введите целое положительное число" << endl;
            continue;
        }

        break;
    }

    float *data = new float[n];
    inputData(data, n);

    cout << endl;
    cout << "Среднее значение: " << average(data, n) << endl;
    cout << "Минимум: " << minValue(data, n) << endl;
    cout << "Максимум: " << maxValue(data, n) << endl;
    cout << endl;

    cout << "Значения выше среднего: " << endl;

    int filteredSize = 0;
    float *abvAvg = filterAboveAverage(data, n, filteredSize);
    if (filteredSize > 0) {
        for (int i = 0; i < filteredSize; i++) {
            cout << *(abvAvg + i) << " ";
        }
    } else {
        cout << "отсутствуют";
    }

    delete[] data;
    delete[] abvAvg;
    data = nullptr;
    abvAvg = nullptr;
}
