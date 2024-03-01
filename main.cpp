// Program for generating convenient text for creating a spreadsheet with the student lessons for the BEST Lviv recruitment marketing campaign
// Author: Volodymyr Bilokopytyi
// Data: 24.02.2023

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

static const std::vector<std::string> g_weekdays_html { "Пн</span>",
                                                        "Вт</span>",
                                                        "Ср</span>",
                                                        "Чт</span>",
                                                        "Пт</span>",
                                                        "Ресурси" }; 
                                                        // Для зручного витягування
                                                        // поточного дня

static const std::vector<std::string> g_lesson_numbers_html { "1</h3>",
                                                              "2</h3>",
                                                              "3</h3>",
                                                              "4</h3>",
                                                              "5</h3>",
                                                              "6</h3>",
                                                              "7</h3>",
                                                              "8</h3>",
                                                              "view-grouping",
                                                              "Ресурси" };
                                                              // Для зручного витягування
                                                              // поточного дня

static const std::string g_full_full_str  = "group_full"; // ціла група                 +
static const std::string g_full_chys_str  = "group_chys"; // ціла група чисельник       +
static const std::string g_full_znam_str  = "group_znam"; // ціла група знаменник       -
static const std::string g_sub1_full_str  = "sub_1_full"; // перша підгрупа             +
static const std::string g_sub2_full_str  = "sub_2_full"; // друга підгрупа             +
static const std::string g_sub1_chys_str  = "sub_1_chys"; // перша підгрупа чисельник   +
static const std::string g_sub2_chys_str  = "sub_2_chys"; // друга підгрупа чисельник   +
static const std::string g_sub1_znam_str  = "sub_1_znam"; // перша підгрупа знаменник   -
static const std::string g_sub2_znam_str  = "sub_2_znam"; // друга підгрупа знаменник   -


int main(int argc, char* argv[]) {

    // Initialisation

    std::string input_file_name(argv[1]);
    std::cout << "Input file: " << input_file_name << '\n';

    std::ifstream in_filestream(input_file_name);
    
    std::string file_contents((std::istreambuf_iterator<char>(in_filestream)),
                               std::istreambuf_iterator<char>());

    in_filestream.close();

    std::cout << "File size: " << file_contents.size() << "\n";

    //std::cout << "Contents of the file:\n" << file_contents << '\n';

    std::string output_file_name;
    std::cout << "Output file name: ";
    //std::cin >> output_file_name;
    ///////////////////////////////////
    int htmlInNamePos = input_file_name.find("html_files", 0);
    int groupNamePos = htmlInNamePos + 16;
    int dotInNamePos = input_file_name.find (".", groupNamePos);

    int groupNameSize = dotInNamePos - groupNamePos;

    output_file_name = input_file_name.substr(groupNamePos, groupNameSize);
    //////////////////////////////////
    output_file_name += ".txt";

    std::ofstream out_filestream(output_file_name);

    // Parsing
    bool skipping_day = false;
    for (int weekday_index = 0; weekday_index < g_weekdays_html.size() - 1; ++weekday_index) {
        std::cout << "Day " << weekday_index + 1 << ".\n";

        // Weekday extraction

        size_t curr_weekday_pos = file_contents.find(g_weekdays_html[weekday_index], 0);
        if (curr_weekday_pos == std::string::npos) {
            std::cout << "Couldn't find weekday'" << g_weekdays_html[weekday_index] << "'.\nExiting...\n";
            out_filestream << "-\t-\t-\t-\t";
            continue;
        }

        size_t next_weekday_pos = 0;
        do {
            next_weekday_pos = file_contents.find(g_weekdays_html[weekday_index + 1], curr_weekday_pos);
            if (next_weekday_pos == std::string::npos) {
                std::cout << "Couldn't find next weekday '" << g_weekdays_html[weekday_index + 1] << "'. Skipping...\n";
                ++weekday_index;
            }
        } while (next_weekday_pos == std::string::npos);

        std::string curr_day_str = file_contents.substr(curr_weekday_pos, next_weekday_pos - curr_weekday_pos);

        for (int lesson_num_index = 0; lesson_num_index < 4 /*4 пара */; ++lesson_num_index) {
            std::cout << "Lesson " << lesson_num_index + 1 << ". ";

            // Current weekday parsing for lessons by number

            size_t curr_lesson_num_pos = curr_day_str.find(g_lesson_numbers_html[lesson_num_index], 0);
            if (curr_lesson_num_pos == std::string::npos) {
                out_filestream << "-\t";
                std::cout << "Lesson not found.\n";
                continue;
            }

            size_t next_lesson_num_pos = 0;
            for (int next_lesson_num_index = lesson_num_index + 1; next_lesson_num_index < g_lesson_numbers_html.size(); ++next_lesson_num_index) {

                // Finding next lesson if it exists

                next_lesson_num_pos = curr_day_str.find(g_lesson_numbers_html[next_lesson_num_index], 0);
                if (next_lesson_num_pos != std::string::npos) {
                    break;
                }
                
                //std::cout << "Couldn't find next lesson '" << g_lesson_numbers_html[next_lesson_num_index] << "' On day " << weekday_index + 1 << ".\n";
            }

            // Extracting current lesson substring

            std::string curr_lesson_str = curr_day_str.substr(curr_lesson_num_pos, next_lesson_num_pos - curr_lesson_num_pos);

            bool readDone = false;

            int full_full_pos = curr_lesson_str.find(g_full_full_str, 0);
            int full_chys_pos = curr_lesson_str.find(g_full_chys_str, 0);
            int sub1_full_pos = curr_lesson_str.find(g_sub1_full_str, 0);
            int sub1_chys_pos = curr_lesson_str.find(g_sub1_chys_str, 0);
            int sub2_full_pos = curr_lesson_str.find(g_sub2_full_str, 0);
            int sub2_chys_pos = curr_lesson_str.find(g_sub2_chys_str, 0);
            

            if (full_full_pos != std::string::npos && !readDone) {
                size_t lesson_name_start_pos = curr_lesson_str.find("<br/>", full_full_pos) + 5;
                
                size_t cabinet_start_pos     = curr_lesson_str.find(",", lesson_name_start_pos) + 2;

                size_t cabinet_end_pos       = curr_lesson_str.find(",", cabinet_start_pos) - 5;

                size_t type_lesson_start_pos = cabinet_end_pos + 7;

                std::string curr_cabinet_str     = curr_lesson_str.substr(cabinet_start_pos, cabinet_end_pos - cabinet_start_pos - 2);
                std::string curr_type_lesson_str = curr_lesson_str.substr(type_lesson_start_pos, 6);

                if (!std::isdigit(curr_lesson_str[cabinet_start_pos])) {
                    curr_cabinet_str     = "n.";
                    curr_type_lesson_str = "a.";
                }

                std::cout << "'" << curr_cabinet_str << "', '" << curr_type_lesson_str << "'. ";
                out_filestream << curr_cabinet_str << " " << curr_type_lesson_str;
                
                readDone = true;
            }

            if (full_chys_pos != std::string::npos && !readDone) {
                size_t lesson_name_start_pos = curr_lesson_str.find("<br/>", full_chys_pos) + 5;
                
                size_t cabinet_start_pos     = curr_lesson_str.find(",", lesson_name_start_pos) + 2;

                size_t cabinet_end_pos       = curr_lesson_str.find(",", cabinet_start_pos) - 5;

                size_t type_lesson_start_pos = cabinet_end_pos + 7;

                std::string curr_cabinet_str     = curr_lesson_str.substr(cabinet_start_pos, cabinet_end_pos - cabinet_start_pos - 2);
                std::string curr_type_lesson_str = curr_lesson_str.substr(type_lesson_start_pos, 6);

                if (!std::isdigit(curr_lesson_str[cabinet_start_pos])) {
                    curr_cabinet_str     = "n.";
                    curr_type_lesson_str = "a.";
                }

                std::cout << "'" << curr_cabinet_str << "', '" << curr_type_lesson_str << "'. ";
                out_filestream << curr_cabinet_str << " " << curr_type_lesson_str;
                
                readDone = true;
            }

            if (sub1_full_pos != std::string::npos && !readDone) {
                size_t lesson_name_start_pos = curr_lesson_str.find("<br/>", sub1_full_pos) + 5;
                
                size_t cabinet_start_pos     = curr_lesson_str.find(",", lesson_name_start_pos) + 2;

                size_t cabinet_end_pos       = curr_lesson_str.find(",", cabinet_start_pos) - 5;

                size_t type_lesson_start_pos = cabinet_end_pos + 7;

                std::string curr_cabinet_str     = curr_lesson_str.substr(cabinet_start_pos, cabinet_end_pos - cabinet_start_pos - 2);
                std::string curr_type_lesson_str = curr_lesson_str.substr(type_lesson_start_pos, 6);

                if (!std::isdigit(curr_lesson_str[cabinet_start_pos])) {
                    curr_cabinet_str     = "n.";
                    curr_type_lesson_str = "a.";
                }

                std::cout << "'" << curr_cabinet_str << "', '" << curr_type_lesson_str << "'. ";
                out_filestream << curr_cabinet_str << " " << curr_type_lesson_str;
            }

            if (sub1_chys_pos != std::string::npos && !readDone) {
                size_t lesson_name_start_pos = curr_lesson_str.find("<br/>", sub1_chys_pos) + 5;
                
                size_t cabinet_start_pos     = curr_lesson_str.find(",", lesson_name_start_pos) + 2;

                size_t cabinet_end_pos       = curr_lesson_str.find(",", cabinet_start_pos) - 5;

                size_t type_lesson_start_pos = cabinet_end_pos + 7;

                std::string curr_cabinet_str     = curr_lesson_str.substr(cabinet_start_pos, cabinet_end_pos - cabinet_start_pos - 2);
                std::string curr_type_lesson_str = curr_lesson_str.substr(type_lesson_start_pos, 6);

                if (!std::isdigit(curr_lesson_str[cabinet_start_pos])) {
                    curr_cabinet_str     = "n.";
                    curr_type_lesson_str = "a.";
                }

                std::cout << "'" << curr_cabinet_str << "', '" << curr_type_lesson_str << "'. ";
                out_filestream << curr_cabinet_str << " " << curr_type_lesson_str;
            }          

            if (sub1_full_pos == std::string::npos && sub1_chys_pos == std::string::npos && 
                full_full_pos == std::string::npos && full_chys_pos == std::string::npos) {
                out_filestream << "-";
            }

            if (sub1_full_pos != std::string::npos || 
                sub1_chys_pos != std::string::npos || 
                sub2_full_pos != std::string::npos || 
                sub2_chys_pos != std::string::npos) {
                out_filestream << " / ";
            }       

            if (sub2_full_pos != std::string::npos && !readDone) {
                size_t lesson_name_start_pos = curr_lesson_str.find("<br/>", sub2_full_pos) + 5;
                
                size_t cabinet_start_pos     = curr_lesson_str.find(",", lesson_name_start_pos) + 2;

                size_t cabinet_end_pos       = curr_lesson_str.find(",", cabinet_start_pos) - 5;

                size_t type_lesson_start_pos = cabinet_end_pos + 7;

                std::string curr_cabinet_str     = curr_lesson_str.substr(cabinet_start_pos, cabinet_end_pos - cabinet_start_pos - 2);
                std::string curr_type_lesson_str = curr_lesson_str.substr(type_lesson_start_pos, 6);

                if (!std::isdigit(curr_lesson_str[cabinet_start_pos])) {
                    curr_cabinet_str     = "n.";
                    curr_type_lesson_str = "a.";
                }

                std::cout << "'" << curr_cabinet_str << "', '" << curr_type_lesson_str << "'. ";
                out_filestream << curr_cabinet_str << " " << curr_type_lesson_str;
            }


            if (sub2_chys_pos != std::string::npos && !readDone) {
                size_t lesson_name_start_pos = curr_lesson_str.find("<br/>", sub2_chys_pos) + 5;
                
                size_t cabinet_start_pos     = curr_lesson_str.find(",", lesson_name_start_pos) + 2;

                size_t cabinet_end_pos       = curr_lesson_str.find(",", cabinet_start_pos) - 5;

                size_t type_lesson_start_pos = cabinet_end_pos + 7;

                std::string curr_cabinet_str     = curr_lesson_str.substr(cabinet_start_pos, cabinet_end_pos - cabinet_start_pos - 2);
                std::string curr_type_lesson_str = curr_lesson_str.substr(type_lesson_start_pos, 6);

                if (!std::isdigit(curr_lesson_str[cabinet_start_pos])) {
                    curr_cabinet_str     = "n.";
                    curr_type_lesson_str = "a.";
                }

                std::cout << "'" << curr_cabinet_str << "', '" << curr_type_lesson_str << "'. ";
                out_filestream << curr_cabinet_str << " " << curr_type_lesson_str;
            }

            if (sub2_full_pos == std::string::npos && sub2_chys_pos == std::string::npos &&
                (sub1_full_pos != std::string::npos || sub1_chys_pos != std::string::npos) &&
                full_full_pos == std::string::npos && full_chys_pos == std::string::npos) {
                out_filestream << "-";
            }

            out_filestream << '\t';
            std::cout << "Lesson extracted.\n";
        } // lesson num loop

        //std::cout << "Day " << weekday_index + 1 << " done..\n";
    } // weekday loop
    
    out_filestream << '\n';
    out_filestream.close();
    std::cout << "Program execution done...\n";

    return 0;
}
