#include "scene_graph.hpp"

void ScVector::display()
{
    for (unsigned int i_l = 0; i_l < size(); i_l++)
        at(i_l)->display();
}

void ScVector::display(DisplayMode mode)
{
    for (unsigned int i_l = 0; i_l < size(); i_l++)
        at(i_l)->display(mode);
}


