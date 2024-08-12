#include <iostream>
#include <assert.h>

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    std::cout << "ALERT: Temperature is " << celcius << " celcius.\n";
    // Simulate a failure if temperature exceeds a threshold (e.g., 200°C)
    if (celcius > 200) {
        return 500;
    }
    // Return 200 for OK
    return 200;
}


void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
}

void testAlertFailureCount() {
    // Reset the failure count
    alertFailureCount = 0;
    
    // Test cases
    alertInCelcius(400.5);  // Should fail (204.722°C, above 200°C)
    std::cout << "After alertInCelcius(400.5), alertFailureCount = " << alertFailureCount << std::endl;
    assert(alertFailureCount == 1);
    
    alertInCelcius(395.0);  // Should fail (200.0°C, exactly at 200°C threshold)
    std::cout << "After alertInCelcius(392.0), alertFailureCount = " << alertFailureCount << std::endl;
    assert(alertFailureCount == 2);
    
    alertInCelcius(150);    // Should pass (65.556°C, below 200°C)
    std::cout << "After alertInCelcius(150), alertFailureCount = " << alertFailureCount << std::endl;
    assert(alertFailureCount == 2);  // Count should remain the same

    std::cout << "All tests passed successfully!\n";
}


int main() {
    // Run the test cases
    testAlertFailureCount();
    
    std::cout << alertFailureCount << " alerts failed.\n";
    std::cout << "All is well (maybe!)\n";
    return 0;
}
