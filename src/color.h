#pragma once
#include <iostream>

class Color {
private:
    uint8_t r;  // componente roja
    uint8_t g;  // componente verde
    uint8_t b;  // componente azul

public:
    Color(){}
    // Constructor
    Color(int blue, int green, int red) {
        // Asegurarse de que los valores estén en el rango correcto utilizando clamping
        r = (red < 0) ? 0 : ((red > 255) ? 255 : red);
        g = (green < 0) ? 0 : ((green > 255) ? 255 : green);
        b = (blue < 0) ? 0 : ((blue > 255) ? 255 : blue);
    }

    // Método para imprimir el color
    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "RGB(" << color.r << ", " << color.g << ", " << color.b << ")";
        return os;
    }

    const int getRed() {
        return r;
    }

    const int getGreen() {
        return g;
    }

    const int getBlue() {
        return b;
    }

    // Sobrecarga del operador de suma para sumar dos colores
    Color operator+(const Color& other) const {
        int newR = r + other.r;
        int newG = g + other.g;
        int newB = b + other.b;

        // Asegurarse de que los valores no excedan 255
        newR = (newR > 255) ? 255 : newR;
        newG = (newG > 255) ? 255 : newG;
        newB = (newB > 255) ? 255 : newB;

        return Color(newR, newG, newB);
    }

    // Sobrecarga del operador de multiplicación para multiplicar el color por un float
    Color operator*(float value) const {
        int newR = static_cast<int>(r * value);
        int newG = static_cast<int>(g * value);
        int newB = static_cast<int>(b * value);

        // Asegurarse de que los valores no excedan 255
        newR = (newR > 255) ? 255 : newR;
        newG = (newG > 255) ? 255 : newG;
        newB = (newB > 255) ? 255 : newB;

        return Color(newR, newG, newB);
    }

    bool operator==(const Color &color)
    {
        if (r == color.r && b == color.b && g == color.g)
            return true;
        return false;
    }
};