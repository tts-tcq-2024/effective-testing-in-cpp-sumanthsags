#include <iostream>
#include <assert.h>
#include <sstream>

int printColorMap() 
{
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) 
    {
        for(j = 0; j < 5; j++) 
        {
            std::cout << i * 5 + j << " | " << majorColor[i] << " | " << minorColor[i] << "\n";
        }
    }
    return i * j;
}

void testAllColorPairs() 
{
    // Capture the output of printColorMap
    std::ostringstream capturedOutput;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(capturedOutput.rdbuf()); // Redirect cout to capturedOutput
    
    printColorMap(); // Generate the color map output

    std::cout.rdbuf(oldCoutBuffer); // Reset cout to its original state
    
    // Define expected major and minor colors
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    
    // Process captured output line by line
    std::istringstream iss(capturedOutput.str());
    std::string line;
    int lineCount = 0;

    while (std::getline(iss, line)) 
    {
        int expectedPairNumber = lineCount;
        std::string expectedOutput = std::to_string(expectedPairNumber) + " | " + majorColor[lineCount / 5] + " | " + minorColor[lineCount % 5];
        
        // If the captured line does not match the expected output, print an error message
        if (line != expectedOutput) 
        {
            std::cerr << "Test failed at index: " << lineCount << "\nActual: " << line << "\nExpected: " << expectedOutput << "\n";
            assert(false && "Mismatch in color pair output");
        }
        
        lineCount++;
    }
}

int main() 
{
    int result = printColorMap();
    assert(result == 25);
    testAllColorPairs();
    std::cout << "All tests passed successfully!\n";
    return 0;
}
