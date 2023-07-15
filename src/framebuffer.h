#pragma once

#include "color.h"
#include "vertex2.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <cmath>
#include <functional>
#include <Windows.h>
#include <stack>

const int framebufferWidth = 1000;
const int framebufferHeight = 450;

std::vector<Color> framebuffer;

void clear(const Color& clearColor) {
    framebuffer.resize(framebufferWidth * framebufferHeight);
    fill(framebuffer.begin(), framebuffer.end(), clearColor);
}

void point(const Vertex2 vertex, const Color color) {
    

    int x = static_cast<int>(vertex.x);
    int y = static_cast<int>(vertex.y);

    if (x >= 0 && x < framebufferWidth && y >= 0 && y < framebufferHeight) {
        int index = y * framebufferWidth + x;
        framebuffer[index] = color;
    }
}


// Dibujar línea
void drawLine(int x0, int y0, int x1, int y1, Color color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        point(Vertex2{x0, y0}, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

Vertex2 getCenter(std::vector<Vertex2> points)
{
    int minX = points[0].x;
    int maxX = points[0].x;
    int minY = points[0].y;
    int maxY = points[0].y;
    for (int i = 0; i < points.size(); i++)
    {
        minX = points[i].x < minX ? points[i].x : minX;
        maxX = points[i].x > maxX ? points[i].x : maxX;
        minY = points[i].y < minY ? points[i].y : minY;
        maxY = points[i].y > maxY ? points[i].y : maxY;
    }
    return Vertex2{(minX + maxX) / 2, (minY + maxY) / 2};
}

void fillPolygon(Vertex2 start, Color fillColor, Color currentColor)
{
    // Crear una pila para almacenar las coordenadas de los píxeles a procesar
    std::stack<std::pair<int, int>> pixelStack;

    // Agregar las coordenadas iniciales a la pila
    pixelStack.push(std::make_pair(start.x, start.y));

    // Realizar el relleno de cubeta
    while (!pixelStack.empty())
    {
        // Obtener las coordenadas del píxel actual
        int x = pixelStack.top().first;
        int y = pixelStack.top().second;
        pixelStack.pop();

        // Verificar si el píxel actual necesita ser pintado
        if (!(framebuffer[y * framebufferWidth + x] == fillColor) && !(framebuffer[y * framebufferWidth + x] == currentColor))
        {
            // Pintar el píxel actual con el color de relleno
            framebuffer[y * framebufferWidth + x] = fillColor;

            // Agregar los píxeles adyacentes a la pila si cumplen con las condiciones
            if (x > 0)
                pixelStack.push(std::make_pair(x - 1, y)); // Píxel izquierdo
            if (x < framebufferWidth - 1)
                pixelStack.push(std::make_pair(x + 1, y)); // Píxel derecho
            if (y > 0)
                pixelStack.push(std::make_pair(x, y - 1)); // Píxel superior
            if (y < framebufferHeight - 1)
                pixelStack.push(std::make_pair(x, y + 1)); // Píxel inferior
        }
    }
}

void drawPolygon(std::vector<Vertex2> points, Color fillColor, Color currentColor)
{
    for (int i = 0; i < points.size(); i++)
    {
        if (i == points.size() - 1)
        {
            drawLine(points[i].x, points[i].y, points[0].x, points[0].y, currentColor);
            continue;
        }
        drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, currentColor);
    }
    fillPolygon(getCenter(points), fillColor, currentColor);
}

void renderBuffer()
{
    std::ofstream file("out.bmp", std::ios::binary);

    // Encabezado del archivo BMP
    uint32_t fileSize = 54 + (framebufferWidth * framebufferHeight * 3);
    uint32_t reserved = 0;
    uint32_t dataOffset = 54;
    uint32_t headerSize = 40;
    uint32_t imageWidth = framebufferWidth;
    uint32_t imageHeight = framebufferHeight;
    uint16_t colorPlanes = 1;
    uint16_t bitsPerPixel = 24;
    uint32_t compression = 0;
    uint32_t dataSize = (framebufferWidth * framebufferHeight * 3);
    uint32_t horizontalResolution = 2835; // 72 dpi
    uint32_t verticalResolution = 2835;   // 72 dpi
    uint32_t colorsInPalette = 0;
    uint32_t importantColors = 0;

    file.write("BM", 2); // Identificador del archivo BMP
    file.write(reinterpret_cast<char *>(&fileSize), sizeof(fileSize));
    file.write(reinterpret_cast<char *>(&reserved), sizeof(reserved));
    file.write(reinterpret_cast<char *>(&dataOffset), sizeof(dataOffset));
    file.write(reinterpret_cast<char *>(&headerSize), sizeof(headerSize));
    file.write(reinterpret_cast<char *>(&imageWidth), sizeof(imageWidth));
    file.write(reinterpret_cast<char *>(&imageHeight), sizeof(imageHeight));
    file.write(reinterpret_cast<char *>(&colorPlanes), sizeof(colorPlanes));
    file.write(reinterpret_cast<char *>(&bitsPerPixel), sizeof(bitsPerPixel));
    file.write(reinterpret_cast<char *>(&compression), sizeof(compression));
    file.write(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));
    file.write(reinterpret_cast<char *>(&horizontalResolution), sizeof(horizontalResolution));
    file.write(reinterpret_cast<char *>(&verticalResolution), sizeof(verticalResolution));
    file.write(reinterpret_cast<char *>(&colorsInPalette), sizeof(colorsInPalette));
    file.write(reinterpret_cast<char *>(&importantColors), sizeof(importantColors));

    // Rellenar fila con píxeles
    int paddingSize = (4 - (framebufferWidth * 3) % 4) % 4; // Relleno para asegurar que cada fila sea múltiplo de 4 bytes
    char paddingBytes[3] = {0, 0, 0};            // Bytes de relleno
    for (int y = framebufferHeight - 1; y >= 0; --y)
    {
        for (int x = 0; x < framebufferWidth; ++x)
        {
            int index = y * framebufferWidth + x;
            Color color = framebuffer[index];
            file.write(reinterpret_cast<char *>(&color), sizeof(color));
        }
        file.write(paddingBytes, paddingSize); // Escribir bytes de relleno al final de cada fila
    }

    file.close();
}