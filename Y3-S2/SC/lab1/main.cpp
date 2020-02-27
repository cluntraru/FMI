#include <iostream>
#include <fstream>

std::ofstream fout("Test.out");

#include <cctype>

int toInt(char hex) {
    if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 10;
    }

    return hex - '0';
}

int main() {
    std::string ct = "3CC8";//5DD318D40EC809810EC05DC518C20FC80DD518DB148110C40EC017D411";
    for (int i = 0; i < 65536; ++i) { // Cipher key
        std::string ans = "";
        bool flag = true;
        for (int j = 0; j < ct.size(); j += 4) {
            int c1 = toInt(ct[j]) * 16 + toInt(ct[j + 1]);
            int c2 = toInt(ct[j + 2]) * 16 + toInt(ct[j + 3]);

            std::cout << c1 << ' ' << c2 << '\n';

            int cif1 = i & (((1 << 16) - 1) - (((1 << 8) - 1)));
            int cif2 = i & ((1 << 8) - 1);

            int dec1 = (c1^cif1);
            int dec2 = (c2^cif2);
//            std::cout << dec1 << ' ' << dec2 << '\n';
//            if ((dec1 == ' ' || isalpha(dec1)) && (dec2 == ' ' || isalpha(dec2))) {
                ans += (char) dec1;
                ans += " ";
                ans += (char) dec2;
                ans += " ";
 //           } else {
                //std::cout << dec1 << ' ';
 //               flag = false;
//            }
        }

        if (flag) {
            fout << ans << "\n";
        } 
    }

    return 0;
}
