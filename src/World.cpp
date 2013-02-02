#include "../include/World.hpp"

#include <iostream>

#define PIXELS_SIZE WORLD_H*WORLD_W*4

#define EPILEPTIC

World::World()
{
    for(unsigned int i=0; i<WORLD_H; i++)
    {
        for(unsigned int j=0; j<WORLD_W; j++)
        {
            int Random = sf::Randomizer::Random(0, 20);
            if(Random <= 10)
                world[i][j] = false;
            else
                world[i][j] = true;
        }
    }
    generation = 0;
    //ctor
}

World::~World()
{
    //dtor
}

void World::Reset()
{
    for(unsigned int i=0; i<WORLD_H; i++)
    {
        for(unsigned int j=0; j<WORLD_W; j++)
        {
            int Random = sf::Randomizer::Random(0, 20);
            if(Random <= 10)
                world[i][j] = false;
            else
                world[i][j] = true;
        }
    }
    generation = 0;
}

/**
    Method drawing the full simulation onto the screen
*/
void World::Draw(sf::RenderWindow &App)
{
    sf::Uint8 pixels[PIXELS_SIZE];

    for(unsigned int i=0; i<WORLD_H; i++)
    {
        for(unsigned int j=0; j<WORLD_W; j++)
        {
            if(world[i][j])
            {
                if(epileptic)
                {
                    pixels[(i * WORLD_W + j) * 4]     = sf::Randomizer::Random(0,255); // R?
                    pixels[(i * WORLD_W + j) * 4 + 1] = sf::Randomizer::Random(0,255); // G?
                    pixels[(i * WORLD_W + j) * 4 + 2] = sf::Randomizer::Random(0,255); // B?
                }
                else
                {
                    pixels[(i * WORLD_W + j) * 4]     = 0; // R?
                    pixels[(i * WORLD_W + j) * 4 + 1] = 0; // G?
                    pixels[(i * WORLD_W + j) * 4 + 2] = 0; // B?
                }
                pixels[(i * WORLD_W + j) * 4 + 3] = 255; // A?
            }
            else
            {
                pixels[(i * WORLD_W + j) * 4]     = 255; // R?
                pixels[(i * WORLD_W + j) * 4 + 1] = 255; // G?
                pixels[(i * WORLD_W + j) * 4 + 2] = 255; // B?
                pixels[(i * WORLD_W + j) * 4 + 3] = 255; // A?
            }
        }
    }

    sf::Image image;
    image.LoadFromPixels(WORLD_W, WORLD_H, pixels);
    image.SetSmooth(false);

    sf::Sprite sprite;
    sprite.SetImage(image);

    App.Draw(sprite);
}

/**
    Method computing the state of the next generation cells
*/
void World::ComputeNextStep()
{
    for(unsigned int i=0; i<WORLD_H; i++)
    {
        for(unsigned int j=0; j<WORLD_W; j++)
        {
            nextWorld[i][j] = ComputeCell(i, j);
        }
    }

    //swap between the two generations
    std::swap(world, nextWorld);
    generation ++;

    std::cout << "Generation : " << generation << std::endl;
}

/**
    Method executing the rules for a specific cell and returning the new state
*/
bool World::ComputeCell(int x, int y)
{
    bool resultState = false;

    // Somme des cellules voisines
    int neighbourgSum = 0;
    for(int i=x-1; i<=x+1; i++)
        if(i >= 0 && i < WORLD_H)
            for(int j=y-1; j<=y+1; j++)
                if(j >= 0 && j < WORLD_W)
                    if(world[i][j])
                        neighbourgSum ++;

    if(world[x][y])
        neighbourgSum --;

    // Regle du "Jeu de Vie"
    if(world[x][y]) {
        if(neighbourgSum < 2 || neighbourgSum > 3)
        {
            resultState = false;
        }
        else
        {
            resultState = true;
        }
    } else {
        if(neighbourgSum == 3)
            resultState = true;
    }

    return resultState;
}

/**
    Method setting the state of a specific cell
*/
void World::SetCell(int x, int y, bool state)
{
    world[y][x] = state;
}

/**
    Method clearing the world with either alive or dead cells
*/
void World::Clear(bool alive)
{
    for(unsigned int i=0; i<WORLD_H; i++)
    {
        for(unsigned int j=0; j<WORLD_W; j++)
        {
            world[i][j] = alive;
        }
    }
    generation = 0;
}

void World::ToggleEpileptic()
{
    epileptic = !epileptic;
}
