# BestScheduleParser

This project is a C++ application designed to generate convenient text for creating a spreadsheet with the student lessons for the BEST Lviv recruitment marketing campaign.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- CMake version 3.10 or higher
- A C++14 compatible compiler

### Building

1. Clone the repository
```bash
git clone https://github.com/PicklesRcool/BestScheduleParser.git
```
2. Navigate to the project directory
```bash
cd BestScheduleParser
```
3. Create a build directory and navigate to it
```bash
mkdir build && cd build
```
4. Run CMake to generate the build files
```bash
cmake ..
```
5. Build the project
```bash
make
```

## Usage

After building the project, you can run the application with:
```bash
./BestScheduleParser <input_file>
```
Where `<input_file>` is the path to the input file. You then specify `<output_file>`, which is the path to the output file, at the start of the program.