#ifndef WORLD_HPP
#define WORLD_HPP

#define WORLD_H 400
#define WORLD_W 400

#include <SFML/Graphics.hpp>

class World
{
    public:
        World();
        virtual ~World();

        void Reset();
        void ComputeNextStep();
        void Draw(sf::RenderWindow &App);

        void SetCell(int x, int y, bool state);

        void Clear(bool alive);

        void ToggleEpileptic();

    protected:

        bool world[WORLD_H][WORLD_W];
        bool nextWorld[WORLD_H][WORLD_W];

    private:

        bool ComputeCell(int x, int y);
        int generation;
        bool epileptic;
};

#endif // WORLD_HPP
