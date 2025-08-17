#include "vector.hpp"

int main(void)
{
    Vector<int> v1{10}, v4{11};
    Vector<int> v2{v1}, v3{}, mv4 = std::move(v4), mv5{20};
    v3 = v2;
    mv5 = std::move(v2);
    std::cout << &mv5;

    int* ar = new int[10];
    for(int i{}; i < 10; i++)
        ar[i] = i * i;
    Vector<int> v6{ar, 10};

    int total = 25;
    // std::unique_ptr<int[]> arr {std::make_unique<int[]>(total)};
    // Vector<int> v7 {std::move(arr), total};

    Vector<int> v8 {25, 10};
    int* ptr = v8.get_data();
    int size = v8.get_size();
    for(int j{}; j < size; j++)
        std::cout << ptr[j] << ' ';

    std::cout << std::endl;

    for(int i{}; i < 10; i++)
        v8.push_back(i * i);

    v8.remove(v8.get_size() - 1);
    v8.emplace(10, 10000);

    int* ptr_out = v8.get_data();
    std::cout << v8.get_size() << std::endl;
    for(int i{}; i < v8.get_size(); i++)
        std::cout << ptr_out[i] << ' ';

    std::cout << std::endl;

    Vector<int> v9 (10, 1);
    v9.insert(4, 3, 10);
    std::cout << "vec v9: ";
    for(int i{}; i < v9.get_size(); i++)
        std::cout << v9.get_data()[i] << ' ';

    std::cout << std::endl << v9.get_size() << std::endl;
    v9[17] = 1000;
    try
    {
        total = v9[20];
    }
    catch(const char* err)
    {
        std::cerr << err;
    }
    std::cout << total << std::endl;
    std::cout << v9[16] << std::endl;

    for(int i{}; i < v9.get_size(); i++)
        std::cout << v9[i] << std::endl;

    Vector<int> v10{1, 2, 3, 4, 5, 32, 543, 564, 654, 12, 76};
    std::cout << "v10 size: " << v10.get_size() << " v10 capacity: " << v10.get_capacity() << std::endl;
    std::cout << "v10 elemets: ";
    for(int i{}; i < v10.get_size(); i++)
        std::cout << v10[i] << ' ';
    
    delete[] ar;
    return 0;
}
