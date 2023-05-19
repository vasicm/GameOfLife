#include <chrono>
#include <map>

class PerformanceMeasurer {
  public:
    static std::map<int, std::chrono::steady_clock::time_point> measure;

    static void StarMeasuring(int id) {
        measure[id] = std::chrono::steady_clock::now();
    }

    static long GetElapsedTime(int id) {
        auto end = std::chrono::steady_clock::now();

        return std::chrono::duration_cast<std::chrono::microseconds>(end - measure[id]).count();
    }
};


std::map<int, std::chrono::steady_clock::time_point> PerformanceMeasurer::measure;
