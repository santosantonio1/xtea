/*
                FILE FORMATTER (HEXADECIMAL NUMBERS)

        author: Antônio dos Santos
        version: 5/6/2024
        github: @santosantonio1

        This program formats a file so that you can just copy and paste into a test list.

        Example:
            fmt.txt

            {0x546cf7be,0xe2cd9a9b,0x2213ba3c,0x9a23039e},
            {0x2E4D1C1C,0x82D7AEED,0xE97C851A,0x7809F717},
            {0x11719bd1,0x74f1087b,0xece3337b,0xdb45799f},
            {0x3224F131,0x7B44CBA0,0xB053D945,0xD3BD3F40},
            {0xc5b3f4ab,0x3ca0b22f,0x5fed902f,0xf7f42b32},
            {0xB89A56EC,0xEF0D3242,0x53B8BEAB,0x154F605F},
            {0x16943fbf,0x12575dd8,0x306acfd6,0xd3567ae8},
            {0x0c01e919,0xf60329a9,0x0e09c248,0x87f7e7d5},
            {0x63bc22b8,0x3100fe86,0x5e090607,0x24c19bcd},
            {0x6a542539,0x305ba527,0x87308195,0xb5d5a372},

        NOTE: Remove comma at the end of last line.

        tests[10][4] = {
            {0x546cf7be,0xe2cd9a9b,0x2213ba3c,0x9a23039e},
            {0x2E4D1C1C,0x82D7AEED,0xE97C851A,0x7809F717},
            {0x11719bd1,0x74f1087b,0xece3337b,0xdb45799f},
            {0x3224F131,0x7B44CBA0,0xB053D945,0xD3BD3F40},
            {0xc5b3f4ab,0x3ca0b22f,0x5fed902f,0xf7f42b32},
            {0xB89A56EC,0xEF0D3242,0x53B8BEAB,0x154F605F},
            {0x16943fbf,0x12575dd8,0x306acfd6,0xd3567ae8},
            {0x0c01e919,0xf60329a9,0x0e09c248,0x87f7e7d5},
            {0x63bc22b8,0x3100fe86,0x5e090607,0x24c19bcd},
            {0x6a542539,0x305ba527,0x87308195,0xb5d5a372}
        };

        Execution: ./format <file to be formatted>
            optional: ./format <file to be formatted> <formatted filename>

        compiler used: gcc 14.1.0
*/

#include<iostream>
#include<fstream>
#include<ranges>

int main(int argc, char **argv)
{
    std::ifstream in(argv[1]);
    // std::ofstream out("fmt.txt");

    const std::string path = (argc > 2) ? argv[2] : "fmt.txt";
    std::ofstream out(path);

    std::string line;

    while(getline(in, line))
    {
        out << "{0x" << line.substr(0, 8);
        for(const auto &s : line | std::ranges::views::chunk(8) 
                                 | std::ranges::views::drop(1)){
            
            out << ",0x" << std::string{s.begin(), s.end()};
        }

        out << "},\n";
    }

    in.close();
    out.close();

    return 0;
}