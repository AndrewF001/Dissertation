#include "TSP_GUI.h"
#include <QtWidgets/QApplication>
#include <memory>

#include "tsp_template.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    TSP_GUI w;

    //auto output = 

    //const Square area = { {0, 0}, 10, 10 };
    //std::mt19937 engine(2);
    //auto tsp = std::make_unique<TspTemplate<Type2d, 100, CachingType::full, PartitioningType::linearSearch, ConstructionType::NearestNeighbour, OptimisationType::TwoOpt>>(area, GenerationType::rectangle, engine);
    //auto data = tsp->run(4);

    Square area = { {0, 0}, 1000, 1000 };
    std::mt19937 engine(1340283431);
    constexpr size_t size = 100;

    auto cities = TspDataTemplate<Type2d, size, CachingType::full, PartitioningType::quadTree>::generateCities(area, GenerationType::rectangle, engine);

    //auto quad = std::make_unique<TspTemplate<Type2d, 100, CachingType::full, PartitioningType::quadTree, ConstructionType::ConvexHull, OptimisationType::TwoOpt>>(area, cities)->run({ 1 });
    auto linear = std::make_unique<TspTemplate<Type2d, size, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::None>>(area, cities)->run({ 2 });


    w.setData(linear);
    //w.setData(linear);

    w.show();
    return a.exec();
}
