//#include <iostream>
//#include <vector>
//#include <algorithm>

#include <bits/stdc++.h>

int main()
{
      std::vector<int> v = {1, 2, 3, 4, 5};

        std::shift_right(v.begin(), v.end(), 2);

          for (int x : v) {
                  std::cout << x << ',';
                    }
            std::cout << std::endl;
}
