#ifndef UTIL_HPP
#define UTIL_HPP

#include <chrono>
#include <fstream>
#include <istream>
#include <string>
#include <vector>

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>
namespace rematch {
namespace util {

class Timer
/*
Usage:
                Timer t;

                // Code to time goes here

                std::cout << "Time elapsed: " << t.elapsed() << " seconds\n"
*/
{

 public:
  Timer() : start_time_(take_time_stamp()) {}

  void reset() { start_time_ = take_time_stamp(); }

  double elapsed() const {
    return double((take_time_stamp() - start_time_) * 1e-6);
  }

  std::uint64_t elapsed_nanoseconds() const {
    return take_time_stamp() - start_time_;
  }

 protected:
  static std::uint64_t take_time_stamp() {
    return std::uint64_t(
        std::chrono::high_resolution_clock::now().time_since_epoch().count());
  }

 private:
  std::uint64_t start_time_;
};

std::string file2str(const std::string& filename);

std::tuple<std::string, std::string> handle_args(int argc, char const* argv[],
                                                 CLI::App& app);
struct VectorHasher {
  size_t operator()(const std::vector<size_t>& V) const {
    size_t hash = V.size();
    for (auto& i : V) {
      hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
  }
};

}  // end namespace util
}  // end namespace rematch

#endif  // UTIL_HPP
