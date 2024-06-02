/*
        128 BIT (POSTIVIE) NUMBER GENERATOR

    author: Antônio dos Santos
    version: 2/6/2024
    github: @santosantonio1

    Usage: ./gen <n_bits> <how many numbers>

    This implementation was focused on training C++23 features,
    such as ranges, lambdas...
*/

#include<random>
#include<fstream>
#include<ranges>
#include<algorithm>
#include<vector>

int main(int argc, char ** argv)
{
    // Generates distinct numbers and stores on a std::vector
    auto gen = [](const size_t n_numbers){
        std::vector<unsigned int> v(n_numbers);
        std::size_t it = 0;

        // Random numbers generator
        std::random_device rd;
        std::mt19937 rng{rd()};
        std::uniform_int_distribution<unsigned int> dist{0, UINT32_MAX}; 

        while(it<n_numbers)
        {
            unsigned int n = dist(rng);
            // If the number was not generated yet, store on v
            if(std::ranges::find(v, n) == v.end()) v[it++] = n;
        }

        return v;
    };
    
    // Number of bits of the numbers that are to be generated
    const size_t n_bits = (argc > 2) ? std::stoi(argv[1])/32 : 128/32;

    // Number of numbers to be generated
    const size_t n_numbers = (argc > 2) ? std::stoi(argv[2]) : 10;

    // 128 bits number -> 4 32 bits integer
    const auto v = gen(n_bits*n_numbers);

    //--------------------------------------------------------------------------
    //  Method 1
    // for(auto it = v.begin(); it < v.end(); it = it + 4)
    // {   
    //     for(auto i : std::ranges ::subrange(it, v.end())
    //                | std::ranges::views::take(4)) out << std::hex << i;
 
    //     out << '\n';
    // }

    //--------------------------------------------------------------
    //  Writes on tests.txt:
    //      n_numbers
    //      num1
    //      num2
    //      ...

    std::ofstream out("tests.txt");

    out << n_numbers;

    for(const auto &a : v | std::ranges::views::chunk(n_bits)) {
        out << '\n'; 
        for(const auto i : a) 
            out << std::hex << i; 
    } 

    out.close();

    return 0;
}
