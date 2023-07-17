#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
const auto Seed = 123;
const auto WriteSizeGb = 128;
const auto TestPath = "/Volumes/Z Slim/random_rw_test";
const auto MBSize = 1024 * 1024;
const auto GBSize = MBSize * 1024l;
inline auto transform(int j) {
    // return j % 26 + 'a';
    return 'a';
}
int main() {
    std::ranlux24_base gen, gen2;  // mersenne_twister_engine seeded with rd()
    gen.seed(Seed);
    gen2.seed(Seed);
    std::uniform_int_distribution<char> distrib('a', 'z');
    std::ofstream os(TestPath);
    for (int gb = 0; gb < WriteSizeGb; gb++) {
        for (int i = 0; i < 1024; i++) {
            auto start = std::chrono::steady_clock::now();
            for (int j = 0; j < MBSize; j++) {
                char c = transform(i);
                os.write(&c, 1);
            }
            auto end = std::chrono::steady_clock::now();
            const std::chrono::duration<double> elapsed_seconds = end - start;
            std::cout << "Write: " << (gb + 1) << "GB " << (1 / elapsed_seconds.count()) << "MB/s"
                      << std::endl;
        }
    }
    os.close();
    std::cout << "Write complete" << std::endl;
    std::ifstream is(TestPath);
    char c;
    for (int gb = 0; gb < WriteSizeGb; gb++) {
        for (int i = 0; i < 1024; i++) {
            auto start = std::chrono::steady_clock::now();
            for (auto j = 0; j < MBSize; j++) {
                is.read(&c, 1);
                if (c != transform(c)) {
                    std::cout << gb << "GB " << i << "MB" << std::endl;
                    return 0;
                }
            }
            auto end = std::chrono::steady_clock::now();
            const std::chrono::duration<double> elapsed_seconds = end - start;
            std::cout << "Read: " << (gb + 1) << "GB "  << (1 / elapsed_seconds.count()) << "MB/s"
                      << std::endl;
        }
        std::cout << "Read " << (gb + 1) << "GB" << std::endl;
    }
    is.close();
    std::cout << '\n';
}