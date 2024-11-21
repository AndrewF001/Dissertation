#include "TSP_GUI.h"
#include <QtWidgets/QApplication>
#include <memory>

#include "tsp_template.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    TSP_GUI w;

    const Square area = { {0, 0}, 10, 10 };
    std::mt19937 engine(2);
    auto tsp = std::make_unique<TspTemplate<Type2d, 100, CachingType::Full, PartitioningType::NoPartitioning, ConstructionType::LookaheadConvexHull, OptimisationType::None>>(area, GenerationType::Rectangle, engine);
    tsp->run(4);

    w.setData(tsp->getOutput());

    w.show();
    return a.exec();
}
