#include "TSP_GUI.h"
#include <QtWidgets/QApplication>
#include <memory>
#include "tsp_template.h"

int main(int argc, char *argv[])
{
    const Square area = { {0, 0}, 10, 10 };
    std::mt19937 engine(1);

    auto tsp = std::make_unique<TspTemplate<Type2d, 500, CachingType::Full, PartitioningType::NoPartitioning, ConstructionType::LookaheadConvexHull, OptimisationType::kopt>>(area, GenerationType::Rectangle, engine);

    QApplication a(argc, argv);
    TSP_GUI w;
    w.show();
    return a.exec();
}
