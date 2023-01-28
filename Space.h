#include <map>
#include <string>
#include <optional>

class Space
{
private:
int ** allocate2dGrid(int, int);
int *** allocate3dGrid(int, int);

protected:
    int ** grid_t;
    int ** grid_t1;
    int *** grid_t3d;
    int *** grid_t13d;
    int cols;
    int rows;
    std::optional<int> depth;
    std::string neighbourhood;
    bool isPeriodic;

public:
    Space(std::string, bool,int x, int y);
    Space(std::string, bool, int x, int y, int z);

    void applyBoundaryCondition();
    bool isEmpty() const;

    void save_perf(std::string event, int micros);

    std::map <int, int> checkoutMooreNeighbourhood(int **, int, int) const;
    std::map <int, int> checkoutMooreNeighbourhood(int ***, int, int, int) const;
    std::map <int, int> checkoutVonNeumannNeighbourhood(int **, int, int) const;
    std::map <int, int> checkoutVonNeumannNeighbourhood(int ***, int, int, int) const;

    ~Space();
};