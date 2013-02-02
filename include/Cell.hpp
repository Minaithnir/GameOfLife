#ifndef CELL_HPP
#define CELL_HPP


class Cell
{
    public:

        enum State
        {
            DEAD,
            ALIVE
        }

        Cell();
        virtual ~Cell();
    protected:

        Cell.State state;

    private:
};

#endif // CELL_HPP
