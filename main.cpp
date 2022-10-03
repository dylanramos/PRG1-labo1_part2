#include <iostream>
#include <cmath>

using namespace std;

const int SPACES_FOR_INDENTATION = 15;

string convertDecimalToBinary(int decimal) {
    int base = 2, remainder;
    string result;

    while (decimal > 0) {
        remainder = decimal % base;
        decimal /= base;
        result.insert(0, to_string(remainder));
    }

    return result;
}

string convertBinaryToDecimal(string binary) {
    int exponent = 0;
    long long number = 0;

    for (int i = binary.length() - 1; i >= 0; --i) {
        if (binary[i] == '1') {
            number += pow(2, exponent);
        }
        exponent++;
    }

    return to_string(number);
}

string makeIndentation(string label) {
    int spaces = SPACES_FOR_INDENTATION - label.length();

    for (int i = 0; i < spaces; i++) {
        label.append(" ");
    }

    label.append(" : ");

    return label;
}

bool numberIsZero(long double number, int totalBits, int totalMantissaBits) {
    if (number == 0) {
        string exponent, mantissa;

        for (int i = 0; i < totalBits - totalMantissaBits; ++i) {
            exponent.append("0");
        }

        for (int i = 0; i < totalMantissaBits; ++i) {
            mantissa.append("0");
        }

        cout << makeIndentation("Representation") << "0 " << exponent << " " << mantissa;

        return true;
    }

    return false;
}

int main() {
    long double number;
    int totalBits, totalMantissaBits;

    cout << "Entrez un nombre reel, le nombre de bits total et celui de la mantisse \n";

    cin >> number;
    cin >> totalBits;
    cin >> totalMantissaBits;

    if (numberIsZero(number, totalBits, totalMantissaBits)) return 0;

    int exponentCount, exponentBitsCount, exponentDecimalValue, bias;
    long double quotient = number;
    string sign = number < 0 ? "-" : "+";

    exponentCount = 0;
    exponentBitsCount = totalBits - 1 - totalMantissaBits;
    bias = pow(2, exponentBitsCount - 1) - 1;

    if (number > 0) {
        while (quotient >= 2) {
            quotient /= 2;
            exponentCount++;
        }
    } else {
        while (quotient >= -1) {
            quotient *= 2;
            exponentCount--;
        }
    }

    exponentDecimalValue = exponentCount + bias;
    string exponent = convertDecimalToBinary(exponentDecimalValue);

    string mantissa;
    long double mantissaDecimalValue = quotient;

    if (number > 0) {
        quotient -= 1;

        for (int i = 0; i < totalMantissaBits; ++i) {
            quotient *= 2;

            if (quotient >= 1) {
                mantissa.append("1");
                quotient -= 1;
            } else {
                mantissa.append("0");
            }
        }
    } else {
        quotient += 1;

        for (int i = 0; i < totalMantissaBits; ++i) {
            quotient *= 2;

            if (quotient <= -1) {
                mantissa.append("1");
                quotient += 1;
            } else {
                mantissa.append("0");
            }
        }
    }

    string mantissaDecimalValueFromBinary = convertBinaryToDecimal(mantissa);

    cout << "\n" << fixed << number << " = " << (number > 0 ? sign : "");
    cout << fixed << mantissaDecimalValue << " * ( 2 ^ " << exponentCount << " )\n\n";

    // Sign display
    cout << makeIndentation("Signe") << sign << "1\n";
    cout << makeIndentation("") << (number < 0) << "\n\n";

    // Exponent display
    cout << makeIndentation("Exposant biaise");
    cout << exponentCount << " + " << bias << " = " << exponentDecimalValue << "\n";
    cout << makeIndentation("") << exponent << "\n\n";

    // Mantissa display
    cout << makeIndentation("Mantisse") << "1 + ( " << mantissaDecimalValueFromBinary << " / ";
    cout << fixed << (long long) pow(2, totalMantissaBits) << " )\n";
    cout << makeIndentation("") << mantissa << "\n\n";

    // Representation display
    cout << makeIndentation("Representation") << (number < 0) << " " << exponent << " " << mantissa << "\n\n";

    return 0;
}
