#pragma once
#include <vector>
#include <random>

namespace GenerateTerrain
{
    void calculateMidpoint(std::vector<std::vector<int>>& heightMap,
                           std::size_t step,
                           std::size_t midX,
                           std::size_t midY,
                           std::size_t randomLimit)
    {
        std::random_device randomizer;
        std::default_random_engine engine(randomizer());
        std::uniform_int_distribution<std::size_t> distribution(0, randomLimit);

        auto test1 = heightMap[midX - step][midY - step];
        auto test2 = heightMap[midX - step][midY + step];
        auto test3 = heightMap[midX + step][midY + step];
        auto test4 = heightMap[midX + step][midY - step];

        heightMap[midX][midY] = heightMap[midX - step][midY - step] +
            heightMap[midX - step][midY + step] +
            heightMap[midX + step][midY + step] +
            heightMap[midX + step][midY - step];

        heightMap[midX][midY] /= 4;
        heightMap[midX][midY] += distribution(engine);
    }

    void calculateEdges(std::vector<std::vector<int>>& heightMap,
                        std::size_t step,
                        std::size_t midX,
                        std::size_t midY,
                        std::size_t randomLimit)
    {
        std::size_t smallX = midX - step;
        std::size_t bigX = midX + step;

        std::size_t smallY = midY - step;
        std::size_t bigY = midY + step;

        heightMap[bigX][midY] = (heightMap[bigX][smallY] + heightMap[bigX][bigY]) / 2;
        heightMap[smallX][midY] = (heightMap[smallX][smallY] + heightMap[smallX][bigY]) / 2;
        heightMap[midX][bigY] = (heightMap[smallX][bigY] + heightMap[bigX][bigY]) / 2;
        heightMap[midX][smallY] = (heightMap[smallX][smallY] + heightMap[bigX][smallY]) / 2;

        std::random_device randomizer;
        std::default_random_engine engine(randomizer());
        std::uniform_int_distribution<std::size_t> distribution(0, randomLimit);

        heightMap[bigX][midY] += distribution(engine);
        heightMap[smallX][midY] += distribution(engine);
        heightMap[midX][bigY] += distribution(engine);
        heightMap[midX][smallY] += distribution(engine);


    }
    void diamondSquare(std::vector<std::vector<int>>& heightMap,
                       std::size_t step,
                       std::size_t midX,
                       std::size_t midY,
                       std::size_t randomLimit)
    {
        if (step >= 2)
        {
             std::size_t halfStep = step / 2;
            diamondSquare(heightMap, halfStep, midX - halfStep, midY - halfStep, randomLimit);
            diamondSquare(heightMap, halfStep, midX + halfStep, midY - halfStep, randomLimit);
            diamondSquare(heightMap, halfStep, midX + halfStep, midY + halfStep, randomLimit);
            diamondSquare(heightMap, halfStep, midX - halfStep, midY + halfStep, randomLimit);
        calculateMidpoint(heightMap, step, midX, midY, randomLimit);
        calculateEdges(heightMap, step, midX, midY, randomLimit);
        }
    }
}