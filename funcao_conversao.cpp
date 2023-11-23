#include <iostream>
#include <string>
#include <sstream>

std::string removeNULSOH(const std::string& input) {
    std::string output = input;
    size_t pos = 0;
    
    // Enquanto encontrar '#NUL#SOH', substituir por uma string vazia
    while ((pos = output.find("#NUL#SOH")) != std::string::npos) {
        output.erase(pos, 8); // Remove "#NUL#SOH"
    }
    
    return output;
}

int main() {
    std::string input = R"(The oldest data was removed. Continue...
#NUL#SOH  0.153#NULE#STX#NUL#NUL#NUL#NUL#NUL#NUL#NULà#NULü#SOH  0.153#NULE#STX#NUL#NUL#SOH  0.153#NULE#STX#NUL#NUL#SOH  0.153#NULE#STX#NUL#NUL#NUL#NUL#NUL#NUL#SOH  0.153#NULE#STX#NUL#NUL#SOH  0.153#NULE#STX#NUL#SOH  0.153#NULE#STX#NUL#SOH  0.153#NULE#STX#NUL#NUL#SOH  0.153#NULE#STX#NUL#NUL#SOH  0.153#NULE#STX#NUL.153#NULE#STX#NUL#SOH  0.153#NULE#STX#NUL#SOH  0.153#NULE#STX#NUL#NUL#NUL#SOH  0.153#NULE#STX#NUL#NUL#NUL#NUL#SOH  0.153#NULE#STX#NUL#NUL#NUL#SOH  0.153#NULE#STX#NUL#NUL#NUL#NUL#NUL#SOH  0.152#NULI#STX#NUL#NUL#NUL#NUL#NUL#NUL#NUL#SOH  0.152#NULI#STX#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL@#NUL{FF}#SOH  0.151#NULI#STX#NUL#NUL#NUL#NUL#NUL#NUL#NUL@#STX#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#SOH#NUL#NUL#EOT#NUL#NUL#NUL#NUL#NUL#SOH  0.152#NULI#STX#NUL#NUL#NUL#NUL#BS#NUL#STX#STX#NUL#BS0"#NUL#NUL!#NUL#NUL#DC1x#SOHÀX€#SOH#ENQ#SOH  0.154#NULI#STX#NUL#NUL#SOH  0.154#NULI#STX#NUL  0.153#NULI#STX#NUL#SOH  0.153#NULI#STX#NUL#NUL#NUL#SOH  0.150#NULI#STX#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#SOH  0.151#NULI#STX#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL  0.153#NULI#STX#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#FF#BS#NUL#NUL#NUL#NUL#NUL#NUL#NUL€@#NUL#NUL#NUL$B#BS!@#NUL#DLE#NUL@À#NUL#NUL#NUL#NUL#NUL#NUL#DLE38#DC1#NUL#ACK#NUL#NUL#NUL#NUL#NUL#STX#BS#SI#NULü#SOH  0.154#NULI#STX#NUL#NUL#NUL#NULà#NUL#STX #NUL{FF}#SOH  0.152#NULI#STX#NUL#NUL#NUL#NUL#NUL#SOH  0.152#NULI#STX#NUL#NUL#NUL#NUL@#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL  0.152#NULI#STX#NUL#NUL#NUL#NUL#DLE0#ENQ#NUL#CAN#BS)#STX#DLE#NUL#SOH€#EOT#ACK#NUL#NUL@à{FF}#NULÅ#NUL#NUL#NUL#DLE#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#NUL#SOH#CR#SOH#STX#DC41(#DC1{FF}#BS#BEL€#BS#SOH  0.153#NULI#STX#NUL#NUL#SOH  0.153#NULI#STX#NUL#NUL#NUL#SOH  0.153#NULE#STX#NUL#NUL#SOH  0.153#NULE#STX#NUL)";
    std::string result = removeNULSOH(input);

    std::istringstream iss(result);
    std::string line;
    while (std::getline(iss, line, ' ')) {
        try {
            double num = std::stod(line);
            std::cout << num << std::endl;
        } catch (const std::invalid_argument& e) {
            // Se a conversão para double falhar, continua para a próxima linha
            continue;
        }
    }

    return 0;
}

